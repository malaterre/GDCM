
#ifndef __gdcmSequenceOfItems_h
#define __gdcmSequenceOfItems_h

#include "gdcmCompositeValue.h"
#include "gdcmItem.h"

namespace gdcm
{

/**
 * \brief Class to represent a Sequence Of Items
 * (value representation : SQ)
 *  - a Value Representation for Data Elements that contains a sequence of Data Sets.
 *  - Sequence of Item allows for Nested Data Sets
 *
 * See PS 3.5, 7.4.6 Data Element Type Within a Sequence
 * \note
 * SEQUENCE OF ITEMS (VALUE REPRESENTATION SQ)
 * A Value Representation for Data Elements that contain a sequence of 
 * Data Sets. Sequence of Items allows for Nested Data Sets.
 */
class GDCM_EXPORT SequenceOfItems : public Value
{
public:
  // Typdefs:
  typedef std::vector<Item> ItemVector;

/// \brief constructor (UndefinedLength by default)
  SequenceOfItems(uint32_t length = 0xFFFFFFFF) { SequenceLengthField = length; }

  friend std::ostream& operator<< < >(std::ostream& _os, const SequenceOfItems<DEType> &_val);

  /// \brief Returns the SQ length, as read from disk
  uint32_t GetSequenceLength() { return SequenceLengthField; }
  /// \brief Sets the actual SQ length
  void SetSequenceLength(uint32_t length) { SequenceLengthField = length; }

  /// \brief Appends an Item to the already added ones
  void AddItem(Item<DEType> const &item);

protected:
  DICOMOStream& Write(DICOMOStream& _os) const;
  //DICOMIStream& Read(DICOMIStream& _os);

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
    _os << "Sequence Item #" << i++ << std::endl << *it << std::endl;
    }
  // Print delimitation if undefined
  if( _val.SequenceLengthField == 0xFFFFFFFF )
    {
    //DataElement endSeq;
    //endSeq.SetTag( Tag(0xfffe,0xe0dd) ); // Sequence Delimitation Item
    //_os << endSeq << std::endl;
    // FIXME: Stupid code
    _os << Tag(0xfffe,0xe00d) << std::endl;
    }
  return _os;
}

} // end namespace gdcm

#endif //__gdcmSequenceOfItems_h
