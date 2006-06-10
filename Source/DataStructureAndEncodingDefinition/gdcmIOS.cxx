#include "gdcmIOS.h"

namespace gdcm
{

IOS::IOS(std::streambuf *sb, SwapCode const &sc):Sbuf(sb),SwapCodeValue(sc),Width(0)
{
}

IOS::~IOS()
{
}

void IOS::Rdbuf(std::streambuf *sb)
{
  Sbuf = sb;
}

} // end namespace gdcm
