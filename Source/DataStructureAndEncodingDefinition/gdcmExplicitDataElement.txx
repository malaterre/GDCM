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
#ifndef __gdcmExplicitDataElement_txx
#define __gdcmExplicitDataElement_txx

#include "gdcmSequenceOfItems.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmVL.h"
#include "gdcmParseException.h"
#include "gdcmImplicitDataElement.h"

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
  //assert( TagField != Tag(0xfeff,0xdde0) );
  const Tag itemDelItem(0xfffe,0xe00d);
  if( TagField == itemDelItem )
    {
    if( !ValueLengthField.Read<TSwap>(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    if( ValueLengthField )
      {
      gdcmWarningMacro(
        "Item Delimitation Item has a length different from 0 and is: " << ValueLengthField );
      }
    // Set pointer to NULL to avoid user error
    ValueField = 0;
    return is;
    }

#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  if( TagField == Tag(0x00ff, 0x4aa5) )
    {
    //assert(0 && "Should not happen" );
    // gdcmDataExtra/gdcmBreakers/DigitexAlpha_no_7FE0.dcm
    throw Exception( "Unhandled" );
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
  catch( Exception &ex )
    {
    // gdcm-MR-PHILIPS-16-Multi-Seq.dcm
    // assert( TagField == Tag(0xfffe, 0xe000) );
    // -> For some reason VR is written as {44,0} well I guess this is a VR...
    // Technically there is a second bug, dcmtk assume other things when reading this tag, 
    // so I need to change this tag too, if I ever want dcmtk to read this file. oh well
    // 0019004_Baseline_IMG1.dcm
    // -> VR is garbage also...
    // assert( TagField == Tag(8348,0339) || TagField == Tag(b5e8,0338))
    //gdcmWarningMacro( "Assuming 16 bits VR for Tag=" <<
    //  TagField << " in order to read a buggy DICOM file." );
    //VRField = VR::INVALID;
    ParseException pe;
    pe.SetLastElement( *this );
    throw pe;
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
  //std::cerr << "exp cur tag=" << TagField << " VR=" << VRField << " VL=" << ValueLengthField << std::endl;
  // 
  // I don't like the following 3 lines, what if 0000,0000 was indeed -wrongly- sent, we should be able to continue
  // chances is that 99% of times there is now way we can reach here, so safely throw an exception
  if( TagField == Tag(0x0000,0x0000) && ValueLengthField == 0 && VRField == VR::INVALID )
    {
    ParseException pe;
    pe.SetLastElement( *this );
    throw pe;
    }

  if( ValueLengthField == 0 )
    {
    // Simple fast path
    ValueField = 0;
    return is;
    }

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
        ParseException pe;
        pe.SetLastElement(*this);
        throw pe;
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
#if defined(GDCM_SUPPORT_BROKEN_IMPLEMENTATION) && 0
  // PHILIPS_Intera-16-MONO2-Uncompress.dcm
  if( TagField == Tag(0x2001,0xe05f)
    || TagField == Tag(0x2001,0xe100)
    || TagField == Tag(0x2005,0xe080)
    || TagField == Tag(0x2005,0xe083)
    || TagField == Tag(0x2005,0xe084)
    || TagField == Tag(0x2005,0xe402)
    //TagField.IsPrivate() && VRField == VR::SQ
    //-> Does not work for 0029
    //we really need to read item marker
  )
    {
    gdcmWarningMacro( "ByteSwaping Private SQ: " << TagField );
    assert( VRField == VR::SQ );
    assert( TagField.IsPrivate() );
    try
      {
      if( !ValueIO<ExplicitDataElement,SwapperDoOp>::Read(is,*ValueField) )
        {
        assert(0 && "Should not happen");
        }
      Value* v = &*ValueField;
      SequenceOfItems *sq = dynamic_cast<SequenceOfItems*>(v);
      assert( sq );
      SequenceOfItems::Iterator it = sq->Begin();
      for( ; it != sq->End(); ++it)
        {
        Item &item = *it;
        DataSet &ds = item.GetNestedDataSet();
        ByteSwapFilter bsf(ds);
        bsf.ByteSwap();
        }
      }
    catch( std::exception &ex )
      {
      ValueLengthField = ValueField->GetLength();
      }
    return is;
    }
#endif

  bool failed;
  //assert( VRField != VR::UN );
  if( VRField & VR::VRASCII )
    {
    //assert( VRField.GetSize() == 1 );
    failed = !ValueIO<ExplicitDataElement,TSwap>::Read(is,*ValueField);
    }
  else
    {
    assert( VRField & VR::VRBINARY );
    unsigned int vrsize = VRField.GetSize();
    assert( vrsize == 1 || vrsize == 2 || vrsize == 4 || vrsize == 8 );
    switch(vrsize)
      {
    case 1:
      failed = !ValueIO<ExplicitDataElement,TSwap,uint8_t>::Read(is,*ValueField);
      break;
    case 2:
      failed = !ValueIO<ExplicitDataElement,TSwap,uint16_t>::Read(is,*ValueField);
      break;
    case 4:
      failed = !ValueIO<ExplicitDataElement,TSwap,uint32_t>::Read(is,*ValueField);
      break;
    case 8:
      failed = !ValueIO<ExplicitDataElement,TSwap,uint64_t>::Read(is,*ValueField);
      break;
    default:
      abort();
      }
    }
  if( failed )
    {
    if( TagField == Tag(0x7fe0,0x0010) )
      {
      // PMS-IncompletePixelData.dcm
      gdcmWarningMacro( "Incomplete Pixel Data found, use file at own risk" );
      is.clear();
      }
    else
      {
      // Might be the famous UN 16bits
      ParseException pe;
      pe.SetLastElement( *this );
      throw pe;
      }
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
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  if( VRField == VR::INVALID )
    {
    VR un = VR::UN;
    un.Write(os);
    Value* v = &*ValueField;
    if( dynamic_cast<const SequenceOfItems*>(v) )
      {
      VL vl = 0xFFFFFFFF;
      assert( vl.IsUndefined() );
      vl.Write<TSwap>(os);
      }
    else
      ValueLengthField.Write<TSwap>(os);
    }
  else
#endif
    {
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
    }
  if( ValueLengthField )
    {
#ifdef NDEBUG
    if( dynamic_cast<const ByteValue*>(&*ValueField) )
      {
      assert( ValueField->GetLength() == ValueLengthField );
      }
#endif
    // We have the length we should be able to write the value
    if( VRField == VR::UN && ValueLengthField.IsUndefined() )
      {
      //assert( dynamic_cast<const SequenceOfItems*>(ValueField) );
      ValueIO<ImplicitDataElement,TSwap>::Write(os,*ValueField);
      }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    else if( VRField == VR::INVALID && dynamic_cast<const SequenceOfItems*>(&*ValueField) )
      {
      // We have pretended so far that the Sequence was encoded as UN. Well the real
      // troubles is that we cannot store the length as explicit length, otherwise
      // we will loose the SQ, therefore change the length into undefined length
      // and add a seq del item:
      ValueIO<ImplicitDataElement,TSwap>::Write(os,*ValueField);
      // seq del item is not stored, write it !
      const Tag seqDelItem(0xfffe,0xe0dd);
      seqDelItem.Write<TSwap>(os);
      VL zero = 0;
      zero.Write<TSwap>(os);
      }
#endif
    else 
      {
      bool failed;
      if( VRField & VR::VRASCII || VRField == VR::INVALID )
        {
        failed = !ValueIO<ExplicitDataElement,TSwap>::Write(os,*ValueField);
        }
      else
        {
        assert( VRField & VR::VRBINARY );
        unsigned int vrsize = VRField.GetSize();
        assert( vrsize == 1 || vrsize == 2 || vrsize == 4 || vrsize == 8 );
        switch(vrsize)
          {
        case 1:
          failed = !ValueIO<ExplicitDataElement,TSwap,uint8_t >::Write(os,*ValueField);
          break;
        case 2:
          failed = !ValueIO<ExplicitDataElement,TSwap,uint16_t>::Write(os,*ValueField);
          break;
        case 4:
          failed = !ValueIO<ExplicitDataElement,TSwap,uint32_t>::Write(os,*ValueField);
          break;
        case 8:
          failed = !ValueIO<ExplicitDataElement,TSwap,uint64_t>::Write(os,*ValueField);
          break;
        default:
          abort();
          }
        }
      if( failed )
        {
        assert( 0 && "Should not happen" );
        }
      }
    }

  return os;
}



} // end namespace gdcm

#endif // __gdcmExplicitDataElement_txx
