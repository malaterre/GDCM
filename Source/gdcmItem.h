
#ifndef __gdcmItem_h
#define __gdcmItem_h

#include "gdcmDataElement.h"
#include "gdcmDICOMIStream.h"
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

template<class DEType>
DICOMIStream& operator>>(DICOMIStream& _os, Item<DEType> &_val);

template<class DEType>
DICOMOStream& operator<<(DICOMOStream& _os, const Item<DEType> &_val);

// Sequence Item (Items within a SQ)
template<class DEType> // DataElementType

/**
 * \brief Class to represent an Item
 * A component of the value of a Data Element that is of Value Representation Sequence of Items.
 * An Item contains a Data Set .
 * See PS 3.5 7.5.1 Item Encoding Rules
 * Each Item of a Data Element of VR SQ shall be encoded as a DICOM Standart Data
 * Element with a specific Data Element Tag of Value (FFFE,E000). The Item Tag is
 * followed by a 4 byte Item Length field encoded in one of the following two ways
 * Explicit/ Implicit
 * \note bla
 */

class GDCM_EXPORT Item : public DataElement
{
public:
  Item() { ItemLengthField = 0; }

  friend std::ostream& operator<< < >(std::ostream& _os, const Item<DEType> &_val);
  friend DICOMIStream& operator>> < >(DICOMIStream& _os, Item<DEType> &_val);
  friend DICOMOStream& operator<< < >(DICOMOStream& _os, const Item<DEType> &_val);

  uint32_t GetLength() { 
    assert( ItemLengthField != 0xFFFFFFF );
    return ItemLengthField; }

  void AddDataElement(const DEType& de)
    {
    NestedDataSet.AddDataElement(de);
    }
  const DEType& GetDataElement(const Tag& t) const
    {
    return NestedDataSet.GetDataElement(t);
    }

private:
  // This is the value read from the file, might either be a defined lenght
  // or undefined
  uint32_t ItemLengthField; // Can be 0xFFFFFFF

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
  _os << _val.TagField << " Item L=" << _val.ItemLengthField << " V= " << _val.ValueField;
  _os << _val.NestedDataSet;
  return _os;
}


} // end namespace gdcm

#endif //__gdcmItem_h
