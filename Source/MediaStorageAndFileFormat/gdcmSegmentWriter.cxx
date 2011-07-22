#include "gdcmSegmentWriter.h"
#include "gdcmAttribute.h"

namespace gdcm
{

SegmentWriter::SegmentWriter()
{
}

SegmentWriter::~SegmentWriter()
{
}

const unsigned int SegmentWriter::GetNumberOfSegments() const
{
  return Segments.size();
}

void SegmentWriter::SetNumberOfSegments(const unsigned int size)
{
  Segments.resize(size);
}

const SegmentWriter::SegmentVector & SegmentWriter::GetSegments() const
{
  return Segments;
}

SegmentWriter::SegmentVector & SegmentWriter::GetSegments()
{
  return Segments;
}

SmartPointer< Segment > SegmentWriter::GetSegment(const unsigned int idx /*= 0*/) const
{
  assert( idx < Segments.size() );
  return Segments[idx];
}

void SegmentWriter::AddSegment(SmartPointer< Segment > segment)
{
  Segments.push_back(segment);
}

void SegmentWriter::SetSegments(SegmentVector & segments)
{
  Segments = segments;
}

bool SegmentWriter::PrepareWrite()
{
  File &      file    = GetFile();
  DataSet &   ds      = file.GetDataSet();

  // Segment Sequence
  SmartPointer<SequenceOfItems> segmentsSQ;
  if( !ds.FindDataElement( Tag(0x0062, 0x0002) ) )
  {
    segmentsSQ = new SequenceOfItems;
    DataElement detmp( Tag(0x0062, 0x0002) );
    detmp.SetVR( VR::SQ );
    detmp.SetValue( *segmentsSQ );
    detmp.SetVLToUndefined();
    ds.Insert( detmp );
  }
  segmentsSQ = ds.GetDataElement( Tag(0x0062, 0x0002) ).GetValueAsSQ();
  segmentsSQ->SetLengthToUndefined();

  // Fill the Segment Sequence
  const unsigned int              numberOfSegments  = this->GetNumberOfSegments();
  const unsigned int              nbItems           = segmentsSQ->GetNumberOfItems();
  if (nbItems < numberOfSegments)
  {
    const unsigned int diff           = numberOfSegments - nbItems;
    const unsigned int nbOfItemToMake = (diff > 0?diff:0);
    for(unsigned int i = 1; i <= nbOfItemToMake; ++i)
    {
      Item item;
      item.SetVLToUndefined();
      segmentsSQ->AddItem(item);
    }
  }
  // else Should I remove items?

  std::vector< SmartPointer< Segment > >::const_iterator  it    = Segments.begin();
  std::vector< SmartPointer< Segment > >::const_iterator  itEnd = Segments.end();
  unsigned int                                            i     = 1;
  for (; it != itEnd; it++)
  {
    SmartPointer< Segment > segment = *it;
    assert( segment );

    Item &    segmentItem = segmentsSQ->GetItem(i++);
    DataSet & segmentDS   = segmentItem.GetNestedDataSet();

    // Segment Number
    Attribute<0x0062, 0x0004> segmentNumber;
    segmentNumber.SetValue( segment->GetSegmentNumber() );
    segmentDS.Replace( segmentNumber.GetAsDataElement() );

    // Segment Label
    Attribute<0x0062, 0x0005> segmentLabel;
    segmentLabel.SetValue( segment->GetSegmentLabel() );
    segmentDS.Replace( segmentLabel.GetAsDataElement() );

    // Segment Algorithm Type
    Attribute<0x0062, 0x0008> segmentAlgorithmType;
    segmentAlgorithmType.SetValue( Segment::GetALGOTypeString( segment->GetSegmentAlgorithmType() ) );
    segmentDS.Replace( segmentAlgorithmType.GetAsDataElement() );

    //*****   GENERAL ANATOMY MANDATORY MACRO ATTRIBUTES   *****//
    {
      // Anatomic Region Sequence (0008,2218) Type 1
      SmartPointer<SequenceOfItems> anatRegSQ;
      const Tag anatRegSQTag(0x0008, 0x2218);
      if( !segmentDS.FindDataElement( anatRegSQTag ) )
      {
        anatRegSQ = new SequenceOfItems;
        DataElement detmp( anatRegSQTag );
        detmp.SetVR( VR::SQ );
        detmp.SetValue( *anatRegSQ );
        detmp.SetVLToUndefined();
        segmentDS.Insert( detmp );
      }
      anatRegSQ = segmentDS.GetDataElement( anatRegSQTag ).GetValueAsSQ();
      anatRegSQ->SetLengthToUndefined();

      // Fill the Anatomic Region Sequence
      const unsigned int nbItems = anatRegSQ->GetNumberOfItems();
      if (nbItems < 1)  // Only one item is a type 1
      {
        Item item;
        item.SetVLToUndefined();
        anatRegSQ->AddItem(item);
      }

      Item &    anatRegItem = anatRegSQ->GetItem(1);
      DataSet & anatRegDS   = anatRegItem.GetNestedDataSet();

      //*****   CODE SEQUENCE MACRO ATTRIBUTES   *****//
      {
        const Segment::BasicCodedEntry & anatReg = segment->GetAnatomicRegion();

        // Code Value
        Attribute<0x0008, 0x0100> codeValueAt;
        codeValueAt.SetValue( anatReg.CV );
        anatRegDS.Replace( codeValueAt.GetAsDataElement() );

        // Coding Scheme
        Attribute<0x0008, 0x0102> codingSchemeAt;
        codingSchemeAt.SetValue( anatReg.CSD );
        anatRegDS.Replace( codingSchemeAt.GetAsDataElement() );

        // Code Meaning
        Attribute<0x0008, 0x0104> codeMeaningAt;
        codeMeaningAt.SetValue( anatReg.CM );
        anatRegDS.Replace( codeMeaningAt.GetAsDataElement() );
      }
    }

    //*****   Segmented Property Category Code Sequence   *****//
    {
      // Segmented Property Category Code Sequence (0062,0003) Type 1
      SmartPointer<SequenceOfItems> propCatSQ;
      const Tag propCatSQTag(0x0062, 0x0003);
      if( !segmentDS.FindDataElement( propCatSQTag ) )
      {
        propCatSQ = new SequenceOfItems;
        DataElement detmp( propCatSQTag );
        detmp.SetVR( VR::SQ );
        detmp.SetValue( *propCatSQ );
        detmp.SetVLToUndefined();
        segmentDS.Insert( detmp );
      }
      propCatSQ = segmentDS.GetDataElement( propCatSQTag ).GetValueAsSQ();
      propCatSQ->SetLengthToUndefined();

      // Fill the Segmented Property Category Code Sequence
      const unsigned int nbItems = propCatSQ->GetNumberOfItems();
      if (nbItems < 1)  // Only one item is a type 1
      {
        Item item;
        item.SetVLToUndefined();
        propCatSQ->AddItem(item);
      }

      Item &    propCatItem = propCatSQ->GetItem(1);
      DataSet & propCatDS   = propCatItem.GetNestedDataSet();

      //*****   CODE SEQUENCE MACRO ATTRIBUTES   *****//
      {
        const Segment::BasicCodedEntry & propCat = segment->GetPropertyCategory();

        // Code Value
        Attribute<0x0008, 0x0100> codeValueAt;
        codeValueAt.SetValue( propCat.CV );
        propCatDS.Replace( codeValueAt.GetAsDataElement() );

        // Coding Scheme
        Attribute<0x0008, 0x0102> codingSchemeAt;
        codingSchemeAt.SetValue( propCat.CSD );
        propCatDS.Replace( codingSchemeAt.GetAsDataElement() );

        // Code Meaning
        Attribute<0x0008, 0x0104> codeMeaningAt;
        codeMeaningAt.SetValue( propCat.CM );
        propCatDS.Replace( codeMeaningAt.GetAsDataElement() );
      }
    }

    //*****   Segmented Property Type Code Sequence   *****//
    {
      // Segmented Property Type Code Sequence (0062,000F) Type 1
      SmartPointer<SequenceOfItems> propTypeSQ;
      const Tag propTypeSQTag(0x0062, 0x000F);
      if( !segmentDS.FindDataElement( propTypeSQTag ) )
      {
        propTypeSQ = new SequenceOfItems;
        DataElement detmp( propTypeSQTag );
        detmp.SetVR( VR::SQ );
        detmp.SetValue( *propTypeSQ );
        detmp.SetVLToUndefined();
        segmentDS.Insert( detmp );
      }
      propTypeSQ = segmentDS.GetDataElement( propTypeSQTag ).GetValueAsSQ();
      propTypeSQ->SetLengthToUndefined();

      // Fill the Segmented Property Category Code Sequence
      const unsigned int nbItems = propTypeSQ->GetNumberOfItems();
      if (nbItems < 1)  // Only one item is a type 1
      {
        Item item;
        item.SetVLToUndefined();
        propTypeSQ->AddItem(item);
      }

      Item &    propTypeItem = propTypeSQ->GetItem(1);
      DataSet & propTypeDS   = propTypeItem.GetNestedDataSet();

      //*****   CODE SEQUENCE MACRO ATTRIBUTES   *****//
      {
        const Segment::BasicCodedEntry & propType = segment->GetPropertyType();

        // Code Value
        Attribute<0x0008, 0x0100> codeValueAt;
        codeValueAt.SetValue( propType.CV );
        propTypeDS.Replace( codeValueAt.GetAsDataElement() );

        // Coding Scheme
        Attribute<0x0008, 0x0102> codingSchemeAt;
        codingSchemeAt.SetValue( propType.CSD );
        propTypeDS.Replace( codingSchemeAt.GetAsDataElement() );

        // Code Meaning
        Attribute<0x0008, 0x0104> codeMeaningAt;
        codeMeaningAt.SetValue( propType.CM );
        propTypeDS.Replace( codeMeaningAt.GetAsDataElement() );
      }
    }

    //***** Referenced Surface Sequence *****//
    const unsigned int surfaceCount = segment->GetSurfaceCount();
    if (surfaceCount > 0)
    {
      // Surface Count
      Attribute<0x0066, 0x002A> surfaceCountAt;
      surfaceCountAt.SetValue( surfaceCount );
      segmentDS.Replace( surfaceCountAt.GetAsDataElement() );

      //*****   Referenced Surface Sequence   *****//
      SmartPointer<SequenceOfItems> segmentsRefSQ;
      if( !segmentDS.FindDataElement( Tag(0x0066, 0x002B) ) )
      {
        segmentsRefSQ = new SequenceOfItems;
        DataElement detmp( Tag(0x0066, 0x002B) );
        detmp.SetVR( VR::SQ );
        detmp.SetValue( *segmentsRefSQ );
        detmp.SetVLToUndefined();
        segmentDS.Insert( detmp );
      }
      segmentsRefSQ = segmentDS.GetDataElement( Tag(0x0066, 0x002B) ).GetValueAsSQ();
      segmentsRefSQ->SetLengthToUndefined();

      // Fill the Segment Surface Generation Algorithm Identification Sequence
      const unsigned int              nbItems           = segmentsRefSQ->GetNumberOfItems();
      if (nbItems < surfaceCount)
      {
        const unsigned int diff           = surfaceCount - nbItems;
        const unsigned int nbOfItemToMake = (diff > 0?diff:0);
        for(unsigned int i = 1; i <= nbOfItemToMake; ++i)
        {
          Item item;
          item.SetVLToUndefined();
          segmentsRefSQ->AddItem(item);
        }
      }
      // else Should I remove items?

      std::vector< SmartPointer< Surface > >                  surfaces          = segment->GetSurfaces();
      std::vector< SmartPointer< Surface > >::const_iterator  it                = surfaces.begin();
      std::vector< SmartPointer< Surface > >::const_iterator  itEnd             = surfaces.end();
      unsigned long                                           refSurfaceNumber  = segment->GetSegmentNumber();
      unsigned int                                            surfaceNum        = 0;
      for (; it != itEnd; it++)
      {
        SmartPointer< Surface > surface = *it;

        Item &    segmentsRefItem = segmentsRefSQ->GetItem( surfaceNum + 1 );
        DataSet & segmentsRefDS   = segmentsRefItem.GetNestedDataSet();

        // Referenced Surface Number
        Attribute<0x0066, 0x002C> refSurfaceNumberAt;
        refSurfaceNumberAt.SetValue( refSurfaceNumber + surfaceNum );
        segmentsRefDS.Replace( refSurfaceNumberAt.GetAsDataElement() );

        //*****   Segment Surface Generation Algorithm Identification Sequence    *****//
        {
          SmartPointer<SequenceOfItems> segmentsAlgoIdSQ;
          const Tag segmentsAlgoIdTag(0x0066, 0x002D);
          if( !segmentsRefDS.FindDataElement( segmentsAlgoIdTag ) )
          {
            segmentsAlgoIdSQ = new SequenceOfItems;
            DataElement detmp( segmentsAlgoIdTag );
            detmp.SetVR( VR::SQ );
            detmp.SetValue( *segmentsAlgoIdSQ );
            detmp.SetVLToUndefined();
            segmentsRefDS.Insert( detmp );
          }
          segmentsAlgoIdSQ = segmentsRefDS.GetDataElement( segmentsAlgoIdTag ).GetValueAsSQ();
          segmentsAlgoIdSQ->SetLengthToUndefined();

          if (segmentsAlgoIdSQ->GetNumberOfItems() < 1)
          {
            Item item;
            item.SetVLToUndefined();
            segmentsAlgoIdSQ->AddItem(item);
          }

          ::gdcm::Item &    segmentsAlgoIdItem  = segmentsAlgoIdSQ->GetItem(1);
          ::gdcm::DataSet & segmentsAlgoIdDS    = segmentsAlgoIdItem.GetNestedDataSet();

          //*****   Algorithm Family Code Sequence    *****//
          //See: PS.3.3 Table 8.8-1 and PS 3.16 Context ID 7162
          {
            SmartPointer<SequenceOfItems> algoFamilyCodeSQ;
          const Tag algoFamilyCodeTag(0x0066, 0x002F);
            if( !segmentsAlgoIdDS.FindDataElement( algoFamilyCodeTag ) )
            {
              algoFamilyCodeSQ = new SequenceOfItems;
              DataElement detmp( algoFamilyCodeTag );
              detmp.SetVR( VR::SQ );
              detmp.SetValue( *algoFamilyCodeSQ );
              detmp.SetVLToUndefined();
              segmentsAlgoIdDS.Insert( detmp );
            }
            algoFamilyCodeSQ = segmentsAlgoIdDS.GetDataElement( algoFamilyCodeTag ).GetValueAsSQ();
            algoFamilyCodeSQ->SetLengthToUndefined();

            // Fill the Algorithm Family Code Sequence
            const unsigned int nbItems = algoFamilyCodeSQ->GetNumberOfItems();
            if (nbItems < 1)
            {
                Item item;
                item.SetVLToUndefined();
                algoFamilyCodeSQ->AddItem(item);
            }

            ::gdcm::Item &    algoFamilyCodeItem  = algoFamilyCodeSQ->GetItem(1);
            ::gdcm::DataSet & algoFamilyCodeDS    = algoFamilyCodeItem.GetNestedDataSet();

            //*****   CODE SEQUENCE MACRO ATTRIBUTES   *****//
            {
              const Segment::BasicCodedEntry & algoFamily = segment->GetAlgorithmFamily();

              // Code Value
              Attribute<0x0008, 0x0100> codeValueAt;
              codeValueAt.SetValue( algoFamily.CV );
              algoFamilyCodeDS.Replace( codeValueAt.GetAsDataElement() );

              // Coding Scheme
              Attribute<0x0008, 0x0102> codingSchemeAt;
              codingSchemeAt.SetValue( algoFamily.CSD );
              algoFamilyCodeDS.Replace( codingSchemeAt.GetAsDataElement() );

              // Code Meaning
              Attribute<0x0008, 0x0104> codeMeaningAt;
              codeMeaningAt.SetValue( algoFamily.CM );
              algoFamilyCodeDS.Replace( codeMeaningAt.GetAsDataElement() );
            }
          }

          // Algorithm Version
          Attribute<0x0066, 0x0031> algoVersion;
          algoVersion.SetValue( segment->GetAlgorithmVersion() );
          segmentsAlgoIdDS.Replace( algoVersion.GetAsDataElement() );

          // Algorithm Name
          Attribute<0x0066, 0x0036> algoName;
          algoName.SetValue( segment->GetAlgorithmName() );
          segmentsAlgoIdDS.Replace( algoName.GetAsDataElement() );
        }

        //*****   Segment Surface Source Instance Sequence   *****//
        {
          SmartPointer<SequenceOfItems> surfaceSourceSQ;
          if( !segmentsRefDS.FindDataElement( Tag(0x0066, 0x002E) ) )
          {
            surfaceSourceSQ = new SequenceOfItems;
            DataElement detmp( Tag(0x0066, 0x002E) );
            detmp.SetVR( VR::SQ );
            detmp.SetValue( *surfaceSourceSQ );
            detmp.SetVLToUndefined();
            segmentsRefDS.Insert( detmp );
          }
          surfaceSourceSQ = segmentsRefDS.GetDataElement( Tag(0x0066, 0x002E) ).GetValueAsSQ();
          surfaceSourceSQ->SetLengthToUndefined();
          //NOTE: If surfaces are derived from image, include ‘Image SOP Instance Reference Macro’ PS 3.3 Table C.10-3.
          //      How to know it?
        }
      }
    }
    else
    {
      // Segment Algorithm Name
      Attribute<0x0062, 0x0009> segmentAlgorithmName;
      segmentAlgorithmName.SetValue( segment->GetSegmentAlgorithmName() );
      segmentDS.Replace( segmentAlgorithmName.GetAsDataElement() );
    }
  }

  return true;
}

bool SegmentWriter::Write()
{
  if( !PrepareWrite() )
  {
    return false;
  }

  assert( Stream );
  if( !Writer::Write() )
  {
    return false;
  }

  return true;
}

}
