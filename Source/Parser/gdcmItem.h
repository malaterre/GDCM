
#ifndef __gdcmItem_h
#define __gdcmItem_h

#include "gdcmDataElement.h"
//#include "gdcmDICOMIStream.h"
#include "gdcmDICOMOStream.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmDataSet.h"

namespace gdcm
{
// This is needed in order to declare a friend of template class
template<class DEType>
class Item;
template<class DEType>
std::ostream& operator<<(std::ostream& _os, const Item<DEType> &_val);

//template<class DEType>
//DICOMIStream& operator>>(DICOMIStream& _os, Item<DEType> &_val);

template<class DEType>
DICOMOStream& operator<<(DICOMOStream& _os, const Item<DEType> &_val);

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

// Sequence Item (Items within a SQ)
template<class DEType> // DataElementType

class GDCM_EXPORT Item : public DataElement
{
public:
  Item(uint32_t length = 0xFFFFFFFF) { TagField = Tag(0xfffe,0xe000); ValueLengthField = length; }

  friend std::ostream& operator<< < >(std::ostream& _os, const Item<DEType> &_val);
  //friend DICOMIStream& operator>> < >(DICOMIStream& _os, Item<DEType> &_val);
  friend class DICOMIStream;
  friend DICOMOStream& operator<< < >(DICOMOStream& _os, const Item<DEType> &_val);

  void Clear()
    {
    NestedDataSet.Clear();
    }
  uint32_t GetValueLength() const { return ValueLengthField; }
  uint32_t GetLength() const { 
    assert( ValueLengthField != 0xFFFFFFFF );
    return ValueLengthField; }

  void AddDataElement(const DEType& de)
    {
    NestedDataSet.AddDataElement(de);
    // Update the length
    if (ValueLengthField != 0xFFFFFFFF )
      {
      ValueLengthField += de.GetLength();
      }
    }
  const DEType& GetDataElement(const Tag& t) const
    {
    return NestedDataSet.GetDataElement(t);
    }

  // Completely defines it with the nested dataset
  // destroy anything present
  void SetNestedDataSet(const DataSet<DEType>& nested)
    {
    NestedDataSet = nested;
    }
  // Return a const ref to the Nested Data Set
  const DataSet<DEType>& GetNestedDataSet() const
    {
    return NestedDataSet;
    }

private:
  // This is the value read from the file, might either be a defined lenght
  // or undefined
  //uint32_t ItemLengthField; // Can be 0xFFFFFFFF

  /* NESTED DATA SET  a Data Set contained within a Data Element of an other Data Set.
   * May be nested recursively.
   * Only Data Elements with VR = SQ  may, themselves, contain Data Sets
   */
  DataSet<DEType> NestedDataSet;
};
//-----------------------------------------------------------------------------
template<class DEType>
inline std::ostream& operator<<(std::ostream& _os, const Item<DEType> &_val)
{
  _os << _val.TagField << " Item Length=" << _val.ValueLengthField << /*" Item Value= " << _val.ValueField <<*/ std::endl;
  _os << _val.NestedDataSet;
  // Print delimitation if undefined
  if( _val.ValueLengthField == 0xFFFFFFFF )
    {
    //DataElement endItem;
    //endItem.SetTag( Tag(0xfffe,0xe00d) );
    //_os << endItem << std::endl;
    //FIXME: Stupid code
    _os << Tag(0xfffe, 0xe00d) << std::endl;
    }

  return _os;
}


} // end namespace gdcm

#endif //__gdcmItem_h
