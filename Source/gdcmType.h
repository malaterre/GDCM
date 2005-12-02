
#ifndef __gdcmType_h
#define __gdcmType_h

#include "gdcmConfigure.h"

#include "gdcmWin32.h"

//-----------------------------------------------------------------------------
#ifdef CMAKE_HAVE_STDINT_H
#include <stdint.h>
#else
#ifdef CMAKE_HAVE_INTTYPES_H
// Old system only have this
#include <inttypes.h>   // For uint8_t uint16_t and uint32_t
#else
// Broken plateforms do not respect C99 and do not provide those typedef
// Special case for recent Borland compiler, comes with stdint.h
#if defined(_MSC_VER) || defined(__BORLANDC__) && (__BORLANDC__ < 0x0560)  \
  || defined(__MINGW32__)
typedef  signed char         int8_t;
typedef  signed short        int16_t;
typedef  signed int          int32_t;
typedef  unsigned char       uint8_t;
typedef  unsigned short      uint16_t;
typedef  unsigned int        uint32_t;
#else
#error "Sorry your plateform is not supported"
#endif // defined(_MSC_VER) || defined(__BORLANDC__) && (__BORLANDC__ < 0x0560)  || defined(__MINGW32__)
#endif // CMAKE_HAVE_INTTYPES_H
#endif // CMAKE_HAVE_STDINT_H

// Basically for VS6 and bcc 5.5.1:
#ifndef UINT32_MAX
#define UINT32_MAX    (4294967295U)
#endif

namespace gdcm 
{
  class GDCM_EXPORT SC // SwapCode
    {
  public:
    typedef enum {
      Unknown         = 0,
      LittleEndian    = 1234,
      BigEndian       = 4321,
      BadLittleEndian = 3412,
      BadBigEndian    = 2143
    } SwapCodeType;
    };

} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif // __gdcmType_h
