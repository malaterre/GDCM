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

#include "gdcmSequenceOfItems.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmVL.h"

#include "gdcmValueIO.h"
#include "gdcmSwapper.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
template <typename TSwap>
std::istream &ExplicitDataElement::Read(std::istream &is)
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
  assert( TagField != Tag(0xfffe,0xe0dd) );
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
    //  is.read(&c, 1);
    //  std::cerr << "Debug: " << c << std::endl;
    }
#endif
  // Read VR
  try
    {
    if( !VRField.Read(is) )
      {
      assert(0 && "Should not happen" );
      return is;
      }
    }
  catch( std::exception &ex )
    {
    // gdcm-MR-PHILIPS-16-Multi-Seq.dcm
    // assert( TagField == Tag(0xfffe, 0xe000) );
    // -> For some reason VR is written as {44,0} well I guess this is a VR...
    // 0019004_Baseline_IMG1.dcm
    // -> VR is garbage also...
    // assert( TagField == Tag(8348,0339) || TagField == Tag(b5e8,0338))
    gdcmWarningMacro( "Assuming 16 bits VR for Tag=" <<
      TagField << " in order to read a buggy DICOM file." );
    VRField = VR::INVALID;
    }
  // Read Value Length
  if( VR::GetLength(VRField) == 4 )
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
    if( !ValueLengthField.template Read16<TSwap>(is) )
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

  //std::cerr << "exp cur tag=" << TagField <<  " VL=" << ValueLengthField << std::endl;
  // Read the Value
  //assert( ValueField == 0 );
  if( VRField == VR::SQ )
    {
    // Check wether or not this is an undefined length sequence
    assert( TagField != Tag(0x7fe0,0x0010) );
    ValueField = new SequenceOfItems;
    }
  else if( ValueLengthField.IsUndefined() )
    {
    if( VRField == VR::UN )
      {
      // Support cp246 conforming file:
      // Enhanced_MR_Image_Storage_PixelSpacingNotIn_0028_0030.dcm (illegal)
      // vs
      // undefined_length_un_vr.dcm
      assert( TagField != Tag(0x7fe0,0x0010) );
      ValueField = new SequenceOfItems;
      ValueField->SetLength(ValueLengthField); // perform realloc
      try
        {
        if( !ValueIO<ImplicitDataElement,TSwap>::Read(is,*ValueField) )
          {
          abort();
          }
        }
      catch( std::exception &ex)
        {
        // Must be one of those non-cp246 file...
        // but for some reason seekg back to previous offset + Read
        // as Explicit does not work...
        throw Exception( "CP 246" );
        }
      return is;
      }
    else
      {
      // Ok this is Pixel Data fragmented...
      assert( TagField == Tag(0x7fe0,0x0010) );
      assert( VRField & VR::OB_OW );
      ValueField = new SequenceOfFragments;
      }
    }
  else
    {
    //assert( TagField != Tag(0x7fe0,0x0010) );
    ValueField = new ByteValue;
    }
  // We have the length we should be able to read the value
  ValueField->SetLength(ValueLengthField); // perform realloc
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  if( TagField == Tag(0x2001,0xe05f)
    || TagField == Tag(0x2001,0xe100)
    || TagField == Tag(0x2005,0xe080)
    || TagField == Tag(0x2005,0xe083)
    || TagField == Tag(0x2005,0xe084)
    //TagField.IsPrivate() && VRField == VR::SQ
    //-> Does not work for 0029
    //we really need to read item marker
  )
    {
    gdcmWarningMacro( "ByteSwaping Private SQ: " << TagField );
    assert( VRField == VR::SQ );
    try
      {
      if( !ValueIO<ExplicitDataElement,SwapperDoOp>::Read(is,*ValueField) )
        {
        assert(0 && "Should not happen");
        }
      }
    catch( std::exception &ex )
      {
      ValueLengthField = ValueField->GetLength();
      }
    return is;
    }
#endif
  //if( !ValueField->Read<TSwap>(is) )
  if( !ValueIO<ExplicitDataElement,TSwap>::Read(is,*ValueField) )
    {
    assert(0 && "Should not happen");
    return is;
    }

  return is;
}

//-----------------------------------------------------------------------------
template <typename TSwap>
const std::ostream &ExplicitDataElement::Write(std::ostream &os) const
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
    if( !ValueLengthField.template Write16<TSwap>(os) )
      {
      assert( 0 && "Should not happen" );
      return os;
      }
    }
  // We have the length we should be able to write the value
  if( VRField == VR::UN && ValueLengthField.IsUndefined() )
    {
    ValueIO<ImplicitDataElement,TSwap>::Write(os,*ValueField);
    }
  else if( !ValueIO<ExplicitDataElement,TSwap>::Write(os,*ValueField) )
    {
    assert( 0 && "Should not happen" );
    return os;
    }

  return os;
}



} // end namespace gdcm

#endif // __gdcmExplicitDataElement_txx
