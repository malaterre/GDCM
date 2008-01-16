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

#ifndef __gdcmItem_h
#define __gdcmItem_h

#include "gdcmDataElement.h"
#include "gdcmDataSet.h"

namespace gdcm
{

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
class DataSet;

class GDCM_EXPORT Item : public DataElement
{
public:
  Item(const Tag& t = Tag(0), uint32_t const &vl = 0) 
	  : DataElement(t, vl), NestedDataSet() {
  }
  friend std::ostream& operator<< (std::ostream &os, const Item &val);

  void Clear() {
    NestedDataSet.Clear();
    }

  template <typename TDE>
  VL GetLength() const;

  void InsertDataElement(const DataElement & de) {
    NestedDataSet.Insert(de);
    // Update the length
    assert( 0 && "InsertDataElement" );
    if( !IsUndefinedLength() )
      {
      //ValueLengthField += de.GetLength();
      }
    }
  const DataElement& GetDataElement(const Tag& t) const
    {
    return NestedDataSet.GetDataElement(t);
    }

  // Completely defines it with the nested dataset
  // destroy anything present
  void SetNestedDataSet(const DataSet& nested)
    {
    NestedDataSet = nested;
    }
  // Return a const ref to the Nested Data Set
  const DataSet &GetNestedDataSet() const
    {
    return NestedDataSet;
    }
  DataSet &GetNestedDataSet()
    {
    return NestedDataSet;
    }

  //Value const & GetValue() const { return *NestedDataSet; }

  Item(Item const &val):DataElement(val)
    {
    NestedDataSet = val.NestedDataSet;
    }

  //void SetType(TS::NegociatedType type) { NestedDataSet.SetType(type); }

template <typename TDE, typename TSwap>
std::istream &Read(std::istream &is)
{
  // Superclass
  if( !TagField.Read<TSwap>(is) )
    {
	    //std::cerr << TagField << std::endl;
    //assert(0 && "Should not happen");
    throw Exception("Should not happen");
    return is;
    }
  assert ( TagField == Tag(0xfffe, 0xe000)
        || TagField == Tag(0xfffe, 0xe0dd) 
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
        || TagField == Tag(0xfeff, 0x00e0)
        || TagField == Tag(0x3f3f, 0x3f00)
#endif
  );
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  // TODO FIXME: should not change value on the fly, only at write time
  if( TagField == Tag(0xfeff, 0x00e0) ) 
    {
    gdcmDebugMacro( "FIXME" );
    TagField = Tag(0xfffe, 0xe000);
    }
#endif
  if( !ValueLengthField.Read<TSwap>(is) )
    {
    assert(0 && "Should not happen");
    return is;
    }
  // Self
  // Some file written by GDCM 1.0 we writting 0xFFFFFFFF instead of 0x0
  if( TagField == Tag(0xfffe,0xe0dd) )
    {
    if( ValueLengthField )
      {
      gdcmErrorMacro( "ValueLengthField is not 0" );
      gdcmDebugMacro( "FIXME" ); // should not change the value at read time
      ValueLengthField = 0; // FIXME should not set value inplace
      }
    }
  else if( ValueLengthField == 0 )
    {
    assert( TagField == Tag( 0xfffe, 0xe0dd)
        /* || TagField == Tag( 0xfffe, 0xe000)*/ );
    if( TagField != Tag( 0xfffe, 0xe0dd) )
      {
      gdcmErrorMacro( "SQ: " << TagField << " has a length of 0" );
      }
    }
  else if( ValueLengthField.IsUndefined() )
    {
    DataSet &nested = NestedDataSet;
    nested.Clear();
    assert( nested.IsEmpty() );
    nested.template ReadNested<TDE,TSwap>(is);
    }
  else /* if( ValueLengthField.IsUndefinedLength() ) */
    {
    DataSet &nested = NestedDataSet;
    nested.Clear();
    nested.template ReadWithLength<TDE,TSwap>(is, ValueLengthField);
    }

  return is;
}

template <typename TDE, typename TSwap>
const std::ostream &Write(std::ostream &os) const
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
  NestedDataSet.Write<TDE,TSwap>(os);
  if( ValueLengthField.IsUndefined() )
    {
    const Tag itemDelItem(0xfffe,0xe00d);
    itemDelItem.Write<TSwap>(os);
    VL zero = 0;
    zero.Write<TSwap>(os);
    }

  return os;
}


private:
  /* NESTED DATA SET  a Data Set contained within a Data Element of an other Data Set.
   * May be nested recursively.
   * Only Data Elements with VR = SQ  may, themselves, contain Data Sets
   */
  DataSet NestedDataSet;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const Item &val)
{
  os << val.TagField;
  os << "\t" << val.ValueLengthField << "\n";
  val.NestedDataSet.Print( os, "\t" );

  return os;
}


} // end namespace gdcm

#include "gdcmItem.txx"

#endif //__gdcmItem_h
