
#ifndef __gdcmSequenceItems_h
#define __gdcmSequenceItems_h

#include "gdcmType.h"
#include "gdcmDICOMIStream.h"
#include "gdcmDICOMOStream.h"
#include "gdcmItem.h"
#include <vector>

namespace gdcm
{
// This is needed in order to declare a friend of template class
template<class DEType>
class SequenceItems;
template<class DEType>
std::ostream& operator<<(std::ostream& _os, const SequenceItems<DEType> &_val);

template<class DEType>
DICOMIStream& operator>>(DICOMIStream& _os, SequenceItems<DEType> &_val);

template<class DEType>
DICOMOStream& operator<<(DICOMOStream& _os, const SequenceItems<DEType> &_val);

// Sequence Data Element
// == bunch of Item
// But does not know anything about a Sequence Item : lik eht delimitation
template<class DEType>

/**
 * \brief Class to represent a Sequence Of Items
 * (value representation : SQ)
 * a Value Representation for Data Elements that contains a sequence of Data Sets.
 * Sequence of Item allows for Nested Data Sets
 *
 * See PS 3.5, 7.4.6 Data Element Type Within a Sequence
 * \note bla
 */
class SequenceItems
{
public:
  SequenceItems(uint32_t length = 0xFFFFFFFF) { SequenceLengthField = length; }
  typedef std::vector<Item<DEType> > ItemVector;

  friend std::ostream& operator<< < >(std::ostream& _os, const SequenceItems<DEType> &_val);
  friend DICOMIStream& operator>> < >(DICOMIStream& _os, SequenceItems<DEType> &_val);
  friend DICOMOStream& operator<< < >(DICOMOStream& _os, const SequenceItems<DEType> &_val);

  uint32_t GetSequenceLength() { return SequenceLengthField; }
  void SetSequenceLength(uint32_t length) { SequenceLengthField = length; }

  // Return true length of the SQ not the undefined one
  uint32_t GetLength() {
    assert( SequenceLengthField != 0xFFFFFFFF );
    return SequenceLengthField; 
  }
  bool IsUndefinedLength() { return SequenceLengthField == 0xFFFFFFFF; }

  void AddItem(Item<DEType> const &item);

private:
  uint32_t SequenceLengthField;
  ItemVector Items;
};
//-----------------------------------------------------------------------------
template<class DEType>
inline std::ostream& operator<<(std::ostream& _os, const SequenceItems<DEType> &_val)
{
  _os << "SQ L= " << _val.SequenceLengthField << std::endl;
  typename SequenceItems<DEType>::ItemVector::const_iterator it = _val.Items.begin();
  int i = 0;
  for( ; it != _val.Items.end();
    ++it)
    {
    _os << "Sequence #" << i++ << std::endl << *it << std::endl;
    }
  return _os;
}


} // end namespace gdcm

#endif //__gdcmSequenceItems_h
