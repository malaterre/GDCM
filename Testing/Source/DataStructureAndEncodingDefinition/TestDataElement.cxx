#include "gdcmDataElement.h"
#include "gdcmTag.h"
#include <sstream>
#include <fstream>

void WriteRead(gdcm::DataElement const &w, gdcm::DataElement &r)
{
  // w will be written
  // r will be read back
  std::stringstream ss;
  w.Write(ss);
  r.Read(ss);
}

// Test Data Element
int TestDataElement(int , char *[])
{
  const char *str;
  std::stringstream ss;
  const uint16_t group = 0x0010;
  const uint16_t element = 0x0012;

  // SimpleData Element, just group,element and length
  str = reinterpret_cast<const char*>(&group);
  ss.write(str, sizeof(group));
  str = reinterpret_cast<const char*>(&element);
  ss.write(str, sizeof(element));
  const uint16_t vl = 0x0;
  str = reinterpret_cast<const char*>(&vl);
  ss.write(str, sizeof(vl));

  gdcm::DataElement de;
  de.Read( ss );
  //std::cerr << de << std::endl;
  if( de.GetTag().GetGroup()   != group ||
      de.GetTag().GetElement() != element ||
      de.GetValueLength()      != vl )
    {
    return 1;
    }

  gdcm::DataElement de2;
  WriteRead(de, de2);
  if( !(de == de2) )
    {
    std::cerr << de << std::endl;
    std::cerr << de2 << std::endl;
    return 1;
    }

  // Full DataElement
  //const char value[] = "ABCDEFGHIJKLMNOP";
  //os << "AE";
  //os << value;

  //std::ofstream of("/tmp/bla.bin", std::ios::binary);
  //of.write(os.str().c_str(), os.str().size());
  //of.close();

  return 0;
}
