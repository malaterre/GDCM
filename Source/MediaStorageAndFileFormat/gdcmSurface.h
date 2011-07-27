/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMSURFACE_H
#define GDCMSURFACE_H

#include <gdcmObject.h>
#include <gdcmDataElement.h>
#include <gdcmMeshPrimitive.h>
#include "gdcmSegmentHelper.h"  // for BasicCodedEntry

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
  unsigned short GetRecommendedDisplayGrayscaleValue() const;
  void SetRecommendedDisplayGrayscaleValue(const unsigned short vl);

  const unsigned short * GetRecommendedDisplayCIELabValue() const;
  unsigned short GetRecommendedDisplayCIELabValue(const unsigned int idx) const;
  void SetRecommendedDisplayCIELabValue(const unsigned short vl[3]);
  void SetRecommendedDisplayCIELabValue(const unsigned short vl, const unsigned int idx = 0);
  void SetRecommendedDisplayCIELabValue(const std::vector< unsigned short > & vl);

  float GetRecommendedPresentationOpacity() const;
  void SetRecommendedPresentationOpacity(const float opacity);

  VIEWType GetRecommendedPresentationType() const;
  void SetRecommendedPresentationType(VIEWType type);

  unsigned long GetSurfaceNumber() const;
  void SetSurfaceNumber(const unsigned long nb);

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

  SegmentHelper::BasicCodedEntry const & GetAlgorithmFamily() const;
  SegmentHelper::BasicCodedEntry & GetAlgorithmFamily();
  void SetAlgorithmFamily(SegmentHelper::BasicCodedEntry const & BSE);

  const char * GetAlgorithmVersion() const;
  void SetAlgorithmVersion(const char * str);

  const char * GetAlgorithmName() const;
  void SetAlgorithmName(const char * str);

  //**    Points getters/setters      **//
  unsigned long GetNumberOfSurfacePoints() const;
  void SetNumberOfSurfacePoints(const unsigned long nb);

  const DataElement & GetPointCoordinatesData() const;
  DataElement & GetPointCoordinatesData();

  void SetPointCoordinatesData(DataElement const & de);

  //**    Vectors getters/setters      **//
  unsigned long GetNumberOfVectors() const;
  void SetNumberOfVectors(const unsigned long nb);

  unsigned long GetVectorDimensionality() const;
  void SetVectorDimensionality(const unsigned long dim);

  const DataElement & GetVectorCoordinateData() const;
  DataElement & GetVectorCoordinateData();

  void SetVectorCoordinateData(DataElement const & de);

  //**    Primitive getters/setters      **//
  const MeshPrimitive & GetMeshPrimitive() const;
  MeshPrimitive & GetMeshPrimitive();

  void SetMeshPrimitive(MeshPrimitive & mp);

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

  // Algorithm Family Code
  SegmentHelper::BasicCodedEntry AlgorithmFamily;

  //0066 0031 LO 1 Algorithm Version
  std::string     AlgorithmVersion;
  //0066 0032 LT 1 Algorithm Parameters
  //0066 0036 LO 1 Algorithm Name
  std::string     AlgorithmName;




  //**        Point members      **//
  //0066 0015 UL 1 Number of Surface Points
  unsigned long NumberOfSurfacePoints;
  //0066 0016 OF 1 Point Coordinates Data
  DataElement   PointCoordinatesData;


  //**        Normal members      **//
  //0066 001e UL 1 Number of Vectors
  unsigned long NumberOfVectors;
  //0066 001f US 1 Vector Dimensionality
  unsigned long VectorDimensionality;
  //0066 0021 OF 1 Vector Coordinate Data
  DataElement   VectorCoordinateData;


  //**        Primitive members      **//
  SmartPointer< MeshPrimitive > Primitive;

  //0066 0023 OW 1 Triangle Point Index List

  //0066 0024 OW 1 Edge Point Index List
  //0066 0025 OW 1 Vertex Point Index List
  //0066 0029 OW 1 Primitive Point Index List
};

}

#endif // GDCMSURFACE_H
