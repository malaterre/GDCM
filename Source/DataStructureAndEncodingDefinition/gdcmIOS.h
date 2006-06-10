
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
  IOS (std::streambuf *sb = NULL, SwapCode const &sc = SwapCode::Unknown);
  virtual ~IOS();

  operator void * ( ) const { assert(0); return 0; }

  std::streambuf *Rdbuf() const { return StreamBuf; }
  void Rdbuf(std::streambuf *sb);

//  std::streamsize GetWidth() const { return Width; }
//  void SetWidth(std::streamsize wide) { Width = wide; }

  SwapCode const &GetSwapCode() const { return SwapCodeValue; }
  void SetSwapCode(SwapCode const &sc) { SwapCodeValue = sc; }

private:
  std::streambuf *StreamBuf;
  // SwapCode of the file once figured out (can be Unknown)
  SwapCode SwapCodeValue;
//  std::streamsize Width;

  IOS(IOS const&);
  IOS &operator= (IOS const&);
};

}

#endif //__gdcmIOS_h

