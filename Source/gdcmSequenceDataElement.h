
#ifndef __gdcmSequenceDataElement_h
#define __gdcmSequenceDataElement_h

#include "gdcmType.h"
#include "gdcmDICOMIStream.h"
#include "gdcmDICOMOStream.h"
#include "gdcmSequenceItem.txx"
#include <vector>

namespace gdcm
{
// This is needed in order to declare a friend of template class
template<class DEType>
class SequenceDataElement;
template<class DEType>
std::ostream& operator<<(std::ostream& _os, const SequenceDataElement<DEType> &_val);

template<class DEType>
DICOMIStream& operator>>(DICOMIStream& _os, SequenceDataElement<DEType> &_val);

template<class DEType>
DICOMOStream& operator<<(DICOMOStream& _os, const SequenceDataElement<DEType> &_val);

// Sequence Data Element
// == bunch of SequenceItem
// But does not know anything about a Sequence Item : lik eht delimitation
template<class DEType>

/**
 * \brief Class to represent a Sequence Data Element
 * See PS 3.5, 7.4.6 Data Element Type Within a Sequence
 * \note bla
 */
class SequenceDataElement
{
public:
  SequenceDataElement(uint32_t length = 0xFFFFFFFF) { SequenceLengthField = length; }
  typedef std::vector<SequenceItem<DEType> > SequenceItemVector;

  friend std::ostream& operator<< < >(std::ostream& _os, const SequenceDataElement<DEType> &_val);
  friend DICOMIStream& operator>> < >(DICOMIStream& _os, SequenceDataElement<DEType> &_val);
  friend DICOMOStream& operator<< < >(DICOMOStream& _os, const SequenceDataElement<DEType> &_val);

  uint32_t GetSequenceLength() { return SequenceLengthField; }
  void SetSequenceLength(uint32_t length) { SequenceLengthField = length; }

  // Return true length of the SQ not the undefined one
  uint32_t GetLength() {
    assert( SequenceLengthField != 0xFFFFFFFF );
    return SequenceLengthField; 
  }
  bool IsUndefinedLength() { return SequenceLengthField == 0xFFFFFFFF; }

  void AddSequenceItem(SequenceItem<DEType> const &item);

private:
  uint32_t SequenceLengthField;
  SequenceItemVector SequenceItems;
};
//-----------------------------------------------------------------------------
template<class DEType>
inline std::ostream& operator<<(std::ostream& _os, const SequenceDataElement<DEType> &_val)
{
  _os << "SQ L= " << _val.SequenceLengthField << std::endl;
  typename SequenceDataElement<DEType>::SequenceItemVector::const_iterator it = _val.SequenceItems.begin();
  int i = 0;
  for( ; it != _val.SequenceItems.end();
    ++it)
    {
    _os << "Sequence #" << i++ << std::endl << *it << std::endl;
    }
  return _os;
}


} // end namespace gdcm

#endif //__gdcmSequenceDataElement_h
