#include "gdcmDataElement.h"
#include "gdcmIStream.h"
#include "gdcmExplicitDataElement.h"
#include <sstream>
#include <fstream>

// Test Data Element
int TestDataElement(int , char *[])
{
  std::ostringstream os;
  os << "AE";
  const uint16_t vl = 16;
  char *vl_str = (char*)(&vl);
  os.write(vl_str, sizeof(vl));
  const char value[] = "ABCDEFGHIJKLMNOP";
  os << value;

  std::ofstream of("/tmp/bla.bin", std::ios::binary);
  of.write(os.str().c_str(), os.str().size());
  of.close();

  gdcm::IStream is;
  is.SetFileName("/tmp/bla.bin");
  is.Open();
  gdcm::ExplicitDataElement de;
  is >> de;
  is.Close();

  std::cout << de << std::endl;

  gdcm::OStream Os;
  Os.SetFileName("/tmp/bla2.bin");
  Os.Open();
  Os << de;
  Os.Close();

  return 0;
}
