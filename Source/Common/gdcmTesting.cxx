  /*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmTesting.h"
#include "gdcmFilename.h"

#include <string.h> // strcmp
#include <stdlib.h> // malloc
#include <stdio.h> // fopen

#include "gdcm_md5.h"


namespace gdcm
{

#ifndef GDCM_BUILD_TESTING
#error how did that happen ?
#endif

#include "gdcmDataFileNames.cxx"
#include "gdcmMD5DataImages.cxx"
#include "gdcmMediaStorageDataFiles.cxx"

inline void process_file(const char *filename, md5_byte_t *digest)
{
  if( !filename || !digest ) return;

  FILE *file = fopen(filename, "rb");
  if(!file) 
    {
    throw Exception("Could not open");
    }

  /* go to the end */
  /*int*/ fseek(file, 0, SEEK_END);
  size_t file_size = ftell(file);
  /*int*/ fseek(file, 0, SEEK_SET);
  void *buffer = malloc(file_size);
  if(!buffer) 
    {
    fclose(file);
    throw Exception("could not allocate");
    }
  size_t read = fread(buffer, 1, file_size, file);
  assert( read == file_size ); (void)read;

  md5_state_t state;
  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)buffer, file_size);
  md5_finish(&state, digest);
  /*printf("MD5 (\"%s\") = ", test[i]); */
  /*for (int di = 0; di < 16; ++di)
  {
    printf("%02x", digest[di]);
  }*/
  //printf("\t%s\n", filename);
  free(buffer);
  fclose(file);
}

bool Testing::ComputeMD5(const char *buffer, unsigned long buf_len,
  char digest_str[33])
{
  if( !buffer || !buf_len )
    {
    return false;
    }
  md5_byte_t digest[16];
  md5_state_t state;
  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)buffer, buf_len);
  md5_finish(&state, digest);

  //char digest_str[2*16+1];
  for (int di = 0; di < 16; ++di)
  {
    sprintf(digest_str+2*di, "%02x", digest[di]);
  }
  digest_str[2*16] = '\0';
  return true;
}

bool Testing::ComputeFileMD5(const char *filename, char *digest_str)
{
  // If not file exist
  // return false;
  md5_byte_t digest[16];

  /* Do the file */
  process_file(filename, digest);

  //char digest_str[2*16+1];
  for (int di = 0; di < 16; ++di)
  {
    sprintf(digest_str+2*di, "%02x", digest[di]);
  }
  digest_str[2*16] = '\0';
  return true;
}

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

Testing::MediaStorageDataFilesType Testing::GetMediaStorageDataFiles()
{
  return gdcmMediaStorageDataFiles;
}
unsigned int Testing::GetNumberOfMediaStorageDataFiles()
{
  // Do not count NULL value:
  static const unsigned int size = sizeof(gdcmMediaStorageDataFiles)/sizeof(*gdcmMediaStorageDataFiles) - 1;
  return size;
}
const char * const * Testing::GetMediaStorageDataFile(unsigned int file)
{
  if( file < Testing::GetNumberOfMediaStorageDataFiles() ) return gdcmMediaStorageDataFiles[file];
  // else return the {0x0, 0x0} sentinel:
  assert( *gdcmMediaStorageDataFiles[ Testing::GetNumberOfMediaStorageDataFiles() ] == 0 );
  return gdcmMediaStorageDataFiles[ Testing::GetNumberOfMediaStorageDataFiles() ];
}
const char * Testing::GetMediaStorageFromFile(const char *filepath)
{
  unsigned int i = 0;
  MediaStorageDataFilesType mediastorages = GetMediaStorageDataFiles();
  const char *p = mediastorages[i][0];
  Filename comp(filepath);
  const char *filename = comp.GetName();
  while( p != 0 )
    {
    if( strcmp( filename, p ) == 0 )
      {
      break;
      }
    ++i;
    p = mediastorages[i][0];
    }
  // \postcondition always valid (before sentinel)
  assert( i <= GetNumberOfMediaStorageDataFiles() );
  return mediastorages[i][1];
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
  // else return the {0x0, 0x0} sentinel:
  assert( *gdcmMD5DataImages[ Testing::GetNumberOfMD5DataImages() ] == 0 );
  return gdcmMD5DataImages[ Testing::GetNumberOfMD5DataImages() ];
}

const char * Testing::GetMD5FromFile(const char *filepath)
{
  unsigned int i = 0;
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
  // \postcondition always valid (before sentinel)
  assert( i <= GetNumberOfMD5DataImages() );
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
