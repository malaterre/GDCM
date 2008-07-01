/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImage.h"
#include "gdcmTrace.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmDataSet.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmFragment.h"
#include "gdcmRAWCodec.h"
#include "gdcmJPEGCodec.h"
#include "gdcmJPEG2000Codec.h"
#include "gdcmRLECodec.h"

#include <iostream>

namespace gdcm
{

/*
 * Internal implementation everything assume that NumberOfDimensions was set
 */
unsigned int Image::GetNumberOfDimensions() const
{
  assert( NumberOfDimensions );
  return NumberOfDimensions;
}

void Image::SetNumberOfDimensions(unsigned int dim)
{
  NumberOfDimensions = dim;
  assert( NumberOfDimensions );
  Dimensions.resize( NumberOfDimensions ); // fill with 0
  Spacing.resize( NumberOfDimensions, 1 ); // fill with 1
}

// TODO does it make sense to PlanarConfiguration in Image
// and SamplesPerPixel in PixelFormat when those two are linked...
unsigned int Image::GetPlanarConfiguration() const
{
  if( PlanarConfiguration && PF.GetSamplesPerPixel() != 3 )
    {
    // LEADTOOLS_FLOWERS-8-PAL-RLE.dcm
    // User specify PlanarConfiguration whereas SamplesPerPixel != 3
    gdcmWarningMacro( 
      "Can't set PlanarConfiguration if SamplesPerPixel is not 3" );
    // Let's assume it's this way...
    return 0;
    }
  return PlanarConfiguration;
}

void Image::SetPlanarConfiguration(unsigned int pc)
{
  PlanarConfiguration = pc;
}

const PhotometricInterpretation &Image::GetPhotometricInterpretation() const
{
  return PI;
}

void Image::SetPhotometricInterpretation(
  PhotometricInterpretation const &pi)
{
  PI = pi;
}

const unsigned int *Image::GetDimensions() const
{
  assert( NumberOfDimensions );
  return &Dimensions[0];
}

unsigned int Image::GetDimension(unsigned int idx) const
{
  return Dimensions[idx];
}

void Image::SetDimensions(unsigned int *dims)
{
  assert( NumberOfDimensions );
  assert( Dimensions.empty() );
  Dimensions = std::vector<unsigned int>(dims, 
    dims+NumberOfDimensions);
}

void Image::SetDimension(unsigned int idx, unsigned int dim)
{
  assert( NumberOfDimensions );
  assert( idx < NumberOfDimensions );
  Dimensions.resize( NumberOfDimensions );
  // Can dim be 0 ??
  Dimensions[idx] = dim;
}

const double *Image::GetSpacing() const
{
  assert( NumberOfDimensions );
  return &Spacing[0];
}

double Image::GetSpacing(unsigned int idx) const
{
  assert( NumberOfDimensions );
  if( idx < Spacing.size() )
    {
    return Spacing[idx];
    }
  //assert( 0 && "Should not happen" );
  return 1; // FIXME ???
}

void Image::SetSpacing(const double *spacing)
{
  assert( NumberOfDimensions );
  Spacing = std::vector<double>(spacing, 
    spacing+NumberOfDimensions);
}

void Image::SetSpacing(unsigned int idx, double spacing)
{
  Spacing.resize( idx + 1 );
  Spacing[idx] = spacing;
}

const double *Image::GetOrigin() const
{
  assert( NumberOfDimensions );
  if( !Origin.empty() )
    return &Origin[0];
  return 0;
}

double Image::GetOrigin(unsigned int idx) const
{
  assert( NumberOfDimensions );
  if( idx < Origin.size() )
    {
    return Origin[idx];
    }
  return 0; // FIXME ???
}

void Image::SetOrigin(const float *ori)
{
  assert( NumberOfDimensions );
  Origin.resize( NumberOfDimensions );
  for(unsigned int i = 0; i < NumberOfDimensions; ++i)
    {
    Origin[i] = ori[i];
    }
}

void Image::SetOrigin(const double *ori)
{
  assert( NumberOfDimensions );
  Origin = std::vector<double>(ori, 
    ori+NumberOfDimensions);
}

void Image::SetOrigin(unsigned int idx, double ori)
{
  Origin.resize( idx + 1 );
  Origin[idx] = ori;
}

const double *Image::GetDirectionCosines() const
{
  assert( NumberOfDimensions );
  if( !DirectionCosines.empty() )
    return &DirectionCosines[0];
  return 0;
}
double Image::GetDirectionCosines(unsigned int idx) const
{
  assert( NumberOfDimensions );
  if( idx < DirectionCosines.size() )
    {
    return DirectionCosines[idx];
    }
  return 0; // FIXME !!
}
void Image::SetDirectionCosines(const float *dircos)
{
  assert( NumberOfDimensions );
  DirectionCosines.resize( 6 );
  for(int i = 0; i < 6; ++i)
    {
    DirectionCosines[i] = dircos[i];
    }
}
void Image::SetDirectionCosines(const double *dircos)
{
  assert( NumberOfDimensions );
  DirectionCosines = std::vector<double>(dircos, 
    dircos+6);
}
void Image::SetDirectionCosines(unsigned int idx, double dircos)
{
  DirectionCosines.resize( idx + 1 );
  DirectionCosines[idx] = dircos;
}

unsigned long Image::GetBufferLength() const
{
  assert( NumberOfDimensions );
  assert( NumberOfDimensions == Dimensions.size() );
  unsigned long len = 0;
  unsigned int mul = 1;
  // First multiply the dimensions:
  std::vector<unsigned int>::const_iterator it = Dimensions.begin();
  for(; it != Dimensions.end(); ++it)
    {
    mul *= *it;
    }
  // Multiply by the pixel size:
  // Special handling of packed format:
  if( PF == PixelFormat::UINT12 )
    {
    assert( PF.GetSamplesPerPixel() == 1 );
    unsigned int save = mul;
    save *= 12;
    save /= 8;
    assert( save * 8 / 12 == mul );
    mul = save;
    }
  else
    {
    mul *= PF.GetPixelSize();
    }
  len = mul;

  assert( len != 0 );
  return len;
}


bool Image::AreOverlaysInPixelData() const
{
  int total = 0;
  std::vector<Overlay>::const_iterator it = Overlays.begin();
  for(; it != Overlays.end(); ++it)
    {
    total += (int)it->IsInPixelData();
    }
  assert( total == (int)GetNumberOfOverlays() || !total );
  return total != 0;
}

void Image::Print(std::ostream &os) const
{
  //assert( NumberOfDimensions );
  os << "NumberOfDimensions: " << NumberOfDimensions << "\n";
  if( NumberOfDimensions )
    {
    assert( Dimensions.size() );
    os << "Dimensions: (";
    std::vector<unsigned int>::const_iterator it = Dimensions.begin();
    os << *it;
    for(++it; it != Dimensions.end(); ++it)
      {
      os << "," << *it;
      }
    os << ")\n";
{
  os << "Origin: (";
  if( !Origin.empty() )
    {
    std::vector<double>::const_iterator it = Origin.begin();
    os << *it;
    for(++it; it != Origin.end(); ++it)
      {
      os << "," << *it;
      }
    }
  os << ")\n";
}
{
    os << "Spacing: (";
    std::vector<double>::const_iterator it = Spacing.begin();
    os << *it;
    for(++it; it != Spacing.end(); ++it)
      {
      os << "," << *it;
      }
    os << ")\n";
}
{
  os << "DirectionCosines: (";
  if( !DirectionCosines.empty() )
    {
    std::vector<double>::const_iterator it = DirectionCosines.begin();
    os << *it;
    for(++it; it != DirectionCosines.end(); ++it)
      {
      os << "," << *it;
      }
    }
  os << ")\n";
}
{
  os << "Rescale Intercept/Slope: (" << Intercept << "," << Slope << ")\n";
}
    //std::vector<double> Spacing;
    //std::vector<double> Origin;

    PF.Print(os);
    }
  os << "TransferSyntax: " << TS << "\n";
}

bool Image::TryRAWCodec(char *buffer) const
{
  unsigned long len = GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();

  const ByteValue *bv = PixelData.GetByteValue();
  if( bv )
    {
    RAWCodec codec;
    codec.SetPlanarConfiguration( GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
    codec.SetLUT( GetLUT() );
    codec.SetPixelFormat( GetPixelFormat() );
    codec.SetNeedByteSwap( GetNeedByteSwap() );
    codec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
    DataElement out;
    bool r = codec.Decode(PixelData, out);
    const ByteValue *outbv = out.GetByteValue();
    assert( outbv );
    if( len != bv->GetLength() )
      {
      // SIEMENS_GBS_III-16-ACR_NEMA_1.acr
      gdcmDebugMacro( "Pixel Length " << bv->GetLength() <<
        " is different from computed value " << len );
      ((ByteValue*)outbv)->SetLength( len );
      }
    unsigned long check = outbv->GetLength();  // FIXME
    assert( check == len );
    memcpy(buffer, outbv->GetPointer(), outbv->GetLength() );  // FIXME
    return r;
    }
  return false;
}

bool Image::TryJPEGCodec(char *buffer) const
{
  unsigned long len = GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();

  JPEGCodec codec;
  if( codec.CanDecode( ts ) )
    {
    codec.SetPlanarConfiguration( GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
    codec.SetPixelFormat( GetPixelFormat() );
    codec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
    DataElement out;
    bool r = codec.Decode(PixelData, out);
    // PHILIPS_Gyroscan-12-MONO2-Jpeg_Lossless.dcm    
    if( !r )
      {
      return false;
      }
    // FIXME ! This should be done all the time for all codec:
    // Did PI change or not ?
    if ( GetPhotometricInterpretation() != codec.GetPhotometricInterpretation() )
      {
      // HACK
      //gdcm::Image *i = (gdcm::Image*)this;
      //i->SetPhotometricInterpretation( codec.GetPhotometricInterpretation() );
      }
    const ByteValue *outbv = out.GetByteValue();
    assert( outbv );
    unsigned long check = outbv->GetLength();  // FIXME
    // DermaColorLossLess.dcm has a len of 63531, but DICOM will give us: 63532 ...
    assert( len <= outbv->GetLength() );
    memcpy(buffer, outbv->GetPointer(), len /*outbv->GetLength()*/ );  // FIXME

    return true;
    }
  return false;
}

bool Image::TryJPEGCodec2(std::ostream &os) const
{
  unsigned long len = GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();

  JPEGCodec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( GetDimensions() );
    codec.SetPlanarConfiguration( GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
    codec.SetPixelFormat( GetPixelFormat() );
    codec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
    DataElement out;
    bool r = codec.Code(PixelData, out);
    // PHILIPS_Gyroscan-12-MONO2-Jpeg_Lossless.dcm    
    if( !r )
      {
      return false;
      }
    // FIXME ! This should be done all the time for all codec:
    // Did PI change or not ?
    if ( GetPhotometricInterpretation() != codec.GetPhotometricInterpretation() )
      {
      // HACK
      //gdcm::Image *i = (gdcm::Image*)this;
      //i->SetPhotometricInterpretation( codec.GetPhotometricInterpretation() );
      }
    const ByteValue *outbv = out.GetByteValue();
    assert( outbv );
    unsigned long check = outbv->GetLength();  // FIXME
    // DermaColorLossLess.dcm has a len of 63531, but DICOM will give us: 63532 ...
    assert( outbv->GetLength() < len );
    //memcpy(buffer, outbv->GetPointer(), outbv->GetLength() );
    os.write( outbv->GetPointer(), outbv->GetLength() );

    return true;
    }
  return false;
}
   
bool Image::TryJPEG2000Codec(char *buffer) const
{
  unsigned long len = GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();

  JPEG2000Codec codec;
  if( codec.CanDecode( ts ) )
    {
    codec.SetNumberOfDimensions( GetNumberOfDimensions() );
    codec.SetPlanarConfiguration( GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
    codec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
    DataElement out;
    bool r = codec.Decode(PixelData, out);
    assert( r );
    const ByteValue *outbv = out.GetByteValue();
    assert( outbv );
    unsigned long check = outbv->GetLength();  // FIXME
    memcpy(buffer, outbv->GetPointer(), outbv->GetLength() );  // FIXME
    return r;
    }
  return false;
}

bool Image::TryJPEG2000Codec2(std::ostream &os) const
{
  unsigned long len = GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();

  JPEG2000Codec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( GetDimensions() );
    codec.SetPixelFormat( GetPixelFormat() );
    codec.SetNumberOfDimensions( GetNumberOfDimensions() );
    codec.SetPlanarConfiguration( GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
    codec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
    DataElement out;
    bool r = codec.Code(PixelData, out);
    assert( r );
    const ByteValue *outbv = out.GetByteValue();
    assert( outbv );
    unsigned long check = outbv->GetLength();  // FIXME
    //memcpy(buffer, outbv->GetPointer(), outbv->GetLength() );  // FIXME
    os.write(outbv->GetPointer(), outbv->GetLength() );
    return r;
    }
  return false;
}

bool Image::TryRLECodec(char *buffer) const
{
  unsigned long len = GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();

  RLECodec codec;
  if( codec.CanDecode( ts ) )
    {
    //assert( sf->GetNumberOfFragments() == 1 );
    //assert( sf->GetNumberOfFragments() == GetDimensions(2) );
    codec.SetPlanarConfiguration( GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( GetPhotometricInterpretation() );
    codec.SetPixelFormat( GetPixelFormat() );
    codec.SetLUT( GetLUT() );
    codec.SetNeedOverlayCleanup( AreOverlaysInPixelData() );
    codec.SetBufferLength( len );
    DataElement out;
    bool r = codec.Decode(PixelData, out);
    assert( r );
    const ByteValue *outbv = out.GetByteValue();
    //unsigned long check = outbv->GetLength();  // FIXME
    memcpy(buffer, outbv->GetPointer(), outbv->GetLength() );  // FIXME
    return true;
    }
  return false;
}

#if 0
bool Image::TryDeltaEncodingCodec(char *buffer) const
{
  unsigned long len = GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();

  DeltaEncodingCodec codec;
  if( codec.CanDecode( ts ) )
    {
    DataElement out;
    bool r = codec.Decode(PixelData, out);
    assert( r );
    const ByteValue *outbv = out.GetByteValue();
    //unsigned long check = outbv->GetLength();  // FIXME
    memcpy(buffer, outbv->GetPointer(), outbv->GetLength() );  // FIXME
    return true;
    }
  return false;
}
#endif

// Acces the raw data
bool Image::GetBuffer(char *buffer) const
{
  bool success = false;
  if( !success ) success = TryRAWCodec(buffer);
  if( !success ) success = TryJPEGCodec(buffer);
  if( !success ) success = TryJPEG2000Codec(buffer);
  if( !success ) success = TryRLECodec(buffer);
  //if( !success ) success = TryDeltaEncodingCodec(buffer);
  if( !success )
    {
    buffer = 0;
    //throw Exception( "No codec found for this image");
    }

  return success;
}

// Compress the raw data
bool Image::GetBuffer2(std::ostream &os) const
{
  bool success = false;
  //if( !success ) success = TryRAWCodec2(buffer);
  if( !success ) success = TryJPEGCodec2(os);
  //if( !success ) success = TryJPEG2000Codec2(os);
  //if( !success ) success = TryRLECodec2(buffer);
  if( !success )
    {
    //buffer = 0;
    throw Exception( "No codec found for this image");
    }

  return success;
}

} // end namespace gdcm

