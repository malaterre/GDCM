
#ifndef __gdcmSequenceOfItems_h
#define __gdcmSequenceOfItems_h

#include "gdcmValue.h"
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
  SequenceOfItems(VL const & vl = 0xFFFFFFFF):SequenceLengthField(vl) { }

  friend std::ostream& operator<<(std::ostream& _os, const SequenceOfItems &_val);
  void Print(std::ostream &os) const {
    (void)os;
  }

  /// \brief Returns the SQ length, as read from disk
  const VL& GetLength() const { return SequenceLengthField; }
  /// \brief Sets the actual SQ length
  void SetLength(VL const & length) {
    SequenceLengthField = length;
  }
  void Clear() {}
  std::istream &Read(std::istream &is,
    SC::SwapCode const &sc = SC::LittleEndian) {
    ItemVector::iterator it = Items.begin();
    for(;it != Items.end(); ++it)
      {
      it->Read(is, sc);
      }
    return is;
  }
  std::ostream const & Write(std::ostream &os,
    SC::SwapCode const &sc = SC::LittleEndian) const {
    ItemVector::const_iterator it = Items.begin();
    for(;it != Items.end(); ++it)
      {
      it->Write(os, sc);
      }
    return os;
  }

  /// \brief Appends an Item to the already added ones
  void AddItem(Item const &item);

private:
  /// \brief Total length of the Sequence (or 0xffffffff) if undefined
  VL SequenceLengthField;
  /// \brief Vector of Sequence Items
  ItemVector Items;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const SequenceOfItems &val)
{
  os << "SQ L= " << val.SequenceLengthField << std::endl;
  return os;
}

} // end namespace gdcm

#endif //__gdcmSequenceOfItems_h
