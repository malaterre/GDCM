#include "gdcmElement.h"

#define TPI 3.1415926535897931

int TestFL()
{
  gdcm::Element<gdcm::VR::FL, gdcm::VM::VM1> a = { TPI };
  a.Print( std::cout );
  std::cout << std::endl;

  gdcm::Element<gdcm::VR::FL, gdcm::VM::VM8> b = 
    { 0,1,2,3,4,5,6,7 };
  b.Print( std::cout );
  std::cout << std::endl;

  return 0;
}

int TestFD()
{
  gdcm::Element<gdcm::VR::FD, gdcm::VM::VM1> a = { TPI };
  std::ostringstream os;
  a.Print( os );
  std::string st = os.str(); // important
  const char *s = st.c_str();
  //double t = *reinterpret_cast<const double*>(*s);
  //std::cout << t << std::endl;

  gdcm::Element<gdcm::VR::FD, gdcm::VM::VM8> b = 
    { 0,1,2,3,4,5,6,7 };
  b.Print( std::cout );
  std::cout << std::endl;

  return 0;
}

int TestElement(int , char *[])
{
  int r = 0;
  r += TestFL();
  r += TestFD();

  return r;
}

