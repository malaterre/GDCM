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

const MeshPrimitive::PrimitivesData & MeshPrimitive::GetPrimitivesData() const
{
  return PrimitiveData;
}

MeshPrimitive::PrimitivesData & MeshPrimitive::GetPrimitivesData()
{
  return PrimitiveData;
}

void MeshPrimitive::SetPrimitivesData(PrimitivesData const & DEs)
{
  PrimitiveData = DEs;
}

void MeshPrimitive::SetPrimitiveData(const unsigned int idx, DataElement const & de)
{
  assert( idx < this->GetNumberOfPrimitivesData() );
  PrimitiveData[idx] = de;
}

const DataElement & MeshPrimitive::GetPrimitiveData(const unsigned int idx) const
{
    assert( idx < this->GetNumberOfPrimitivesData() );
    return PrimitiveData[idx];
}
DataElement & MeshPrimitive::GetPrimitiveData(const unsigned int idx)
{
    assert( idx < this->GetNumberOfPrimitivesData() );
    return PrimitiveData[idx];
}

const unsigned int MeshPrimitive::GetNumberOfPrimitivesData() const
{
  return PrimitiveData.size();
}

}
