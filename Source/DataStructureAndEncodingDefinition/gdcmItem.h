
#ifndef __gdcmItem_h
#define __gdcmItem_h

#include "gdcmDataElement.h"
#include "gdcmImplicitDataElement.h"
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
  Item(const Tag& t = Tag(0), uint32_t const &vl = 0) : DataElement(t, vl), NestedDataSet(TS::Explicit) {}
  friend std::ostream& operator<<(std::ostream &os, const Item&val);

  void Clear() {
    NestedDataSet.Clear();
    }

  virtual VL GetLength() const {
    assert( !ValueLengthField.IsUndefined() );
    return TagField.GetLength() + ValueLengthField.GetLength() + ValueLengthField;
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

  IStream &Read(IStream &is) {
    // Superclass 
    if( !TagField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    if( !ValueLengthField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    // Self
    //FragmentValue.SetLength(ValueLengthField);
    if( ValueLengthField.IsUndefined() )
      {
      NestedDataSet.ReadNested(is);
      // WARNING we are not storing the Item Del Tag nor its length
      // in the structure
      }
    else
      {
      NestedDataSet.ReadWithLength(is, ValueLengthField);
      //is.Seekg(ValueLengthField, std::ios::cur);
      }
    return is;
    }

  OStream &Write(OStream &os) const {
    return NestedDataSet.Write(os);
    }

  Value const & GetValue() const { return NestedDataSet; }

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
  os << "Item Length=" << val.ValueLengthField << std::endl;
  os << val.NestedDataSet;
  // GDCM is NOT storing this value, we need to explicitely print it:
  // and incidently make sure to write it
  if( val.ValueLengthField.IsUndefined() )
    {
    const Tag itemDelItem(0xfffe,0xe00d);
    const ImplicitDataElement ide(itemDelItem);
    os << ide;
    }

  return os;
}


} // end namespace gdcm

#endif //__gdcmItem_h
