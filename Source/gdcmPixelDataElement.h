
#ifndef __gdcmPixelDataElement_h
#define __gdcmPixelDataElement_h

/**
 * \brief Class to represent a Sequence Data Element
 * See PS 3.5, 7.4.6 Data Element Type Within a Sequence
 * \note bla
 */

#include "gdcmType.h"
#include "gdcmDICOMIStream.h"
#include "gdcmDICOMOStream.h"

namespace gdcm
{
// This is needed in order to declare a friend of template class
template<class DEType>
class PixelDataElement;
template<class DEType>
std::ostream& operator<<(std::ostream& _os, const PixelDataElement<DEType> &_val);

template<class DEType>
DICOMIStream& operator>>(DICOMIStream& _os, PixelDataElement<DEType> &_val);

template<class DEType>
DICOMOStream& operator<<(DICOMOStream& _os, const PixelDataElement<DEType> &_val);

// Sequence Data Element
// == bunch of SequenceItem
// But does not know anything about a Sequence Item : lik eht delimitation
template<class DEType>
class PixelDataElement
{
public:
  PixelDataElement() { }

  friend std::ostream& operator<< < >(std::ostream& _os, const PixelDataElement<DEType> &_val);
  friend DICOMIStream& operator>> < >(DICOMIStream& _os, PixelDataElement<DEType> &_val);
  friend DICOMOStream& operator<< < >(DICOMOStream& _os, const PixelDataElement<DEType> &_val);

  // Return true length of the SQ not the undefined one
  uint32_t GetLength() {
    assert( 0 && "Not Implemented" );
    return 0; }

private:
};
//-----------------------------------------------------------------------------
template<class DEType>
inline std::ostream& operator<<(std::ostream& _os, const PixelDataElement<DEType> &_val)
{
  (void)_val;
  assert( 0 );
  return _os;
}


} // end namespace gdcm

#endif //__gdcmPixelDataElement_h
