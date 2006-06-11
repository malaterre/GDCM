#include "gdcmStringStream.h"

#include <iostream>

int TestStringStream(int, char *[])
{
  gdcm::StringStream ss;
  const char s[] = "GDCM";
  ss.Write(s, strlen(s));
  std::cout << ss.Str() << std::endl;

  return 0;
}
