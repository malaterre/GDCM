/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmByteValue_h
#define __gdcmByteValue_h

#include "gdcmValue.h"
#include "gdcmTrace.h"
#include "gdcmVL.h"

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
    Internal(array, array+vl),Length(vl) {
      if( vl.IsOdd() )
        {
        gdcmWarningMacro( "Odd length" );
        Internal.resize(vl+1);
        }
  }
  ByteValue(std::ostringstream const &os) {
	   abort(); // TODO
  }
  ~ByteValue() {
    Internal.clear();
  }

  // When 'dumping' dicom file we still have some information from
  // Either the VR: eg LO (private tag)
  void PrintASCII(std::ostream &os) {
    (void)os;
  }

  // Either from Element Number (== 0x0000)
  void PrintGroupLength(std::ostream &os) {
    assert( Length == 2 );
    (void)os;
  }

  VL GetLength() const { return Length; }
  // Does a reallocation
  void SetLength(VL vl) {
    VL l(vl);
    assert( !l.IsUndefined() );
    if ( l.IsOdd() ) {
      gdcmDebugMacro(
        "BUGGY HEADER: Your dicom contain odd length value field." );
      ++l;
      }
    // I cannot use reserve for now. I need to implement:
    // STL - vector<> and istream
    // http://groups.google.com/group/comp.lang.c++/msg/37ec052ed8283e74
    Internal.resize(l);
    //Internal.reserve(l);
    // Keep the exact length
    Length = vl;
  }

  ByteValue &operator=(const ByteValue &val) {
    Internal = val.Internal;
    return *this;
    }

  bool operator==(const ByteValue &val) const {
    if( Length != val.Length )
      return false;
    if( Internal == val.Internal )
      return true;
    return false;
    }

  void Clear() {
    Internal.clear();
  }
  // Use that only if you understand what you are doing
  const char *GetPointer() const {
    return &Internal[0];
  }
  bool GetBuffer(char *buffer, unsigned long length) const {
    // SIEMENS_GBS_III-16-ACR_NEMA_1.acr has a weird pixel length
    // so we need an inequality
    if( length <= Internal.size() )
      {
      memcpy(buffer, &Internal[0], length);
      return true;
      }
    abort();
    return false;
    }
  bool WriteBuffer(std::ostream &os) const {
    assert( Internal.size() <= Length );
    assert( !(Internal.size() % 2) );
    os.write(&Internal[0], Internal.size() );
    return true;
  }


  template <typename TSwap>
  std::istream &Read(std::istream &is) {
    // If Length is odd we have detected that in SetLength
    // and calling std::vector::resize make sure to allocate *AND* 
    // initialize values to 0 so we are sure to have a \0 at the end
    // even in this case
#ifdef SHORT_READ_HACK
    if( Length > 0xfff )
      {
      is.seekg(Length, std::ios::cur);
      }
    else
      {
      is.read(&Internal[0], Length);
      }
    return is;
#else
    return is.read(&Internal[0], Length);
#endif
  }

  template <typename TSwap>
  std::ostream const &Write(std::ostream &os) const {
#ifdef GDCM_WRITE_ODD_LENGTH
    return os.write(&Internal[0], Length);
#else
    assert( !(Internal.size() % 2) );
    return os.write(&Internal[0], Internal.size());
#endif
    }

protected:
  /**
   * \brief  Checks whether a 'ByteValue' is printable or not (in order
   *         to avoid corrupting the terminal of invocation when printing)
   *         I dont think this function is working since it does not handle
   *         UNICODE or character set...
   */
  bool IsPrintable() const {
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

  void Print(std::ostream &os) const {
  // This is perfectly valid to have a Length = 0 , so we cannot check
  // the lenght for printing
  if( !Internal.empty() )
    {
    if( IsPrintable() )
      {
      // WARNING: Internal.end() != Internal.begin()+Length
      std::copy(Internal.begin(), Internal.begin()+Length,
        std::ostream_iterator<char>(os));
      }
    else
      os << "Loaded:" << Internal.size();
    }
  else
    {
    //os << "Not Loaded";
    os << "(no value available)";
    }
  }


private:
  std::vector<char> Internal;

  // WARNING Length IS NOT Internal.size() some *featured* DICOM
  // implementation define odd length, we always load them as even number
  // of byte, so we need to keep the right Length
  VL Length;
};

} // end namespace gdcm

#endif //__gdcmByteValue_h

