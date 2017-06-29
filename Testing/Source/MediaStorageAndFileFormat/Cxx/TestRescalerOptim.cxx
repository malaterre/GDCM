/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmRescaler.h"
#include "gdcmDirectory.h"
#include "gdcmImageRegionReader.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmSystem.h"
#include "gdcmFilename.h"
#include "gdcmByteSwap.h"
#include "gdcmTrace.h"
#include "gdcmTesting.h"

static gdcm::PixelFormat::ScalarType ComputePixelTypeFromFiles(const char *filename)
{
  gdcm::PixelFormat::ScalarType outputpt;
  outputpt = gdcm::PixelFormat::UNKNOWN;
  if( !gdcm::System::FileIsDirectory( filename ) )
    {
    gdcm::ImageRegionReader reader;
    reader.SetFileName( filename );
    if( !reader.ReadInformation() )
        return gdcm::PixelFormat::UNKNOWN;
    const gdcm::Image &image = reader.GetImage();
    const gdcm::PixelFormat &pixeltype = image.GetPixelFormat();
    double shift = image.GetIntercept();
    double scale = image.GetSlope();

    gdcm::Rescaler r;
    r.SetIntercept( shift );
    r.SetSlope( scale );
    r.SetPixelFormat( pixeltype );
    outputpt = r.ComputeInterceptSlopePixelType();
    }
  else
    {
    gdcm::Directory dir;
    const unsigned int n = dir.Load( filename );
    if( n == 0 )
        return gdcm::PixelFormat::UNKNOWN;
    gdcm::Directory::FilenamesType const & filenames = dir.GetFilenames();
    std::set< gdcm::PixelFormat::ScalarType > pixeltypes;
    std::set< unsigned short > samplesperpixel;
    // FIXME a gdcm::Scanner would be much faster here:
    for( gdcm::Directory::FilenamesType::const_iterator it = filenames.begin(); it != filenames.end(); ++it )
      {
      const char *filename = it->c_str();
      gdcm::ImageRegionReader reader;
      reader.SetFileName( filename );
      if( !reader.ReadInformation() )
        {
        //vtkGenericWarningMacro( "ImageReader failed: " << filename );
        return gdcm::PixelFormat::UNKNOWN;
        }
      const gdcm::Image &image = reader.GetImage();
      const gdcm::PixelFormat &pixeltype = image.GetPixelFormat();
      samplesperpixel.insert( pixeltype.GetSamplesPerPixel() );

      double shift = image.GetIntercept();
      double scale = image.GetSlope();

      gdcm::PixelFormat::ScalarType outputpt2 = pixeltype;
      gdcm::Rescaler r;
      r.SetIntercept( shift );
      r.SetSlope( scale );
      r.SetPixelFormat( pixeltype );
      outputpt2 = r.ComputeInterceptSlopePixelType();
      //std::cout << "Found: " << outputpt << std::endl;
      pixeltypes.insert( outputpt2 );
      }
    if( pixeltypes.size() == 1 )
      {
      assert( samplesperpixel.size() == 1 );
      // Ok easy case
      outputpt = *pixeltypes.begin();
      }
    else if( samplesperpixel.size() == 1 )
      {
      // Hardcoded. If Pixel Type found is the maximum (as of PS 3.5 - 2008)
      // There is nothing bigger that FLOAT64
      if( pixeltypes.count( gdcm::PixelFormat::FLOAT64 ) != 0 )
        {
        outputpt = gdcm::PixelFormat::FLOAT64;
        }
      else
        {
        // should I just take the biggest value ?
        // MM: I am not sure UINT16 and INT16 are really compatible
        // so taking the biggest value might not be the solution
        // In this case we could use INT32, but FLOAT64 also works...
        // oh well, let's just use FLOAT64 always.
        //vtkGenericWarningMacro( "This may not always be optimized. Sorry" );
        outputpt = gdcm::PixelFormat::FLOAT64;
        abort();
        }
      }
    else
      {
      //vtkGenericWarningMacro( "Could not compute Pixel Type. Sorry" );
      abort();
      }
    }

  return outputpt;
}

static int TestRescalerOptimFunc(const char* filename, bool verbose = false, bool lossydump = false)
{
  if( verbose )
    std::cerr << "Reading: " << filename << std::endl;
  gdcm::PixelFormat::ScalarType st = ComputePixelTypeFromFiles(filename);
  char * pointer = NULL;
  char * copy = NULL;
  if( gdcm::System::FileIsDirectory( filename ) )
  {
    gdcm::Directory dir;
    const unsigned int n = dir.Load( filename );
    if( n == 0 )
      return 1;
    gdcm::Directory::FilenamesType const & filenames = dir.GetFilenames();
    for( gdcm::Directory::FilenamesType::const_iterator it = filenames.begin(); it != filenames.end(); ++it )
    {
      const char *filename = it->c_str();
      gdcm::ImageRegionReader reader;
      reader.SetFileName( filename );
      if( !reader.ReadInformation() ) return 1;
      const gdcm::Image &image = reader.GetImage();
  const gdcm::PixelFormat &pixeltype = image.GetPixelFormat();
  unsigned long len = reader.ComputeBufferLength();

    gdcm::Rescaler r;
    r.SetIntercept( image.GetIntercept() );
    r.SetSlope( image.GetSlope() );
    gdcm::PixelFormat::ScalarType targetpixeltype = st;
    r.SetTargetPixelType( targetpixeltype );
    r.SetUseTargetPixelType(true);
    r.SetPixelFormat( pixeltype );
    if( copy == NULL ) copy = new char[len];
    if( pointer == NULL ) pointer = new char [ len * 2 ];
    reader.ReadIntoBuffer(copy, len);
    if( !r.Rescale(pointer,copy,len) )
      {
      return 1;
      }
    }
  }
  else
  {
    gdcm::ImageRegionReader reader;
    reader.SetFileName( filename );
      if( !reader.ReadInformation() ) return 1;
      const gdcm::Image &image = reader.GetImage();
  const gdcm::PixelFormat &pixeltype = image.GetPixelFormat();
  unsigned long len = reader.ComputeBufferLength();

    gdcm::Rescaler r;
    r.SetIntercept( image.GetIntercept() );
    r.SetSlope( image.GetSlope() );
    gdcm::PixelFormat::ScalarType targetpixeltype = st;
    r.SetTargetPixelType( targetpixeltype );
    r.SetUseTargetPixelType(true);
    r.SetPixelFormat( pixeltype );
    if( copy == NULL ) copy = new char[len];
    if( pointer == NULL ) pointer = new char [ len * 4 ];
    reader.ReadIntoBuffer(copy, len);
    if( !r.Rescale(pointer,copy,len) )
      {
      return 1;
      }
    }

    delete[] copy;
delete[] pointer;
  return 0;
}

int TestRescalerOptim(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestRescalerOptimFunc(filename, true);
    }

  // else
  // First of get rid of warning/debug message
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  gdcm::Trace::ErrorOff();
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestRescalerOptimFunc(filename,true);
    ++i;
    }

  return r;
}

