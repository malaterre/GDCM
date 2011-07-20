#ifndef GDCMSEGMENTREADER_H
#define GDCMSEGMENTREADER_H

#include <map>

#include <gdcmReader.h>
#include <gdcmSegment.h>

namespace gdcm
{

class GDCM_EXPORT SegmentReader : public Reader
{
public:
//  typedef std::vector< SmartPointer< Segment > > SegmentVector;
  typedef std::map< unsigned long, SmartPointer< Segment > > SegmentMap;

  SegmentReader();

  virtual ~SegmentReader();

  /// Read
  virtual bool Read(); // Set to protected ?

  //**        Segment getters/setters     **//
//  const unsigned int GetNumberOfSegments() const;

//  const SegmentVector & GetSegments() const;
//  SegmentVector & GetSegments();

  const SegmentMap & GetSegments() const;
  SegmentMap & GetSegments();

protected:

  bool ReadSegments();

  bool ReadSegment(const Item & segmentItem, const unsigned int idx);

//  SegmentVector Segments;
  SegmentMap Segments;
};

}

#endif // GDCMSEGMENTREADER_H
