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
#include "gdcmReader.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmFile.h"
#include "gdcmTesting.h"
#include "gdcmMediaStorage.h"


int TestReadUpToTag(const char* filename, bool verbose = false)
{
  if( verbose )
  std::cout << "TestRead: " << filename << std::endl;

  gdcm::Reader reader;
  reader.SetFileName( filename );
  // Let's read up to Pixel Data el...
  gdcm::Tag pixeldata (0x7fe0,0x0010);
  std::set<gdcm::Tag> skiptags;
  // ... but do not read it (to skip mem allocation)
  skiptags.insert( pixeldata );
  std::streamoff outStreamOffset;
  if ( !reader.ReadUpToTag( pixeldata, skiptags, outStreamOffset) )
    {
    std::cerr << "TestReadError: Failed to read: " << filename << std::endl;
    return 1;
    }

  const gdcm::FileMetaInformation &h = reader.GetFile().GetHeader();

  const gdcm::DataSet &ds = reader.GetFile().GetDataSet();

  //std::cout << "{ \"" << filename << "\"," << outStreamOffset << " }" << std::endl;
  std::streamoff refoffset = gdcm::Testing::GetStreamOffsetFromFile(filename);
  if( refoffset != outStreamOffset ) return 1;

  return 0;
}

int TestReaderUpToTag(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestReadUpToTag(filename, true);
    }

  // else
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestReadUpToTag( filename );
    ++i;
    }

  return r;
}
