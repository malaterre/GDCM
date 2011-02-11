/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmDataElement.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmTag.h"

#include "gdcmSwapper.h"

#include <fstream>

inline void DebugElement(std::stringstream const &os)
{
  std::ofstream of("/tmp/bla.bin", std::ios::binary);
  const char *s = os.str().c_str();
  int size = os.str().size();
  of.write(s, size);
  of.close();
}


inline void WriteRead(gdcm::DataElement const &w, gdcm::DataElement &r)
{
  // w will be written
  // r will be read back
  std::stringstream ss;
  w.Write<gdcm::SwapperNoOp>(ss);
  r.Read<gdcm::SwapperNoOp>(ss);
}

int TestDataElement1(const uint16_t group, const uint16_t element,
  const uint16_t vl)
{
  const char *str;
  std::stringstream ss;
  // SimpleData Element, just group,element and length
  str = reinterpret_cast<const char*>(&group);
  ss.write(str, sizeof(group));
  str = reinterpret_cast<const char*>(&element);
  ss.write(str, sizeof(element));
  str = reinterpret_cast<const char*>(&vl);
  ss.write(str, sizeof(vl));

//  gdcm::DataElement de;
//  de.Read( ss );
//  if( de.GetTag().GetGroup()   != group ||
//      de.GetTag().GetElement() != element ||
//      de.GetVL()               != vl )
//    {
//    std::cerr << de << std::endl;
//    return 1;
//    }
//
//  gdcm::DataElement de2;
//  WriteRead(de, de2);
//  if( !(de == de2) )
//    {
//    std::cerr << de << std::endl;
//    std::cerr << de2 << std::endl;
//    return 1;
//    }

  return 0;
}

// Explicit
int TestDataElement2(const uint16_t group, const uint16_t element,
  const char* vr, const char* value)
{
  const char *str;
  const uint32_t vl = strlen( value );
  std::stringstream ss;
  // SimpleData Element, just group,element and length
  str = reinterpret_cast<const char*>(&group);
  ss.write(str, sizeof(group));
  str = reinterpret_cast<const char*>(&element);
  ss.write(str, sizeof(element));
  if( gdcm::VR::GetVRType(vr) == gdcm::VR::INVALID )
    {
    std::cerr << "Test buggy" << std::endl;
    return 1;
    }
  ss.write(vr, strlen(vr) );
  str = reinterpret_cast<const char*>(&vl);
  ss.write(str, sizeof(vl));
  assert( !(strlen(value) % 2) );
  ss.write(value, strlen(value) );
  //DebugElement(ss);

  gdcm::ExplicitDataElement de;
  de.Read<gdcm::SwapperNoOp>( ss );
  if( de.GetTag().GetGroup()   != group ||
      de.GetTag().GetElement() != element ||
      de.GetVL()               != vl )
    {
    std::cerr << de << std::endl;
    return 1;
    }

  gdcm::ExplicitDataElement de2;
  WriteRead(de, de2);
  if( !(de == de2) )
    {
    std::cerr << de << std::endl;
    std::cerr << de2 << std::endl;
    return 1;
    }

  return 0;
}

// Test Data Element
int TestDataElement(int , char *[])
{
  const uint16_t group = 0x0010;
  const uint16_t element = 0x0012;
  const uint16_t vl = 0x0;
  int r = 0;
  r += TestDataElement1(group, element, vl);

  // Full DataElement
  //const char vr[] = "UN";
  //const char value[] = "ABCDEFGHIJKLMNOP";
  //r += TestDataElement2(group, element, vr, value);

  return r;
}
