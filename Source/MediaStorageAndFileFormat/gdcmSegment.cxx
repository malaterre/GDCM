#include "gdcmSegment.h"
#include "gdcmCodeString.h"

#include <cstring>

namespace gdcm
{

static const char * ALGOTypeStrings[] = {
  "MANUAL",
  "AUTOMATIC",

  0
};

const char * Segment::GetALGOTypeString(ALGOType type)
{
  assert( type <= ALGOType_END );
  return ALGOTypeStrings[(int)type];
}

Segment::ALGOType Segment::GetALGOType(const char * type)
{
  if(!type) return ALGOType_END;

  // Delete possible space as last character
  String<>  str( type );
  str.Trim();
  const char * strClear = str.Trim().c_str();

  for(unsigned int i = 0; ALGOTypeStrings[i] != 0; ++i)
    {
    if( strcmp(strClear, ALGOTypeStrings[i]) == 0 )
      {
      return (ALGOType)i;
      }
    }
  // Ouch ! We did not find anything, that's pretty bad, let's hope that
  // the toolkit which wrote the image is buggy and tolerate space padded binary
  // string
  CodeString codestring = strClear;
  std::string cs = codestring.GetAsString();
  for(unsigned int i = 0; ALGOTypeStrings[i] != 0; ++i)
    {
    if( strcmp(cs.c_str(), ALGOTypeStrings[i]) == 0 )
      {
      return (ALGOType)i;
      }
    }

  return ALGOType_END;
}

Segment::Segment():
  SegmentNumber(0),
  SegmentLabel(""),
//    SegmentDescription(),
  AnatomicRegion(),
  PropertyCategory(),
  PropertyType(),
  AlgorithmFamily(),
  SegmentAlgorithmType(ALGOType_END),
  SegmentAlgorithmName(""),
  SurfaceCount(0),
  AlgorithmVersion(""),
  AlgorithmName("")
{
}

Segment::~Segment()
{
}

const unsigned short Segment::GetSegmentNumber() const
{
  return SegmentNumber;
}

void Segment::SetSegmentNumber(const unsigned short num)
{
  SegmentNumber = num;
}

const char * Segment::GetSegmentLabel() const
{
  return SegmentLabel.c_str();
}

void Segment::SetSegmentLabel(const char * label)
{
  SegmentLabel = label;
}

Segment::BasicCodedEntry const & Segment::GetAnatomicRegion() const
{
  return AnatomicRegion;
}

void Segment::SetAnatomicRegion(BasicCodedEntry const & BSE)
{
  AnatomicRegion.CV   = BSE.CV;
  AnatomicRegion.CSD  = BSE.CSD;
  AnatomicRegion.CM   = BSE.CM;
}

Segment::BasicCodedEntry const & Segment::GetPropertyCategory() const
{
return PropertyCategory;
}

void Segment::SetPropertyCategory(BasicCodedEntry const & BSE)
{
  PropertyCategory.CV   = BSE.CV;
  PropertyCategory.CSD  = BSE.CSD;
  PropertyCategory.CM   = BSE.CM;
}

Segment::BasicCodedEntry const & Segment::GetPropertyType() const
{
return PropertyType;
}

void Segment::SetPropertyType(BasicCodedEntry const & BSE)
{
  PropertyType.CV   = BSE.CV;
  PropertyType.CSD  = BSE.CSD;
  PropertyType.CM   = BSE.CM;
}

Segment::BasicCodedEntry const & Segment::GetAlgorithmFamily() const
{
  return AlgorithmFamily;
}

void Segment::SetAlgorithmFamily(BasicCodedEntry const & BSE)
{
  AlgorithmFamily.CV   = BSE.CV;
  AlgorithmFamily.CSD  = BSE.CSD;
  AlgorithmFamily.CM   = BSE.CM;
}

Segment::ALGOType Segment::GetSegmentAlgorithmType() const
{
  return SegmentAlgorithmType;
}

void Segment::SetSegmentAlgorithmType(Segment::ALGOType type)
{
  assert(type <= ALGOType_END);
  SegmentAlgorithmType = type;
}

void Segment::SetSegmentAlgorithmType(const char * typeStr)
{
  SetSegmentAlgorithmType( GetALGOType(typeStr) );
}

const char * Segment::GetSegmentAlgorithmName() const
{
  return SegmentAlgorithmName.c_str();
}

void Segment::SetSegmentAlgorithmName(const char * name)
{
  SegmentAlgorithmName = name;
}

unsigned long Segment::GetSurfaceCount() const
{
  return SurfaceCount;
}

void Segment::SetSurfaceCount(const unsigned long nb)
{
  SurfaceCount = nb;
}

std::vector< SmartPointer< Surface > > Segment::GetSurfaces() const
{
  return Surfaces;
}

SmartPointer< Surface > Segment::GetSurface(const unsigned int idx /*= 0*/) const
{
  assert( idx < SurfaceCount );
  return Surfaces[idx];
}

void Segment::AddSurface(SmartPointer< Surface > surface)
{
  Surfaces.push_back(surface);
}

const char * Segment::GetAlgorithmVersion() const
{
  return AlgorithmVersion.c_str();
}

void Segment::SetAlgorithmVersion(const char * str)
{
  AlgorithmVersion = str;
}

const char * Segment::GetAlgorithmName() const
{
  return AlgorithmName.c_str();
}

void Segment::SetAlgorithmName(const char * str)
{
  AlgorithmName = str;
}

}
