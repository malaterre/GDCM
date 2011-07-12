#ifndef GDCMSEGMENT_H
#define GDCMSEGMENT_H

#include <vector>

#include <gdcmObject.h>
#include <gdcmSurface.h>

namespace gdcm
{

class GDCM_EXPORT Segment : public Object
{
public:

  struct BasicCodedEntry
  {
    BasicCodedEntry():
      CV(""),
      CSD(""),
      CM("")
    {}

    BasicCodedEntry(const char * a_CV, const char * a_CSD, const char * a_CM):
      CV(a_CV),
      CSD(a_CSD),
      CM(a_CM)
    {}

    std::string CV;  // Code Value
    std::string CSD; // Coding Scheme Designator
    std::string CM;  // Code Meaning
  };

  typedef enum {
    MANUAL = 0,
    AUTOMATIC,
    ALGOType_END
  } ALGOType;

  static const char * GetALGOTypeString(ALGOType type);
  static ALGOType GetALGOType(const char *str);


  Segment();

  virtual ~Segment();

  //**        Segment getters/setters     **//
  const unsigned short GetSegmentNumber() const;
  void SetSegmentNumber(const unsigned short num);

  const char * GetSegmentLabel() const;
  void SetSegmentLabel(const char * label);

  //    const char * GetSegmentDescription() const;	// Type 3

  BasicCodedEntry const & GetAnatomicRegion() const;
  void SetAnatomicRegion(BasicCodedEntry const & BSE);

  BasicCodedEntry const & GetPropertyCategory() const;
  void SetPropertyCategory(BasicCodedEntry const & BSE);

  BasicCodedEntry const & GetPropertyType() const;
  void SetPropertyType(BasicCodedEntry const & BSE);

  BasicCodedEntry const & GetAlgorithmFamily() const;
  void SetAlgorithmFamily(BasicCodedEntry const & BSE);

  ALGOType GetAlgorithmType() const;
  void SetAlgorithmType(ALGOType type);
  void SetAlgorithmType(const char * typeStr);

  const char * GetAlgorithmName() const;
  void SetAlgorithmName(const char * name);

  //**        Surface getters/setters     **//
  unsigned long GetSurfaceCount() const;
  void SetSurfaceCount(const unsigned long nb)
  {
    assert( nb );
    SurfaceCount = nb;
  }

  std::vector< SmartPointer< Surface > > GetSurfaces() const;
  SmartPointer< Surface > GetSurface(const unsigned int idx=0) const
  {
    assert( SurfaceCount );
    assert( idx < SurfaceCount );
    return Surfaces[idx];
  }

  void AddSurface(SmartPointer< Surface > surface)
  {
    Surfaces.push_back(surface);
  }

protected :
  //**        Segment members     **//
  //0062 0004 US 1 Segment Number
  unsigned short  SegmentNumber;
  //0062 0005 LO 1 Segment Label
  std::string     SegmentLabel;
  //0062 0006 ST 1 Segment Description
  //    std::string     SegmentDescription;

  // General Anatomic Region
  BasicCodedEntry AnatomicRegion;
  // Property Category Code
  BasicCodedEntry PropertyCategory;
  // Property Type Code
  BasicCodedEntry PropertyType;

  // Algorithm Family Code
  BasicCodedEntry AlgorithmFamily;

  //0062 0008 CS 1 Segment Algorithm Type
  ALGOType        SegmentAlgorithmType;
  //0062 0009 LO 1 Segment Algorithm Name
  std::string     SegmentAlgorithmName;

  //**        Surface members     **//
  //0066 002a UL 1 Surface Count
  unsigned long   SurfaceCount;

  std::vector< SmartPointer< Surface > > Surfaces;
};

}

#endif // GDCMSEGMENT_H
