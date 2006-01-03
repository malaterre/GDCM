
#ifndef __gdcmSequenceOfItems_h
#define __gdcmSequenceOfItems_h

#include "gdcmType.h"
#include "gdcmDICOMIStream.h"
#include "gdcmDICOMOStream.h"
#include "gdcmItem.h"
#include <vector>

namespace gdcm
{
// This is needed in order to declare a friend of template class
template<class DEType>
class SequenceOfItems;
template<class DEType>
std::ostream& operator<<(std::ostream& _os, const SequenceOfItems<DEType> &_val);

template<class DEType>
DICOMIStream& operator>>(DICOMIStream& _os, SequenceOfItems<DEType> &_val);

template<class DEType>
DICOMOStream& operator<<(DICOMOStream& _os, const SequenceOfItems<DEType> &_val);

// Sequence Data Element
// == bunch of Items
// But does not know anything about a Sequence Item : lik eht delimitation
template<class DEType>

/**
 * \brief Class to represent a Sequence Of Items
 * (value representation : SQ)
 *  - a Value Representation for Data Elements that contains a sequence of Data Sets.
 *  - Sequence of Item allows for Nested Data Sets
 *
 * See PS 3.5, 7.4.6 Data Element Type Within a Sequence
 * \note bla
 */
class GDCM_EXPORT SequenceOfItems
{
public:
/// \brief contructor (UndefinedLength by default)
  SequenceOfItems(uint32_t length = 0xFFFFFFFF) { SequenceLengthField = length; }
  typedef std::vector<Item<DEType> > ItemVector;

  friend std::ostream& operator<< < >(std::ostream& _os, const SequenceOfItems<DEType> &_val);
  friend DICOMIStream& operator>> < >(DICOMIStream& _os, SequenceOfItems<DEType> &_val);
  friend DICOMOStream& operator<< < >(DICOMOStream& _os, const SequenceOfItems<DEType> &_val);

  /// \brief Returns the SQ length, as read from disk
  uint32_t GetSequenceLength() { return SequenceLengthField; }
  /// \brief Sets the actual SQ length
  void SetSequenceLength(uint32_t length) { SequenceLengthField = length; }

  /// \brief Returns the true length of the SQ not the undefined one
  uint32_t GetLength() {
    assert( SequenceLengthField != 0xFFFFFFFF );
    return SequenceLengthField; 
  }
  /// \brief tells us whether Sequence length is undefined (= 0xffffffff)
  bool IsUndefinedLength() { return SequenceLengthField == 0xFFFFFFFF; }

/// \brief Appends an Item to the already added ones
  void AddItem(Item<DEType> const &item);

private:
  /// \brief Total length of the Sequence (or 0xffffffff) if undefined
  uint32_t SequenceLengthField;
  /// \brief Vector of Sequence Items
  ItemVector Items;
};
//-----------------------------------------------------------------------------
template<class DEType>
inline std::ostream& operator<<(std::ostream& _os, const SequenceOfItems<DEType> &_val)
{
  _os << "SQ L= " << _val.SequenceLengthField << std::endl;
  typename SequenceOfItems<DEType>::ItemVector::const_iterator it = _val.Items.begin();
  // Print each Item
  int i = 0;
  for( ; it != _val.Items.end();
    ++it)
    {
    _os << "Sequence #" << i++ << std::endl << *it << std::endl;
    }
  // Print delimitation if undefined
  if( _val.SequenceLengthField == 0xFFFFFFFF )
    {
    DataElement endSeq;
    endSeq.SetTag( Tag(0xfffe,0xe0dd) ); // Sequence Delimitation Item
    _os << endSeq << std::endl;
    }
  return _os;
}


} // end namespace gdcm

#endif //__gdcmSequenceOfItems_h
