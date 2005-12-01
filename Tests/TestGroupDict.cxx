#include "gdcmGroupDict.h"

int TestGroupDict(int , char *[])
{
  gdcm::GroupDict gd;
  std::cout << gd << std::endl;

  return 0;
}
