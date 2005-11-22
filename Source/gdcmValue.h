
#ifndef __gdcmValue_h
#define __gdcmValue_h

/**
 * \brief Class to represent a Data Element Tag (Group, Element).
 * Basically an uint32_t or expressad as two uint16_t (group and element)
 * \note bla
 */

#include "gdcmType.h"
#include <iostream>
#include <string.h>

namespace gdcm
{
// Data Element Value Field
class Value
{
  friend class DICOMIStream;
  friend class DICOMOStream;
public:
  Value() { Internal = 0; Length = 0; }
  ~Value() { delete[] Internal; Internal = 0; Length = 0; }

  friend std::ostream& operator<<(std::ostream& _os, const Value &_val);

  uint32_t GetLength() const { return Length; }
  // Does a reallocation
  void SetLength(uint32_t l) { 
    assert( !(l%2) );
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
    Internal = _val.Internal;
    Length = _val.Length;
    }

  Value &operator=(const Value &_val)
    {
    Internal = _val.Internal;
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
inline std::ostream& operator<<(std::ostream& _os, const Value &_val)
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
