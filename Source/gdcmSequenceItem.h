
#ifndef __gdcmSequenceItem_h
#define __gdcmSequenceItem_h

/**
 * \brief Class to represent a Sequence Data Element
 * See PS 3.5 7.5.1 Item Encoding Rules
 * Each Item of a Data Element of VR SQ shall be encoded as a DICOM Standart Data
 * Element with a specific Data Element Tag of Value (FFFE,E000). The Item Tag is
 * followed by a 4 byte Item Length field encoded in one of the following two ways
 * Explicit/ Implicit
 * \note bla
 */

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
class SequenceItem;
template<class DEType>
std::ostream& operator<<(std::ostream& _os, const SequenceItem<DEType> &_val);

template<class DEType>
DICOMIStream& operator>>(DICOMIStream& _os, SequenceItem<DEType> &_val);

template<class DEType>
DICOMOStream& operator<<(DICOMOStream& _os, const SequenceItem<DEType> &_val);

// Sequence Item (Items within a SQ)
template<class DEType> // DataElementType
class SequenceItem : public DataElement
{
public:
  SequenceItem() { ItemLengthField = 0; }

  friend std::ostream& operator<< < >(std::ostream& _os, const SequenceItem<DEType> &_val);
  friend DICOMIStream& operator>> < >(DICOMIStream& _os, SequenceItem<DEType> &_val);
  friend DICOMOStream& operator<< < >(DICOMOStream& _os, const SequenceItem<DEType> &_val);

  uint32_t GetLength() { 
    assert( ItemLengthField != 0xFFFFFFF );
    return ItemLengthField; }

  void AddDataElement(const DEType& de)
    {
    SQDataSet.AddDataElement(de);
    }
  const DEType& GetDataElement(const Tag& t) const
    {
    return SQDataSet.GetDataElement(t);
    }

private:
  // This is the value read from the file, might either be a defined lenght
  // or undefined
  uint32_t ItemLengthField; // Can be 0xFFFFFFF
  DataSet<DEType> SQDataSet;
};
//-----------------------------------------------------------------------------
template<class DEType>
inline std::ostream& operator<<(std::ostream& _os, const SequenceItem<DEType> &_val)
{
  _os << _val.TagField << " Item L=" << _val.ItemLengthField << " V= " << _val.ValueField;
  _os << _val.SQDataSet;
  return _os;
}


} // end namespace gdcm

#endif //__gdcmSequenceItem_h
