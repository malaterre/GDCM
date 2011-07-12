#include "gdcmSegmentReader.h"
#include "gdcmMediaStorage.h"
#include "gdcmAttribute.h"

namespace gdcm
{

SegmentReader::SegmentReader()
{
}

SegmentReader::~SegmentReader()
{
}

//const unsigned int SegmentReader::GetNumberOfSegments() const
//{
//  return Segments.size();
//}

//const SegmentReader::SegmentVector & SegmentReader::GetSegments() const
//{
//  return Segments;
//}

//SegmentReader::SegmentVector & SegmentReader::GetSegments()
//{
//  return Segments;
//}

const SegmentReader::SegmentMap & SegmentReader::GetSegments() const
{
  return Segments;
}

SegmentReader::SegmentMap & SegmentReader::GetSegments()
{
  return Segments;
}

bool SegmentReader::Read()
{
  if( !Reader::Read() )
  {
    return false;
  }

  const FileMetaInformation & header  = F->GetHeader();

  bool                        res     = false;

  MediaStorage                ms      = header.GetMediaStorage();
  if ( strncmp(ms.GetModality(), "SEG", 3) == 0 )
  {
    res = ReadSegments();
  }
  else
  {
    if( ms == MediaStorage::SegmentationStorage
     || ms == MediaStorage::SurfaceSegmentationStorage )
    {
      res = ReadSegments();
    }
    // else if ( found Segment Sequence ) ?
  }

  return res;
}

bool SegmentReader::ReadSegments()
{
  bool                        res     = false;

  const FileMetaInformation & header  = F->GetHeader();
  const DataSet &             ds      = F->GetDataSet();
  const TransferSyntax &      ts      = header.GetDataSetTransferSyntax();

  // Segment Sequence
  const Tag segmentSQTag(0x0062, 0x0002);
  if (ds.FindDataElement(segmentSQTag))
  {
    SmartPointer< SequenceOfItems > segmentSQ = ds.GetDataElement(segmentSQTag).GetValueAsSQ();

    const unsigned int numberOfSegments = segmentSQ->GetNumberOfItems();
    if ( numberOfSegments == 0)
      return false;

    for (unsigned int i = 1; i <= numberOfSegments; ++i)
    {
      if ( !ReadSegment( segmentSQ->GetItem(i), i ) )
      {
        gdcmWarningMacro( "Segment "<<i<<" reading error" );
      }
    }

    res = true;
  }

  return res;
}

bool SegmentReader::ReadSegment(const Item & segmentItem, const unsigned int idx)
{
  SmartPointer< Segment > segment = new Segment;

  const DataSet & segmentDS = segmentItem.GetNestedDataSet();

  // Segment Number
  Attribute<0x0062, 0x0004> segmentNumber;
  segmentNumber.SetFromDataSet( segmentDS );
  segment->SetSegmentNumber( segmentNumber.GetValue() );

  // Segment Label
  Attribute<0x0062, 0x0005> segmentLabel;
  segmentLabel.SetFromDataSet( segmentDS );
  segment->SetSegmentLabel( segmentLabel.GetValue() );

  // Segment Algorithm Type
  Attribute<0x0062, 0x0008> segmentAlgoType;
  segmentAlgoType.SetFromDataSet( segmentDS );
  segment->SetAlgorithmType( segmentAlgoType.GetValue() );

  // Surface Count
  Attribute<0x0066, 0x002A> surfaceCountAt;
  surfaceCountAt.SetFromDataSet( segmentDS );
  const unsigned long surfaceCount = surfaceCountAt.GetValue();
  segment->SetSurfaceCount( surfaceCount );

  // Referenced Surface Sequence
  const Tag refSurfaceSQTag(0x0066, 0x002B);
  if (segmentDS.FindDataElement(refSurfaceSQTag))
  {
    SmartPointer< SequenceOfItems > refSurfaceSQ = segmentDS.GetDataElement(refSurfaceSQTag).GetValueAsSQ();

    const unsigned int numberOfSurfaces = refSurfaceSQ->GetNumberOfItems();
    if ( (unsigned long) numberOfSurfaces != surfaceCount)
    {
        segment->SetSurfaceCount( numberOfSurfaces ); // Is it the right thing to do?
    }

    for (unsigned int i = 1; i <= numberOfSurfaces; ++i)
    {
      const DataSet & refSurfaceDS = refSurfaceSQ->GetItem(i).GetNestedDataSet();

      // Referenced Surface Number
      Attribute<0x0066, 0x002C> refSurfaceNumberAt;
      refSurfaceNumberAt.SetFromDataSet( refSurfaceDS );
      unsigned long refSurfaceNumber = idx;
      if ( !refSurfaceNumberAt.GetAsDataElement().IsEmpty() )
      {
        refSurfaceNumber = refSurfaceNumberAt.GetValue();
      }
      // Index the segment with its surface number
      Segments[refSurfaceNumber] = segment;
    }
  }
  else
  {
    if (surfaceCount > 0)
    {
      Segments[idx] = segment;
    }
    else
    { // If is not a surface segmentation storage

      // Segment Algorithm Name
      Attribute<0x0062, 0x0009> segmentAlgoName;
      segmentAlgoName.SetFromDataSet( segmentDS );
      segment->SetAlgorithmName( segmentAlgoName.GetValue() );
    }
  }

  return true;
}

}
