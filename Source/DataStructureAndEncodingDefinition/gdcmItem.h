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

#ifndef __gdcmItem_h
#define __gdcmItem_h

#include "gdcmDataElement.h"
#include "gdcmDataSet.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmTS.h"

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
public:
  Item(TS::NegociatedType const &type, const Tag& t = Tag(0),
    uint32_t const &vl = 0) : DataElement(t, vl), NType(type), NestedDataSet(0) {
  }
  friend std::ostream& operator<<(std::ostream &os, const Item&val);

  void Clear() {
    NestedDataSet->Clear();
    }

  virtual VL GetLength() const;

  void InsertDataElement(const DataElement& de) {
    NestedDataSet->InsertDataElement(de);
    // Update the length
    abort();
    if( !IsUndefinedLength() )
      {
      //ValueLengthField += de.GetLength();
      }
    }
  const DataElement& GetDataElement(const Tag& t) const
    {
    return NestedDataSet->GetDataElement(t);
    }

  // Completely defines it with the nested dataset
  // destroy anything present
  void SetNestedDataSet(const DataSet& nested)
    {
    NestedDataSet = &nested;
    }
  // Return a const ref to the Nested Data Set
  const DataSet& GetNestedDataSet() const
    {
    return *NestedDataSet;
    }

  IStream &Read(IStream &is);

  OStream &Write(OStream &os) const;

  Value const & GetValue() const { return *NestedDataSet; }

  Item(Item const &val):DataElement(val)
    {
    NestedDataSet = val.NestedDataSet;
    }

private:
  /* NESTED DATA SET  a Data Set contained within a Data Element of an other Data Set.
   * May be nested recursively.
   * Only Data Elements with VR = SQ  may, themselves, contain Data Sets
   */
  TS::NegociatedType NType;
  typedef SmartPointer<DataSet> DataSetPtr;
  DataSetPtr NestedDataSet;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const Item &val)
{
  os << "Item Length=" << val.ValueLengthField << std::endl;
  if( val.NestedDataSet )
    {
    val.NestedDataSet->Print( os << "\t" );
    }
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
