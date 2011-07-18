#include "gdcmMeshPrimitive.h"
#include "gdcmCodeString.h"

#include <cstring>

namespace gdcm
{

static const char * MPStrings[] = {
  "VERTEX",
  "EDGE",
  "TRIANGLE",
  "TRIANGLESTRIP",
  "TRIANGLEFAN",
  "LINE",
  "FACET",
  0
};

const char * MeshPrimitive::GetMPTypeString(const MPType type)
{
  assert( type <= MPType_END );
  return MPStrings[(int)type];
}

MeshPrimitive::MPType MeshPrimitive::GetMPType(const char * type)
{
  if(!type) return MPType_END;

  // Delete possible space as last character
  String<>  str( type );
  str.Trim();
  const char * typeClear = str.Trim().c_str();

  for(unsigned int i = 0; MPStrings[i] != 0; ++i)
  {
    if( strcmp(typeClear, MPStrings[i]) == 0 )
    {
      return (MPType)i;
    }
  }
  // Ouch ! We did not find anything, that's pretty bad, let's hope that
  // the toolkit which wrote the image is buggy and tolerate space padded binary
  // string
  CodeString  codestring  = typeClear;
  std::string cs          = codestring.GetAsString();
  for(unsigned int i = 0; MPStrings[i] != 0; ++i)
  {
    if( strcmp(cs.c_str(), MPStrings[i]) == 0 )
    {
      return (MPType)i;
    }
  }

  return MPType_END;
}

MeshPrimitive::MeshPrimitive():
  PrimitiveData(),
  PrimitiveType(MPType_END)
{

}

MeshPrimitive::~MeshPrimitive()
{

}

const DataElement & MeshPrimitive::GetPrimitiveData() const
{
  return PrimitiveData.front();
}

DataElement & MeshPrimitive::GetPrimitiveData()
{
  return PrimitiveData.front();
}

void MeshPrimitive::SetPrimitiveData(DataElement const & de)
{
  PrimitiveData.front() = de;
}

const ::std::vector< DataElement > & MeshPrimitive::GetPrimitivesData() const
{
  return PrimitiveData;
}

::std::vector< DataElement > & MeshPrimitive::GetPrimitivesData()
{
  return PrimitiveData;
}

void MeshPrimitive::SetPrimitivesData(::std::vector< DataElement > const & DEs)
{
  PrimitiveData = DEs;
}

}
