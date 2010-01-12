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
#include "gdcmImageWriter.h"
#include "gdcmTrace.h"
#include "gdcmDataSet.h"
#include "gdcmDataElement.h"
#include "gdcmAttribute.h"
#include "gdcmUIDGenerator.h"
#include "gdcmSystem.h"
#include "gdcmImageHelper.h"
#include "gdcmLookupTable.h"
#include "gdcmItem.h"
#include "gdcmSequenceOfItems.h"

namespace gdcm
{

ImageWriter::ImageWriter()
{
  PixelData = new Image;
}

ImageWriter::~ImageWriter()
{
}

//void ImageWriter::SetImage(Image const &img)
//{
//  PixelData = img;
//}

bool ImageWriter::Write()
{
  if( !PrepareWrite() ) return false;

  //assert( Stream.is_open() );
  File& file = GetFile();
  DataSet& ds = file.GetDataSet();


  MediaStorage ms;
  ms.SetFromFile( GetFile() );
  assert( ms != MediaStorage::MS_END );

  Image & pixeldata = GetImage();
  PixelFormat pf = pixeldata.GetPixelFormat();
  PhotometricInterpretation pi = pixeldata.GetPhotometricInterpretation();

  // Do the Rescale Intercept & Slope
  if( pi == PhotometricInterpretation::MONOCHROME1 || pi == PhotometricInterpretation::MONOCHROME2 )
    {
    assert( pf.GetSamplesPerPixel() == 1 );
    ImageHelper::SetRescaleInterceptSlopeValue(GetFile(), pixeldata);
    }
  else
    {
    assert( pixeldata.GetIntercept() == 0 && pixeldata.GetSlope() == 1 );
    }

  // Spacing:
  std::vector<double> sp;
  sp.resize(3); // important !
  sp[0] = pixeldata.GetSpacing(0);
  sp[1] = pixeldata.GetSpacing(1);
  sp[2] = pixeldata.GetSpacing(2); // might be a dummy value...
  ImageHelper::SetSpacingValue(ds, sp);

  // Direction Cosines:
  const double *dircos = pixeldata.GetDirectionCosines();
  if( dircos )
    {
    std::vector<double> iop;
    iop.resize(6);
    iop[0] = dircos[0];
    iop[1] = dircos[1];
    iop[2] = dircos[2];
    iop[3] = dircos[3];
    iop[4] = dircos[4];
    iop[5] = dircos[5];
    ImageHelper::SetDirectionCosinesValue(ds, iop);
    }

  // Origin:
  const double *origin = pixeldata.GetOrigin();
  if( origin )
    {
    ImageHelper::SetOriginValue(ds, pixeldata);
    }

  assert( Stream );
  if( !Writer::Write() )
    {
    return false;
    }
  return true;
}

} // end namespace gdcm
