#include "gdcmImplicitDataElement.h"

#include <sstream>

int TestImplicitDataElement1(const uint16_t group,
                             const uint16_t element,
                             const uint32_t vl)
{
  const char *str;
  std::stringstream ss;
  str = reinterpret_cast<const char*>(&group);
  ss.write(str, sizeof(group));
  str = reinterpret_cast<const char*>(&element);
  ss.write(str, sizeof(element));
  str = reinterpret_cast<const char*>(&vl);
  ss.write(str, sizeof(vl));

  gdcm::ImplicitDataElement de;
  if( !de.Read(ss) )
    {
    std::cerr << de << std::endl;
    return 1;
    }
  if( de.GetTag().GetGroup()   != group ||
      de.GetTag().GetElement() != element ||
      de.GetValueLength()      != vl )
    {
    std::cerr << de << std::endl;
    return 1;
    }
  std::cout << de << std::endl;
  return 0;
}

int TestImplicitDataElement2(const uint16_t group,
                             const uint16_t element,
                             const char *value)
{
  const char *str;
  const uint32_t vl = strlen(value);
  std::stringstream ss;
  str = reinterpret_cast<const char*>(&group);
  ss.write(str, sizeof(group));
  str = reinterpret_cast<const char*>(&element);
  ss.write(str, sizeof(element));
  str = reinterpret_cast<const char*>(&vl);
  ss.write(str, sizeof(vl));
  str = value;
  ss.write(str, vl);

  gdcm::ImplicitDataElement de;
  if( !de.Read(ss) )
    {
    std::cerr << de << std::endl;
    return 1;
    }
  if( de.GetTag().GetGroup()   != group ||
      de.GetTag().GetElement() != element ||
      de.GetValueLength()      != vl )
    {
    std::cerr << de << std::endl;
    return 1;
    }
  std::cout << de << std::endl;
  return 0;
}

int TestImplicitDataElement(int, char *[])
{
  const uint16_t group   = 0x0010;
  const uint16_t element = 0x0012;
  const uint32_t vl      = 0x0;
  const char value[]     = "GDCM";
  int r = 0;
  r += TestImplicitDataElement1(group, element, vl);
  r += TestImplicitDataElement2(group, element, value);


  return r;
}
