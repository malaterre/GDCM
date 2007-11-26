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
#ifndef __gdcmImplicitDataElement_txx
#define __gdcmImplicitDataElement_txx

#include "gdcmSequenceOfItems.h"

#include "gdcmValueIO.h"
#include "gdcmSwapper.h"

namespace gdcm
{

//-----------------------------------------------------------------------------
template <typename TSwap>
std::istream &ImplicitDataElement::Read(std::istream &is)
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  // Read Tag
  if( !TagField.Read<TSwap>(is) )
    {
    if( !is.eof() ) // FIXME This should not be needed
      assert(0 && "Should not happen");
    return is;
    }

  //assert( TagField != Tag(0xfffe,0xe0dd) );
  // Read Value Length
  if( !ValueLengthField.Read<TSwap>(is) )
    {
    assert(0 && "Should not happen");
    return is;
    }
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
    //VRField = VR::SQ;
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
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  // THE WORST BUG EVER. From GE Workstation
  if( ValueLengthField == 13 )
    {
    // Historically gdcm did not enforce proper length
    // thus Theralys started writing illegal DICOM images:
    const Tag theralys1(0x0008,0x0070);
    const Tag theralys2(0x0008,0x0080);
    if( TagField != theralys1
     && TagField != theralys2 )
      {
      gdcmWarningMacro( "GE,13: Replacing VL=0x000d with VL=0x000a, for Tag="
        << TagField << " in order to read a buggy DICOM file." );
      ValueLengthField = 10;
      }
    }
#endif
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  if( ValueLengthField == 0x31f031c && TagField == Tag(0x031e,0x0324) )
    {
    // TestImages/elbow.pap
    gdcmWarningMacro( "Replacing a VL. To be able to read a supposively"
      "broken Payrus file." );
    ValueLengthField = 202; // 0xca
    }
#endif
  // We have the length we should be able to read the value
  ValueField->SetLength(ValueLengthField); // perform realloc
  if( !ValueIO<ImplicitDataElement,TSwap>::Read(is,*ValueField) )
    {
    throw Exception("Should not happen");
    return is;
    }

#ifndef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  assert( VRField == VR::INVALID );
#endif

  return is;
}

//-----------------------------------------------------------------------------
template <typename TSwap>
const std::ostream &ImplicitDataElement::Write(std::ostream &os) const
{
#ifndef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  assert( VRField == VR::INVALID );
#endif
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  // Write Tag
  if( !TagField.Write<TSwap>(os) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  // Write Value Length
  if( !ValueLengthField.Write<TSwap>(os) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  // Write Value
  if( ValueLengthField )
    {
    assert( ValueField );
    assert( TagField != Tag(0xfffe, 0xe00d)
         && TagField != Tag(0xfffe, 0xe0dd) );
    if( !ValueIO<ImplicitDataElement,TSwap>::Write(os,*ValueField) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    }
  return os;
}


} // end namespace gdcm


#endif // __gdcmImplicitDataElement_txx
