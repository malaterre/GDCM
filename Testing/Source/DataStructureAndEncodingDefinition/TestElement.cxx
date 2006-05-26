#include "gdcmElement.h"

int TestElement(int , char *[])
{
  gdcm::Element<gdcm::VR::FL, gdcm::VM::VM1> a = { 2 };
  a.Print( std::cout );
  std::cout << std::endl;

  return 0;
}
