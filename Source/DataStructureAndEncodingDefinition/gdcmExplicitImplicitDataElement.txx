/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmExplicitImplicitDataElement_txx
#define __gdcmExplicitImplicitDataElement_txx

#include "gdcmSequenceOfItems.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmVL.h"

#include "gdcmValueIO.h"
#include "gdcmSwapper.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
// Depending whether the tag is private or not we switch to implicit or explicit
// A lot of bug support were removed, we only keep the handling of philips bugs:
// Byte Swap inversion, Fake SQ ...
// Note: When reading implicit we are marking SQ with a VR of SQ, when rewritting element
// this is nicer
template <typename TSwap>
std::istream &ExplicitImplicitDataElement::Read(std::istream &is)
{
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
  if( !TagField.IsPrivate() )
    {
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
      // Technically there is a second bug, dcmtk assume other things when reading this tag, 
      // so I need to change this tag too, if I ever want dcmtk to read this file. oh well
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
      }

  if( ValueLengthField == 0 )
    {
    // Simple fast path
    ValueField = 0;
    return is;
    }

    //std::cerr << "exp cur tag=" << TagField << " VR=" << VRField << " VL=" << ValueLengthField << std::endl;
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
          //if( !ValueIO<ExplicitDataElement,TSwap>::Read(is,*ValueField) ) // non cp246
          if( !ValueIO<ImplicitDataElement,TSwap>::Read(is,*ValueField) ) // cp246 compliant
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
      // Might be the famous UN 16bits
      throw Exception( "Should not happen" );
      return is;
      }

    }
  else
    {
    // First thing, clears the VR:
    VRField = VR::INVALID;
    //VRField = VR::UN; // TODO FIXME
    bool issequence = false;
    //assert( TagField != Tag(0xfffe,0xe0dd) );
    // Read Value Length
    if( !ValueLengthField.Read<TSwap>(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    assert( ValueLengthField < 65535 );
    //std::cerr << "imp cur tag=" << TagField <<  " VL=" << ValueLengthField << std::endl;
    if( ValueLengthField == 0 )
      {
      // Simple fast path
      ValueField = 0;
      return is;
      }
    else if( ValueLengthField.IsUndefined() )
      {
      //assert( de.GetVR() == VR::SQ );
      // FIXME what if I am reading the pixel data...
      assert( TagField != Tag(0x7fe0,0x0010) );
      ValueField = new SequenceOfItems;
      issequence = true;
      }
    else
      {
      if( ValueLengthField < 8 )
        {
        ValueField = new ByteValue;
        }
      else
        {
        // In the following we read 4 more bytes in the Value field
        // to find out if this is a SQ or not
        // there is still work to do to handle the PMS featured SQ
        // where item Start is in fact 0xfeff, 0x00e0 ... sigh
        const Tag itemStart(0xfffe, 0xe000);
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
        const Tag itemPMSStart(0xfeff, 0x00e0);
        const Tag itemPMSStart2(0x3f3f, 0x3f00);
#endif
        Tag item;
        // TODO FIXME
        // This is pretty dumb to actually read to later on seekg back, why not `peek` directly ?
        item.Read<TSwap>(is);
        // Maybe this code can later be rewritten as I believe that seek back
        // is very slow...
        is.seekg(-4, std::ios::cur );
        if( item == itemStart )
          {
          assert( TagField != Tag(0x7fe0,0x0010) );
          ValueField = new SequenceOfItems;
          issequence = true;
          }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
        else if ( item == itemPMSStart )
          {
          // MR_Philips_Intera_No_PrivateSequenceImplicitVR.dcm
          gdcmWarningMacro( "Illegal: Explicit SQ found in a file with "
            "TransferSyntax=Implicit for tag: " << TagField );
          // TODO: We READ Explicit ok...but we store Implicit !
          // Indeed when copying the VR will be saved... pretty cool eh ?
          ValueField = new SequenceOfItems;
          issequence = true;
          ValueField->SetLength(ValueLengthField); // perform realloc
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
        else if ( item == itemPMSStart2 )
          {
          gdcmWarningMacro( "Illegal: SQ start with " << itemPMSStart2
            << " instead of " << itemStart << " for tag: " << TagField );
          ValueField = new SequenceOfItems;
          issequence = true;
          ValueField->SetLength(ValueLengthField); // perform realloc
          if( !ValueIO<ImplicitDataElement,TSwap>::Read(is,*ValueField) )
            {
            assert(0 && "Should not happen");
            }
          return is;
          }
#endif
        else
          {
          ValueField = new ByteValue;
          }
        }
      }
    // We have the length we should be able to read the value
    ValueField->SetLength(ValueLengthField); // perform realloc
    if( !ValueIO<ImplicitDataElement,TSwap>::Read(is,*ValueField) )
      {
      throw Exception("Should not happen");
      return is;
      }

    }

  return is;
}


} // end namespace gdcm

#endif // __gdcmExplicitImplicitDataElement_txx
