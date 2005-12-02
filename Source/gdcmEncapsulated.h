
#ifndef __gdcmEncapsulated_h
#define __gdcmEncapsulated_h

#include "gdcmType.h"
#include "gdcmDICOMIStream.h"
#include "gdcmDICOMOStream.h"

namespace gdcm
{
/**
 * \brief Class to represent a Encapsulated Pixel Data
 * See PS 3.5, A.4 Transfer Syntaxes for encapsulation of encoded Pixel Data
 * \note bla
 */
class Encapsulated
{
public:
  Encapsulated() { }

  friend std::ostream& operator<< < >(std::ostream& _os, const Encapsulated<DEType> &_val);
  friend DICOMIStream& operator>> < >(DICOMIStream& _os, Encapsulated<DEType> &_val);
  friend DICOMOStream& operator<< < >(DICOMOStream& _os, const Encapsulated<DEType> &_val);

  // Return true length of the Encapsulated Pixel Data
  uint32_t GetLength() {
    assert( 0 && "Not Implemented" );
    return 0; }

private:
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const Encapsulated &_val)
{
  (void)_val;
  assert( 0 );
  return _os;
}

} // end namespace gdcm

#endif //__gdcmEncapsulated_h
