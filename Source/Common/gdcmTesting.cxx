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
#include "gdcmTesting.h"
#include "gdcmFilename.h"

#include <string.h> // strcmp

namespace gdcm
{

#ifdef GDCM_BUILD_TESTING
#include "gdcmDataFileNames.cxx"
#include "gdcmMD5DataImages.cxx"
#else
static const char GDCM_DATA_ROOT[] = "";
static const char GDCM_DATA_EXTRA_ROOT[] = "";
static const char GDCM_PIXEL_SPACING_DATA_ROOT[] = "";
static const char GDCM_TEMP_DIRECTORY[] = "";
static const char * const gdcmDataFileNames[] = { 0 };
static const char * const gdcmMD5DataImages[][2] = { {0,0} };
#endif

const char * const *Testing::GetFileNames()
{
  return gdcmDataFileNames;
}

unsigned int Testing::GetNumberOfFileNames()
{
  // Do not count NULL value:
  static const unsigned int size = sizeof(gdcmDataFileNames)/sizeof(*gdcmDataFileNames) - 1;
  return size;
}

const char * Testing::GetFileName(unsigned int file)
{
  if( file < Testing::GetNumberOfFileNames() ) return gdcmDataFileNames[file];
  return NULL;
}


Testing::MD5DataImagesType Testing::GetMD5DataImages()
{
  return gdcmMD5DataImages;
}
unsigned int Testing::GetNumberOfMD5DataImages()
{
  // Do not count NULL value:
  static const unsigned int size = sizeof(gdcmMD5DataImages)/sizeof(*gdcmMD5DataImages) - 1;
  return size;
}

const char * const * Testing::GetMD5DataImage(unsigned int file)
{
  if( file < Testing::GetNumberOfMD5DataImages() ) return gdcmMD5DataImages[file];
  return gdcmMD5DataImages[ Testing::GetNumberOfMD5DataImages() ];
}

const char * Testing::GetMD5FromFile(const char *filepath)
{
  int i = 0;
  MD5DataImagesType md5s = GetMD5DataImages();
  const char *p = md5s[i][1];
  Filename comp(filepath);
  const char *filename = comp.GetName();
  while( p != 0 )
    {
    if( strcmp( filename, p ) == 0 )
      {
      break;
      }
    ++i;
    p = md5s[i][1];
    }
  return md5s[i][0];
}

const char *Testing::GetDataRoot()
{
  return GDCM_DATA_ROOT;
}

const char *Testing::GetDataExtraRoot()
{
  return GDCM_DATA_EXTRA_ROOT;
}

const char *Testing::GetPixelSpacingDataRoot()
{
  return GDCM_PIXEL_SPACING_DATA_ROOT;
}

const char *Testing::GetTempDirectory(const char * subdir)
{
  if( !subdir ) return GDCM_TEMP_DIRECTORY;
  // else
  static std::string buffer;
  std::string tmpdir = GDCM_TEMP_DIRECTORY;
  tmpdir += "/";
  tmpdir += subdir;
  buffer = tmpdir;
  return buffer.c_str();
}

const char * Testing::GetTempFilename(const char *filename, const char * subdir)
{
  if( !filename ) return 0;

  static std::string buffer;
  std::string outfilename = GetTempDirectory(subdir);
  outfilename += "/";
  gdcm::Filename out(filename);
  outfilename += out.GetName();
  buffer = outfilename;

  return buffer.c_str();
}

void Testing::Print(std::ostream &os)
{
  os << "DataFileNames:\n";
  const char * const * filenames = gdcmDataFileNames;
  while( *filenames )
    {
    os << *filenames << "\n";
    ++filenames;
    }

  os << "MD5DataImages:\n";
  MD5DataImagesType md5s = gdcmMD5DataImages;
  while( (*md5s)[0] )
    {
    os << (*md5s)[0] << " -> " << (*md5s)[1] << "\n";
    ++md5s;
    }
}

} // end of namespace gdcm
