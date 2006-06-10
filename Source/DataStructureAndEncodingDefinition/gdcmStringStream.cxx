#include "gdcmStringStream.h"

namespace gdcm
{
StringStream::StringStream()
{
}

StringStream::StringStream(const std::string &str)
{
  InternalSStream.str(str);
}

} // end namespace gdcm
