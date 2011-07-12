#ifndef GDCMSEGMENTWRITER_H
#define GDCMSEGMENTWRITER_H

#include <gdcmWriter.h>
#include <gdcmSegment.h>

namespace gdcm
{

class GDCM_EXPORT SegmentWriter : public Writer
{
public:
  typedef std::vector< SmartPointer< Segment > > SegmentVector;

  SegmentWriter();

  virtual ~SegmentWriter();

  /// Write
  bool Write(); // Set to protected ?

  //**        Segment getters/setters     **//
  const unsigned int GetNumberOfSegments() const { return Segments.size(); }
  void SetNumberOfSegments(const unsigned int size) { Segments.resize(size); }

  const SegmentVector & GetSegments() const { return Segments; }
  SegmentVector & GetSegments() { return Segments; }
  SmartPointer< Segment > GetSegment(const unsigned int idx=0) const
  {
    assert( idx < Segments.size() );
    return Segments[idx];
  }
  void AddSegment(SmartPointer< Segment > segment)
  {
    Segments.push_back(segment);
  }

protected:

  bool PrepareWrite();


  SegmentVector Segments;
};

}

#endif // GDCMSEGMENTWRITER_H
