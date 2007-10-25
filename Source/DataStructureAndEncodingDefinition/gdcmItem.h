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

#include "gdcmDataSet.h"
#include "gdcmImplicitDataElement.h"

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

class GDCM_EXPORT Item : public DataElement
{
  template <typename TSwap> friend class IOSerialize;
public:
  Item(const Tag& t = Tag(0), uint32_t const &vl = 0) 
	  : DataElement(t, vl), NestedDataSet() {
  }
  friend std::ostream& operator<<(std::ostream &os, const Item&val);

  void Clear() {
    NestedDataSet.Clear();
    }

  VL GetLength() const;

  void InsertDataElement(const ExplicitDataElement& de) {
    NestedDataSet.InsertDataElement(de);
    // Update the length
    assert( 0 && "InsertDataElement" );
    if( !IsUndefinedLength() )
      {
      //ValueLengthField += de.GetLength();
      }
    }
  const ExplicitDataElement& GetDataElement(const Tag& t) const
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

  void SetType(TS::NegociatedType type) { NestedDataSet.SetType(type); }

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
  os << DataElement(val) << std::endl;
  os << "Item Length=" << val.ValueLengthField << std::endl;
  val.NestedDataSet.Print( os << "\t" );
  // GDCM is NOT storing this value, we need to explicitely print it:
  // and incidently make sure to write it
  if( val.ValueLengthField.IsUndefined() )
    {
    const Tag itemDelItem(0xfffe,0xe00d);
    const ImplicitDataElement ide(itemDelItem);
    os << ide << "\n";
    }
  os << "End of Item" << std::endl;

  return os;
}


} // end namespace gdcm

#endif //__gdcmItem_h
