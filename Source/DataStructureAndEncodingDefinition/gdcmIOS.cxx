#include "gdcmIOS.h"

namespace gdcm
{

IOS::IOS(std::streambuf *sb, SwapCode const &sc):StreamBuf(sb),SwapCodeValue(sc),Width(0)
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
