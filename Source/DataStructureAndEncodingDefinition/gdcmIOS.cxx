#include "gdcmIOS.h"

namespace gdcm
{

IOS::IOS(SwapCode const &sc):SwapCodeValue(sc)
{
}

IOS::~IOS()
{
}

void IOS::Rdbuf(std::streambuf *sb)
{
  StreamBuf = sb;
}

} // end namespace gdcm
