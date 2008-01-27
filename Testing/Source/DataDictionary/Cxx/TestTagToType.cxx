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

  // Make sure the group length works too:
  gdcm::TagToType<0x0009,0x0000>::Type l1 = 0xF0000000;
  std::cout << l1 << std::endl;
  gdcm::TagToType<0x0010,0x0000>::Type l2 = 0xF0000000;
  std::cout << l2 << std::endl;
  gdcm::TagToType<0x1234,0x0000>::Type l3 = 0xF0000000;
  std::cout << l3 << std::endl;

  return 0;
}
