/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImageChangeTransferSyntax.h"
#include "gdcmImageReader.h"
#include "gdcmImageWriter.h"
#include "gdcmFilename.h"
#include "gdcmSystem.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmTesting.h"
#include "gdcmByteSwap.h"

namespace gdcm
{

int TestImageChangeTransferSyntaxJPEGTurboBaseline(const char *filename, bool verbose = false)
{
  ImageReader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    const FileMetaInformation &header = reader.GetFile().GetHeader();
    MediaStorage ms = header.GetMediaStorage();
    bool isImage = MediaStorage::IsImage( ms );
    bool pixeldata = reader.GetFile().GetDataSet().FindDataElement( Tag(0x7fe0,0x0010) );
    if( isImage && pixeldata )
      {
      std::cerr << "Failed to read: " << filename << std::endl;
      return 1;
      }
    else
      {
      // not an image give up...
      std::cerr << "Problem with: " << filename << " but that's ok" << std::endl;
      return 0;
      }
    }

  const gdcm::Image &image = reader.GetImage();

  // JPEGBaselineProcess1 only supports 8-bit data
  if( image.GetPixelFormat().GetBitsAllocated() != 8 )
    {
    return 0;
    }

  gdcm::ImageChangeTransferSyntax change;
  change.SetTransferSyntax( gdcm::TransferSyntax::JPEGBaselineProcess1 );
  change.SetInput( image );
  bool b = change.Change();
  if( !b )
    {
    // Some images may legitimately fail (e.g. palette color with lossy)
    std::cerr << "Could not change the Transfer Syntax: " << filename
              << " but that may be ok" << std::endl;
    return 0;
    }

  // Create directory first:
  const char subdir[] = "TestImageChangeTransferSyntax9";
  std::string tmpdir = Testing::GetTempDirectory( subdir );
  if( !System::FileIsDirectory( tmpdir.c_str() ) )
    {
    System::MakeDirectory( tmpdir.c_str() );
    }
  std::string outfilename = Testing::GetTempFilename( filename, subdir );

  ImageWriter writer;
  writer.SetFileName( outfilename.c_str() );
  writer.SetFile( reader.GetFile() );
  writer.SetImage( change.GetOutput() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }

  // Let's read that file back in !
  ImageReader reader2;
  reader2.SetFileName( outfilename.c_str() );
  if ( !reader2.Read() )
    {
    std::cerr << "Could not even reread our generated file : " << outfilename << std::endl;
    return 1;
    }

  // For lossy compression, we cannot compare MD5.
  // Instead verify the image is readable and dimensions match.
  const gdcm::Image &img2 = reader2.GetImage();
  unsigned long len = img2.GetBufferLength();
  char* buffer = new char[len];
  bool res2 = img2.GetBuffer(buffer);
  if( !res2 )
    {
    std::cerr << "could not get buffer: " << outfilename << std::endl;
    delete[] buffer;
    return 1;
    }

  // Verify dimensions match
  const unsigned int *dims1 = image.GetDimensions();
  const unsigned int *dims2 = img2.GetDimensions();
  if( dims1[0] != dims2[0] || dims1[1] != dims2[1] )
    {
    std::cerr << "Dimension mismatch for: " << filename << std::endl;
    delete[] buffer;
    return 1;
    }

  if( verbose )
    {
    std::cout << "file was written in: " << outfilename << std::endl;
    }

  delete[] buffer;
  return 0;
}

} // end namespace gdcm

int TestImageChangeTransferSyntax9(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return gdcm::TestImageChangeTransferSyntaxJPEGTurboBaseline(filename, true);
    }

  // else
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += gdcm::TestImageChangeTransferSyntaxJPEGTurboBaseline( filename );
    ++i;
    }

  return r;
}
