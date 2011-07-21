#ifndef GDCMSURFACE_H
#define GDCMSURFACE_H

#include <gdcmObject.h>
#include <gdcmDataElement.h>
#include <gdcmMeshPrimitive.h>

namespace gdcm
{

class GDCM_EXPORT Surface : public Object
{
public:

  typedef enum {
    NO = 0,
    YES,
    UNKNOWN,
    STATES_END
  } STATES;

  static const char * GetSTATESString(STATES state);
  static STATES GetSTATES(const char * state);

  typedef enum {
    SURFACE = 0,
    WIREFRAME,
    POINTS,
    VIEWType_END
  } VIEWType;

  static const char * GetVIEWTypeString(VIEWType type);
  static VIEWType GetVIEWType(const char * type);

  Surface();

  virtual ~Surface();

  //**    Common getters/setters      **//
  const unsigned short GetRecommendedDisplayGrayscaleValue() const;
  void SetRecommendedDisplayGrayscaleValue(const unsigned short vl);

  const unsigned short * GetRecommendedDisplayCIELabValue() const;
  const unsigned short GetRecommendedDisplayCIELabValue(const unsigned int idx) const;
  void SetRecommendedDisplayCIELabValue(const unsigned short vl[3]);
  void SetRecommendedDisplayCIELabValue(const unsigned short vl, const unsigned int idx = 0);
  void SetRecommendedDisplayCIELabValue(const std::vector< unsigned short > & vl);

  float GetRecommendedPresentationOpacity() const;
  void SetRecommendedPresentationOpacity(const float opacity);

  VIEWType GetRecommendedPresentationType() const;
  void SetRecommendedPresentationType(VIEWType type);

  const unsigned long GetSurfaceNumber() const { return SurfaceNumber; }
  void SetSurfaceNumber(const unsigned long nb) { SurfaceNumber = nb; }

  const char * GetSurfaceComments() const;
  void SetSurfaceComments(const char * comment);

  bool GetSurfaceProcessing() const;
  void SetSurfaceProcessing(bool b);

  float GetSurfaceProcessingRatio() const;
  void SetSurfaceProcessingRatio(const float ratio);

  STATES GetFiniteVolume() const;
  void SetFiniteVolume(STATES state);

  STATES GetManifold() const;
  void SetManifold(STATES state);

  //**    Points getters/setters      **//
  unsigned long GetNumberOfSurfacePoints() const { return NumberOfSurfacePoints; }
  void SetNumberOfSurfacePoints(const unsigned long nb) { NumberOfSurfacePoints = nb; }

  const DataElement & GetPointCoordinatesData() const { return PointCoordinatesData; }
  DataElement & GetPointCoordinatesData() { return PointCoordinatesData; }

  void SetPointCoordinatesData(DataElement const & de) { PointCoordinatesData = de; }

  //**    Vectors getters/setters      **//
  unsigned long GetNumberOfVectors() const { return NumberOfVectors; }
  void SetNumberOfVectors(const unsigned long nb) { NumberOfVectors = nb; }

  unsigned long GetVectorDimensionality() const { return VectorDimensionality; }
  void SetVectorDimensionality(const unsigned long dim) { VectorDimensionality = dim; }

  const DataElement & GetVectorCoordinateData() const { return VectorCoordinateData; }
  DataElement & GetVectorCoordinateData() { return VectorCoordinateData; }

  void SetVectorCoordinateData(DataElement const & de) { VectorCoordinateData = de; }

  //**    Primitive getters/setters      **//
  const MeshPrimitive & GetMeshPrimitive() const { return *Primitive; }
  MeshPrimitive & GetMeshPrimitive() { return *Primitive; }

  void SetMeshPrimitive(MeshPrimitive & mp) { Primitive = mp; }

private:

  //**        Common members      **//
  //0062 000c US 1 Recommended Display Grayscale Value
  unsigned short  RecommendedDisplayGrayscaleValue;
  //0062 000d US 3 Recommended Display CIELab Value
  unsigned short  RecommendedDisplayCIELabValue[3];

  // 0066 000c FL 1 Recommended Presentation Opacity
  float           RecommendedPresentationOpacity;
  // 0066 000d CS 1 Recommended Presentation Type
  VIEWType        RecommendedPresentationType;

  //0066 0003 UL 1 Surface Number
  unsigned long SurfaceNumber;
  //0066 0004 LT 1 Surface Comments
  std::string   SurfaceComments;
  //0066 0009 CS 1 Surface Processing
  bool          SurfaceProcessing;
  //0066 000a FL 1 Surface Processing Ratio
  float         SurfaceProcessingRatio;
  //0066 000b LO 1 Surface Processing Description

  //0066 000e CS 1 Finite Volume
  STATES FiniteVolume;
  //0066 0010 CS 1 Manifold
  STATES Manifold;




  //**        Point members      **//
  //0066 0015 UL 1 Number of Surface Points
  unsigned long NumberOfSurfacePoints;
  //0066 0016 OF 1 Point Coordinates Data
  DataElement PointCoordinatesData;


  //**        Normal members      **//
  //0066 001e UL 1 Number of Vectors
  unsigned long NumberOfVectors;
  //0066 001f US 1 Vector Dimensionality
  unsigned long VectorDimensionality;
  //0066 0021 OF 1 Vector Coordinate Data
  DataElement VectorCoordinateData;


  //**        Primitive members      **//
  SmartPointer< MeshPrimitive > Primitive;

  //0066 0023 OW 1 Triangle Point Index List

  //0066 0024 OW 1 Edge Point Index List
  //0066 0025 OW 1 Vertex Point Index List
  //0066 0029 OW 1 Primitive Point Index List
};

}

#endif // GDCMSURFACE_H
