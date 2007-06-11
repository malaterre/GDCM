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
#ifndef __gdcmIOSerialize_txx
#define __gdcmIOSerialize_txx

#include "gdcmIOSerialize.h"

#include "gdcmTag.h"
#include "gdcmVL.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmDataSet.h"
#include "gdcmByteValue.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmSequenceOfFragments.h"


namespace gdcm
{

//-----------------------------------------------------------------------------
  template <typename TSwap>
  IStream &IOSerialize<TSwap>::Read(IStream &is,Tag &t)
    {
    is.read(t.ElementTag.bytes, 4);
    TSwap::SwapArray(t.ElementTag.tags, 2);
    return is;
    }

  template <typename TSwap>
  const OStream &IOSerialize<TSwap>::Write(OStream &os,const Tag &t)
    {
    uint16_t copy[2];
    copy[0]= t.ElementTag.tags[0];
    copy[1]= t.ElementTag.tags[1];
    TSwap::SwapArray(copy, 2);
    return os.write((char*)(&copy), 4);
    }

  template <typename TSwap>
  IStream &IOSerialize<TSwap>::Read(IStream &is,VL & vl)
    {
    is.read((char*)(&vl.ValueLength), sizeof(uint32_t));
    TSwap::SwapArray(&vl.ValueLength,1);
    return is;
    }

  template <typename TSwap>
  IStream &IOSerialize<TSwap>::Read16(IStream &is,VL & vl)
    {
    uint16_t copy;
    is.read((char*)(&copy), sizeof(uint16_t));
    TSwap::SwapArray(&copy,1);
    vl.ValueLength = copy;
    assert( vl.ValueLength <= 0xffff );
    return is;
    }

  template <typename TSwap>
  const OStream &IOSerialize<TSwap>::Write(OStream &os, VL const &vl)
    {
    uint32_t copy = vl.ValueLength;
#ifndef GDCM_WRITE_ODD_LENGTH
    if( vl.IsOdd() )
      {
      ++copy;
      }
#endif
    TSwap::SwapArray(&copy,1);
    return os.write((char*)(&copy), sizeof(uint32_t));
    }

  template <typename TSwap>
  const OStream &IOSerialize<TSwap>::Write16(OStream &os, VL const &vl)
    {
    assert( vl.ValueLength <= 0xffff );
    uint16_t copy = vl.ValueLength;
#ifndef GDCM_WRITE_ODD_LENGTH
    if( vl.IsOdd() )
      {
      ++copy;
      }
#endif
    TSwap::SwapArray(&copy,1);
    return os.write((char*)(&copy), sizeof(uint16_t));
    }



//-----------------------------------------------------------------------------
template <typename TSwap>
IStream &IOSerialize<TSwap>::Read(IStream &is,ExplicitDataElement &xde)
{
  // See PS 3.5, Data Element Structure With Explicit VR
  // Read Tag
  if( !Read(is,xde.TagField) )
    {
    if( !is.eof() ) // FIXME This should not be needed
      {
      assert(0 && "Should not happen" );
      }
    return is;
    }
  //std::cerr << "cur tag=" << xde.TagField << std::endl;
  const Tag itemDelItem(0xfffe,0xe00d);
  if( xde.TagField == itemDelItem )
    {
    if( !Read(is,xde.ValueLengthField) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    if( xde.ValueLengthField != 0 )
      {
      gdcmDebugMacro(
        "Item Delimitation Item has a length different from 0" );
      }
    // Set pointer to NULL to avoid user error
    xde.ValueField = 0;
    return is;
    }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  if( xde.TagField == Tag(0x00ff, 0x4aa5) )
    {
    assert(0 && "Should not happen" );
    //  char c;
    //  is.Read(&c, 1);
    //  std::cerr << "Debug: " << c << std::endl;
    }
#endif
  // Read VR
  if( !xde.VRField.Read(is) )
    {
    assert(0 && "Should not happen" );
    return is;
    }
  // Read Value Length
  if( xde.VRField & (VR::OB | VR::OW | VR::OF | VR::SQ | VR::UN ) )
    {
    if( !Read(is,xde.ValueLengthField) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    }
  else
    {
    // 16bits only
    if( !Read16(is,xde.ValueLengthField) )
      {
      assert(0 && "Should not happen");
      return is;
      }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    // HACK for SIEMENS Leonardo
    if( xde.ValueLengthField == 0x0006
     && xde.VRField == VR::UL
     && xde.TagField.GetGroup() == 0x0009 )
      {
      gdcmWarningMacro( "Replacing VL=0x0006 with VL=0x0004, for Tag=" <<
        xde.TagField << " in order to read a buggy DICOM file." );
      xde.ValueLengthField = 0x0004;
      }
#endif
    }
  // Read the Value
  //assert( ValueField == 0 );
  //if ( TagField == Tag(0x0008,0x1120) )
  //{
  //        assert( VRField == VR::SQ );
  //}
  if( xde.VRField == VR::SQ )
    {
    // Check wether or not this is an undefined length sequence
    assert( xde.TagField != Tag(0x7fe0,0x0010) );
    xde.ValueField = new SequenceOfItems;
    }
  else if( xde.ValueLengthField.IsUndefined() )
    {
    // Ok this is Pixel Data fragmented...
    if( xde.VRField != VR::UN )
      {
      assert( xde.TagField == Tag(0x7fe0,0x0010) );
      assert( xde.VRField == VR::OB
           || xde.VRField == VR::OW );
      }
    xde.ValueField = new SequenceOfFragments;
    }
  else
    {
    //assert( TagField != Tag(0x7fe0,0x0010) );
    xde.ValueField = new ByteValue;
    }
  // We have the length we should be able to read the value
  xde.ValueField->SetLength(xde.ValueLengthField); // perform realloc
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  if( xde.TagField == Tag(0x2001, 0xe05f) )
    {
    assert( xde.VRField == VR::SQ );
    //SwapCode oldsw = is.GetSwapCode();
    //assert( oldsw == SwapCode::LittleEndian );
    //is.SetSwapCode( SwapCode::BigEndian );
    if( !Read(is,*(xde.ValueField)) )
      {
      assert(0 && "Should not happen");
      }
    //is.SetSwapCode( oldsw );
    return is;
    }
  else if( xde.TagField == Tag(0x2001, 0xe100) )
    {
    assert( xde.VRField == VR::SQ );
    //SwapCode oldsw = is.GetSwapCode();
    //assert( oldsw == SwapCode::LittleEndian );
    //is.SetSwapCode( SwapCode::BigEndian );
    if( !Read(is,*(xde.ValueField)) )
      {
      assert(0 && "Should not happen");
      }
    //is.SetSwapCode( oldsw );
    return is;
    }
#endif
  if( !Read(is,*(xde.ValueField)) )
    {
    assert(0 && "Should not happen");
    return is;
    }

  return is;
}

//-----------------------------------------------------------------------------
template <typename TSwap>
const OStream &IOSerialize<TSwap>::Write(OStream &os, ExplicitDataElement const & xde)
{
  if( !Write(os,xde.TagField) )
    {
    assert( 0 && "Should not happen" );
    return os;
    }
  assert( xde.TagField != Tag(0xfffe,0xe0dd) );
  const Tag itemDelItem(0xfffe,0xe00d);
  if( xde.TagField == itemDelItem )
    {
    assert( xde.ValueField == 0 );
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    if( xde.ValueLengthField != 0 )
      {
      gdcmWarningMacro(
        "Item Delimitation Item had a length different from 0." );
      VL zero = 0;
      Write(os,zero);
      return os;
      }
#endif
    // else
    assert( xde.ValueLengthField == 0 );
    if( !Write(os,xde.ValueLengthField) )
      {
      assert( 0 && "Should not happen" );
      return os;
      }
    return os;
    }
  if( !xde.VRField.Write(os) )
    {
    assert( 0 && "Should not happen" );
    return os;
    }
  if( xde.VRField & ( VR::OB | VR::OW | VR::OF | VR::SQ | VR::UN | VR::UT ) )
    {
    if( !Write(os,xde.ValueLengthField) )
      {
      assert( 0 && "Should not happen" );
      return os;
      }
    }
  else
    {
    // 16bits only
    if( !Write16(os,xde.ValueLengthField) )
      {
      assert( 0 && "Should not happen" );
      return os;
      }
    }
  // We have the length we should be able to write the value
  if( ! IOSerialize<TSwap>::Write(os,*(xde.ValueField)) )
    {
    assert( 0 && "Should not happen" );
    return os;
    }

  return os;
}
  template <typename TSwap>
  IStream &IOSerialize<TSwap>::Read(IStream &is,Value &v) {
    if( ByteValue *bv = dynamic_cast<ByteValue*>(&v) )
    {
	    Read(is,*bv);
    }
    else if( SequenceOfItems *si = dynamic_cast<SequenceOfItems*>(&v) )
    {
	    Read(is,*si);
    }
    else if( SequenceOfFragments *sf = dynamic_cast<SequenceOfFragments*>(&v) )
    {
	    Read(is,*sf);
    }
    else
    {
	    assert( 0 && "error" );
    }
    return is;
  }
  template <typename TSwap>
  const OStream &IOSerialize<TSwap>::Write(OStream &os,const Value &v) {
    if( const ByteValue *bv = dynamic_cast<const ByteValue*>(&v) )
    {
	    Write(os,*bv);
    }
    else if( const SequenceOfItems *si = dynamic_cast<const SequenceOfItems*>(&v) )
    {
	    Write(os,*si);
    }
    else if( const SequenceOfFragments *sf = dynamic_cast<const SequenceOfFragments*>(&v) )
    {
	    Write(os,*sf);
    }
    else
    {
	    assert( 0 && "error" );
    }
    return os;
  }
  
  template <typename TSwap>
  IStream &IOSerialize<TSwap>::Read(IStream &is,ByteValue &bv) {
    // If Length is odd we have detected that in SetLength
    // and calling std::vector::resize make sure to allocate *AND* 
    // initialize values to 0 so we are sure to have a \0 at the end
    // even in this case
    return is.read(&bv.Internal[0], bv.Length);
    }

  template <typename TSwap>
  OStream const &IOSerialize<TSwap>::Write(OStream &os,ByteValue const &bv) {
#ifdef GDCM_WRITE_ODD_LENGTH
    return os.write(&bv.Internal[0], bv.Length);
#else
    assert( !(bv.Internal.size() % 2) );
    return os.write(&bv.Internal[0], bv.Internal.size());
#endif
    }

  template <typename TSwap>
  IStream &IOSerialize<TSwap>::Read(IStream &is,BasicOffsetTable &bot) {
    // Superclass 
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !Read(is,bot.TagField) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    assert( bot.TagField == itemStart );
    if( !Read(is,bot.ValueLengthField) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    // Self
    bot.Offsets = new ByteValue;
    bot.Offsets->SetLength(bot.ValueLengthField);
    if( !Read(is,*(bot.Offsets)) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    return is;
    }

  template <typename TSwap>
  OStream &IOSerialize<TSwap>::Write(OStream &os,BasicOffsetTable const &bot) {
    // Superclass 
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !Write(os,bot.TagField) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    assert( bot.TagField == itemStart );
    if( !Write(os,bot.ValueLengthField) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    // Self
    if( !Write(os, *(bot.Offsets)) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    return os;
    }

template <typename TSwap>
  IStream &IOSerialize<TSwap>::Read(IStream &is,Fragment &frag)
    {
    // Superclass
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !Read(is,frag.TagField) )
      {
      assert(0 && "Should not happen");
      return is;
      }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    if( frag.TagField != itemStart && frag.TagField != seqDelItem )
      {
      // gdcm-JPEG-LossLess3a.dcm
      std::streampos pos = is.tellg();
      is.seekg( 0, std::ios::end );
      std::streampos end = is.tellg();
      assert( (long)(end-pos) == 4 );
      gdcmWarningMacro( "Broken file: " << (long)(end-pos)
        << " bytes were skipped at the end of file. Use at own risk." );
      // Pretend to end properly...
      frag.TagField = Tag(0xfffe,0xe0dd);
      frag.ValueLengthField = 0;
      // Make sure to clear the FragmentValue
      frag.FragmentValue = new ByteValue;
      frag.FragmentValue->SetLength( frag.ValueLengthField );
      return is;
      }
#endif
    if( !Read(is,frag.ValueLengthField) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    // Self
    ByteValue *bv = new ByteValue;
    bv->SetLength(frag.ValueLengthField);
    if( !Read(is,*bv) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    frag.FragmentValue = bv;
    return is;
    }


  template <typename TSwap>
  OStream &IOSerialize<TSwap>::Write(OStream &os, Fragment const &frag)
  {
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !Write(os,frag.TagField) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    assert( frag.TagField == itemStart
         || frag.TagField == seqDelItem );
    if( !Write(os,frag.ValueLengthField) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    // Self
    if( !Write(os,*(frag.FragmentValue)) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    return os;
    }

 
template <typename TSwap>
IStream& IOSerialize<TSwap>::Read(IStream &is, SequenceOfFragments &sf)
{
  assert( sf.SequenceLengthField.IsUndefined() );
  //if( SequenceLengthField.IsUndefined() )
    {
    const Tag seqDelItem(0xfffe,0xe0dd);
    // First item is the basic offset table:
    Read(is,sf.Table);
    gdcmDebugMacro( "Table: " << sf.Table );
    // not used for now...
    Fragment frag;
    while( Read(is,frag) && frag.GetTag() != seqDelItem );
      {
      gdcmDebugMacro( "Frag: " << frag );
      sf.Fragments.push_back( frag );
      }
    assert( frag.GetTag() == seqDelItem && frag.GetVL() == 0 );
    }
  //else
  //  {
  //  abort();
  //  }
  return is;
}

template <typename TSwap>
OStream const &IOSerialize<TSwap>::Write(OStream &os, SequenceOfFragments const &sf)
{
  if( !Write(os,sf.Table) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  SequenceOfFragments::FragmentVector::const_iterator it = sf.Fragments.begin();
  for(;it != sf.Fragments.end(); ++it)
    {
    Write(os,*it);
    }
  return os;
}

template <typename TSwap>
IStream &IOSerialize<TSwap>::Read(IStream &is, Item &item)
{
  // Superclass
  if( !Read(is,item.TagField) )
    {
	    //std::cerr << TagField << std::endl;
    assert(0 && "Should not happen");
    return is;
    }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  assert ( item.TagField == Tag(0xfffe, 0xe000)
        || item.TagField == Tag(0xfffe, 0xe0dd) 
        || item.TagField == Tag(0x3f3f, 0x3f00) );
//  if( TagField == Tag(0x3f3f, 0x3f00) )
//    {
//    TagField = Tag(0xfffe, 0xe000);
//    }
#else
  assert ( item.TagField == Tag(0xfffe, 0xe000)
        || item.TagField == Tag(0xfffe, 0xe0dd) );
#endif
  if( !Read(is,item.ValueLengthField) )
    {
    assert(0 && "Should not happen");
    return is;
    }
  // Self
  //NestedDataSet = new DataSet; //StructuredSet<DEType>;
  //std::cerr << "NestedDataSet Length=" << ValueLengthField << std::endl;
  item.NestedDataSet.SetLength( item.ValueLengthField );
  // BUG: This test is required because DataSet::Read with a Length
  // of 0 is actually thinking it is reading a root DataSet
  // so we need to make sure not to call NestedDataSet.Read here
  if( item.ValueLengthField == 0 )
    {
    assert( item.TagField == Tag( 0xfffe, 0xe0dd)
         || item.TagField == Tag( 0xfffe, 0xe000) );
    if( item.TagField != Tag( 0xfffe, 0xe0dd) )
      {
      gdcmErrorMacro( "SQ: " << item.TagField << " has a length of 0" );
      }
    }
  else
    {
    Read(is,item.NestedDataSet);
    }
//#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
//  // Ok we have read the item, sometime the ValueLengthField was wrong
//  // check that:
//  if( !ValueLengthField.IsUndefined() && ValueLengthField != 0 )
//    {
//    if( ValueLengthField != NestedDataSet->GetLength() )
//      {
//      ValueLengthField = NestedDataSet->GetLength();
//      }
//    }
//#endif
  return is;
}

template <typename TSwap>
const OStream &IOSerialize<TSwap>::Write(OStream &os, Item const & item)
{
  if( !Write(os,item.TagField) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  assert ( item.TagField == Tag(0xfffe, 0xe000)
        || item.TagField == Tag(0xfffe, 0xe0dd) );
  if( !Write(os,item.ValueLengthField) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  // Self
  Write(os,item.NestedDataSet);
  //if( ValueLengthField.IsUndefined() )
  //  {
  //  const Tag itemDelItem(0xfffe,0xe00d);
  //  const ImplicitDataElement ide(itemDelItem);
  //  assert( ide.GetVL() == 0 );
  //  ide.Write(os);
  //  }

  return os;
}


template <typename TSwap>
IStream &IOSerialize<TSwap>::Read(IStream &is, SequenceOfItems &si)
{
	//std::cerr << "SequenceLengthField: " << SequenceLengthField << std::endl;
  if( si.SequenceLengthField.IsUndefined() )
    {
    Item item;
    const Tag seqDelItem(0xfffe,0xe0dd);
    do
      {
      Read(is,item);
      //std::cout << "Item: " << item << std::endl;
      si.Items.push_back( item );
      }
    while( item.GetTag() != seqDelItem );
    }
  else
    {
    Item item;
    VL l = 0;
    //std::cout << "l: " << l << std::endl;
    while( l != si.SequenceLengthField )
      {
      Read(is,item);
      //std::cout << "Item: " << item << std::endl;
      si.Items.push_back( item );
      l += item.GetLength();
      //std::cerr << "l=" << l << std::endl;
      //assert( !item.GetVL().IsUndefined() );
      assert( l <= si.SequenceLengthField );
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
      // MR_Philips_Intera_No_PrivateSequenceImplicitVR.dcm
      // (0x2005, 0x1080): for some reason computation of length fails...
      if( si.SequenceLengthField == 778 && l == 774 )
        {
        gdcmWarningMacro( "PMS: Super bad hack" );
        l = si.SequenceLengthField;
        }
      // Bug_Philips_ItemTag_3F3F
      // (0x2005, 0x1080): Because we do not handle fully the bug at the item
      // level we need to check here too
      else if ( si.SequenceLengthField == 444 && l == 3*71 )
        {
        // This one is a double bug. Item length is wrong and impact SQ length
        gdcmWarningMacro( "PMS: Super bad hack" );
        l = si.SequenceLengthField;
        }
#endif
      }
    assert( l == si.SequenceLengthField );
    }
  return is;
}

template <typename TSwap>
OStream const &IOSerialize<TSwap>::Write(OStream &os,SequenceOfItems const &si)
{
  SequenceOfItems::ItemVector::const_iterator it = si.Items.begin();
  for(;it != si.Items.end(); ++it)
    {
    Write(os, *it);
    }
  //if( SequenceLengthField.IsUndefined() )
  //  {
  //  const Tag seqDelItem(0xfffe,0xe0dd);
  //  const ImplicitDataElement ide(seqDelItem);
  //  assert( ide.GetVL() == 0 );
  //  ide.Write(os);
  //  }
  return os;
}

//-----------------------------------------------------------------------------
template <typename TSwap>
IStream &IOSerialize<TSwap>::Read(IStream &is,DataSet &ds)
{
  //std::cerr << "DataSet::Read Length=" << Length << std::endl;
  if( ds.Length == 0)
    {
    // Ok we are reading a root DataSet
    if(ds.NegociatedTS == TS::Implicit)
      {
      StructuredSet<ImplicitDataElement> ssi;
      //std::cerr << "passed 0" << std::endl;
      Read(is,ssi);
      //std::cerr << "passed" << std::endl;
      ds.Internal.Copy(ssi);
      }
    else if ( ds.NegociatedTS == TS::Explicit )
      {
      Read(is,ds.Internal);
      //Internal.ReadSwap(is);
      }
    }
  else if( ds.Length.IsUndefined() )
    {
    // Nested DataSet with undefined length 
    ReadNested(is,ds.Internal);
    }
  else
    {
    // Nested DataSet with defined length
    ReadWithLength(is, ds.Internal, ds.Length);
    }
  //std::cerr << "Finished DataSet::Read" << std::endl;
  return is;
}

//-----------------------------------------------------------------------------
template <typename TSwap>
OStream const &IOSerialize<TSwap>::Write(OStream &os,DataSet const &ds)
{
    if(ds.NegociatedTS == TS::Implicit)
      {
      StructuredSet<ImplicitDataElement> ssi;
      ssi.Copy(ds.Internal);
      Write(os,ssi);
      }
    else if ( ds.NegociatedTS == TS::Explicit )
    {
   Write(os,ds.Internal);
    }
  return os;
}

//-----------------------------------------------------------------------------
template <typename TSwap>
IStream &IOSerialize<TSwap>::Read(IStream &is,ImplicitDataElement & ide)
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  // Read Tag
  if( !Read(is,ide.TagField) )
    {
    if( !is.eof() ) // FIXME This should not be needed
      assert(0 && "Should not happen");
    return is;
    }
  // Read Value Length
  if( !Read(is,ide.ValueLengthField) )
    {
    assert(0 && "Should not happen");
    return is;
    }
  if( ide.ValueLengthField == 0 )
    {
    // Simple fast path
    ide.ValueField = 0;
    return is;
    }
  else if( ide.ValueLengthField.IsUndefined() )
    {
    //assert( de.GetVR() == VR::SQ );
    // FIXME what if I am reading the pixel data...
    assert( ide.TagField != Tag(0x7fe0,0x0010) );
    ide.ValueField = new SequenceOfItems; //(TS::Implicit);
    }
  else
    {
    if( ide.ValueLengthField < 8 )
      {
      ide.ValueField = new ByteValue;
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
      Read(is,item);
      // Maybe this code can later be rewritten as I believe that seek back
      // is very slow...
      is.seekg(-4, std::ios::cur );
      if( item == itemStart )
        {
        assert( ide.TagField != Tag(0x7fe0,0x0010) );
        ide.ValueField = new SequenceOfItems; //(TS::Implicit);
        }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
      else if ( item == itemPMSStart )
        {
        gdcmWarningMacro( "Illegal: Explicit SQ found in a file with "
          "TransferSyntax=Implicit for tag: " << ide.TagField );
        ide.ValueField = new SequenceOfItems; //(TS::Explicit);
        //SwapCode oldsw = is.GetSwapCode();
        //assert( oldsw == SwapCode::LittleEndian );
        //is.SetSwapCode( SwapCode::BigEndian );
        ide.ValueField->SetLength(ide.ValueLengthField); // perform realloc
        if( !Read(is,*(ide.ValueField)) )
          {
          assert(0 && "Should not happen");
          }
        //is.SetSwapCode( oldsw );
        return is;
        }
      else if ( item == itemPMSStart2 )
        {
        gdcmWarningMacro( "Illegal: SQ start with " << itemPMSStart2
          << " instead of " << itemStart << " for tag: " << ide.TagField );
        ide.ValueField = new SequenceOfItems; //(TS::Implicit);
        ide.ValueField->SetLength(ide.ValueLengthField); // perform realloc
        if( !Read(is,*(ide.ValueField)) )
          {
          assert(0 && "Should not happen");
          }
        return is;
        }
#endif
      else
        {
        ide.ValueField = new ByteValue;
        }
      }
    }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  // THE WORST BUG EVER. From GE Workstation
  if( ide.ValueLengthField == 13 )
    {
    // Historically gdcm did not enforce proper length
    // thus Theralys started writing illegal DICOM images:
    const Tag theralys1(0x0008,0x0070);
    const Tag theralys2(0x0008,0x0080);
    if( ide.TagField != theralys1
     && ide.TagField != theralys2 )
      {
      gdcmWarningMacro( "GE,13: Replacing VL=0x000d with VL=0x000a, for Tag="
        << ide.TagField << " in order to read a buggy DICOM file." );
      ide.ValueLengthField = 10;
      }
    }
#endif
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  if( ide.ValueLengthField == 0x31f031c && ide.TagField == Tag(0x031e,0x0324) )
    {
    // TestImages/elbow.pap
    gdcmWarningMacro( "Replacing a VL. To be able to read a supposively"
      "broken Payrus file." );
    ide.ValueLengthField = 202; // 0xca
    }
#endif
  // We have the length we should be able to read the value
  ide.ValueField->SetLength(ide.ValueLengthField); // perform realloc
  if( !Read(is,*(ide.ValueField)) )
    {
    assert(0 && "Should not happen");
    return is;
    }

  return is;
}

//-----------------------------------------------------------------------------
template <typename TSwap>
const OStream &IOSerialize<TSwap>::Write(OStream &os, ImplicitDataElement const & ide)
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  // Write Tag
  if( !Write(os,ide.TagField) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  // Write Value Length
  if( !Write(os,ide.ValueLengthField) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  // Write Value
  if( ide.ValueLengthField )
    {
    assert( ide.ValueField );
    assert( ide.TagField != Tag(0xfffe, 0xe00d)
         && ide.TagField != Tag(0xfffe, 0xe0dd) );
    if( !Write(os,*(ide.ValueField)) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    }
  return os;
}

  template <typename TSwap> template<typename DEType>
  IStream &IOSerialize<TSwap>::Read(IStream &is,StructuredSet<DEType> &ss) {
    DEType de;
    while( !is.eof() && IOSerialize<TSwap>::Read(is,de) )
      {
      //std::cerr << "DEBUG:" << de << std::endl;
      assert( de.GetTag() != Tag(0,0) );
      ss.DES.insert( de );
      }
      //std::cerr << "finsih"  << std::endl;
    return is;
  }

  template <typename TSwap> template <typename DEType>
  OStream const &IOSerialize<TSwap>::Write(OStream &os,StructuredSet<DEType> const &ss) {
    //DEType de;
    typename StructuredSet<DEType>::ConstIterator it = ss.DES.begin();
    for( ; it != ss.DES.end(); ++it)
      {
      std::cerr << "DEBUG:" << *it << std::endl;
      const DEType & de = *it;
      // If this is a group length make sure this is consistant
      if( de.GetTag().GetGroup() == 0x0001
       || de.GetTag().GetGroup() == 0x0003
       || de.GetTag().GetGroup() == 0x0005
       || de.GetTag().GetGroup() == 0x0007 )
        {
        gdcmWarningMacro( "DataSet contains illegal Tags. "
          "Those elements will be discarded:" << de.GetTag() );
        }
      // After that we are sure the elements are valid
      else if( de.GetTag().GetElement() == 0x0 )
        {
        Element<VR::UL, VM::VM1> el;
        StringStream sst;
        //sst.SetSwapCode( os.GetSwapCode() );
        const Value &v = de.GetValue();
        const Value *pv = &v;
        const ByteValue *bv = dynamic_cast<const ByteValue*>(pv);
	IOSerialize<TSwap>::Write(sst,*bv );
        el.Read( sst );
        //std::cerr << "GL=";
        //el.Print( std::cerr );
        //std::cerr << std::endl;
        unsigned int len = ss.ComputeGroupLength( de.GetTag() );
        //std::cerr << len << std::endl;
        if( len != el.GetValue() )
          {
          gdcmWarningMacro( "Wrong group length for " << de.GetTag() << ":"
            << el.GetValue() << " should be " << len << ". Corrected." );
          DEType correct(de);
          // Set correct value:
          el.SetValue( len );
          el.Write( sst );
          // Pass it to the ByteValue
          ByteValue *bv2 = new ByteValue;
          bv2->SetLength(4);
          Read(sst,*bv2);
          correct.SetValue( *bv2 );
          IOSerialize<TSwap>::Write(os,correct);
          }
        else
          {
          // okay good value
          IOSerialize<TSwap>::Write(os,de);
          }
        }
      else // well simply writes it
        {
        IOSerialize<TSwap>::Write(os,de);
        }
      }
    return os;
  }

  template <typename TSwap> template <typename DEType>
  IStream &IOSerialize<TSwap>::ReadWithLength(IStream &is, StructuredSet<DEType> &ss, VL &length) {
    DEType de;
    VL l = 0;
    //std::cout << "ReadWithLength Length: " << l << std::endl;
    VL locallength = length;
    while( l != locallength && Read(is,de))
      {
      //std::cout << "Nested: " << de << std::endl;
      ss.DES.insert( de );
      l += de.GetLength();
      assert( !de.GetVL().IsUndefined() );
      //std::cerr << "DEBUG: " << de.GetTag() << " "<< de.GetLength() << 
      //  "," << de.GetVL() << "," << l << std::endl;
      // Bug_Philips_ItemTag_3F3F
      //  (0x2005, 0x1080): for some reason computation of length fails...
      if( l == 70 && locallength == 63 )
        {
        gdcmWarningMacro( "PMS: Super bad hack. Changing length" );
        length = locallength = 140;
        }
      assert( l <= locallength );
      }
    assert( l == locallength );
    return is;
  }

  template <typename TSwap> template <typename DEType>
  IStream &IOSerialize<TSwap>::ReadNested(IStream &is, StructuredSet<DEType> &ss) {
    DEType de;
    const Tag itemDelItem(0xfffe,0xe00d);
    while( Read(is,de) && de.GetTag() != itemDelItem )
      {
      //std::cout << "DEBUG Nested: " << de << std::endl;
      ss.DES.insert( de );
      }
    assert( de.GetTag() == itemDelItem );
    //std::cerr << "Finish nested" << std::endl;
    return is;
  }

 
 

} // end namespace gdcm

#endif // __gdcmExplicitDataElement_txx

