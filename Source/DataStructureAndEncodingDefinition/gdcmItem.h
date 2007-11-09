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

#ifndef __gdcmItem_h
#define __gdcmItem_h

//#include "gdcmTS.h"
#include "gdcmDataElement.h"
#include "gdcmStructuredSet.h"

namespace gdcm
{
// This is needed in order to declare a friend of template class
template <typename DEType>
class Item;
template <typename DEType>
std::ostream& operator<<(std::ostream& _os, const Item<DEType> &_val);

/**
 * \brief Class to represent an Item
 * A component of the value of a Data Element that is of Value Representation Sequence of Items.
 * An Item contains a Data Set .
 * See PS 3.5 7.5.1 Item Encoding Rules
 * Each Item of a Data Element of VR SQ shall be encoded as a DICOM Standart Data
 * Element with a specific Data Element Tag of Value (FFFE,E000). The Item Tag is
 * followed by a 4 byte Item Length field encoded in one of the following two ways
 * Explicit/ Implicit
 * \note
 * ITEM: A component of the Value of a Data Element that is of Value
 * Representation Sequence of Items. An Item contains a Data Set.
 */
template<class DEType>
class StructuredSet;

template <typename DEType>
class GDCM_EXPORT Item : public DataElement
{
public:
  Item(const Tag& t = Tag(0), uint32_t const &vl = 0) 
	  : DataElement(t, vl), NestedDataSet() {
  }
  friend std::ostream& operator<< < >(std::ostream &os, const Item<DEType> &val);

  void Clear() {
    NestedDataSet.Clear();
    }

  VL GetLength() const;

  void InsertDataElement(const DEType & de) {
    NestedDataSet.InsertDataElement(de);
    // Update the length
    assert( 0 && "InsertDataElement" );
    if( !IsUndefinedLength() )
      {
      //ValueLengthField += de.GetLength();
      }
    }
  const DEType& GetDataElement(const Tag& t) const
    {
    return NestedDataSet.GetDataElement(t);
    }

  // Completely defines it with the nested dataset
  // destroy anything present
  void SetNestedDataSet(const StructuredSet<DEType>& nested)
    {
    NestedDataSet = nested;
    }
  // Return a const ref to the Nested Data Set
  const StructuredSet<DEType> &GetNestedDataSet() const
    {
    return NestedDataSet;
    }

//  template <typename TSwap>
//  IStream &Read(IStream &is);
//
//  template <typename TSwap>
//  const OStream &Write(OStream &os) const;

  //Value const & GetValue() const { return *NestedDataSet; }

  Item(Item const &val):DataElement(val)
    {
    NestedDataSet = val.NestedDataSet;
    }

  //void SetType(TS::NegociatedType type) { NestedDataSet.SetType(type); }


template <typename TSwap>
IStream &Read(IStream &is)
{
  // Superclass
  if( !TagField.Read<TSwap>(is) )
    {
	    //std::cerr << TagField << std::endl;
    assert(0 && "Should not happen");
    return is;
    }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  assert ( TagField == Tag(0xfffe, 0xe000)
        || TagField == Tag(0xfffe, 0xe0dd) 
        || TagField == Tag(0x3f3f, 0x3f00) );
//  if( TagField == Tag(0x3f3f, 0x3f00) )
//    {
//    TagField = Tag(0xfffe, 0xe000);
//    }
#else
  assert ( TagField == Tag(0xfffe, 0xe000)
        || TagField == Tag(0xfffe, 0xe0dd) );
#endif
  if( !ValueLengthField.Read<TSwap>(is) )
    {
    assert(0 && "Should not happen");
    return is;
    }
  // Self
  //NestedDataSet = new DataSet; //StructuredSet<DEType>;
  //std::cerr << "NestedDataSet Length=" << ValueLengthField << std::endl;
//  NestedDataSet.SetLength( ValueLengthField ); // FIXME
  // BUG: This test is required because DataSet::Read with a Length
  // of 0 is actually thinking it is reading a root DataSet
  // so we need to make sure not to call NestedDataSet.Read here
  if( ValueLengthField == 0 )
    {
    assert( TagField == Tag( 0xfffe, 0xe0dd)
         || TagField == Tag( 0xfffe, 0xe000) );
    if( TagField != Tag( 0xfffe, 0xe0dd) )
      {
      gdcmErrorMacro( "SQ: " << TagField << " has a length of 0" );
      }
    }
  else if( ValueLengthField.IsUndefined() )
    {
    StructuredSet<DEType> &nested = NestedDataSet;
    nested.template ReadNested<TSwap>(is);
    }
  else /* if( ValueLengthField.IsUndefinedLength() ) */
    {
    StructuredSet<DEType> &nested = NestedDataSet;
    nested.template ReadWithLength<TSwap>(is, ValueLengthField);
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
const OStream &Write(OStream &os) const
{
  if( !TagField.Write<TSwap>(os) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  assert ( TagField == Tag(0xfffe, 0xe000)
        || TagField == Tag(0xfffe, 0xe0dd) );
  if( !ValueLengthField.Write<TSwap>(os) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  // Self
  NestedDataSet.Write<TSwap>(os);
  //if( ValueLengthField.IsUndefined() )
  //  {
  //  const Tag itemDelItem(0xfffe,0xe00d);
  //  const ImplicitDataElement ide(itemDelItem);
  //  assert( ide.GetVL() == 0 );
  //  ide.Write(os);
  //  }

  return os;
}


private:
  /* NESTED DATA SET  a Data Set contained within a Data Element of an other Data Set.
   * May be nested recursively.
   * Only Data Elements with VR = SQ  may, themselves, contain Data Sets
   */
  StructuredSet<DEType> NestedDataSet;
};
//-----------------------------------------------------------------------------
template <typename DEType>
inline std::ostream& operator<<(std::ostream& os, const Item<DEType> &val)
{
  os << DataElement(val) << std::endl;
  os << "Item Length=" << val.ValueLengthField << std::endl;
  val.NestedDataSet.Print( os << "\t" );
  // GDCM is NOT storing this value, we need to explicitely print it:
  // and incidently make sure to write it
  if( val.ValueLengthField.IsUndefined() )
    {
    const Tag itemDelItem(0xfffe,0xe00d);
    //const ImplicitDataElement ide(itemDelItem);
    //os << ide << "\n";
    }
  os << "End of Item" << std::endl;

  return os;
}


} // end namespace gdcm

#include "gdcmItem.txx"

#endif //__gdcmItem_h
