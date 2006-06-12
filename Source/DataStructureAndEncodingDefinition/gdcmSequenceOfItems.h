
#ifndef __gdcmSequenceOfItems_h
#define __gdcmSequenceOfItems_h

#include "gdcmValue.h"
#include "gdcmItem.h"

#include <vector>

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
  SequenceOfItems(VL const & vl = 0xFFFFFFFF):SequenceLengthField(vl) { }

  /// \brief Returns the SQ length, as read from disk
  const VL & GetLength() const { return SequenceLengthField; }
  /// \brief Sets the actual SQ length
  void SetLength(VL const & length) {
    SequenceLengthField = length;
  }
  void Clear() {}

  IStream &Read(IStream &is);
  OStream const & Write(OStream &os) const;

  /// \brief Appends an Item to the already added ones
  void AddItem(Item const &item);

protected:
  void Print(std::ostream &os) const {
    os << "SQ L= " << SequenceLengthField << "\n";
    ItemVector::const_iterator it =
      Items.begin();
    for(;it != Items.end(); ++it)
      {
      os << "  " << *it << "\n";
      }
  }

private:
  /// \brief Total length of the Sequence (or 0xffffffff) if undefined
  VL SequenceLengthField;
  /// \brief Vector of Sequence Items
  ItemVector Items;
};

} // end namespace gdcm

#endif //__gdcmSequenceOfItems_h
