#include "gdcmElement.h"

#define TPI 3.1415926535897931

int TestFL()
{
  gdcm::Element<gdcm::VR::FL, gdcm::VM::VM1> a = { TPI };
  a.Print( std::cout );
  std::cout << std::endl;
  return 0;
}

int TestFD()
{
  gdcm::Element<gdcm::VR::FD, gdcm::VM::VM1> a = { TPI };
  std::ostringstream os;
  a.Print( os );
  const char *s = os.str().c_str();
  std::cout << s << std::endl;
  //double t = *reinterpret_cast<const double*>(*s);
  //std::cout << t << std::endl;

  return 0;
}

int TestElement(int , char *[])
{
  int r = 0;
  r += TestFL();
  r += TestFD();

  return r;
}

