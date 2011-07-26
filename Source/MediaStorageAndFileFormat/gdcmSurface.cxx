#include "gdcmSurface.h"
#include "gdcmCodeString.h"
#include "gdcmString.h"

#include <cstring>


namespace gdcm
{
static const char * STATESStrings[] = {
  "NO",
  "YES",
  "UNKNOWN",

  0
};

const char * Surface::GetSTATESString(STATES state)
{
  assert( state <= STATES_END );
  return STATESStrings[(int)state];
}

Surface::STATES Surface::GetSTATES(const char * state)
{
  if(!state) return STATES_END;

  // Delete possible space as last character
  String<>  str( state );
  str.Trim();
  const char * stateClear = str.Trim().c_str();

  for(unsigned int i = 0; STATESStrings[i] != 0; ++i)
  {
    if( strcmp(stateClear, STATESStrings[i]) == 0 )
    {
      return (STATES)i;
    }
  }
  // Ouch ! We did not find anything, that's pretty bad, let's hope that
  // the toolkit which wrote the image is buggy and tolerate space padded binary
  // string
  CodeString  codestring  = stateClear;
  std::string cs          = codestring.GetAsString();
  for(unsigned int i = 0; STATESStrings[i] != 0; ++i)
  {
    if( strcmp(cs.c_str(), STATESStrings[i]) == 0 )
    {
      return (STATES)i;
    }
  }

  return STATES_END;
}

static const char * VIEWStrings[] = {
  "SURFACE",
  "WIREFRAME",
  "POINTS",

  0
};

const char * Surface::GetVIEWTypeString(VIEWType type)
{
  assert( type <= VIEWType_END );
  return VIEWStrings[(int)type];
}

Surface::VIEWType Surface::GetVIEWType(const char * type)
{
  if(!type) return VIEWType_END;

  // Delete possible space as last character
  String<>  str( type );
  str.Trim();
  const char * typeClear = str.Trim().c_str();

  for(unsigned int i = 0; VIEWStrings[i] != 0; ++i)
  {
    if( strcmp(typeClear, VIEWStrings[i]) == 0 )
    {
      return (VIEWType)i;
    }
  }
  // Ouch ! We did not find anything, that's pretty bad, let's hope that
  // the toolkit which wrote the image is buggy and tolerate space padded binary
  // string
  CodeString  codestring  = typeClear;
  std::string cs          = codestring.GetAsString();
  for(unsigned int i = 0; VIEWStrings[i] != 0; ++i)
  {
    if( strcmp(cs.c_str(), VIEWStrings[i]) == 0 )
    {
      return (VIEWType)i;
    }
  }

  return VIEWType_END;
}

Surface::Surface():
  RecommendedDisplayGrayscaleValue(0),
  RecommendedPresentationOpacity(1),
  RecommendedPresentationType(SURFACE),
  SurfaceNumber(0),
  SurfaceComments(""),
  SurfaceProcessing(false),
  SurfaceProcessingRatio(1.),
  FiniteVolume(UNKNOWN),
  Manifold(UNKNOWN),
  AlgorithmFamily(),
  AlgorithmVersion(""),
  AlgorithmName(""),
  NumberOfSurfacePoints(0),
  PointCoordinatesData(),
  NumberOfVectors(0),
  VectorDimensionality(0),
  VectorCoordinateData(),
  Primitive(new MeshPrimitive)
{
  RecommendedDisplayCIELabValue[0] = 0;
  RecommendedDisplayCIELabValue[1] = 0;
  RecommendedDisplayCIELabValue[2] = 0;
}

Surface::~Surface()
{
}

const unsigned short Surface::GetRecommendedDisplayGrayscaleValue() const
{
  return RecommendedDisplayGrayscaleValue;
}

void Surface::SetRecommendedDisplayGrayscaleValue(const unsigned short vl)
{
  RecommendedDisplayGrayscaleValue = vl;
}

const unsigned short * Surface::GetRecommendedDisplayCIELabValue() const
{
  return &RecommendedDisplayCIELabValue[0];
}

const unsigned short Surface::GetRecommendedDisplayCIELabValue(const unsigned int idx) const
{
  assert( idx < 3 );
  return RecommendedDisplayCIELabValue[idx];
}

void Surface::SetRecommendedDisplayCIELabValue(const unsigned short vl[3])
{
  RecommendedDisplayCIELabValue[0] = vl[0];
  RecommendedDisplayCIELabValue[1] = vl[1];
  RecommendedDisplayCIELabValue[2] = vl[2];
}

void Surface::SetRecommendedDisplayCIELabValue(const unsigned short vl, const unsigned int idx/* = 0*/)
{
  assert( idx < 3 );
  RecommendedDisplayCIELabValue[idx] = vl;
}

void Surface::SetRecommendedDisplayCIELabValue(const std::vector< unsigned short > & vl)
{
  assert( vl.size() > 2 );

  RecommendedDisplayCIELabValue[0] = vl[0];
  RecommendedDisplayCIELabValue[1] = vl[1];
  RecommendedDisplayCIELabValue[2] = vl[2];
}

float Surface::GetRecommendedPresentationOpacity() const
{
  return RecommendedPresentationOpacity;
}

void Surface::SetRecommendedPresentationOpacity(float opacity)
{
  if( 0 <= opacity && opacity <= 1);
    RecommendedPresentationOpacity = opacity;
  //else keep default value : 1
}

Surface::VIEWType Surface::GetRecommendedPresentationType() const
{
  return RecommendedPresentationType;
}

void Surface::SetRecommendedPresentationType(VIEWType type)
{
  if( type < VIEWType_END);
    RecommendedPresentationType = type;
}

const unsigned long Surface::GetSurfaceNumber() const
{
  return SurfaceNumber;
}

void Surface::SetSurfaceNumber(const unsigned long nb)
{
  SurfaceNumber = nb;
}

const char * Surface::GetSurfaceComments() const
{
  return SurfaceComments.c_str();
}

void Surface::SetSurfaceComments(const char * comment)
{
  SurfaceComments = comment;
}

bool Surface::GetSurfaceProcessing() const
{
  return SurfaceProcessing;
}

void Surface::SetSurfaceProcessing(bool b)
{
  SurfaceProcessing = b;
}

float Surface::GetSurfaceProcessingRatio() const
{
  return SurfaceProcessingRatio;
}

void Surface::SetSurfaceProcessingRatio(const float ratio)
{
  SurfaceProcessingRatio = ratio;
}

Surface::STATES Surface::GetFiniteVolume() const
{
  return FiniteVolume;
}

void Surface::SetFiniteVolume(STATES state)
{
  assert( state < STATES_END );
  FiniteVolume = state;
}

Surface::STATES Surface::GetManifold() const
{
  return Manifold;
}

void Surface::SetManifold(STATES state)
{
  assert( state < STATES_END );
  Manifold = state;
}

SegmentHelper::BasicCodedEntry const & Surface::GetAlgorithmFamily() const
{
  return AlgorithmFamily;
}

SegmentHelper::BasicCodedEntry & Surface::GetAlgorithmFamily()
{
  return AlgorithmFamily;
}

void Surface::SetAlgorithmFamily(SegmentHelper::BasicCodedEntry const & BSE)
{
  AlgorithmFamily.CV   = BSE.CV;
  AlgorithmFamily.CSD  = BSE.CSD;
  AlgorithmFamily.CM   = BSE.CM;
}

const char * Surface::GetAlgorithmVersion() const
{
  return AlgorithmVersion.c_str();
}

void Surface::SetAlgorithmVersion(const char * str)
{
  AlgorithmVersion = str;
}

const char * Surface::GetAlgorithmName() const
{
  return AlgorithmName.c_str();
}

void Surface::SetAlgorithmName(const char * str)
{
  AlgorithmName = str;
}

unsigned long Surface::GetNumberOfSurfacePoints() const
{
  return NumberOfSurfacePoints;
}

void Surface::SetNumberOfSurfacePoints(const unsigned long nb)
{
  NumberOfSurfacePoints = nb;
}

const DataElement & Surface::GetPointCoordinatesData() const
{
  return PointCoordinatesData;
}

DataElement & Surface::GetPointCoordinatesData()
{
  return PointCoordinatesData;
}

void Surface::SetPointCoordinatesData(DataElement const & de)
{
  PointCoordinatesData = de;
}

unsigned long Surface::GetNumberOfVectors() const
{
  return NumberOfVectors;
}

void Surface::SetNumberOfVectors(const unsigned long nb)
{
  NumberOfVectors = nb;
}

unsigned long Surface::GetVectorDimensionality() const
{
  return VectorDimensionality;
}

void Surface::SetVectorDimensionality(const unsigned long dim)
{
  VectorDimensionality = dim;
}

const DataElement & Surface::GetVectorCoordinateData() const
{
  return VectorCoordinateData;
}

DataElement & Surface::GetVectorCoordinateData()
{
  return VectorCoordinateData;
}

void Surface::SetVectorCoordinateData(DataElement const & de)
{
  VectorCoordinateData = de;
}

const MeshPrimitive & Surface::GetMeshPrimitive() const
{
  return *Primitive;
}

MeshPrimitive & Surface::GetMeshPrimitive()
{
  return *Primitive;
}

void Surface::SetMeshPrimitive(MeshPrimitive & mp)
{
  Primitive = mp;
}

}
