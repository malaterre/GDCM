#include "gdcmGroup.txx"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"

void TestGroupInstanciation()
{
  typedef gdcm::ExplicitDataElement DEType;
  gdcm::Group<DEType> g;
  DEType el;

  g.AddDataElement(el);
  g.SetGroupNumber( 2 );

  std::cout << el << std::endl;
  std::cout << g << std::endl;
  
  typedef gdcm::ImplicitDataElement DEType2;
  gdcm::Group<DEType2> g2;
  DEType2 el2;

  g2.AddDataElement(el2);
  g2.SetGroupNumber( 4 );

  std::cout << el2 << std::endl;
  std::cout << g2 << std::endl;
}

int TestGroup(int , char *[])
{
  TestGroupInstanciation();

  return 0;
}
