#include "gdcmTagToType.h"
#include <iostream>

int TestTagToType(int, char *[])
{
  // Let's test a couple of them:
  gdcm::TagToType<0x0018,0x9219>::Type v1 = 0x8000;
  std::cout << v1 << std::endl;
  gdcm::TagToType<0x0028,0x0010>::Type v2 = 0x8000;
  std::cout << v2 << std::endl;
  gdcm::TagToType<0x0028,0x0011>::Type v3 = 0x8000;
  std::cout << v3 << std::endl;

  return 0;
}
