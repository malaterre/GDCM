#include "gdcmSurfaceWriter.h"
#include "gdcmAttribute.h"

namespace gdcm
{

SurfaceWriter::SurfaceWriter():
  NumberOfSurfaces(0)
{
}

SurfaceWriter::~SurfaceWriter()
{
}

const unsigned long SurfaceWriter::GetNumberOfSurfaces() const
{
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

  File &      file  = GetFile();
  DataSet &   ds    = file.GetDataSet();

  FileMetaInformation &  fmi = file.GetHeader();
  const TransferSyntax & ts  = fmi.GetDataSetTransferSyntax();
  assert( ts.IsExplicit() || ts.IsImplicit() );

  // Number Of Surface
  const unsigned long       nbSurfaces = this->GetNumberOfSurfaces();
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
    const unsigned int diff           = nbSurfaces - nbItems;
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

      Item &    surfaceItem = surfacesSQ->GetItem(numSurface++);
      DataSet & surfaceDS   = surfaceItem.GetNestedDataSet();

      // Recommended Display Grayscale Value
      Attribute<0x0062, 0x000C> recommendedDisplayGrayscaleValue;
      recommendedDisplayGrayscaleValue.SetValue( surface->GetRecommendedDisplayGrayscaleValue() );
      surfaceDS.Replace( recommendedDisplayGrayscaleValue.GetAsDataElement() );

      // Recommended Display CIELab Value
      Attribute<0x0062, 0x000D> recommendedDisplayCIELabValue;
      recommendedDisplayCIELabValue.SetValues( surface->GetRecommendedDisplayCIELabValue(), 3 );
      surfaceDS.Replace( recommendedDisplayCIELabValue.GetAsDataElement() );

      // Surface Number
      Attribute<0x0066, 0x0003> surfaceNumber;
      surfaceNumber.SetValue( surface->GetSurfaceNumber() );
      surfaceDS.Replace( surfaceNumber.GetAsDataElement() );

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

        //*****   Surface Processing Algorithm Identification Sequence    *****//
        // hack me
      }

      // Presentation Opacity
      Attribute<0x0066, 0x000C> presentationOpacity;
      presentationOpacity.SetValue( surface->GetRecommendedPresentationOpacity() );
      surfaceDS.Replace( presentationOpacity.GetAsDataElement() );

      // Presentation Type
      Attribute<0x0066, 0x000D> presentationType;
      presentationType.SetValue( Surface::GetVIEWTypeString( surface->GetRecommendedPresentationType() ) );
      surfaceDS.Replace( presentationType.GetAsDataElement() );

      // Finite Volume
      Attribute<0x0066, 0x000E> finiteVolume;
      finiteVolume.SetValue( Surface::GetSTATESString( surface->GetFiniteVolume() ) );
      surfaceDS.Replace( finiteVolume.GetAsDataElement() );

      // Manifold
      Attribute<0x0066, 0x0010> manifold;
      manifold.SetValue( Surface::GetSTATESString( surface->GetManifold() ) );
      surfaceDS.Replace( manifold.GetAsDataElement() );

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

        // Number Of Surface Points
        Attribute<0x0066, 0x0015> numberOfSurfacePoints;
        numberOfSurfacePoints.SetValue( surface->GetNumberOfSurfacePoints() );
        surfacePointsDs.Replace( numberOfSurfacePoints.GetAsDataElement() );

        // Point Coordinates Data
        DataElement pointCoordDataDE( Tag(0x0066, 0x0016) );
        pointCoordDataDE.SetVR( VR::OF );
        const Value & pointCoordinateDataValue = surface->GetPointCoordinatesData().GetValue();
        assert( &pointCoordinateDataValue );
        pointCoordDataDE.SetValue( pointCoordinateDataValue );

        const ByteValue *bv = pointCoordDataDE.GetByteValue();
        VL vl;
        if( bv && ts.IsExplicit() )
        {
          vl = bv->GetLength();
        }
        else
        {
          vl.SetToUndefined();
        }
        pointCoordDataDE.SetVL( vl );

        surfacePointsDs.Replace( pointCoordDataDE );
      }

      //******    Surface Points Normals    *****//
      //        (0066,0012) SQ (Sequence with undefined length #=1)     # u/l, 1 Surface Points Sequence
      //          (fffe,e000) na (Item with undefined length #=1)         # u/l, 1 Item
      //            (0066,001e) UL                                         #  0, 1 Number of Vectors
      //            (0066,001f) US                                         #  0, 1 Vector Dimensionality
      //            (0066,0021) OF                                         #  0, 1_n Vector Coordinate Data
      //          (fffe,e00d) na (ItemDelimitationItem)                   #   0, 0 ItemDelimitationItem
      //        (fffe,e0dd) na (SequenceDelimitationItem)               #   0, 0 SequenceDelimitationItem
      const unsigned long numberOfVectors = surface->GetNumberOfVectors();
      if (numberOfVectors > 0)
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
        if( bv && ts.IsExplicit() )
        {
          vl = bv->GetLength();
        }
        else
        {
          vl.SetToUndefined();
        }
        vectorCoordDataDE.SetVL( vl );

        surfacePointsNormalsDS.Replace( vectorCoordDataDE );
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
        SmartPointer< MeshPrimitive > meshPrimitive = surface->GetMeshPrimitive();
        const MeshPrimitive::MPType   type          = meshPrimitive->GetPrimitiveType();
        bool                          insertInSQ    = false;

        // Primitive Point Index List
        Tag         typedPrimitiveTag;
        typedPrimitiveTag.SetGroup(0x0066);
        DataSet &   pointIndexListDS  = surfaceMeshPrimitivesDS;

        switch (type)
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
          switch (type)
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
          const unsigned int              nbItems             = typedSequenceSQ->GetNumberOfItems();
          if (nbItems < numberOfPrimitives)
          {
            const unsigned int diff           = numberOfPrimitives - nbItems;
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
            typedPointIndexListDE.SetVR( VR::OW );

            const Value & pointIndexListValue = it->GetValue();
            assert( &pointIndexListValue );
            typedPointIndexListDE.SetValue( pointIndexListValue );

            const ByteValue * pointIndexListBV = typedPointIndexListDE.GetByteValue();
            VL pointIndexListVL;
            if( pointIndexListBV && ts.IsExplicit() )
            {
              pointIndexListVL = pointIndexListBV->GetLength();
            }
            else
            {
              pointIndexListVL.SetToUndefined();
            }
            typedPointIndexListDE.SetVL( pointIndexListVL );

            pointIndexListDS.Replace( typedPointIndexListDE );
          }
        }
        else
        {
          // Handled "simple" mesh primitives

          // "Typed" Point Index List
          DataElement typedPointIndexListDE( typedPrimitiveTag );
          typedPointIndexListDE.SetVR( VR::OW );

          const Value & pointIndexListValue = meshPrimitive->GetPrimitiveData().GetValue();
          assert( &pointIndexListValue );
          typedPointIndexListDE.SetValue( pointIndexListValue );

          const ByteValue * pointIndexListBV = typedPointIndexListDE.GetByteValue();
          VL pointIndexListVL;
          if( pointIndexListBV && ts.IsExplicit() )
          {
            pointIndexListVL = pointIndexListBV->GetLength();
          }
          else
          {
            pointIndexListVL.SetToUndefined();
          }
          typedPointIndexListDE.SetVL( pointIndexListVL );

          pointIndexListDS.Replace( typedPointIndexListDE );
        }
      }
    }
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
