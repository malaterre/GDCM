#include "gdcmSegmentReader.h"
#include "gdcmMediaStorage.h"
#include "gdcmAttribute.h"
#include "gdcmString.h"

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

const SegmentReader::SegmentVector SegmentReader::GetSegments() const
{
  return GetSegments();
}

SegmentReader::SegmentVector SegmentReader::GetSegments()
{
  SegmentVector res;

  SegmentMap::const_iterator itMap    = Segments.begin();
  SegmentMap::const_iterator itMapEnd = Segments.end();

  res.push_back(itMap->second);
  itMap++;

  SegmentVector::const_iterator itVec    = res.begin();
  SegmentVector::const_iterator itVecEnd = res.end();
  for (; itMap != itMapEnd; itMap++)
  {
    while (itVec != itVecEnd && itMap->second != *itVec)
      itVec++;
    if (itVec == itVecEnd)
      res.push_back(itMap->second);
  }

  return res;
}

//const SegmentReader::SegmentMap & SegmentReader::GetSegments() const
//{
//  return Segments;
//}

//SegmentReader::SegmentMap & SegmentReader::GetSegments()
//{
//  return Segments;
//}

bool SegmentReader::Read()
{
  bool res = false;

  // Read a file
  if( !Reader::Read() )
  {
    return res;
  }

  // Set Segments from file
  const FileMetaInformation & header  = F->GetHeader();
  MediaStorage                ms      = header.GetMediaStorage();

  // Check modality
  const char * modality = ms.GetModality();
  if (modality != 0)
  {
    String<>     modality( ms.GetModality() );

    if ( modality.Trim() == "SEG" )
    {
      res = ReadSegments();
    }
  }
  else if( ms == MediaStorage::SegmentationStorage
        || ms == MediaStorage::SurfaceSegmentationStorage )
  {
    res = ReadSegments();
  }
  else
  {
    // Try to find Segment Sequence
    const DataSet & dsRoot = F->GetDataSet();
    if (dsRoot.FindDataElement( Tag(0x0062, 0x0002) ))
    {
      res = ReadSegments();
    }
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
    {
      gdcmErrorMacro( "No segment found" );
      return false;
    }

    for (unsigned int i = 1; i <= numberOfSegments; ++i)
    {
      if ( !ReadSegment( segmentSQ->GetItem(i), i ) )
      {
        gdcmWarningMacro( "Segment "<<i<<" reading error" );
        // return false?
      }
    }

    res = true;
  }

  return res;
}

bool SegmentReader::ReadSegment(const Item & segmentItem, const unsigned int idx)
{
  SmartPointer< Segment > segment   = new Segment;

  const DataSet &         segmentDS = segmentItem.GetNestedDataSet();

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
  segment->SetSegmentAlgorithmType( segmentAlgoType.GetValue() );

  // Surface Count
  Attribute<0x0066, 0x002A> surfaceCountAt;
  surfaceCountAt.SetFromDataSet( segmentDS );
  const unsigned long surfaceCount = surfaceCountAt.GetValue();
  segment->SetSurfaceCount( surfaceCount );

  // Check if there is a Surface Segmentation Module
  if (surfaceCount > 0)
  {
    //*****   GENERAL ANATOMY MANDATORY MACRO ATTRIBUTES   *****//
    // Anatomic Region Sequence (0008,2218) Type 1
    if( !segmentDS.FindDataElement( Tag(0x0008, 0x2218) ) )
    {
      SmartPointer<SequenceOfItems> anatRegSQ = segmentDS.GetDataElement( Tag(0x0008, 0x2218) ).GetValueAsSQ();

      if (anatRegSQ->GetNumberOfItems() > 0)  // Only one item is a type 1
      {
        const Item &    anatRegItem = anatRegSQ->GetItem(1);
        const DataSet & anatRegDS   = anatRegItem.GetNestedDataSet();

        //*****   CODE SEQUENCE MACRO ATTRIBUTES   *****//
        Segment::BasicCodedEntry & anatReg = segment->GetAnatomicRegion();

        // Code Value (Type 1)
        Attribute<0x0008, 0x0100> codeValueAt;
        codeValueAt.SetFromDataSet( anatRegDS );
        anatReg.CV = codeValueAt.GetValue();

        // Coding Scheme (Type 1)
        Attribute<0x0008, 0x0102> codingSchemeAt;
        codingSchemeAt.SetFromDataSet( anatRegDS );
        anatReg.CSD = codeValueAt.GetValue();

        // Code Meaning (Type 1)
        Attribute<0x0008, 0x0104> codeMeaningAt;
        codeMeaningAt.SetFromDataSet( anatRegDS );
        anatReg.CM = codeValueAt.GetValue();
      }
    }
    // else assert? return false? gdcmWarning?

    //*****   Segmented Property Category Code Sequence   *****//
    // Segmented Property Category Code Sequence (0062,0003) Type 1
    if( !segmentDS.FindDataElement( Tag(0x0062, 0x0003) ) )
    {
      SmartPointer<SequenceOfItems> propCatSQ = segmentDS.GetDataElement( Tag(0x0062, 0x0003) ).GetValueAsSQ();

      if (propCatSQ->GetNumberOfItems() > 0)  // Only one item is a type 1
      {
        const Item &    propCatItem = propCatSQ->GetItem(1);
        const DataSet & propCatDS   = propCatItem.GetNestedDataSet();

        //*****   CODE SEQUENCE MACRO ATTRIBUTES   *****//
        Segment::BasicCodedEntry & propCat = segment->GetPropertyCategory();

        // Code Value (Type 1)
        Attribute<0x0008, 0x0100> codeValueAt;
        codeValueAt.SetFromDataSet( propCatDS );
        propCat.CV = codeValueAt.GetValue();

        // Coding Scheme (Type 1)
        Attribute<0x0008, 0x0102> codingSchemeAt;
        codingSchemeAt.SetFromDataSet( propCatDS );
        propCat.CSD = codeValueAt.GetValue();

        // Code Meaning (Type 1)
        Attribute<0x0008, 0x0104> codeMeaningAt;
        codeMeaningAt.SetFromDataSet( propCatDS );
        propCat.CM = codeValueAt.GetValue();
      }
    }
    // else assert? return false? gdcmWarning?

    //*****   Segmented Property Type Code Sequence   *****//
    // Segmented Property Type Code Sequence (0062,000F) Type 1
    if( !segmentDS.FindDataElement( Tag(0x0062, 0x000F) ) )
    {
      SmartPointer<SequenceOfItems> propTypSQ = segmentDS.GetDataElement( Tag(0x0062, 0x000F) ).GetValueAsSQ();

      if (propTypSQ->GetNumberOfItems() > 0)  // Only one item is a type 1
      {
        const Item &    propTypItem = propTypSQ->GetItem(1);
        const DataSet & propTypDS   = propTypItem.GetNestedDataSet();

        //*****   CODE SEQUENCE MACRO ATTRIBUTES   *****//
        Segment::BasicCodedEntry & propTyp = segment->GetPropertyType();

        // Code Value (Type 1)
        Attribute<0x0008, 0x0100> codeValueAt;
        codeValueAt.SetFromDataSet( propTypDS );
        propTyp.CV = codeValueAt.GetValue();

        // Coding Scheme (Type 1)
        Attribute<0x0008, 0x0102> codingSchemeAt;
        codingSchemeAt.SetFromDataSet( propTypDS );
        propTyp.CSD = codeValueAt.GetValue();

        // Code Meaning (Type 1)
        Attribute<0x0008, 0x0104> codeMeaningAt;
        codeMeaningAt.SetFromDataSet( propTypDS );
        propTyp.CM = codeValueAt.GetValue();
      }
    }
    // else assert? return false? gdcmWarning?

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

      // Index each surface of a segment
      for (unsigned int i = 1; i <= numberOfSurfaces; ++i)
      {
        const DataSet & refSurfaceDS = refSurfaceSQ->GetItem(i).GetNestedDataSet();

        // Referenced Surface Number
        Attribute<0x0066, 0x002C> refSurfaceNumberAt;
        refSurfaceNumberAt.SetFromDataSet( refSurfaceDS );
        unsigned long             refSurfaceNumber;
        if ( !refSurfaceNumberAt.GetAsDataElement().IsEmpty() )
        {
          refSurfaceNumber = refSurfaceNumberAt.GetValue();
        }
        else
        {
          refSurfaceNumber = idx;
        }
        // Index the segment with its referenced surface number
        Segments[refSurfaceNumber] = segment;

        // Algorithm Version
        Attribute<0x0066, 0x0031> algoVersionAt;
        algoVersionAt.SetFromDataSet( refSurfaceDS );
        segment->SetAlgorithmVersion( algoVersionAt.GetValue() );

        // Algorithm Name
        Attribute<0x0066, 0x0036> algoNameAt;
        algoNameAt.SetFromDataSet( refSurfaceDS );
        segment->SetAlgorithmName( algoNameAt.GetValue() );
      }
    }
    else
    {// Index the segment with item number
      Segments[idx] = segment;
    }
  }
  else
  { // If is not a surface segmentation storage

    // Segment Algorithm Name
    Attribute<0x0062, 0x0009> segmentAlgoName;
    segmentAlgoName.SetFromDataSet( segmentDS );
    segment->SetAlgorithmName( segmentAlgoName.GetValue() );
  }

  return true;
}

}
