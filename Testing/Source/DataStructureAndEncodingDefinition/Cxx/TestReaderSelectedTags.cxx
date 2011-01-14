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


int TestReadSelectedTags(const char* filename, bool verbose = false)
{
  if( verbose )
    std::cout << "TestRead: " << filename << std::endl;

  std::ifstream is( filename );
  gdcm::Reader reader;
  reader.SetStream( is );
  // Let's read up to Pixel Data Group Length el...
  gdcm::Tag pixeldatagl (0x7fe0,0x0000);
  std::set<gdcm::Tag> selectedtags;
  selectedtags.insert ( pixeldatagl );
  if ( !reader.ReadSelectedTags( selectedtags ) )
    {
    std::cerr << "TestReadSelectedTags : Failed to read: " << filename << std::endl;
    return 1;
    }

  std::streamoff outStreamOffset = is.tellg();

  if(verbose)
    std::cout << "{ \"" << filename << "\"," << outStreamOffset << " }," << std::endl;
  std::streamoff refoffset = gdcm::Testing::GetSelectedTagsOffsetFromFile(filename);
  if( refoffset != outStreamOffset )
    {
    std::cerr << filename << ": " << outStreamOffset << " should be " << refoffset << std::endl;
    return 1;
    }
  is.close();

  return 0;
}

int TestReaderSelectedTags(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestReadSelectedTags(filename, true);
    }

  // else
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestReadSelectedTags( filename );
    //r += TestReadSelectedTags( filename , true);
    ++i;
    }

  return r;
}
