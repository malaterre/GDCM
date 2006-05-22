#include "gdcmDataElement.h"
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
  const char value[] = "ABCDEFGHIJKLMNOP";
  const uint16_t vl = strlen(value);
  char *str = (char*)(&vl);
  os.write(str, sizeof(vl));
  os << value;

  std::ofstream of("/tmp/bla.bin", std::ios::binary);
  of.write(os.str().c_str(), os.str().size());
  of.close();

  return 0;
}
