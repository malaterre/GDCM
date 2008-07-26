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
#include "gdcmImageChangeTransferSyntax.h"
#include "gdcmImageReader.h"
#include "gdcmImageWriter.h"
#include "gdcmFilename.h"
#include "gdcmSystem.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmTesting.h"

namespace gdcm
{

int TestImageChangeTransferSyntaxJ2K(const char *filename)
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

  gdcm::ImageChangeTransferSyntax change;
  change.SetTransferSyntax( gdcm::TransferSyntax::JPEG2000Lossless );
  change.SetInput( image );
  bool b = change.Change();
  if( !b )
    {
    std::cerr << "Could not change the Transfer Syntax: " << filename << std::endl;
    return 1;
    }

  // Create directory first:
  const char subdir[] = "TestImageChangeTransferSyntax2";
  std::string tmpdir = Testing::GetTempDirectory( subdir );
  if( !System::FileIsDirectory( tmpdir.c_str() ) )
    {
    System::MakeDirectory( tmpdir.c_str() );
    //return 1;
    }
  std::string outfilename = Testing::GetTempFilename( filename, subdir );

  ImageWriter writer;
  writer.SetFileName( outfilename.c_str() );
  //writer.SetFile( reader.GetFile() ); // increase test goal
  writer.SetImage( change.GetOutput() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }
  std::cout << "success: " << outfilename << std::endl;

  // Let's read that file back in !
  ImageReader reader2;

  reader2.SetFileName( outfilename.c_str() );
  if ( !reader2.Read() )
    {
    return 1;
    }
  // TODO: need to check decompression equal initial buffer !
  return 0;
}

} // end namespace gdcm

int TestImageChangeTransferSyntax2(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return gdcm::TestImageChangeTransferSyntaxJ2K(filename);
    }

  // else
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += gdcm::TestImageChangeTransferSyntaxJ2K( filename );
    ++i;
    }

  return r;
}
