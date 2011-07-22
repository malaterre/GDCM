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
  typedef std::vector< SmartPointer< Segment > >             SegmentVector;

  SegmentReader();

  virtual ~SegmentReader();

  /// Read
  virtual bool Read(); // Set to protected ?

  //**        Segment getters/setters     **//
//  const unsigned int GetNumberOfSegments() const;

  const SegmentVector GetSegments() const;
  SegmentVector GetSegments();

protected:

  typedef std::map< unsigned long, SmartPointer< Segment > > SegmentMap;

  bool ReadSegments();

  bool ReadSegment(const Item & segmentItem, const unsigned int idx);

//  const SegmentMap & GetSegmentMap() const;
//  SegmentMap & GetSegmentMap();

//  SegmentVector Segments;
  SegmentMap Segments;
};

}

#endif // GDCMSEGMENTREADER_H
