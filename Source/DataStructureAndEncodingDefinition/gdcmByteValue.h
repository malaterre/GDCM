
#ifndef __gdcmByteValue_h
#define __gdcmByteValue_h

#include "gdcmValue.h"
#include "gdcmTrace.h"

#include <vector>
#include <iterator>

namespace gdcm
{
/**
 * \brief Class to represent binary value (array of bytes)
 * \note
 */
class GDCM_EXPORT ByteValue : public Value
{
public:
  ByteValue(const char* array = 0, VL const &vl = 0):
    Internal(array, array+vl) { 
  }
  ~ByteValue() { 
    Internal.clear(); 
  }

  friend std::ostream& operator<<(std::ostream &_os, const ByteValue &_val);

  void Print(std::ostream &os) const {
  // This is perfectly valid to have a Length = 0 , so we cannot check
  // the lenght for printing
  if( !Internal.empty() )
    {
    if( IsPrintable() )
      {
      std::copy(Internal.begin(), Internal.end(),
        std::ostream_iterator<char>(os));
      }
    else
      os << "Loaded:" << Internal.size();
    }
  else
    {
    os << "Not Loaded";
    }
  }

  VL GetLength() const { return Internal.size(); }
  // Does a reallocation
  void SetLength(const VL& vl) {
    VL l(vl);
    if ( l.IsOdd() )
      {
      gdcmWarningMacro( "BUGGY HEADER: Your dicom contain odd length value field." );
      ++l;
      }
    Internal.resize(l);
  }

  ByteValue &operator=(const ByteValue &val)
    {
    Internal = val.Internal;
    return *this;
    }

  bool operator==(const ByteValue &val) const
    {
    if( GetLength() != val.GetLength())
      return false;
    if( Internal == val.Internal )
      return true;
    return false;
    }

  void Clear() {
    Internal.clear();
  }
  const char *GetPointer() const { return &Internal[0]; }

  IStream &Read(IStream &is)
    {
    return is.Read(&Internal[0], GetLength());
    }
  OStream const & Write(OStream &os) const
    {
    return os.Write(&Internal[0], GetLength());
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
    VL length = GetLength();
    for(unsigned int i=0; i<length; i++)
      {
      if ( i == (length-1) && Internal[i] == '\0') continue;
      if (!isprint((int)Internal[i]) )
        {
        //gdcmWarningMacro( "Cannot print :" << i );
        return false;
        }
      }
    return true;
    }


private:
  std::vector<char> Internal;
  //char* Internal;
  //VL Length;
};
//----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const ByteValue &val)
{
  val.Print(os);
  return os;
}

} // end namespace gdcm

#endif //__gdcmByteValue_h

