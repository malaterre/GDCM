
#ifndef __gdcmIOS_h
#define __gdcmIOS_h

#include "gdcmSwapCode.h"

#include <streambuf>

namespace gdcm
{

/**
 * \brief Wrapper around ios
 * \note bla
 */

class GDCM_EXPORT IOS
{
public:
  IOS (SwapCode const &sc = SwapCode::Unknown);
  virtual ~IOS();

  virtual operator void * ( ) const { assert(0); return 0; }

  SwapCode const &GetSwapCode() const { return SwapCodeValue; }
  void SetSwapCode(SwapCode const &sc) { SwapCodeValue = sc; }

private:
  // SwapCode of the file once figured out (can be Unknown)
  SwapCode SwapCodeValue;

  IOS(IOS const&);
  IOS &operator= (IOS const&);
};

}

#endif //__gdcmIOS_h

