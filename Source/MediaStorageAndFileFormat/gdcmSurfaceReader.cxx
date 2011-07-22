#include "gdcmSurfaceReader.h"
#include "gdcmMediaStorage.h"
#include "gdcmAttribute.h"
#include "gdcmString.h"

namespace gdcm
{

SurfaceReader::SurfaceReader()
{
}

SurfaceReader::~SurfaceReader()
{
}

const unsigned long SurfaceReader::GetNumberOfSurfaces() const
{
  return Segments.size();
}

bool SurfaceReader::Read()
{
  bool res = false;

  if (!SegmentReader::Read())
  {
    return res;
  }

  const FileMetaInformation & header  = F->GetHeader();
  MediaStorage                ms      = header.GetMediaStorage();
  if( ms == MediaStorage::SurfaceSegmentationStorage )
  {
    res = ReadSurfaces();
  }
  else
  {
    // Try to find Surface Sequence
    const DataSet & dsRoot = F->GetDataSet();
    if (dsRoot.FindDataElement( Tag(0x0066, 0x0002) ))
    {
      res = ReadSurfaces();
    }
  }

  return res;
}

bool SurfaceReader::ReadSurfaces()
{
  bool                        res     = false;

  const FileMetaInformation & header  = F->GetHeader();
  const DataSet &             ds      = F->GetDataSet();
  const TransferSyntax &      ts      = header.GetDataSetTransferSyntax();

  // Surface Sequence
  const Tag surfaceSQTag(0x0066, 0x0002);
  if (ds.FindDataElement(surfaceSQTag))
  {
    SmartPointer< SequenceOfItems > surfaceSQ = ds.GetDataElement(surfaceSQTag).GetValueAsSQ();

    const unsigned long numberOfSurfaces = (unsigned long) surfaceSQ->GetNumberOfItems();
    if ( numberOfSurfaces == 0)
      return false;

    for (unsigned long i = 1; i <= numberOfSurfaces; ++i) // FIXME : use iterator, because GetNumberOfItems() return unsigned int
    {
      const Item & surfaceItem = surfaceSQ->GetItem(i);
      if ( !ReadSurface( surfaceItem, i ) )
      {
        gdcmWarningMacro( "Surface "<<i<<" reading error" );
      }
    }

    res = true;
  }

  return res;
}

bool SurfaceReader::ReadSurface(const Item & surfaceItem, const unsigned long idx)
{
  SmartPointer< Surface > surface = new Surface;

  const DataSet & surfacesDS = surfaceItem.GetNestedDataSet();

  // Recommended Display Grayscale Value
  Attribute<0x0062, 0x000C> recommendedDisplayGrayscaleValue;
  recommendedDisplayGrayscaleValue.SetFromDataSet( surfacesDS );
  surface->SetRecommendedDisplayGrayscaleValue( recommendedDisplayGrayscaleValue.GetValue() );

  // Recommended Display CIELab Value
  Attribute<0x0062, 0x000D> recommendedDisplayCIELabValue;
  recommendedDisplayCIELabValue.SetFromDataSet( surfacesDS );
  const unsigned short *  array     = recommendedDisplayCIELabValue.GetValues();
  unsigned short    CIELavValue[3]  = {0, 0, 0};
  unsigned int      i               = 0;
  while (array != 0 && i < 3)
    CIELavValue[i++] = *(array++);
  surface->SetRecommendedDisplayCIELabValue( CIELavValue );

  // Surface Number
  Attribute<0x0066, 0x0003> surfaceNumberAt;
  surfaceNumberAt.SetFromDataSet( surfacesDS );
  unsigned long surfaceNumber = idx;
  if ( !surfaceNumberAt.GetAsDataElement().IsEmpty() )
  {
    surfaceNumber = surfaceNumberAt.GetValue();
  }
  surface->SetSurfaceNumber( surfaceNumber );

  // Surface Comments
  Attribute<0x0066, 0x0004> surfaceComments;
  surfaceComments.SetFromDataSet( surfacesDS );
  surface->SetSurfaceComments( surfaceComments.GetValue() );

  // Surface Processing
  Attribute<0x0066, 0x0009> surfaceProcessingAt;
  surfaceProcessingAt.SetFromDataSet( surfacesDS );
  String<> surfaceProcessingStr( surfaceProcessingAt.GetValue() );
  bool surfaceProcessing;
  if (surfaceProcessingStr.Trim() == "YES")
    surfaceProcessing = true;
  else
    surfaceProcessing = false;
  surface->SetSurfaceProcessing( surfaceProcessing );

  if (surfaceProcessing)
  {
    Attribute<0x0066, 0x000A> surfaceProcessingRatioAt;
    surfaceProcessingRatioAt.SetFromDataSet( surfacesDS );
    surface->SetSurfaceProcessingRatio( surfaceProcessingRatioAt.GetValue() );

    //*****   Surface Processing Algorithm Identification Sequence    *****//
    // hack me
  }

  // Recommended Presentation Opacity
  Attribute<0x0066, 0x000C> recommendedPresentationOpacity;
  recommendedPresentationOpacity.SetFromDataSet( surfacesDS );
  surface->SetRecommendedPresentationOpacity( recommendedPresentationOpacity.GetValue() );

  // Recommended Presentation Type
  Attribute<0x0066, 0x000D> recommendedPresentationType;
  recommendedPresentationType.SetFromDataSet( surfacesDS );
  surface->SetRecommendedPresentationType( Surface::GetVIEWType( recommendedPresentationType.GetValue() ) );

  // Finite Volume
  Attribute<0x0066, 0x000E> finiteVolume;
  finiteVolume.SetFromDataSet( surfacesDS );
  surface->SetFiniteVolume( Surface::GetSTATES( finiteVolume.GetValue() ) );

  // Manifold
  Attribute<0x0066, 0x0010> manifold;
  manifold.SetFromDataSet( surfacesDS );
  surface->SetManifold( Surface::GetSTATES( manifold.GetValue() ) );

  //*****   Surface Points Sequence   ******//
  const Tag surfacePointsSQTag(0x0066, 0x0011);
  if ( !surfacesDS.FindDataElement(surfacePointsSQTag))
  {
    gdcmWarningMacro( "No Surface Point Sequence Found" );
    return false;
  }
  SmartPointer< SequenceOfItems > surfacePointsSQ = surfacesDS.GetDataElement(surfacePointsSQTag).GetValueAsSQ();

  if ( surfacePointsSQ->GetNumberOfItems() == 0)  // One Item shall be permitted
  {
    gdcmWarningMacro( "Surface Point Sequence empty" );
    return false;
  }

  const DataSet & surfacePointsDS = surfacePointsSQ->GetItem(1).GetNestedDataSet();

  // Number of Surface Points
  Attribute<0x0066, 0x0015> numberOfSurfacePoints;
  numberOfSurfacePoints.SetFromDataSet( surfacePointsDS );
  surface->SetNumberOfSurfacePoints( numberOfSurfacePoints.GetValue() );

  const Tag pointCoordDataTag = Tag(0x0066, 0x0016);
  if( !surfacePointsDS.FindDataElement( pointCoordDataTag ) )
    {
    gdcmWarningMacro( "No Point Coordinates Data Found" );
    return false;
    }
  const DataElement & de = surfacePointsDS.GetDataElement( pointCoordDataTag );
  surface->SetPointCoordinatesData( de );

  //*****   Surface Points Normals Sequence   ******//
  const Tag surfaceNormalsSQTag(0x0066, 0x0012);
  if ( surfacesDS.FindDataElement(surfaceNormalsSQTag))
  {
    SmartPointer< SequenceOfItems > surfaceNormalsSQ = surfacesDS.GetDataElement(surfaceNormalsSQTag).GetValueAsSQ();

    if ( surfaceNormalsSQ->GetNumberOfItems() < 1)  // One Item shall be permitted
    {
      const DataSet & surfaceNormalsDS = surfaceNormalsSQ->GetItem(1).GetNestedDataSet();

      // Number of Vectors
      Attribute<0x0066, 0x001E> numberOfVectors;
      numberOfVectors.SetFromDataSet( surfaceNormalsDS );
      surface->SetNumberOfVectors( numberOfVectors.GetValue() );

      // Vector Dimensionality
      Attribute<0x0066, 0x001F> vectorDimensionality;
      vectorDimensionality.SetFromDataSet( surfaceNormalsDS );
      surface->SetVectorDimensionality( vectorDimensionality.GetValue() );

      const Tag vectorCoordDataTag = Tag(0x0066, 0x0021);
      if( surfaceNormalsDS.FindDataElement( vectorCoordDataTag ) )
      {
        const DataElement & de = surfaceNormalsDS.GetDataElement( vectorCoordDataTag );
        surface->SetVectorCoordinateData( de );
      }
      else
      {
        gdcmWarningMacro( "No Vector Coordinate Data Found" );
        return false;
      }
    }
    else
    {
      gdcmWarningMacro( "Surface Point Normals Sequence empty" );
//      return false;
    }
  }

  //*****   Surface Mesh Primitives Sequence   ******//
  const Tag surfacePrimitivesSQTag(0x0066, 0x0013);
  if ( !surfacesDS.FindDataElement(surfacePrimitivesSQTag))
  {
    gdcmWarningMacro( "No Surface Mesh Primitives Sequence Found" );
    return false;
  }
  SmartPointer< SequenceOfItems > surfacePrimitivesSQ = surfacesDS.GetDataElement(surfacePrimitivesSQTag).GetValueAsSQ();

  if ( surfacePrimitivesSQ->GetNumberOfItems() < 1)  // One Item shall be permitted
  {
    gdcmWarningMacro( "Surface Mesh Primitives Sequence empty" );
    return false;
  }

  SmartPointer< MeshPrimitive > meshPrimitive = new MeshPrimitive;
  DataSet &                     surfacePrimitivesDS = surfacePrimitivesSQ->GetItem(1).GetNestedDataSet();
  Tag                           typedTag;

  if (surfacePrimitivesDS.FindDataElement( Tag(0x0066, 0x0023) ))
  {
    typedTag = Tag(0x0066, 0x0023);
    meshPrimitive->SetPrimitiveType( MeshPrimitive::TRIANGLE );
  }
  else if (surfacePrimitivesDS.FindDataElement( Tag(0x0066, 0x0024)) )
  {
    typedTag = Tag(0x0066, 0x0024);
    meshPrimitive->SetPrimitiveType( MeshPrimitive::EDGE );
  }
  else if (surfacePrimitivesDS.FindDataElement( Tag(0x0066, 0x0025)) )
  {
    typedTag = Tag(0x0066, 0x0025);
    meshPrimitive->SetPrimitiveType( MeshPrimitive::VERTEX );
  }
  else
  {
    SmartPointer< SequenceOfItems > typedSQ;
    if (surfacePrimitivesDS.FindDataElement( Tag(0x0066, 0x0026) ))
    {
      typedSQ = surfacePrimitivesDS.GetDataElement( Tag(0x0066, 0x0026) ).GetValueAsSQ();
      meshPrimitive->SetPrimitiveType( MeshPrimitive::TRIANGLE_STRIP );
    }
    else if (surfacePrimitivesDS.FindDataElement( Tag(0x0066, 0x0027)) )
    {
      typedSQ = surfacePrimitivesDS.GetDataElement( Tag(0x0066, 0x0027) ).GetValueAsSQ();
      meshPrimitive->SetPrimitiveType( MeshPrimitive::TRIANGLE_FAN );
    }
    else if (surfacePrimitivesDS.FindDataElement( Tag(0x0066, 0x0028)) )
    {
      typedSQ = surfacePrimitivesDS.GetDataElement( Tag(0x0066, 0x0028) ).GetValueAsSQ();
      meshPrimitive->SetPrimitiveType( MeshPrimitive::LINE );
    }
    else if (surfacePrimitivesDS.FindDataElement( Tag(0x0066, 0x0034)) )
    {
      typedSQ = surfacePrimitivesDS.GetDataElement( Tag(0x0066, 0x0034) ).GetValueAsSQ();
      meshPrimitive->SetPrimitiveType( MeshPrimitive::FACET );
    }

    if (typedSQ && typedSQ->GetNumberOfItems() > 0)
    {
      const unsigned int              nbItems = typedSQ->GetNumberOfItems();
      MeshPrimitive::PrimitivesData & primitivesData= meshPrimitive->GetPrimitivesData();
      primitivesData.reserve( nbItems );

      SequenceOfItems::ConstIterator it   = typedSQ->Begin();
      SequenceOfItems::ConstIterator itEnd= typedSQ->End();
      for (; it != itEnd; it++)
      {
        const DataSet & typedPrimitivesDS = it->GetNestedDataSet();
        if ( typedPrimitivesDS.FindDataElement( Tag(0x0066, 0x0029)) )
        {
          meshPrimitive->AddPrimitiveData( typedPrimitivesDS.GetDataElement( Tag(0x0066, 0x0029)) );
        }
        else
        {
          gdcmWarningMacro( "Missing Primitive Point Index List" );
          return false;
        }
      }
    }
    else
    {
      gdcmWarningMacro( "Mesh Primitive typed Sequence empty" );
      return false;
    }
  }

  if (typedTag.GetElementTag() != 0)
  {
    const DataElement & meshPrimitiveData = surfacePrimitivesDS.GetDataElement( typedTag );
    meshPrimitive->SetPrimitiveData( meshPrimitiveData );
  }
  else
  {
    gdcmWarningMacro( "No typed Point Index List found" );
    return false;
  }

  // Add a MeshPrimitive to the surface
  surface->SetMeshPrimitive( *meshPrimitive );

  // Add surface to the appropriated segment
  SmartPointer< Segment > segment = Segments[surfaceNumber];
  segment->AddSurface(surface);

  return true;
}

}
