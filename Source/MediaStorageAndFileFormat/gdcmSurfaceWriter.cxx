/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmSurfaceWriter.h"
#include "gdcmAttribute.h"
#include "gdcmUIDGenerator.h"

namespace gdcm
{

SurfaceWriter::SurfaceWriter():
  NumberOfSurfaces(0)
{
}

SurfaceWriter::~SurfaceWriter()
{
}

void SurfaceWriter::ComputeNumberOfSurfaces()
{
  std::vector< SmartPointer< Segment > >::const_iterator  it    = Segments.begin();
  std::vector< SmartPointer< Segment > >::const_iterator  itEnd = Segments.end();
  for (; it != itEnd; it++)
  {
    NumberOfSurfaces += (*it)->GetSurfaceCount();
  }
}

unsigned long SurfaceWriter::GetNumberOfSurfaces()
{
  if (NumberOfSurfaces == 0)
  {
    ComputeNumberOfSurfaces();
  }

  return NumberOfSurfaces;
}

void SurfaceWriter::SetNumberOfSurfaces(const unsigned long nb)
{
  NumberOfSurfaces = nb;
}

bool SurfaceWriter::PrepareWrite()
{
  if( !SegmentWriter::PrepareWrite() )
  {
    return false;
  }

  File &                 file = GetFile();
  DataSet &              ds   = file.GetDataSet();

  FileMetaInformation &  fmi  = file.GetHeader();
  const TransferSyntax & ts   = fmi.GetDataSetTransferSyntax();
  assert( ts.IsExplicit() || ts.IsImplicit() );

  // Number Of Surface
  const unsigned long     nbSurfaces = this->GetNumberOfSurfaces();
  if (nbSurfaces == 0)
  {
    gdcmErrorMacro( "No surface to write" );
    return false;
  }
  Attribute<0x0066, 0x0001> numberOfSurfaces;
  numberOfSurfaces.SetValue( nbSurfaces );
  ds.Replace( numberOfSurfaces.GetAsDataElement() );

  // Surface Sequence
  SmartPointer<SequenceOfItems> surfacesSQ;
  if( !ds.FindDataElement( Tag(0x0066, 0x0002) ) )
  {
    surfacesSQ = new SequenceOfItems;
    DataElement detmp( Tag(0x0066, 0x0002) );
    detmp.SetVR( VR::SQ );
    detmp.SetValue( *surfacesSQ );
    detmp.SetVLToUndefined();
    ds.Insert( detmp );
  }
  surfacesSQ = ds.GetDataElement( Tag(0x0066, 0x0002) ).GetValueAsSQ();
  surfacesSQ->SetLengthToUndefined();

  // Fill the Surface Sequence
  const unsigned int              nbItems    = surfacesSQ->GetNumberOfItems();
  if (nbItems < nbSurfaces)
  {
    const int          diff           = nbSurfaces - nbItems;
    const unsigned int nbOfItemToMake = (diff > 0?diff:0);
    for(unsigned int i = 1; i <= nbOfItemToMake; ++i)
    {
      Item item;
      item.SetVLToUndefined();
      surfacesSQ->AddItem(item);
    }
  }
  // else Should I remove items?

  std::vector< SmartPointer< Segment > >                  segments  = this->GetSegments();
  std::vector< SmartPointer< Segment > >::const_iterator  it        = segments.begin();
  std::vector< SmartPointer< Segment > >::const_iterator  itEnd     = segments.end();
  unsigned int                                            numSegment= 1;
  unsigned int                                            numSurface= 1;
  for (; it != itEnd; it++)
  {
    SmartPointer< Segment > segment = *it;
    assert( segment );

    std::vector< SmartPointer< Surface > >                  surfaces  = segment->GetSurfaces();
    std::vector< SmartPointer< Surface > >::const_iterator  it        = surfaces.begin();
    std::vector< SmartPointer< Surface > >::const_iterator  itEnd     = surfaces.end();
    for (; it != itEnd; it++)
    {
      SmartPointer< Surface > surface = *it;
      assert( surface );

      Item &    surfaceItem = surfacesSQ->GetItem( numSurface );
      DataSet & surfaceDS   = surfaceItem.GetNestedDataSet();

      // Recommended Display Grayscale Value
      Attribute<0x0062, 0x000C> recommendedDisplayGrayscaleValue;
      recommendedDisplayGrayscaleValue.SetValue( surface->GetRecommendedDisplayGrayscaleValue() );
      surfaceDS.Replace( recommendedDisplayGrayscaleValue.GetAsDataElement() );

      // Recommended Display CIELab Value
      Attribute<0x0062, 0x000D> recommendedDisplayCIELabValue;
      recommendedDisplayCIELabValue.SetValues( surface->GetRecommendedDisplayCIELabValue(), 3 );
      surfaceDS.Replace( recommendedDisplayCIELabValue.GetAsDataElement() );

      // Surface Number (Type 1)
      Attribute<0x0066, 0x0003> surfaceNumberAt;
      unsigned long surfaceNumber = surface->GetSurfaceNumber();
      if (surfaceNumber == 0)
        surfaceNumber = numSurface;
      surfaceNumberAt.SetValue( surfaceNumber );
      surfaceDS.Replace( surfaceNumberAt.GetAsDataElement() );

      // Surface Comments (Type 3)
      const char * surfaceComments = surface->GetSurfaceComments();
      if (strcmp(surfaceComments, "") != 0)
      {
        Attribute<0x0066, 0x0004> surfaceCommentsAt;
        surfaceCommentsAt.SetValue( surfaceComments );
        surfaceDS.Replace( surfaceCommentsAt.GetAsDataElement() );
      }

      // Surface Processing
      const bool surfaceProcessing = surface->GetSurfaceProcessing();
      Attribute<0x0066, 0x0009> surfaceProcessingAt;
      surfaceProcessingAt.SetValue( (surfaceProcessing ? "YES" : "NO") );
      surfaceDS.Replace( surfaceProcessingAt.GetAsDataElement() );

      if (surfaceProcessing)
      {
        Attribute<0x0066, 0x000A> surfaceProcessingRatioAt;
        surfaceProcessingRatioAt.SetValue( surface->GetSurfaceProcessingRatio() );
        surfaceDS.Replace( surfaceProcessingRatioAt.GetAsDataElement() );

        const char * surfaceProcessingDescription = surface->GetSurfaceProcessingDescription();
        if (strcmp(surfaceProcessingDescription, "") != 0)
        {
          Attribute<0x0066, 0x000B> surfaceProcessingDescriptionAt;
          surfaceProcessingDescriptionAt.SetValue( surfaceProcessingDescription );
          surfaceDS.Replace( surfaceProcessingDescriptionAt.GetAsDataElement() );
        }

        //*****   Surface Processing Algorithm Identification Sequence    *****//
        {
          SmartPointer<SequenceOfItems> processingAlgoIdSQ;
          const Tag processingAlgoIdTag(0x0066, 0x0035);
          if( !surfaceDS.FindDataElement( processingAlgoIdTag ) )
          {
            processingAlgoIdSQ = new SequenceOfItems;
            DataElement detmp( processingAlgoIdTag );
            detmp.SetVR( VR::SQ );
            detmp.SetValue( *processingAlgoIdSQ );
            detmp.SetVLToUndefined();
            surfaceDS.Insert( detmp );
          }
          processingAlgoIdSQ = surfaceDS.GetDataElement( processingAlgoIdTag ).GetValueAsSQ();
          processingAlgoIdSQ->SetLengthToUndefined();

          if (processingAlgoIdSQ->GetNumberOfItems() < 1) // One item shall be permitted
          {
            Item item;
            item.SetVLToUndefined();
            processingAlgoIdSQ->AddItem(item);
          }

          ::gdcm::Item &    processingAlgoIdItem  = processingAlgoIdSQ->GetItem(1);
          ::gdcm::DataSet & processingAlgoIdDS    = processingAlgoIdItem.GetNestedDataSet();

          //*****   Algorithm Family Code Sequence    *****//
          //See: PS.3.3 Table 8.8-1 and PS 3.16 Context ID 7162
          {
            const SegmentHelper::BasicCodedEntry & processingAlgo = surface->GetProcessingAlgorithm();
            if (processingAlgo.IsEmpty())
            {
              gdcmWarningMacro("Surface provessing algorithm family not specified or incomplete");
            }

            SmartPointer<SequenceOfItems> algoFamilyCodeSQ;
            const Tag algoFamilyCodeTag(0x0066, 0x002F);
            if( !processingAlgoIdDS.FindDataElement( algoFamilyCodeTag ) )
            {
              algoFamilyCodeSQ = new SequenceOfItems;
              DataElement detmp( algoFamilyCodeTag );
              detmp.SetVR( VR::SQ );
              detmp.SetValue( *algoFamilyCodeSQ );
              detmp.SetVLToUndefined();
              processingAlgoIdDS.Insert( detmp );
            }
            algoFamilyCodeSQ = processingAlgoIdDS.GetDataElement( algoFamilyCodeTag ).GetValueAsSQ();
            algoFamilyCodeSQ->SetLengthToUndefined();

            // Fill the Algorithm Family Code Sequence
            if (algoFamilyCodeSQ->GetNumberOfItems() < 1)
            {
              Item item;
              item.SetVLToUndefined();
              algoFamilyCodeSQ->AddItem(item);
            }

            ::gdcm::Item &    algoFamilyCodeItem  = algoFamilyCodeSQ->GetItem(1);
            ::gdcm::DataSet & algoFamilyCodeDS    = algoFamilyCodeItem.GetNestedDataSet();

            //*****   CODE SEQUENCE MACRO ATTRIBUTES   *****//
            {
              // Code Value (Type 1)
              Attribute<0x0008, 0x0100> codeValueAt;
              codeValueAt.SetValue( processingAlgo.CV );
              algoFamilyCodeDS.Replace( codeValueAt.GetAsDataElement() );

              // Coding Scheme (Type 1)
              Attribute<0x0008, 0x0102> codingSchemeAt;
              codingSchemeAt.SetValue( processingAlgo.CSD );
              algoFamilyCodeDS.Replace( codingSchemeAt.GetAsDataElement() );

              // Code Meaning (Type 1)
              Attribute<0x0008, 0x0104> codeMeaningAt;
              codeMeaningAt.SetValue( processingAlgo.CM );
              algoFamilyCodeDS.Replace( codeMeaningAt.GetAsDataElement() );
            }
          }
        }
      }

      // Presentation Opacity
      Attribute<0x0066, 0x000C> presentationOpacity;
      presentationOpacity.SetValue( surface->GetRecommendedPresentationOpacity() );
      surfaceDS.Replace( presentationOpacity.GetAsDataElement() );

      // Presentation Type
      Attribute<0x0066, 0x000D> presentationType;
      const char * reconmmendedPresentationType = Surface::GetVIEWTypeString( surface->GetRecommendedPresentationType() );
      if (reconmmendedPresentationType != 0)
        presentationType.SetValue( reconmmendedPresentationType );
      else
        presentationType.SetValue( Surface::GetVIEWTypeString(Surface::SURFACE) );  // Is it the right thing to do?
      surfaceDS.Replace( presentationType.GetAsDataElement() );

      // Finite Volume
      Attribute<0x0066, 0x000E> finiteVolumeAt;
      Surface::STATES finiteVolume = surface->GetFiniteVolume();
      if (finiteVolume == Surface::STATES_END)
        finiteVolume = Surface::UNKNOWN;
      finiteVolumeAt.SetValue( Surface::GetSTATESString( finiteVolume ) );
      surfaceDS.Replace( finiteVolumeAt.GetAsDataElement() );

      // Manifold
      Attribute<0x0066, 0x0010> manifoldAt;
      Surface::STATES manifold = surface->GetManifold();
      if (manifold == Surface::STATES_END)
        manifold = Surface::UNKNOWN;
      manifoldAt.SetValue( Surface::GetSTATESString( manifold ) );
      surfaceDS.Replace( manifoldAt.GetAsDataElement() );

      //******    Surface Points    *****//
      //        (0066,0011) SQ (Sequence with undefined length #=1)     # u/l, 1 Surface Points Sequence
      //          (fffe,e000) na (Item with undefined length #=1)         # u/l, 1 Item
      //            (0066,0015) UL                                         #  0, 1 Number Of Surface Points
      //            (0066,0016) OW                                         #  0, 1 Point Coordinates Data
      //          (fffe,e00d) na (ItemDelimitationItem)                   #   0, 0 ItemDelimitationItem
      //        (fffe,e0dd) na (SequenceDelimitationItem)               #   0, 0 SequenceDelimitationItem

      //*****   Surface Points Sequence   *****//
      {
        SmartPointer<SequenceOfItems> surfacePointsSq;
        if( !surfaceDS.FindDataElement( Tag(0x0066, 0x0011) ) )
        {
          surfacePointsSq = new SequenceOfItems;
          DataElement detmp( Tag(0x0066, 0x0011) );
          detmp.SetVR( VR::SQ );
          detmp.SetValue( *surfacePointsSq );
          detmp.SetVLToUndefined();
          surfaceDS.Insert( detmp );
        }
        surfacePointsSq = surfaceDS.GetDataElement( Tag(0x0066, 0x0011) ).GetValueAsSQ();
        surfacePointsSq->SetLengthToUndefined();

        if (surfacePointsSq->GetNumberOfItems() < 1)  // One item shall be permitted
        {
          Item item;
          item.SetVLToUndefined();
          surfacePointsSq->AddItem(item);
        }

        Item &    surfacePointsItem = surfacePointsSq->GetItem(1);
        DataSet & surfacePointsDs   = surfacePointsItem.GetNestedDataSet();

        // Point Coordinates Data
        DataElement pointCoordDataDE( Tag(0x0066, 0x0016) );
        const Value & pointCoordinateDataValue = surface->GetPointCoordinatesData().GetValue();
        assert( &pointCoordinateDataValue );
        pointCoordDataDE.SetValue( pointCoordinateDataValue );

        const ByteValue *bv = pointCoordDataDE.GetByteValue();
        VL vl;
        if ( bv )
          vl = bv->GetLength();
        else
          vl.SetToUndefined();
        pointCoordDataDE.SetVL( vl );

        if ( ts.IsExplicit() )
          pointCoordDataDE.SetVR( VR::OF );

        surfacePointsDs.Replace( pointCoordDataDE );

        // Number Of Surface Points
        Attribute<0x0066, 0x0015> numberOfSurfacePointsAt;
        unsigned long numberOfSurfacePoints = surface->GetNumberOfSurfacePoints();
        if (numberOfSurfacePoints == 0)
          numberOfSurfacePoints = bv->GetLength() / (VR::GetLength(VR::OF) * 3);
        numberOfSurfacePointsAt.SetValue( numberOfSurfacePoints );
        surfacePointsDs.Replace( numberOfSurfacePointsAt.GetAsDataElement() );
      }

      //******    Surface Points Normals    *****//
      //        (0066,0012) SQ (Sequence with undefined length #=1)     # u/l, 1 Surface Points Sequence
      //          (fffe,e000) na (Item with undefined length #=1)         # u/l, 1 Item
      //            (0066,001e) UL                                         #  0, 1 Number of Vectors
      //            (0066,001f) US                                         #  0, 1 Vector Dimensionality
      //            (0066,0021) OF                                         #  0, 1_n Vector Coordinate Data
      //          (fffe,e00d) na (ItemDelimitationItem)                   #   0, 0 ItemDelimitationItem
      //        (fffe,e0dd) na (SequenceDelimitationItem)               #   0, 0 SequenceDelimitationItem
      const unsigned long           numberOfVectors = surface->GetNumberOfVectors();
      SmartPointer< MeshPrimitive > meshPrimitive   = surface->GetMeshPrimitive();
      const MeshPrimitive::MPType   primitiveType   = meshPrimitive->GetPrimitiveType();
      if (numberOfVectors > 0
       && primitiveType != MeshPrimitive::TRIANGLE_STRIP
       && primitiveType != MeshPrimitive::TRIANGLE_FAN)
      {
        SmartPointer<SequenceOfItems> surfacePointsNormalsSQ;
        if( !surfaceDS.FindDataElement( Tag(0x0066, 0x0012) ) )
        {
          surfacePointsNormalsSQ = new SequenceOfItems;
          DataElement detmp( Tag(0x0066, 0x0012) );
          detmp.SetVR( VR::SQ );
          detmp.SetValue( *surfacePointsNormalsSQ );
          detmp.SetVLToUndefined();
          surfaceDS.Insert( detmp );
        }
        surfacePointsNormalsSQ = surfaceDS.GetDataElement( Tag(0x0066, 0x0012) ).GetValueAsSQ();
        surfacePointsNormalsSQ->SetLengthToUndefined();

        if (surfacePointsNormalsSQ->GetNumberOfItems() < 1)  // One item shall be permitted
        {
          Item item;
          item.SetVLToUndefined();
          surfacePointsNormalsSQ->AddItem(item);
        }

        Item &    surfacePointsNormalsItem = surfacePointsNormalsSQ->GetItem(1);
        DataSet & surfacePointsNormalsDS   = surfacePointsNormalsItem.GetNestedDataSet();

        // Number of Vectors
        Attribute<0x0066, 0x001E> numberOfVectors;
        numberOfVectors.SetValue( surface->GetNumberOfVectors() );
        surfacePointsNormalsDS.Replace( numberOfVectors.GetAsDataElement() );

        // Vector Dimensionality
        Attribute<0x0066, 0x001F> vectorDimensionality;
        assert( surface->GetVectorDimensionality() );
        vectorDimensionality.SetValue( surface->GetVectorDimensionality() );
        surfacePointsNormalsDS.Replace( vectorDimensionality.GetAsDataElement() );

        // Vector Coordinate Data
        DataElement vectorCoordDataDE( Tag(0x0066, 0x0021) );
        vectorCoordDataDE.SetVR( VR::OF );
        const Value & vectorCoordinateDataValue = surface->GetVectorCoordinateData().GetValue();
        assert( &vectorCoordinateDataValue );
        vectorCoordDataDE.SetValue( vectorCoordinateDataValue );

        const ByteValue *bv = vectorCoordDataDE.GetByteValue();
        VL vl;
        if ( bv )
          vl = bv->GetLength();
        else
          vl.SetToUndefined();
        vectorCoordDataDE.SetVL( vl );

        if ( ts.IsExplicit() )
          vectorCoordDataDE.SetVR( VR::OF );

        surfacePointsNormalsDS.Replace( vectorCoordDataDE );
      }
      else if (numberOfVectors > 0)
      {
        gdcmWarningMacro("Triangle strip or fan have no surface points normals");
      }

      //******    Surface Mesh Primitives    *****//
      //        Two exemples :
      //        (0066,0013) SQ (Sequence with undefined length #=1)     # u/l, 1 Surface Mesh Primitives Sequence
      //          (fffe,e000) na (Item with undefined length #=1)         # u/l, 1 Item
      //            (0066,0016) OW                                         #  0, 1 Edge Point Index List
      //          (fffe,e00d) na (ItemDelimitationItem)                   #   0, 0 ItemDelimitationItem
      //        (fffe,e0dd) na (SequenceDelimitationItem)               #   0, 0 SequenceDelimitationItem
      //
      //              OR
      //
      //        (0066,0013) SQ (Sequence with undefined length #=1)     # u/l, 1 Surface Mesh Primitives Sequence
      //          (fffe,e000) na (Item with undefined length #=1)         # u/l, 1 Item
      //            (0066,0026) SQ (Sequence with undefined length #=1)     # u/l, 1 // Triangle Strip Sequence
      //              (fffe,e000) na (Item with undefined length #=1)         # u/l, 1 Item
      //                (0066,0029) OW                                         #  0, 1 // Primitive Point Index List
      //              (fffe,e00d) na (ItemDelimitationItem)                   #   0, 0 ItemDelimitationItem
      //                                            ...
      //              (fffe,e000) na (Item with undefined length #=1)         # u/l, 1 Item
      //                (0066,0029) OW                                         #  0, 1 // Primitive Point Index List
      //              (fffe,e00d) na (ItemDelimitationItem)                   #   0, 0 ItemDelimitationItem
      //            (fffe,e0dd) na (SequenceDelimitationItem)               #   0, 0 SequenceDelimitationItem
      //          (fffe,e00d) na (ItemDelimitationItem)                   #   0, 0 ItemDelimitationItem
      //        (fffe,e0dd) na (SequenceDelimitationItem)               #   0, 0 SequenceDelimitationItem

      // Surface Mesh Primitives Sequence
      {
        SmartPointer<SequenceOfItems> surfaceMeshPrimitivesSQ;
        if( !surfaceDS.FindDataElement( Tag(0x0066, 0x0013) ) )
        {
          surfaceMeshPrimitivesSQ = new SequenceOfItems;
          DataElement detmp( Tag(0x0066, 0x0013) );
          detmp.SetVR( VR::SQ );
          detmp.SetValue( *surfaceMeshPrimitivesSQ );
          detmp.SetVLToUndefined();
          surfaceDS.Insert( detmp );
        }
        surfaceMeshPrimitivesSQ = surfaceDS.GetDataElement( Tag(0x0066, 0x0013) ).GetValueAsSQ();
        surfaceMeshPrimitivesSQ->SetLengthToUndefined();

        if (surfaceMeshPrimitivesSQ->GetNumberOfItems() < 1)  // One itme shall be permitted
        {
          Item item;
          item.SetVLToUndefined();
          surfaceMeshPrimitivesSQ->AddItem(item);
        }

        Item &    surfaceMeshPrimitivesItem = surfaceMeshPrimitivesSQ->GetItem(1);
        DataSet & surfaceMeshPrimitivesDS   = surfaceMeshPrimitivesItem.GetNestedDataSet();

        //*****   Handle "Typed" Point Index List   *****//
        bool      insertInSQ = false;

        // Primitive Point Index List
        Tag         typedPrimitiveTag;
        typedPrimitiveTag.SetGroup(0x0066);
        DataSet &   pointIndexListDS  = surfaceMeshPrimitivesDS;

        switch (primitiveType)
        {
        case MeshPrimitive::VERTEX:
          // Vertex Point Index List
          typedPrimitiveTag.SetElement(0x0025);
          break;
        case MeshPrimitive::EDGE:
          // Edge Point Index List
          typedPrimitiveTag.SetElement(0x0024);
          break;
        case MeshPrimitive::TRIANGLE:
          // Triangle Point Index List
          typedPrimitiveTag.SetElement(0x0023);
          break;
        case MeshPrimitive::TRIANGLE_STRIP:
        case MeshPrimitive::TRIANGLE_FAN:
        case MeshPrimitive::LINE:
        case MeshPrimitive::FACET:
          // Primitive Point Index List
          typedPrimitiveTag.SetElement(0x0029);
          insertInSQ = true;
          break;
        default:
          gdcmErrorMacro( "Unknown surface mesh primitives type" );
          return false;
        }

        if (insertInSQ)
        {
          // Handled "complex" mesh primitives

          Tag typedSequenceTag;
          typedSequenceTag.SetGroup(0x0066);
          switch (primitiveType)
          {
          case MeshPrimitive::TRIANGLE_STRIP:
            // Triangle Strip Sequence
            typedSequenceTag.SetElement(0x0026);
            break;
          case MeshPrimitive::TRIANGLE_FAN:
            // Triangle Fan Sequence
            typedSequenceTag.SetElement(0x0027);
            break;
          case MeshPrimitive::LINE:
            // Line Sequence
            typedSequenceTag.SetElement(0x0028);
            break;
          case MeshPrimitive::FACET:
            // Facet Sequence
            typedSequenceTag.SetElement(0x0034);
            break;
          default:
            gdcmErrorMacro( "Unknown surface mesh primitives type" );
            return false;
          }

          // "Typed" Sequence
          SmartPointer<SequenceOfItems> typedSequenceSQ;
          if( !surfaceMeshPrimitivesDS.FindDataElement( typedSequenceTag ) )
          {
            typedSequenceSQ = new SequenceOfItems;
            DataElement detmp( typedSequenceTag );
            detmp.SetVR( VR::SQ );
            detmp.SetValue( *typedSequenceSQ );
            detmp.SetVLToUndefined();
            surfaceMeshPrimitivesDS.Insert( detmp );
          }
          typedSequenceSQ = surfaceMeshPrimitivesDS.GetDataElement( typedSequenceTag ).GetValueAsSQ();
          typedSequenceSQ->SetLengthToUndefined();

          // Fill the Segment Sequence
          const unsigned int              numberOfPrimitives  = meshPrimitive->GetNumberOfPrimitivesData();
          assert( numberOfPrimitives );
          const unsigned int              nbItems             = typedSequenceSQ->GetNumberOfItems();
          if (nbItems < numberOfPrimitives)
          {
            const int          diff           = numberOfPrimitives - nbItems;
            const unsigned int nbOfItemToMake = (diff > 0?diff:0);
            for(unsigned int i = 1; i <= nbOfItemToMake; ++i)
            {
              Item item;
              item.SetVLToUndefined();
              typedSequenceSQ->AddItem(item);
            }
          }
          // else Should I remove items?

          const MeshPrimitive::PrimitivesData &         primitivesData= meshPrimitive->GetPrimitivesData();
          MeshPrimitive::PrimitivesData::const_iterator it            = primitivesData.begin();
          MeshPrimitive::PrimitivesData::const_iterator itEnd         = primitivesData.end();
          unsigned int                                  i             = 1;
          for (; it != itEnd; it++)
          {
            Item &    typedSequenceItem = typedSequenceSQ->GetItem(i++);
            DataSet & pointIndexListDS  = typedSequenceItem.GetNestedDataSet();

            // "Typed" Point Index List
            DataElement typedPointIndexListDE( typedPrimitiveTag );

            const Value & pointIndexListValue = it->GetValue();
            assert( &pointIndexListValue );
            typedPointIndexListDE.SetValue( pointIndexListValue );

            const ByteValue * pointIndexListBV = typedPointIndexListDE.GetByteValue();
            VL pointIndexListVL;
            if( pointIndexListBV )
            {
              pointIndexListVL = pointIndexListBV->GetLength();
            }
            else
            {
              pointIndexListVL.SetToUndefined();
            }
            typedPointIndexListDE.SetVL( pointIndexListVL );

            if ( ts.IsExplicit() )
              typedPointIndexListDE.SetVR( VR::OW );

            pointIndexListDS.Replace( typedPointIndexListDE );
          }
        }
        else
        {
          // Handled "simple" mesh primitives

          // "Typed" Point Index List
          DataElement   typedPointIndexListDE( typedPrimitiveTag );

          const Value & pointIndexListValue = meshPrimitive->GetPrimitiveData().GetValue();
          assert( &pointIndexListValue );
          typedPointIndexListDE.SetValue( pointIndexListValue );

          const ByteValue * pointIndexListBV = typedPointIndexListDE.GetByteValue();
          VL pointIndexListVL;
          if ( pointIndexListBV )
            pointIndexListVL = pointIndexListBV->GetLength();
          else
            pointIndexListVL.SetToUndefined();
          typedPointIndexListDE.SetVL( pointIndexListVL );

          if ( ts.IsExplicit() )
            typedPointIndexListDE.SetVR( VR::OW );

          pointIndexListDS.Replace( typedPointIndexListDE );
        }
      }
      ++numSurface;
    }


    //*****   Segment Sequence    *****//
    SmartPointer<SequenceOfItems>   segmentsSQ      = ds.GetDataElement( Tag(0x0062, 0x0002) ).GetValueAsSQ();
    Item &                          segmentIt       = segmentsSQ->GetItem( numSegment++ );
    DataSet &                       segmentDS       = segmentIt.GetNestedDataSet();

    //*****   Referenced Surface Sequence    *****//
    SmartPointer<SequenceOfItems>   refSurfaceSQ    = segmentDS.GetDataElement( Tag(0x0066, 0x002B) ).GetValueAsSQ();
    SequenceOfItems::Iterator       itRefSurface    = refSurfaceSQ->Begin();
    SequenceOfItems::Iterator       itEndRefSurface = refSurfaceSQ->End();
    unsigned int                    idxSurface      = 0;
    for (; itRefSurface != itEndRefSurface; itRefSurface++)
    {
      DataSet &                     refSurfaceDS    = itRefSurface->GetNestedDataSet();
      SmartPointer< Surface >       surface         = segment->GetSurface( idxSurface++ );

      //*****   Segment Surface Generation Algorithm Identification Sequence    *****//
      {
        SmartPointer<SequenceOfItems> segmentsAlgoIdSQ;
        const Tag segmentsAlgoIdTag(0x0066, 0x002D);
        if( !refSurfaceDS.FindDataElement( segmentsAlgoIdTag ) )
        {
          segmentsAlgoIdSQ = new SequenceOfItems;
          DataElement detmp( segmentsAlgoIdTag );
          detmp.SetVR( VR::SQ );
          detmp.SetValue( *segmentsAlgoIdSQ );
          detmp.SetVLToUndefined();
          refSurfaceDS.Insert( detmp );
        }
        segmentsAlgoIdSQ = refSurfaceDS.GetDataElement( segmentsAlgoIdTag ).GetValueAsSQ();
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
        const SegmentHelper::BasicCodedEntry & algoFamily = surface->GetAlgorithmFamily();
        if (algoFamily.IsEmpty())
        {
          gdcmWarningMacro("Segment surface generation algorithm family not specified or incomplete");
        }

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
          if (algoFamilyCodeSQ->GetNumberOfItems() < 1)
          {
            Item item;
            item.SetVLToUndefined();
            algoFamilyCodeSQ->AddItem(item);
          }

          ::gdcm::Item &    algoFamilyCodeItem  = algoFamilyCodeSQ->GetItem(1);
          ::gdcm::DataSet & algoFamilyCodeDS    = algoFamilyCodeItem.GetNestedDataSet();

          //*****   CODE SEQUENCE MACRO ATTRIBUTES   *****//
          {
            // Code Value (Type 1)
            Attribute<0x0008, 0x0100> codeValueAt;
            codeValueAt.SetValue( algoFamily.CV );
            algoFamilyCodeDS.Replace( codeValueAt.GetAsDataElement() );

            // Coding Scheme (Type 1)
            Attribute<0x0008, 0x0102> codingSchemeAt;
            codingSchemeAt.SetValue( algoFamily.CSD );
            algoFamilyCodeDS.Replace( codingSchemeAt.GetAsDataElement() );

            // Code Meaning (Type 1)
            Attribute<0x0008, 0x0104> codeMeaningAt;
            codeMeaningAt.SetValue( algoFamily.CM );
            algoFamilyCodeDS.Replace( codeMeaningAt.GetAsDataElement() );
          }

        // Algorithm Version
        const char * algorithmVersion = surface->GetAlgorithmVersion();
        if (strcmp(algorithmVersion, "") != 0)
        {
          gdcmWarningMacro("No algorithm version specified");
        }
        Attribute<0x0066, 0x0031> algorithmVersionAt;
        algorithmVersionAt.SetValue( algorithmVersion );
        segmentsAlgoIdDS.Replace( algorithmVersionAt.GetAsDataElement() );

        // Algorithm Name
        const char * algorithmName = surface->GetAlgorithmName();
        if (strcmp(algorithmName, "") != 0)
        {
          gdcmWarningMacro("No algorithm name specified");
        }
        Attribute<0x0066, 0x0036> algorithmNameAt;
        algorithmNameAt.SetValue( algorithmName );
        segmentsAlgoIdDS.Replace( algorithmNameAt.GetAsDataElement() );
      }
    }

  }

  //**  Complete the file   **//
  // Is SOP Class UID defined?
  if( !ds.FindDataElement( Tag(0x0008, 0x0016) ) )
  {
    const char * SOPClassUID = MediaStorage::GetMSString(MediaStorage::SurfaceSegmentationStorage);

    DataElement de( Tag(0x0008, 0x0016) );
    VL::Type strlenSOPClassUID= (VL::Type)strlen(SOPClassUID);
    de.SetByteValue( SOPClassUID, strlenSOPClassUID );
    de.SetVR( Attribute<0x0008, 0x0016>::GetVR() );
    ds.ReplaceEmpty( de );
  }

  // Is SOP Instance UID defined?
  if( !ds.FindDataElement( Tag(0x0008, 0x0018) ) )
  {
    UIDGenerator  UIDgen;
    UIDgen.SetRoot( MediaStorage::GetMSString(MediaStorage::SurfaceSegmentationStorage) );
    const char * SOPInstanceUID = UIDgen.Generate();

    DataElement de( Tag(0x0008, 0x0018) );
    VL::Type strlenSOPInstanceUID= (VL::Type)strlen(SOPInstanceUID);
    de.SetByteValue( SOPInstanceUID, strlenSOPInstanceUID );
    de.SetVR( Attribute<0x0008, 0x0018>::GetVR() );
    ds.ReplaceEmpty( de );
  }

  fmi.Clear();
  {
    const char *tsuid = TransferSyntax::GetTSString( ts );
    DataElement de( Tag(0x0002,0x0010) );
    VL::Type strlenTSUID = (VL::Type)strlen(tsuid);
    de.SetByteValue( tsuid, strlenTSUID );
    de.SetVR( Attribute<0x0002, 0x0010>::GetVR() );
    fmi.Replace( de );
    fmi.SetDataSetTransferSyntax(ts);
  }
  fmi.FillFromDataSet( ds );

  return true;
}

bool SurfaceWriter::Write()
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
