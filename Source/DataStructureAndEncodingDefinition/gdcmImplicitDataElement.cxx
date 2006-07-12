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
#include "gdcmImplicitDataElement.h"
#include "gdcmValue.h"
#include "gdcmByteValue.h"
#include "gdcmSequenceOfItems.h"

namespace gdcm
{

ImplicitDataElement::~ImplicitDataElement()
{
}

//-----------------------------------------------------------------------------
IStream &ImplicitDataElement::Read(IStream &is)
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  // Read Tag
  if( !TagField.Read(is) )
    {
    //assert(0 && "Should not happen");
    return is;
    }
  // Read Value Length
  if( !ValueLengthField.Read(is) )
    {
    assert(0 && "Should not happen");
    return is;
    }
  if( ValueLengthField.IsUndefined() )
    {
    //assert( de.GetVR() == VR::SQ );
    // FIXME what if I am reading the pixel data...
    assert( TagField != Tag(0x7fe0,0x0010) );
    ValueField = new SequenceOfItems(TS::Implicit);
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
      gdcm::Tag item;
      item.Read(is);
      // Maybe this code can later be rewritten as I believe that seek back
      // is very slow...
      is.Seekg(-4, std::ios::cur );
      if( item == itemStart )
        {
        assert( TagField != Tag(0x7fe0,0x0010) );
        ValueField = new SequenceOfItems(TS::Implicit);
        }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
      else if ( item == itemPMSStart )
        {
        gdcmWarningMacro( "Illegal: Explicit SQ found in a file with TransferSyntax=Implicit"
          " for tag: " << TagField );
        ValueField = new SequenceOfItems(TS::Explicit);
        SwapCode oldsw = is.GetSwapCode();
        assert( oldsw == SwapCode::LittleEndian );
        is.SetSwapCode( SwapCode::BigEndian );
        ValueField->SetLength(ValueLengthField); // perform realloc
        if( !ValueField->Read(is) )
          {
          assert(0 && "Should not happen");
          }
        is.SetSwapCode( oldsw );
        return is;
        }
      else if ( item == itemPMSStart2 )
        {
        gdcmWarningMacro( "Illegal: SQ start with " << itemPMSStart2 << " instead of "
          << itemStart << " for tag: " << TagField );
        ValueField = new SequenceOfItems(TS::Implicit);
        ValueField->SetLength(ValueLengthField); // perform realloc
        if( !ValueField->Read(is) )
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
      gdcmWarningMacro( "GE,13: Replacing VL=0x000d with VL=0x000a, for Tag=" <<
        TagField << " in order to read a buggy DICOM file." );
      ValueLengthField = 10;
      }
    }
#endif
  // We have the length we should be able to read the value
  ValueField->SetLength(ValueLengthField); // perform realloc
  if( !ValueField->Read(is) )
    {
    assert(0 && "Should not happen");
    return is;
    }

  return is;
}

//-----------------------------------------------------------------------------
const OStream &ImplicitDataElement::Write(OStream &os) const
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  // Write Tag
  if( !TagField.Write(os) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  // Write Value Length
  if( !ValueLengthField.Write(os) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  if( !ValueField->Write(os) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  return os;
}

} // end namespace gdcm
