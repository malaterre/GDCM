/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmPixmapWriter.h"
#include "gdcmTrace.h"
#include "gdcmDataSet.h"
#include "gdcmDataElement.h"
#include "gdcmAttribute.h"
#include "gdcmUIDGenerator.h"
#include "gdcmSystem.h"
#include "gdcmPixmap.h"
#include "gdcmLookupTable.h"
#include "gdcmItem.h"
#include "gdcmSequenceOfItems.h"

namespace gdcm
{

PixmapWriter::PixmapWriter():PixelData(new Pixmap)
{
}

PixmapWriter::~PixmapWriter()
{
}

void PixmapWriter::SetPixmap(Pixmap const &img)
{
  PixelData = img;
}

void PixmapWriter::DoIconImage(DataSet & rootds, Pixmap const & image)
{
  //const Tag ticonimage(0x0088,0x0200);
  Attribute<0x0088,0x0200> iiat;
  const IconImage &icon = image.GetIconImage();
  if( !icon.IsEmpty() )
    {
    //DataElement iconimagesq = rootds.GetDataElement( ticonimage );
    //iconimagesq.SetTag( ticonimage );
    DataElement iconimagesq;
    iconimagesq.SetTag( iiat.GetTag() );
    iconimagesq.SetVR( VR::SQ );
    SmartPointer<SequenceOfItems> sq = new SequenceOfItems;
    sq->SetLengthToUndefined();

    DataSet ds;
    //SequenceOfItems* sq = iconimagesq.GetSequenceOfItems();
    //// Is SQ empty ?
    //if( !sq ) return;
    //SequenceOfItems::Iterator it = sq->Begin();
    //DataSet &ds = it->GetNestedDataSet();

    // col & rows:
    Attribute<0x0028, 0x0011> columns;
    columns.SetValue( icon.GetDimension(0) );
    ds.Insert( columns.GetAsDataElement() );

    Attribute<0x0028, 0x0010> rows;
    rows.SetValue( icon.GetDimension(1) );
    ds.Insert( rows.GetAsDataElement() );

  PixelFormat pf = icon.GetPixelFormat();
  Attribute<0x0028, 0x0100> bitsallocated;
  bitsallocated.SetValue( pf.GetBitsAllocated() );
  ds.Replace( bitsallocated.GetAsDataElement() );

  Attribute<0x0028, 0x0101> bitsstored;
  bitsstored.SetValue( pf.GetBitsStored() );
  ds.Replace( bitsstored.GetAsDataElement() );

  Attribute<0x0028, 0x0102> highbit;
  highbit.SetValue( pf.GetHighBit() );
  ds.Replace( highbit.GetAsDataElement() );

  Attribute<0x0028, 0x0103> pixelrepresentation;
  pixelrepresentation.SetValue( pf.GetPixelRepresentation() );
  ds.Replace( pixelrepresentation.GetAsDataElement() );

  Attribute<0x0028, 0x0002> samplesperpixel;
  samplesperpixel.SetValue( pf.GetSamplesPerPixel() );
  ds.Replace( samplesperpixel.GetAsDataElement() );

  if( pf.GetSamplesPerPixel() != 1 )
    {
    Attribute<0x0028, 0x0006> planarconf;
    planarconf.SetValue( icon.GetPlanarConfiguration() );
    ds.Replace( planarconf.GetAsDataElement() );
    }
  PhotometricInterpretation pi = icon.GetPhotometricInterpretation();
Attribute<0x0028,0x0004> piat;
    const char *pistr = PhotometricInterpretation::GetPIString(pi);
    DataElement de( Tag(0x0028, 0x0004 ) );
    de.SetByteValue( pistr, strlen(pistr) );
    de.SetVR( piat.GetVR() );
    ds.Replace( de );

    if ( pi == PhotometricInterpretation::PALETTE_COLOR )
      {
      const LookupTable &lut = icon.GetLUT();
      assert( (pf.GetBitsAllocated() == 8  && pf.GetPixelRepresentation() == 0) 
           || (pf.GetBitsAllocated() == 16 && pf.GetPixelRepresentation() == 0) );
      // lut descriptor:
      // (0028,1101) US 256\0\16                                 #   6, 3 RedPaletteColorLookupTableDescriptor
      // (0028,1102) US 256\0\16                                 #   6, 3 GreenPaletteColorLookupTableDescriptor
      // (0028,1103) US 256\0\16                                 #   6, 3 BluePaletteColorLookupTableDescriptor
      // lut data:
      unsigned short length, subscript, bitsize;
      unsigned short rawlut8[256];
      unsigned short rawlut16[65536];
      unsigned short *rawlut = rawlut8;
      unsigned int lutlen = 256;
      if( pf.GetBitsAllocated() == 16 )
        {
        rawlut = rawlut16;
        lutlen = 65536;
        }
      unsigned int l;

      // FIXME: should I really clear rawlut each time ?
      // RED
      memset(rawlut,0,lutlen*2);
      lut.GetLUT(LookupTable::RED, (unsigned char*)rawlut, l);
      DataElement redde( Tag(0x0028, 0x1201) );
      redde.SetVR( VR::OW );
      redde.SetByteValue( (char*)rawlut, l);
      ds.Replace( redde );
      // descriptor:
      Attribute<0x0028, 0x1101, VR::US, VM::VM3> reddesc;
      lut.GetLUTDescriptor(LookupTable::RED, length, subscript, bitsize);
      reddesc.SetValue(length,0); reddesc.SetValue(subscript,1); reddesc.SetValue(bitsize,2);
      ds.Replace( reddesc.GetAsDataElement() );

      // GREEN
      memset(rawlut,0,lutlen*2);
      lut.GetLUT(LookupTable::GREEN, (unsigned char*)rawlut, l);
      DataElement greende( Tag(0x0028, 0x1202) );
      greende.SetVR( VR::OW );
      greende.SetByteValue( (char*)rawlut, l);
      ds.Replace( greende );
      // descriptor:
      Attribute<0x0028, 0x1102, VR::US, VM::VM3> greendesc;
      lut.GetLUTDescriptor(LookupTable::GREEN, length, subscript, bitsize);
      greendesc.SetValue(length,0); greendesc.SetValue(subscript,1); greendesc.SetValue(bitsize,2);
      ds.Replace( greendesc.GetAsDataElement() );

      // BLUE
      memset(rawlut,0,lutlen*2);
      lut.GetLUT(LookupTable::BLUE, (unsigned char*)rawlut, l);
      DataElement bluede( Tag(0x0028, 0x1203) );
      bluede.SetVR( VR::OW );
      bluede.SetByteValue( (char*)rawlut, l);
      ds.Replace( bluede );
      // descriptor:
      Attribute<0x0028, 0x1103, VR::US, VM::VM3> bluedesc;
      lut.GetLUTDescriptor(LookupTable::BLUE, length, subscript, bitsize);
      bluedesc.SetValue(length,0); bluedesc.SetValue(subscript,1); bluedesc.SetValue(bitsize,2);
      ds.Replace( bluedesc.GetAsDataElement() );
      }

    //ds.Remove( Tag(0x0028, 0x1221) );
    //ds.Remove( Tag(0x0028, 0x1222) );
    //ds.Remove( Tag(0x0028, 0x1223) );


 {
  // Pixel Data
  DataElement de( Tag(0x7fe0,0x0010) );
  const Value &v = icon.GetDataElement().GetValue();
  de.SetValue( v );
  const ByteValue *bv = de.GetByteValue();
  const TransferSyntax &ts = icon.GetTransferSyntax();
  assert( ts.IsExplicit() || ts.IsImplicit() );
  VL vl;
  if( bv )
    {
    // if ts is explicit -> set VR
    vl = bv->GetLength();
    }
  else
    {
    // if ts is explicit -> set VR
    vl.SetToUndefined();
    }
  if( ts.IsExplicit() )
    {
    switch ( pf.GetBitsAllocated() )
      {
      case 8:
        de.SetVR( VR::OB );
        break;
      //case 12:
      case 16:
      case 32:
        de.SetVR( VR::OW );
        break;
      default:
        assert( 0 && "should not happen" );
        break;
      }
    }
  else
    {
    de.SetVR( VR::OB );
    }
  de.SetVL( vl );
  ds.Replace( de );
}

    Item item;
    item.SetNestedDataSet( ds );
    sq->AddItem( item );
    iconimagesq.SetValue( *sq );

    rootds.Replace( iconimagesq );
    
    }
}

bool PixmapWriter::PrepareWrite()
{
  //assert( Stream.is_open() );
  File& file = GetFile();
  DataSet& ds = file.GetDataSet();

  FileMetaInformation &fmi_orig = file.GetHeader();
  const TransferSyntax &ts_orig = fmi_orig.GetDataSetTransferSyntax();

  // col & rows:
  Attribute<0x0028, 0x0011> columns;
  columns.SetValue( PixelData->GetDimension(0) );
  ds.Replace( columns.GetAsDataElement() );

  Attribute<0x0028, 0x0010> rows;
  rows.SetValue( PixelData->GetDimension(1) );
  ds.Replace( rows.GetAsDataElement() );

  // (0028,0008) IS [12]                                     #   2, 1 NumberOfFrames
  const Tag tnumberofframes = Tag(0x0028, 0x0008);
  if( PixelData->GetNumberOfDimensions() == 3  )
    {
    Attribute<0x0028, 0x0008> numberofframes;
    assert( PixelData->GetDimension(2) > 1 );
    numberofframes.SetValue( PixelData->GetDimension(2) );
    ds.Replace( numberofframes.GetAsDataElement() );
    }
  else if( ds.FindDataElement(tnumberofframes) ) // Remove Number Of Frames
    {
    assert( PixelData->GetNumberOfDimensions() == 2 );
    assert( PixelData->GetDimension(2) == 1 );
    ds.Remove( tnumberofframes );
    }

  PixelFormat pf = PixelData->GetPixelFormat();
  PhotometricInterpretation pi = PixelData->GetPhotometricInterpretation();
  if( pi.GetSamplesPerPixel() != pf.GetSamplesPerPixel() )
    {
    gdcmWarningMacro( "Photometric Interpretation and Pixel format are not compatible: " 
      << pi.GetSamplesPerPixel() << " vs " << pf.GetSamplesPerPixel() );
    return false;
    }

  // FIXME HACK !
  if( pf.GetBitsAllocated() == 24 )
    {
    assert(0);
    pi = PhotometricInterpretation::RGB;
    pf.SetBitsAllocated( 8 );
    pf.SetBitsStored( 8 );
    pf.SetHighBit( 7 );
    pf.SetSamplesPerPixel( 3 );
    }
  // Pixel Format :
  // (0028,0100) US 8                                        #   2, 1 BitsAllocated
  // (0028,0101) US 8                                        #   2, 1 BitsStored
  // (0028,0102) US 7                                        #   2, 1 HighBit
  // (0028,0103) US 0                                        #   2, 1 PixelRepresentation
  Attribute<0x0028, 0x0100> bitsallocated;
  bitsallocated.SetValue( pf.GetBitsAllocated() );
  ds.Replace( bitsallocated.GetAsDataElement() );

  Attribute<0x0028, 0x0101> bitsstored;
  bitsstored.SetValue( pf.GetBitsStored() );
  ds.Replace( bitsstored.GetAsDataElement() );

  Attribute<0x0028, 0x0102> highbit;
  highbit.SetValue( pf.GetHighBit() );
  ds.Replace( highbit.GetAsDataElement() );

  Attribute<0x0028, 0x0103> pixelrepresentation;
  pixelrepresentation.SetValue( pf.GetPixelRepresentation() );
  ds.Replace( pixelrepresentation.GetAsDataElement() );

  Attribute<0x0028, 0x0002> samplesperpixel;
  samplesperpixel.SetValue( pf.GetSamplesPerPixel() );
  ds.Replace( samplesperpixel.GetAsDataElement() );

  if( pf.GetSamplesPerPixel() != 1 )
    {
    Attribute<0x0028, 0x0006> planarconf;
    planarconf.SetValue( PixelData->GetPlanarConfiguration() );
    ds.Replace( planarconf.GetAsDataElement() );
    }


  // Overlay Data 60xx
  unsigned int nOv = PixelData->GetNumberOfOverlays();
  for( unsigned int ovidx = 0; ovidx < nOv; ++ovidx )
    {
    // (6000,0010) US 484                                      #   2, 1 OverlayRows
    // (6000,0011) US 484                                      #   2, 1 OverlayColumns
    // (6000,0015) IS [1]                                      #   2, 1 NumberOfFramesInOverlay
    // (6000,0022) LO [Siemens MedCom Object Graphics]         #  30, 1 OverlayDescription
    // (6000,0040) CS [G]                                      #   2, 1 OverlayType
    // (6000,0050) SS 1\1                                      #   4, 2 OverlayOrigin
    // (6000,0051) US 1                                        #   2, 1 ImageFrameOrigin
    // (6000,0100) US 1                                        #   2, 1 OverlayBitsAllocated
    // (6000,0102) US 0                                        #   2, 1 OverlayBitPosition
    // (6000,3000) OW 0000\0000\0000\0000\0000\0000\0000\0000\0000\0000\0000\0000\0000... # 29282, 1 OverlayData
    DataElement de;
    const Overlay &ov = PixelData->GetOverlay(ovidx);
    Attribute<0x6000,0x0010> overlayrows;
    overlayrows.SetValue( ov.GetRows() );
    de = overlayrows.GetAsDataElement();
    de.GetTag().SetGroup( ov.GetGroup() );
    ds.Insert( de );
    Attribute<0x6000,0x0011> overlaycolumns;
    overlaycolumns.SetValue( ov.GetColumns() );
    de = overlaycolumns.GetAsDataElement();
    de.GetTag().SetGroup( ov.GetGroup() );
    ds.Insert( de );
    if( ov.GetDescription() ) // Type 3
      {
      Attribute<0x6000,0x0022> overlaydescription;
      overlaydescription.SetValue( ov.GetDescription() );
      de = overlaydescription.GetAsDataElement();
      de.GetTag().SetGroup( ov.GetGroup() );
      ds.Insert( de );
      }
    Attribute<0x6000,0x0040> overlaytype; // 'G' or 'R'
    overlaytype.SetValue( ov.GetType() );
    de = overlaytype.GetAsDataElement();
    de.GetTag().SetGroup( ov.GetGroup() );
    ds.Insert( de );
    Attribute<0x6000,0x0050> overlayorigin;
    overlayorigin.SetValues( ov.GetOrigin() );
    de = overlayorigin.GetAsDataElement();
    de.GetTag().SetGroup( ov.GetGroup() );
    ds.Insert( de );
    Attribute<0x6000,0x0100> overlaybitsallocated;
    overlaybitsallocated.SetValue( ov.GetBitsAllocated() );
    de = overlaybitsallocated.GetAsDataElement();
    de.GetTag().SetGroup( ov.GetGroup() );
    ds.Insert( de );
    Attribute<0x6000,0x0102> overlaybitposition;
    overlaybitposition.SetValue( ov.GetBitPosition() );
    de = overlaybitposition.GetAsDataElement();
    de.GetTag().SetGroup( ov.GetGroup() );
    ds.Insert( de );

    // FIXME: for now rewrite 'Overlay in pixel data' still in the pixel data element...
    if( !ov.IsInPixelData() )
      {
      const ByteValue & overlaydatabv = ov.GetOverlayData();
      DataElement overlaydata( Tag(0x6000,0x3000) );
      overlaydata.SetByteValue( overlaydatabv.GetPointer(), overlaydatabv.GetLength() );
      overlaydata.SetVR( VR::OW ); // FIXME
      overlaydata.GetTag().SetGroup( ov.GetGroup() );
      ds.Insert( overlaydata );
      }
    }

  // Pixel Data
  DataElement de( Tag(0x7fe0,0x0010) );
  const Value &v = PixelData->GetDataElement().GetValue();
  de.SetValue( v );
  const ByteValue *bv = de.GetByteValue();
  const TransferSyntax &ts = PixelData->GetTransferSyntax();
  assert( ts.IsExplicit() || ts.IsImplicit() );

//  if( !ts.IsLossy() && PixelData->IsLossy() )
//    {
//    gdcmWarningMacro( "Sorry Pixel Data in encapsulated stream was found to be lossy while Transfer Syntax does not authorized that" );
//    return false;
//    }

  if( /*ts.IsLossy() &&*/ PixelData->IsLossy() )
    {
    // Add the Lossy stuff:
    Attribute<0x0028,0x2110> at1;
    at1.SetValue( "01" );
    ds.Replace( at1.GetAsDataElement() );
    /*
    The Defined Terms for Lossy Image Compression Method (0028,2114) ar e :
    ISO_10918_1 = JPEG Lossy Compression
    ISO_14495_1 = JPEG-LS Near-lossless Compression
    ISO_15444_1 = JPEG 2000 Irreversible Compression
    ISO_13818_2 = MPEG2 Compression
     */

    if( ts_orig != TransferSyntax::TS_END )
      {
      assert( ts_orig.IsLossy() );
      Attribute<0x0028,0x2114> at3;
      if( ts_orig == TransferSyntax::JPEG2000 )
        {
        static const CSComp newvalues2[] = {"ISO_15444_1"};
        at3.SetValues(  newvalues2, 1 );
        }
      else if( ts_orig == TransferSyntax::JPEGLSNearLossless )
        {
        static const CSComp newvalues2[] = {"ISO_14495_1"};
        at3.SetValues(  newvalues2, 1 );
        }
      else if ( 
        ts_orig == TransferSyntax::JPEGBaselineProcess1 ||
        ts_orig == TransferSyntax::JPEGExtendedProcess2_4 ||
        ts_orig == TransferSyntax::JPEGExtendedProcess3_5 ||
        ts_orig == TransferSyntax::JPEGSpectralSelectionProcess6_8 ||
        ts_orig == TransferSyntax::JPEGFullProgressionProcess10_12 )
        {
        static const CSComp newvalues2[] = {"ISO_10918_1"};
        at3.SetValues(  newvalues2, 1 );
        }
      else
        {
        gdcmErrorMacro( "Pixel Data is lossy but I cannot find the original transfer syntax" );
        return false;
        }
      ds.Replace( at3.GetAsDataElement() );
      }
    }

  VL vl;
  if( bv )
    {
    // if ts is explicit -> set VR
    vl = bv->GetLength();
    }
  else
    {
    // if ts is explicit -> set VR
    vl.SetToUndefined();
    }
  if( ts.IsExplicit() )
    {
    switch ( pf.GetBitsAllocated() )
      {
      case 8:
        de.SetVR( VR::OB );
        break;
      case 12:
      case 16:
      case 32:
        de.SetVR( VR::OW );
        break;
      default:
        assert( 0 && "should not happen" );
        break;
      }
    }
  else
    {
    de.SetVR( VR::OB );
    }
  de.SetVL( vl );
  ds.Replace( de );

//      Attribute<0x0028, 0x0006> planarconfiguration;
//      planarconfiguration.SetValue( PixelData->GetPlanarConfiguration() );
//      ds.Replace( planarconfiguration.GetAsDataElement() );

  // PhotometricInterpretation
  // const Tag tphotometricinterpretation(0x0028, 0x0004);
  //if( !ds.FindDataElement( Tag(0x0028, 0x0004) ) )
    {
    assert( pi != PhotometricInterpretation::UNKNOW );
    const char *pistr = PhotometricInterpretation::GetPIString(pi);
    DataElement de( Tag(0x0028, 0x0004 ) );
    de.SetByteValue( pistr, strlen(pistr) );
    de.SetVR( Attribute<0x0028,0x0004>::GetVR() );
    ds.Insert( de );
    //if( pi == PhotometricInterpretation::RGB
    //  || pi == PhotometricInterpretation::YBR_FULL ) // FIXME
    //  {
    //  Attribute<0x0028, 0x0006> planarconfiguration;
    //  planarconfiguration.SetValue( PixelData->GetPlanarConfiguration() );
    //  ds.Replace( planarconfiguration.GetAsDataElement() );
    //  }
    //else
    if ( pi == PhotometricInterpretation::PALETTE_COLOR )
      {
      const LookupTable &lut = PixelData->GetLUT();
      assert( lut.Initialized() );
      assert( (pf.GetBitsAllocated() == 8  && pf.GetPixelRepresentation() == 0) 
           || (pf.GetBitsAllocated() == 16 && pf.GetPixelRepresentation() == 0) );
      // lut descriptor:
      // (0028,1101) US 256\0\16                                 #   6, 3 RedPaletteColorLookupTableDescriptor
      // (0028,1102) US 256\0\16                                 #   6, 3 GreenPaletteColorLookupTableDescriptor
      // (0028,1103) US 256\0\16                                 #   6, 3 BluePaletteColorLookupTableDescriptor
      // lut data:
      unsigned short length, subscript, bitsize;
      unsigned short rawlut8[256];
      unsigned short rawlut16[65536];
      unsigned short *rawlut = rawlut8;
      unsigned int lutlen = 256;
      if( pf.GetBitsAllocated() == 16 )
        {
        rawlut = rawlut16;
        lutlen = 65536;
        }
      unsigned int l;

      // FIXME: should I really clear rawlut each time ?
      // RED
      memset(rawlut,0,lutlen*2);
      lut.GetLUT(LookupTable::RED, (unsigned char*)rawlut, l);
      DataElement redde( Tag(0x0028, 0x1201) );
      redde.SetVR( VR::OW );
      redde.SetByteValue( (char*)rawlut, l);
      ds.Replace( redde );
      // descriptor:
      Attribute<0x0028, 0x1101, VR::US, VM::VM3> reddesc;
      lut.GetLUTDescriptor(LookupTable::RED, length, subscript, bitsize);
      reddesc.SetValue(length,0); reddesc.SetValue(subscript,1); reddesc.SetValue(bitsize,2);
      ds.Replace( reddesc.GetAsDataElement() );

      // GREEN
      memset(rawlut,0,lutlen*2);
      lut.GetLUT(LookupTable::GREEN, (unsigned char*)rawlut, l);
      DataElement greende( Tag(0x0028, 0x1202) );
      greende.SetVR( VR::OW );
      greende.SetByteValue( (char*)rawlut, l);
      ds.Replace( greende );
      // descriptor:
      Attribute<0x0028, 0x1102, VR::US, VM::VM3> greendesc;
      lut.GetLUTDescriptor(LookupTable::GREEN, length, subscript, bitsize);
      greendesc.SetValue(length,0); greendesc.SetValue(subscript,1); greendesc.SetValue(bitsize,2);
      ds.Replace( greendesc.GetAsDataElement() );

      // BLUE
      memset(rawlut,0,lutlen*2);
      lut.GetLUT(LookupTable::BLUE, (unsigned char*)rawlut, l);
      DataElement bluede( Tag(0x0028, 0x1203) );
      bluede.SetVR( VR::OW );
      bluede.SetByteValue( (char*)rawlut, l);
      ds.Replace( bluede );
      // descriptor:
      Attribute<0x0028, 0x1103, VR::US, VM::VM3> bluedesc;
      lut.GetLUTDescriptor(LookupTable::BLUE, length, subscript, bitsize);
      bluedesc.SetValue(length,0); bluedesc.SetValue(subscript,1); bluedesc.SetValue(bitsize,2);
      ds.Replace( bluedesc.GetAsDataElement() );
      }

    ds.Remove( Tag(0x0028, 0x1221) );
    ds.Remove( Tag(0x0028, 0x1222) );
    ds.Remove( Tag(0x0028, 0x1223) );

    }

  // FIXME shouldn't this be done by the ImageApplyLookupTable filter ?
  if( pi == PhotometricInterpretation::RGB )
    {
    // usual tags:
    ds.Remove( Tag(0x0028, 0x1101) );
    ds.Remove( Tag(0x0028, 0x1102) );
    ds.Remove( Tag(0x0028, 0x1103) );

    ds.Remove( Tag(0x0028, 0x1201) );
    ds.Remove( Tag(0x0028, 0x1202) );
    ds.Remove( Tag(0x0028, 0x1203) );

    // Dont' forget the segmented one:
    ds.Remove( Tag(0x0028, 0x1221) );
    ds.Remove( Tag(0x0028, 0x1222) );
    ds.Remove( Tag(0x0028, 0x1223) );

    // PaletteColorLookupTableUID ??
    ds.Remove( Tag(0x0028, 0x1199) );
    }
//  Attribute<0x0028, 0x0004> photometricinterpretation;
//  photometricinterpretation.SetValue( pi );
//  ds.Replace( photometricinterpretation.GetAsDataElement() );
Attribute<0x0028,0x0004> piat;
//const DataElement &pide = ds.GetDataElement( piat.GetTag() );
//const char *str1 = pide.GetByteValue()->GetPointer();
{
    const char *pistr = PhotometricInterpretation::GetPIString(pi);
    DataElement de( Tag(0x0028, 0x0004 ) );
    de.SetByteValue( pistr, strlen(pistr) );
    de.SetVR( piat.GetVR() );
    ds.Replace( de );
}


  // Do Icon Image
  DoIconImage(ds, GetPixmap());

  MediaStorage ms;
  ms.SetFromFile( GetFile() );
  assert( ms != MediaStorage::MS_END );

  const char* msstr = MediaStorage::GetMSString(ms);
  if( !ds.FindDataElement( Tag(0x0008, 0x0016) ) )
    {
    DataElement de( Tag(0x0008, 0x0016 ) );
    de.SetByteValue( msstr, strlen(msstr) );
    de.SetVR( Attribute<0x0008, 0x0016>::GetVR() );
    ds.Insert( de );
    }
  else
    {
    const ByteValue *bv = ds.GetDataElement( Tag(0x0008,0x0016) ).GetByteValue();
    if( strncmp( bv->GetPointer(), msstr, bv->GetLength() ) != 0 )
      {
      DataElement de = ds.GetDataElement( Tag(0x0008,0x0016) );
      de.SetByteValue( msstr, strlen(msstr) );
      ds.Replace( de );
      }
    else
      {
      assert( bv->GetLength() == strlen( msstr ) || bv->GetLength() == strlen(msstr) + 1 );
      }
    }

  // (re)Compute MediaStorage:
  if( !ds.FindDataElement( Tag(0x0008, 0x0060) ) )
    {
    const char *modality = ms.GetModality();
    DataElement de( Tag(0x0008, 0x0060 ) );
    de.SetByteValue( modality, strlen(modality) );
    de.SetVR( Attribute<0x0008, 0x0060>::GetVR() );
    ds.Insert( de );
    }
  else
    {
    const ByteValue *bv = ds.GetDataElement( Tag(0x0008, 0x0060 ) ).GetByteValue();
    std::string modality2;
    if( bv )
      {
      modality2 = std::string( bv->GetPointer(), bv->GetLength() );
      //assert( modality2.find( ' ' ) == std::string::npos ); // no space ...
      }
    else
      {
      // remove empty Modality, and set a new one...
      ds.Remove( Tag(0x0008, 0x0060 ) ); // Modality is Type 1 !
      assert( ms != MediaStorage::MS_END );
      }
/*
    if( modality2 != ms.GetModality() )
      {
      assert( std::string(ms.GetModality()).find( ' ' ) == std::string::npos ); // no space ...
      DataElement de( Tag(0x0008, 0x0060 ) );
      de.SetByteValue( ms.GetModality(), strlen(ms.GetModality()) );
      de.SetVR( Attribute<0x0008, 0x0060>::GetVR() );
      ds.Insert( de ); // FIXME: should we always replace ?
      // Well technically you could have a SecondaryCaptureImageStorage with a modality of NM...
      }
*/
    }
  if( !ds.FindDataElement( Tag(0x0008, 0x0064) ) )
    {
    if( ms == MediaStorage::SecondaryCaptureImageStorage )
      {
      // (0008,0064) CS [SI]                                     #   2, 1 ConversionType
      const char conversion[] = "WSD "; // FIXME
      DataElement de( Tag(0x0008, 0x0064 ) );
      de.SetByteValue( conversion, strlen(conversion) );
      de.SetVR( Attribute<0x0008, 0x0064>::GetVR() );
      ds.Insert( de );
      }
    }
  //if( !ds.FindDataElement( Tag(0x0020, 0x0062) ) )
  //  {
  //  if( ms == MediaStorage::SecondaryCaptureImageStorage )
  //    {
  //    const char laterality[] = "U "; // FIXME
  //    DataElement de( Tag(0x0020, 0x0062 ) );
  //    de.SetByteValue( laterality, strlen(laterality) );
  //    de.SetVR( Attribute<0x0020, 0x0062>::GetVR() );
  //    ds.Insert( de );
  //    }
  //  }



  // UIDs:
  // (0008,0018) UI [1.3.6.1.4.1.5962.1.1.1.1.3.20040826185059.5457] #  46, 1 SOPInstanceUID
  // (0020,000d) UI [1.3.6.1.4.1.5962.1.2.1.20040826185059.5457] #  42, 1 StudyInstanceUID
  // (0020,000e) UI [1.3.6.1.4.1.5962.1.3.1.1.20040826185059.5457] #  44, 1 SeriesInstanceUID
  UIDGenerator uid;

  // Be careful with the SOP Instance UID:
  if( ds.FindDataElement( Tag(0x0008, 0x0018) ) && false )
    {
    // We are coming from a real DICOM image, we need to reference it...
    //assert( 0 && "TODO FIXME" );
    const Tag tsourceImageSequence(0x0008,0x2112);
    //assert( ds.FindDataElement( tsourceImageSequence ) == false );
    SmartPointer<SequenceOfItems> sq;
    if( ds.FindDataElement( tsourceImageSequence ) )
      {
      DataElement &de = (DataElement&)ds.GetDataElement( tsourceImageSequence );
      //assert( de.IsUndefinedLength() );
      de.SetVLToUndefined(); // For now
      if( de.IsEmpty() )
        {
        sq = new SequenceOfItems;
        de.SetValue( *sq );
        }
      sq = de.GetValueAsSQ();
      }
    else
      {
      sq = new SequenceOfItems;
      }
    sq->SetLengthToUndefined();
    Item item; //( /*Tag(0xfffe,0xe000)*/ );
    de.SetVLToUndefined();
    //DataSet sourceimageds;
    // (0008,1150) UI =MRImageStorage                          #  26, 1 ReferencedSOPClassUID
    // (0008,1155) UI [1.3.6.1.4.17434.1.1.5.2.1160650698.1160650698.0] #  48, 1 ReferencedSOPInstanceUID
    DataElement referencedSOPClassUID = ds.GetDataElement( Tag(0x0008,0x0016) );
    referencedSOPClassUID.SetTag( Tag(0x0008,0x1150 ) );
    DataElement referencedSOPInstanceUID = ds.GetDataElement( Tag(0x0008,0x0018) );
    referencedSOPInstanceUID.SetTag( Tag(0x0008,0x1155) );
    //item.SetNestedDataSet( sourceimageds );
    item.SetVLToUndefined();
    item.InsertDataElement( referencedSOPClassUID );
    item.InsertDataElement( referencedSOPInstanceUID );
    sq->AddItem( item );
    if( !ds.FindDataElement( tsourceImageSequence ) )
      {
      DataElement de( tsourceImageSequence );
      de.SetVR( VR::SQ );
      de.SetValue( *sq );
      de.SetVLToUndefined();
      //std::cout << de << std::endl;
      ds.Insert( de );
      }
    }
    {
    const char *sop = uid.Generate();
    DataElement de( Tag(0x0008,0x0018) );
    de.SetByteValue( sop, strlen(sop) );
    de.SetVR( Attribute<0x0008, 0x0018>::GetVR() );
    // FIXME: Right now we are not actually 'replacing' the value
    ds.Insert( de );
    }

  // Are we on a particular Study ? If not create a new UID
  if( !ds.FindDataElement( Tag(0x0020, 0x000d) ) )
    {
    const char *study = uid.Generate();
    DataElement de( Tag(0x0020,0x000d) );
    de.SetByteValue( study, strlen(study) );
    de.SetVR( Attribute<0x0020, 0x000d>::GetVR() );
    ds.Insert( de );
    }

  // Are we on a particular Series ? If not create a new UID
  if( !ds.FindDataElement( Tag(0x0020, 0x000e) ) )
    {
    const char *series = uid.Generate();
    DataElement de( Tag(0x0020,0x000e) );
    de.SetByteValue( series, strlen(series) );
    de.SetVR( Attribute<0x0020, 0x000e>::GetVR() );
    ds.Insert( de );
    }

  FileMetaInformation &fmi = file.GetHeader();

  //assert( ts == TransferSyntax::ImplicitVRLittleEndian );
    {
    const char *tsuid = TransferSyntax::GetTSString( ts );
    DataElement de( Tag(0x0002,0x0010) );
    de.SetByteValue( tsuid, strlen(tsuid) );
    de.SetVR( Attribute<0x0002, 0x0010>::GetVR() );
    fmi.Replace( de );
    fmi.SetDataSetTransferSyntax(ts);
    }
  fmi.Remove( Tag(0x0002,0x0012) ); // Set the Implementation Class UID properly
  fmi.Remove( Tag(0x0002,0x0013) ); // 
  fmi.Remove( Tag(0x0002,0x0016) ); // 
  fmi.FillFromDataSet( ds );

  // Some Type 2 Element:
  // PatientName
  if( !ds.FindDataElement( Tag(0x0010,0x0010) ) )
    {
    DataElement de( Tag(0x0010,0x0010) );
    de.SetVR( Attribute<0x0010,0x0010>::GetVR() );
    ds.Insert( de );
    }
  // PatientID
  if( !ds.FindDataElement( Tag(0x0010,0x0020) ) )
    {
    DataElement de( Tag(0x0010,0x0020) );
    de.SetVR( Attribute<0x0010,0x0020>::GetVR() );
    ds.Insert( de );
    }
  // PatientBirthDate
  if( !ds.FindDataElement( Tag(0x0010,0x0030) ) )
    {
    DataElement de( Tag(0x0010,0x0030) );
    de.SetVR( Attribute<0x0010,0x0030>::GetVR() );
    ds.Insert( de );
    }
  // PatientSex
  if( !ds.FindDataElement( Tag(0x0010,0x0040) ) )
    {
    DataElement de( Tag(0x0010,0x0040) );
    de.SetVR( Attribute<0x0010,0x0040>::GetVR() );
    ds.Insert( de );
    }
  // Laterality
  if( false && !ds.FindDataElement( Tag(0x0020,0x0060) ) )
    {
    DataElement de( Tag(0x0020,0x0060) );
    de.SetVR( Attribute<0x0020,0x0060>::GetVR() );
    ds.Insert( de );
    }
  // StudyDate
  char date[22];
  const size_t datelen = 8;
  int res = System::GetCurrentDateTime(date);
  assert( res );
  if( !ds.FindDataElement( Tag(0x0008,0x0020) ) )
    {
    DataElement de( Tag(0x0008,0x0020) );
    // Do not copy the whole cstring:
    de.SetByteValue( date, datelen );
    de.SetVR( Attribute<0x0008,0x0020>::GetVR() );
    ds.Insert( de );
    }
  // StudyTime
  const size_t timelen = 6 + 1 + 6; // time + milliseconds
  Attribute<0x0008, 0x0030> studytime;
  if( !ds.FindDataElement( studytime.GetTag() ) )
    {
    // Do not copy the whole cstring:
    studytime.SetValue( CSComp(date+datelen, timelen) );
    ds.Insert( studytime.GetAsDataElement() );
    }
  // ReferringPhysicianName
  if( !ds.FindDataElement( Tag(0x0008,0x0090) ) )
    {
    DataElement de( Tag(0x0008,0x0090) );
    de.SetVR( Attribute<0x0008,0x0090>::GetVR() );
    ds.Insert( de );
    }
  // StudyID
  if( !ds.FindDataElement( Tag(0x0020,0x0010) ) )
    {
    // FIXME: this one is actually bad since the value is needed for DICOMDIR construction
    DataElement de( Tag(0x0020,0x0010) );
    de.SetVR( Attribute<0x0020,0x0010>::GetVR() );
    ds.Insert( de );
    }
  // AccessionNumber
  if( !ds.FindDataElement( Tag(0x0008,0x0050) ) )
    {
    DataElement de( Tag(0x0008,0x0050) );
    de.SetVR( Attribute<0x0008,0x0050>::GetVR() );
    ds.Insert( de );
    }
  // SeriesNumber
  if( !ds.FindDataElement( Tag(0x0020,0x0011) ) )
    {
    DataElement de( Tag(0x0020,0x0011) );
    de.SetVR( Attribute<0x0020,0x0011>::GetVR() );
    ds.Insert( de );
    }
  // InstanceNumber
  if( !ds.FindDataElement( Tag(0x0020,0x0013) ) )
    {
    DataElement de( Tag(0x0020,0x0013) );
    de.SetVR( Attribute<0x0020,0x0013>::GetVR() );
    ds.Insert( de );
    }
  // Patient Orientation
  if( ms == MediaStorage::SecondaryCaptureImageStorage && !ds.FindDataElement( Tag(0x0020,0x0020) ) )
    {
    DataElement de( Tag(0x0020,0x0020) );
    de.SetVR( Attribute<0x0020,0x0020>::GetVR() );
    ds.Insert( de );
    }
  //const char dummy[] = "dummy";
  //assert( Stream.is_open() );
  //Stream << dummy;


  return true;
}

bool PixmapWriter::Write()
{
  if( !PrepareWrite() ) return false;

  assert( Stream );
  if( !Writer::Write() )
    {
    return false;
    }
  return true;
}

void PixmapWriter::SetImage(Pixmap const &img)
{
  PixelData = img;
}

} // end namespace gdcm
