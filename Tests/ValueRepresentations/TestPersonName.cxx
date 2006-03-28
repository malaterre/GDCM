#include "gdcmPersonName.h"
#include <sstream>

int TestPersonName(int argc, char *argv[])
{
  const char name[] = "Marc^Simon";
  std::cout << name << std::endl;
  gdcm::PersonName pn1;
  std::cout << pn1 << std::endl;
  gdcm::PersonName pn2 = name;
  std::cout << pn2 << std::endl;
  gdcm::PersonName pn3(name);
  std::cout << pn3 << std::endl;

  std::istringstream is;
  is.str( name );
  gdcm::PersonName pn4;
  is >> pn4;
  std::cout << pn4 << std::endl;

  return 0;
}
