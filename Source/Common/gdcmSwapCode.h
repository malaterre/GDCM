#ifndef __gdcmSwapCode_h
#define __gdcmSwapCode_h

#include "gdcmTypes.h"

namespace gdcm 
{

/* \brief SwapCode class
 */
class GDCM_EXPORT SwapCode
{
public:
  typedef enum {
    Unknown         = 0,
    LittleEndian    = 1234,
    BigEndian       = 4321,
    BadLittleEndian = 3412,
    BadBigEndian    = 2143
  } SwapCodeType;

  operator SwapCode::SwapCodeType() const { return SwapCodeValue; }
  SwapCode(SwapCodeType sc = Unknown):SwapCodeValue(sc) { }
  static const char* GetSwapCodeString(SwapCode const & sc);

protected:
  static int GetIndex(SwapCode const & sc);

private:
  SwapCodeType SwapCodeValue;
};

} // end namespace gdcm

#endif
