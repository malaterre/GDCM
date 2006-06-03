
#ifndef __gdcmItem_h
#define __gdcmItem_h

#include "gdcmDataElement.h"
#include "gdcmDataSet.h"
#include "gdcmSwapCode.h"

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
  Item(const Tag& t = Tag(0), uint32_t const &vl = 0) : DataElement(t, vl), NestedDataSet(TS::Implicit) {}
  friend std::ostream& operator<<(std::ostream &os, const Item&val);

  void Clear() {
    NestedDataSet.Clear();
    }

  void InsertDataElement(const DataElement& de) {
    NestedDataSet.InsertDataElement(de);
    // Update the length
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
  const DataSet& GetNestedDataSet() const
    {
    return NestedDataSet;
    }

  void Read(std::istream &is,
    SC::SwapCode const &sc = SC::LittleEndian) {
    NestedDataSet.Read(is, sc);
    }

  void Write(std::ostream &os,
    SC::SwapCode const &sc = SC::LittleEndian) const {
    NestedDataSet.Write(os, sc);
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
  os << " Item Length=" << val.ValueLengthField << std::endl;
  os << val.NestedDataSet;

  return os;
}


} // end namespace gdcm

#endif //__gdcmItem_h
