
#ifndef __gdcmIOS_h
#define __gdcmIOS_h

#include "gdcmIOSBase.h"
#include "gdcmSwapCode.h"

#include <fstream>

namespace gdcm
{

/**
 * \brief Wrapper around ios
 * \note bla
 */

class GDCM_EXPORT IOS : public IOSBase
{
public:
  IOS () {}
  ~IOS() {}

  SwapCode const &GetSwapCode() const { return SwapCodeValue; }

protected:
  // SwapCode of the file once figured out (can be Unknown)
  SwapCode SwapCodeValue;
};

}

#endif //__gdcmIOS_h

