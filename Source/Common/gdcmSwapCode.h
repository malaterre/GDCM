#ifndef __gdcmSwapCode_h
#define __gdcmSwapCode_h

#include "gdcmTypes.h"

namespace gdcm 
{

/* \brief SwapCode class
 */
class GDCM_EXPORT SC
{
public:
  typedef enum {
    Unknown         = 0,
    LittleEndian    = 1234,
    BigEndian       = 4321,
    BadLittleEndian = 3412,
    BadBigEndian    = 2143
  } SwapCodeType;

  static const char* GetSwapCodeString(SwapCodeType sc);

protected:
  static int GetIndex(SwapCodeType sc);
};

} // end namespace gdcm

#endif
