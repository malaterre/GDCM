#include "gdcmExplicitDataElement.h"
#include "gdcmStringStream.h"

int TestExplicitDataElement1(const uint16_t group,
                             const uint16_t element,
                             const char* vr,
                             const uint32_t vl)
{
  const char *str;
  gdcm::StringStream ss;
  str = reinterpret_cast<const char*>(&group);
  ss.Write(str, sizeof(group));
  str = reinterpret_cast<const char*>(&element);
  ss.Write(str, sizeof(element));
  str = vr;
  ss.Write(str, 2);
  ss.Write("\0\0", 2);
  str = reinterpret_cast<const char*>(&vl);
  ss.Write(str, sizeof(vl));

  gdcm::ExplicitDataElement de;
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

int TestExplicitDataElement2(const uint16_t group,
                             const uint16_t element,
                             const char *vr,
                             const char *value)
{
  const char *str;
  const uint32_t vl = strlen(value);
  gdcm::StringStream ss;
  str = reinterpret_cast<const char*>(&group);
  ss.Write(str, sizeof(group));
  str = reinterpret_cast<const char*>(&element);
  ss.Write(str, sizeof(element));
  str = vr;
  ss.Write(str, 2);
  ss.Write("\0\0", 2);
  str = reinterpret_cast<const char*>(&vl);
  ss.Write(str, sizeof(vl));
  str = value;
  ss.Write(str, vl);

  gdcm::ExplicitDataElement de;
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

inline void WriteRead(gdcm::DataElement const &w, gdcm::DataElement &r)
{
  // w will be written
  // r will be read back
  gdcm::StringStream ss;
  w.Write(ss);
  r.Read(ss);
}

int TestExplicitDataElement(int, char *[])
{
  const uint16_t group   = 0x0010;
  const uint16_t element = 0x0012;
  const char vr[]        = "UN"; // UN => 4bytes vl
  const uint32_t vl      = 0x0; // 4 bytes
  const char value[]     = "GDCM";

  int r = 0;
  r += TestExplicitDataElement1(group, element, vr, vl);
  r += TestExplicitDataElement2(group, element, vr, value);

  gdcm::ExplicitDataElement de1(gdcm::Tag(0x1234, 0x5678), 0x4321);
  gdcm::ExplicitDataElement de2(gdcm::Tag(0x1234, 0x6789), 0x9876);
  WriteRead(de1, de2);
  if( !(de1 == de2) )
    {
    std::cerr << de1 << std::endl;
    std::cerr << de2 << std::endl;
    return 1;
    }

  return r;
}
