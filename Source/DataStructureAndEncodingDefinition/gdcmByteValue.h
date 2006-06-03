
#ifndef __gdcmByteValue_h
#define __gdcmByteValue_h

#include "gdcmValue.h"
#include "gdcmTrace.h"

namespace gdcm
{
/**
 * \brief Class to represent binary value (array of bytes)
 * \note
 */
class GDCM_EXPORT ByteValue : public Value
{
public:
  ByteValue() { Internal = 0; Length = 0; }
  ~ByteValue() { Clear(); }

  friend std::ostream& operator<<(std::ostream &_os, const ByteValue &_val);

  const VL& GetLength() const { return Length; }
  // Does a reallocation
  void SetLength(const VL& vl) {
    VL l(vl);
    if ( l.IsOdd() )
      {
      gdcmWarningMacro( "BUGGY HEADER: Your dicom contain odd length value field." );
      ++l;
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
      }
    if( Internal ) Internal[l] = '\0';
    Length = l;
  }

  //ByteValue(const ByteValue&_val)
  //  {
  //  if( this != &_val)
  //    {
  //    *this = _val;
  //    }
  //  }

  ByteValue &operator=(const ByteValue &_val)
    {
    Internal = new char[_val.Length];
    memcpy(Internal,_val.Internal,_val.Length);
    Length = _val.Length;
    return *this;
    }

  bool operator==(const ByteValue &_val) const
    {
    if( Length != _val.Length)
      return false;
    if( memcmp(Internal, _val.Internal, Length) == 0 )
      return true;
    return false;
    }

  void Clear() {
    delete[] Internal; Internal = 0; Length = 0; }

  void Read(std::istream &is,
    SC::SwapCode const &sc = SC::LittleEndian)
    {
    (void)sc;
    is.read(Internal, Length);
    }
  void Write(std::ostream &os,
    SC::SwapCode const &sc = SC::LittleEndian) const
    {
    (void)sc;
    os.write(Internal, Length);
    }

protected:
  /**
   * \brief  Checks whether a 'ByteValue' is printable or not (in order
   *         to avoid corrupting the terminal of invocation when printing)
   *         I dont think this function is working since it does not handle
   *         UNICODE or character set...
   */
  bool IsPrintable() const
    {
    for(unsigned int i=0; i<Length; i++)
      {
      if ( i == (Length-1) && Internal[i] == '\0') continue;
      if (!isprint((int)Internal[i]) )
        {
        //gdcmWarningMacro( "Cannot print :" << i );
        return false;
        }
      }
    return true;
    }


private:
  char* Internal;
  VL Length;
};
//----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &_os, const ByteValue &_val)
{
  // This is perfectly valid to have a Length = 0 , so we cannot check
  // the lenght for printing
  if( _val.Internal )
    {
    if ( _val.IsPrintable() )
      {
      _os << _val.Internal;
      return _os;
      }
    else
      _os << "Loaded:" << _val.Length;
    }
  else
    {
    _os << "Not Loaded";
    }

  return _os;
}

} // end namespace gdcm

#endif //__gdcmByteValue_h

