/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmExplicitDataElement_txx
#define __gdcmExplicitDataElement_txx

#include "gdcmExplicitDataElement.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmVL.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
template <typename TSwap>
IStream &ExplicitDataElement::Read(IStream &is)
{
  // See PS 3.5, Data Element Structure With Explicit VR
  // Read Tag
  if( !TagField.Read<TSwap>(is) )
    {
    if( !is.eof() ) // FIXME This should not be needed
      {
      assert(0 && "Should not happen" );
      }
    return is;
    }
  std::cerr << "cur tag=" << TagField << std::endl;
  const Tag itemDelItem(0xfffe,0xe00d);
  if( TagField == itemDelItem )
    {
    if( !ValueLengthField.Read<TSwap>(is) )
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
  if( VRField & VR::VL32 )
    {
    if( !ValueLengthField.Read<TSwap>(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    }
  else
    {
    // 16bits only
    if( !ValueLengthField.Read16<TSwap>(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    // HACK for SIEMENS Leonardo
    if( ValueLengthField == 0x0006
     && VRField == VR::UL
     && TagField.GetGroup() == 0x0009 )
      {
      gdcmWarningMacro( "Replacing VL=0x0006 with VL=0x0004, for Tag=" <<
        TagField << " in order to read a buggy DICOM file." );
      ValueLengthField = 0x0004;
      }
#endif
    }
  // Read the Value
  //assert( ValueField == 0 );
  //if ( TagField == Tag(0x0008,0x1120) )
  //{
  //        assert( VRField == VR::SQ );
  //}
  if( VRField == VR::SQ )
    {
    // Check wether or not this is an undefined length sequence
    assert( TagField != Tag(0x7fe0,0x0010) );
    ValueField = new SequenceOfItems<ExplicitDataElement>;
    }
  else if( ValueLengthField.IsUndefined() )
    {
    // Ok this is Pixel Data fragmented...
    if( VRField != VR::UN )
      {
      assert( TagField == Tag(0x7fe0,0x0010) );
      assert( VRField & VR::OB_OW );
      }
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
    //SwapCode oldsw = is.GetSwapCode();
    //assert( oldsw == SwapCode::LittleEndian );
    //is.SetSwapCode( SwapCode::BigEndian );
    if( !ValueField->Read<TSwap>(is) )
      {
      assert(0 && "Should not happen");
      }
    //is.SetSwapCode( oldsw );
    return is;
    }
  else if( TagField == Tag(0x2001, 0xe100) )
    {
    assert( VRField == VR::SQ );
    //SwapCode oldsw = is.GetSwapCode();
    //assert( oldsw == SwapCode::LittleEndian );
    //is.SetSwapCode( SwapCode::BigEndian );
    if( !ValueField->Read<TSwap>(is) )
      {
      assert(0 && "Should not happen");
      }
    //is.SetSwapCode( oldsw );
    return is;
    }
#endif
  if( !ValueField->Read<TSwap>(is) )
    {
    assert(0 && "Should not happen");
    return is;
    }

  return is;
}

//-----------------------------------------------------------------------------
template <typename TSwap>
const OStream &ExplicitDataElement::Write(OStream &os) const
{
  if( !TagField.Write<TSwap>(os) )
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
      zero.Write<TSwap>(os);
      return os;
      }
#endif
    // else
    assert( ValueLengthField == 0 );
    if( !ValueLengthField.Write<TSwap>(os) )
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
  if( VRField & VR::VL32 )
    {
    if( !ValueLengthField.Write<TSwap>(os) )
      {
      assert( 0 && "Should not happen" );
      return os;
      }
    }
  else
    {
    // 16bits only
    if( !ValueLengthField.Write16<TSwap>(os) )
      {
      assert( 0 && "Should not happen" );
      return os;
      }
    }
  // We have the length we should be able to write the value
  if( ! ValueField->Write<TSwap>(os) )
    {
    assert( 0 && "Should not happen" );
    return os;
    }

  return os;
}



} // end namespace gdcm

#endif // __gdcmExplicitDataElement_txx
