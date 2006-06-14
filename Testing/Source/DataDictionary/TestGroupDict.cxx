#include "gdcmGroupDict.h"

#include <iostream>

int TestGroupDict(int , char *[])
{
  gdcm::GroupDict gd;
  std::cout << gd << std::endl;

  return 0;
}
