#include "gdcmStringStream.h"

#include <iostream>

int TestStringStream(int, char *[])
{
  gdcm::StringStream ss;
  ss << "GDCM";
  std::cout << ss.Str() << std::endl;

  return 0;
}
