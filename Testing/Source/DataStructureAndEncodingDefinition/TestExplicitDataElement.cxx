#include "gdcmExplicitDataElement.h"

#include <sstream>

int TestExplicitDataElement(int, char *[])
{
  const uint16_t group   = 0x0010;
  const uint16_t element = 0x0012;
  const char vr[]        = "UN";
  const uint16_t vr_pad  = 0x0;
  const uint32_t vl      = 0x0;
  //const char* val = 0;

  const char *str;
  std::stringstream ss;
  str = reinterpret_cast<const char*>(&group);
  ss.write(str, sizeof(group));
  str = reinterpret_cast<const char*>(&element);
  ss.write(str, sizeof(element));
  ss.write(vr, sizeof(vr));
  str = reinterpret_cast<const char*>(&vr_pad);
  ss.write(str, sizeof(vr_pad));
  str = reinterpret_cast<const char*>(&vl);
  ss.write(str, sizeof(vl));

  gdcm::ExplicitDataElement de;
  if( !de.Read(ss) )
    {
    return 1;
    }
  if( de.GetTag().GetGroup()   != group ||
      de.GetTag().GetElement() != element ||
      de.GetValueLength()      != vl )
    {
    std::cerr << de << std::endl;
    //return 1;
    }
  //std::cout << de << std::endl;

  return 0;
}
