
#ifndef __gdcmSequenceOfFragments_h
#define __gdcmSequenceOfFragments_h

#include "gdcmValue.h"
#include "gdcmFragment.h"
#include "gdcmBasicOffsetTable.h"

namespace gdcm
{

/**
 * \brief Class to represent a Sequence Of Fragments
 */
class GDCM_EXPORT SequenceOfFragments : public Value
{
public:
  // Typdefs:
  typedef std::vector<Fragment> FragmentVector;

/// \brief constructor (UndefinedLength by default)
  SequenceOfFragments(VL const & vl = 0xFFFFFFFF):SequenceLengthField(vl) { }

  friend std::ostream& operator<<(std::ostream& _os, const SequenceOfFragments &_val);
  void Print(std::ostream &os) const {
    (void)os;
  }

  /// \brief Returns the SQ length, as read from disk
  VL GetLength() const { return SequenceLengthField; }
  /// \brief Sets the actual SQ length
  void SetLength(VL const & length) {
    SequenceLengthField = length;
  }
  void Clear() {}
  IStream &Read(IStream &is) {
    FragmentVector::iterator it = Fragments.begin();
    for(;it != Fragments.end(); ++it)
      {
      it->Read(is);
      }
    return is;
  }
  OStream const & Write(OStream &os) const {
    FragmentVector::const_iterator it = Fragments.begin();
    for(;it != Fragments.end(); ++it)
      {
      it->Write(os);
      }
    return os;
  }

  /// \brief Appends a Fragment to the already added ones
  void AddFragment(Fragment const &item);

private:
  /// \brief Total length of the Sequence (or 0xffffffff) if undefined
  VL SequenceLengthField;
  BasicOffsetTable Table;
  /// \brief Vector of Sequence Fragments
  FragmentVector Fragments;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const SequenceOfFragments &val)
{
  os << "SQ L= " << val.SequenceLengthField << std::endl;
  return os;
}

} // end namespace gdcm

#endif //__gdcmSequenceOfFragments_h
