#include "gdcmPersonName.h"
#include <sstream>

int TestPersonName(int argc, char *argv[])
{
  const char name[] = "Marc^Simon";
  std::cout << name << std::endl;

  gdcm::String s0;
  if ( !s0.empty() ) return 1;
  std::cout << "S0:" << s0 << std::endl;
  gdcm::String s1 = name;
  std::cout << "S1:" << s1 << std::endl;
  gdcm::String s2 ( name );
  std::cout << "S2:" << s2 << std::endl;

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
  std::cout << "PN4:" << pn4 << std::endl;
  //std::cout << "Bla" << std::endl;

  const char name2[] = "Marc^Simon\\Pierre^Dupont";
  std::istringstream is2;
  is2.str( name2 );
  //std::cout << "IS:" << is2.str() << std::endl;
  gdcm::PersonName pn5;
  is2 >> pn5;
  std::cout << "PN5:" << pn5 << std::endl;

  return 0;
}
