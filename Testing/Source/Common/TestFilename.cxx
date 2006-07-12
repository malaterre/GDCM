#include "gdcmFilename.h"

#include <iostream>

int TestFilename(int, char *[])
{
  gdcm::Filename f("/tmp/debug.dcm");
  std::cout << f.GetPath() << std::endl;
  std::cout << f.GetName() << std::endl;
  
  return 0;
}
