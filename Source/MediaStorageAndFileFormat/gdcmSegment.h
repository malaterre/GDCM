#ifndef GDCMSEGMENT_H
#define GDCMSEGMENT_H

#include <vector>

#include <gdcmObject.h>
#include <gdcmSurface.h>
#include "gdcmSegmentHelper.h"

namespace gdcm
{

class GDCM_EXPORT Segment : public Object
{
public:

  typedef std::vector< SmartPointer< Surface > > SurfaceVector;

  typedef enum {
    MANUAL = 0,
    AUTOMATIC,
    ALGOType_END
  } ALGOType;

  static const char * GetALGOTypeString(ALGOType type);
  static ALGOType GetALGOType(const char * type);


  Segment();

  virtual ~Segment();

  //**        Segment getters/setters     **//
  unsigned short GetSegmentNumber() const;
  void SetSegmentNumber(const unsigned short num);

  const char * GetSegmentLabel() const;
  void SetSegmentLabel(const char * label);

  //    const char * GetSegmentDescription() const;	// Type 3

  SegmentHelper::BasicCodedEntry const & GetAnatomicRegion() const;
  SegmentHelper::BasicCodedEntry & GetAnatomicRegion();
  void SetAnatomicRegion(SegmentHelper::BasicCodedEntry const & BSE);

  SegmentHelper::BasicCodedEntry const & GetPropertyCategory() const;
  SegmentHelper::BasicCodedEntry & GetPropertyCategory();
  void SetPropertyCategory(SegmentHelper::BasicCodedEntry const & BSE);

  SegmentHelper::BasicCodedEntry const & GetPropertyType() const;
  SegmentHelper::BasicCodedEntry & GetPropertyType();
  void SetPropertyType(SegmentHelper::BasicCodedEntry const & BSE);

  ALGOType GetSegmentAlgorithmType() const;
  void SetSegmentAlgorithmType(ALGOType type);
  void SetSegmentAlgorithmType(const char * typeStr);

  const char * GetSegmentAlgorithmName() const;
  void SetSegmentAlgorithmName(const char * name);

  //**        Surface getters/setters     **//
  unsigned long GetSurfaceCount() const;
  void SetSurfaceCount(const unsigned long nb);

  SurfaceVector const & GetSurfaces() const;
  SurfaceVector & GetSurfaces();
  SmartPointer< Surface > GetSurface(const unsigned int idx = 0) const;

  void AddSurface(SmartPointer< Surface > surface);

protected :
  //**        Segment members     **//
  //0062 0004 US 1 Segment Number
  unsigned short  SegmentNumber;
  //0062 0005 LO 1 Segment Label
  std::string     SegmentLabel;
  //0062 0006 ST 1 Segment Description
  //    std::string     SegmentDescription;

  // General Anatomic Region
  SegmentHelper::BasicCodedEntry AnatomicRegion;
  // Property Category Code
  SegmentHelper::BasicCodedEntry PropertyCategory;
  // Property Type Code
  SegmentHelper::BasicCodedEntry PropertyType;

  //0062 0008 CS 1 Segment Algorithm Type
  ALGOType        SegmentAlgorithmType;
  //0062 0009 LO 1 Segment Algorithm Name
  std::string     SegmentAlgorithmName;

  //**        Surface members     **//
  //0066 002a UL 1 Surface Count
  unsigned long   SurfaceCount;

  SurfaceVector   Surfaces;
};

}

#endif // GDCMSEGMENT_H
