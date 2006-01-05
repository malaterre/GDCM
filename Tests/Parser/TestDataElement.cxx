#include "gdcmDataElement.h"
#include "gdcmDICOMIStream.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmTag.h"
#include <sstream>
#include <fstream>

// Test Data Element
int TestDataElement(int , char *[])
{
  std::ostringstream os;
  //const uint16_t group = 0x1234;
  //char *str = (char*)(&group);
  //os.write(str, sizeof(group));
  //const uint16_t element = 0x5678;
  //str = (char*)(&element);
  //os.write(str, sizeof(element));
  os << "AE";
  const uint16_t vl = 16;
  char *str = (char*)(&vl);
  os.write(str, sizeof(vl));
  const char value[] = "ABCDEFGHIJKLMNOP";
  os << value;

  std::ofstream of("/tmp/bla.bin", std::ios::binary);
  of.write(os.str().c_str(), os.str().size());
  of.close();

  gdcm::DICOMIStream is;
  is.SetFileName("/tmp/bla.bin");
  is.Open();
  gdcm::ExplicitDataElement de;
  is >> de;
  is.Close();

  std::cout << de << std::endl;

  gdcm::DICOMOStream Os;
  Os.SetFileName("/tmp/bla2.bin");
  Os.Open();
  Os << de;
  Os.Close();

  return 0;
}
