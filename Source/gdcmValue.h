
#ifndef __gdcmValue_h
#define __gdcmValue_h

#include "gdcmType.h"
#include <iostream>
#include <string.h>

namespace gdcm
{
/**
 * \brief Class to represent the value of a Data Element.
 * 
 * \note bla
 */
class GDCM_EXPORT Value
{
  friend class DICOMIStream;
  friend class DICOMOStream;
public:
  Value() { Internal = 0; Length = 0; }
  ~Value() { delete[] Internal; Internal = 0; Length = 0; }

  friend std::ostream& operator<<(std::ostream &_os, const Value &_val);

  uint32_t GetLength() const { return Length; }
  // Does a reallocation
  void SetLength(uint32_t l) { 
    if (l%2)
      {
      // Unfortunately, there is no way to know on *which* Tag the trouble is.
      std::cerr << "BUGGY HEADER: Your dicom contain odd length value field." << std::endl;
      }
    // FIXME: man realloc
    if( l )
      {
      if( l > Length )
        {
        char *internal = new char[l+1];
        memcpy(internal, Internal, Length);
        delete[] Internal;
        Internal = internal;
        }
      Internal[l] = '\0';
      }
    Length = l;
  }

  Value(const Value&_val)
    {
    if( this != &_val)
      {
      *this = _val;
      }
    }

  Value &operator=(const Value &_val)
    {
    Internal = new char[_val.Length];
    memcpy(Internal,_val.Internal,_val.Length);
    Length = _val.Length;
    return *this;
    }

  bool operator==(const Value &_val) const
    {
    if( Length != _val.Length)
      return false;
    if( memcmp(Internal, _val.Internal, Length) == 0 )
      return true;
    return false;
    }

  const char *GetPointer() const { return Internal; }

private:
  char* Internal;
  uint32_t Length;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &_os, const Value &_val)
{
  if( _val.Internal )
    _os << "Loaded:" << _val.Length;
  else
    _os << "Not Loaded";
  _os << " (Length: " << _val.Length << ")";
  return _os;
}

} // end namespace gdcm

#endif //__gdcmValue_h
