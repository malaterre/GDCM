/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmExplicitDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmSequenceOfFragments.h"

namespace gdcm
{

ExplicitDataElement::~ExplicitDataElement()
{
}

//-----------------------------------------------------------------------------
IStream &ExplicitDataElement::Read(IStream &is)
{
  // See PS 3.5, Date Element Structure With Explicit VR
  // Read Tag
  if( !TagField.Read(is) )
    {
    if( !is.Eof() ) // FIXME This should not be needed
      {
      assert(0 && "Should not happen" );
      }
    return is;
    }
  const Tag itemDelItem(0xfffe,0xe00d);
  if( TagField == itemDelItem )
    {
    if( !ValueLengthField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    if( ValueLengthField != 0 )
      {
      gdcmDebugMacro(
        "Item Delimitation Item has a length different from 0" );
      }
    // Set pointer to NULL to avoid user error
    ValueField = 0;
    return is;
    }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  if( TagField == Tag(0x00ff, 0x4aa5) )
    {
    assert(0 && "Should not happen" );
    //  char c;
    //  is.Read(&c, 1);
    //  std::cerr << "Debug: " << c << std::endl;
    }
#endif
  // Read VR
  if( !VRField.Read(is) )
    {
    assert(0 && "Should not happen" );
    return is;
    }
  // Read Value Length
  if( VRField & (VR::OB | VR::OW | VR::OF | VR::SQ | VR::UN ) )
    {
    if( !ValueLengthField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    }
  else
    {
    // FIXME: Poorly written:
    uint16_t vl16;
    is.Read(vl16);
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    // HACK for SIEMENS Leonardo
    if( vl16 == 0x0006
     && VRField == VR::UL
     && TagField.GetGroup() == 0x0009 )
      {
      gdcmWarningMacro( "Replacing VL=0x0006 with VL=0x0004, for Tag=" <<
        TagField << " in order to read a buggy DICOM file." );
      vl16 = 0x0004;
      }
#endif
    ValueLengthField = vl16;
    }
  // Read the Value
  //assert( ValueField == 0 );
  if( VRField == VR::SQ )
    {
    // Check wether or not this is an undefined length sequence
    assert( TagField != Tag(0x7fe0,0x0010) );
    ValueField = new SequenceOfItems(TS::Explicit);
    }
  else if( ValueLengthField.IsUndefined() )
    {
    // Ok this is Pixel Data fragmented...
    assert( TagField == Tag(0x7fe0,0x0010) );
    assert( VRField == VR::OB
         || VRField == VR::OW );
    ValueField = new SequenceOfFragments;
    }
  else
    {
    //assert( TagField != Tag(0x7fe0,0x0010) );
    ValueField = new ByteValue;
    }
  // We have the length we should be able to read the value
  ValueField->SetLength(ValueLengthField); // perform realloc
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  if( TagField == Tag(0x2001, 0xe05f) )
    {
    assert( VRField == VR::SQ );
    SwapCode oldsw = is.GetSwapCode();
    assert( oldsw == SwapCode::LittleEndian );
    is.SetSwapCode( SwapCode::BigEndian );
    if( !ValueField->Read(is) )
      {
      assert(0 && "Should not happen");
      }
    is.SetSwapCode( oldsw );
    return is;
    }
  else if( TagField == Tag(0x2001, 0xe100) )
    {
    assert( VRField == VR::SQ );
    SwapCode oldsw = is.GetSwapCode();
    assert( oldsw == SwapCode::LittleEndian );
    is.SetSwapCode( SwapCode::BigEndian );
    if( !ValueField->Read(is) )
      {
      assert(0 && "Should not happen");
      }
    is.SetSwapCode( oldsw );
    return is;
    }
#endif
  if( !ValueField->Read(is) )
    {
    assert(0 && "Should not happen");
    return is;
    }

  return is;
}

//-----------------------------------------------------------------------------
const OStream &ExplicitDataElement::Write(OStream &os) const
{
  if( !TagField.Write(os) )
    {
    assert( 0 && "Should not happen" );
    return os;
    }
  assert( TagField != Tag(0xfffe,0xe0dd) );
  const Tag itemDelItem(0xfffe,0xe00d);
  if( TagField == itemDelItem )
    {
    assert( ValueField == 0 );
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    if( ValueLengthField != 0 )
      {
      gdcmWarningMacro(
        "Item Delimitation Item had a length different from 0." );
      VL zero = 0;
      zero.Write(os);
      return os;
      }
#endif
    // else
    assert( ValueLengthField == 0 );
    if( !ValueLengthField.Write(os) )
      {
      assert( 0 && "Should not happen" );
      return os;
      }
    return os;
    }
  if( !VRField.Write(os) )
    {
    assert( 0 && "Should not happen" );
    return os;
    }
  if( VRField == VR::OB
   || VRField == VR::OW
   || VRField == VR::OF
   || VRField == VR::SQ
   || VRField == VR::UN )
    {
    if( !ValueLengthField.Write(os) )
      {
      assert( 0 && "Should not happen" );
      return os;
      }
    }
  else
    {
    // 16bits only
    uint16_t vl16;
    // MR-SIEMENS-DICOM-WithOverlays-extracted-overlays.dcm
    assert( ValueLengthField <= 0xffff ); // FIXME
    vl16 = ValueLengthField;
    assert( !(vl16 % 2) );
    os.Write(vl16);
    }
  // We have the length we should be able to write the value
  if( !ValueField->Write(os) )
    {
    assert( 0 && "Should not happen" );
    return os;
    }

  return os;
}

} // end namespace gdcm
