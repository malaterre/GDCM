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
#include "gdcmSystem.h"
#include "gdcmFilename.h"

#include "md5.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>

#include <iostream>

namespace gdcm
{

inline void process_file(const char *filename, md5_byte_t *digest)
{
  int di;
  size_t file_size, read;
  void *buffer;
  md5_state_t state;
  FILE *file = fopen(filename, "rb");

  /* go to the end */
  /*int*/ fseek(file, 0, SEEK_END);
  file_size = ftell(file);
  /*int*/ fseek(file, 0, SEEK_SET);
  buffer = malloc(file_size);
  read = fread(buffer, 1, file_size, file);
  assert( read == file_size );

  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)buffer, file_size);
  md5_finish(&state, digest);
  /*printf("MD5 (\"%s\") = ", test[i]); */
  for (di = 0; di < 16; ++di)
  {
    printf("%02x", digest[di]);
  }
  printf("\t%s\n", filename);
  free(buffer);
  fclose(file);
}

bool System::ComputeMD5(const char *buffer, const unsigned long buf_len,
  char *digest_str)
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

bool System::ComputeFileMD5(const char *filename, char *digest_str)
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

#if defined(_WIN32) && (defined(_MSC_VER) || defined(__WATCOMC__) || defined(__BORLANDC__) || defined(__MINGW32__)) 
#include <io.h>
#include <direct.h>
#define _unlink unlink
inline int Mkdir(const char* dir)
{
  return _mkdir(dir);
}
inline int Rmdir(const char* dir)
{
  return _rmdir(dir);
}
#else
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
inline int Mkdir(const char* dir)
{
  return mkdir(dir, 00777);
}
inline int Rmdir(const char* dir)
{
  return rmdir(dir);
}
#endif

bool System::MakeDirectory(const char *path)
{
  if(System::FileExists(path))
    {
    return true;
    }
  Filename fn(path);
  std::string dir = fn.ToUnixSlashes();

  std::string::size_type pos = dir.find(':');
  if(pos == std::string::npos)
    {
    pos = 0;
    }
  std::string topdir;
  while((pos = dir.find('/', pos)) != std::string::npos)
    {
    topdir = dir.substr(0, pos);
    Mkdir(topdir.c_str());
    pos++;
    }
  if(dir[dir.size()-1] == '/')
    {
    topdir = dir.substr(0, dir.size());
    }
  else
    {
    topdir = dir;
    }
  if(Mkdir(topdir.c_str()) != 0)
    {
    // There is a bug in the Borland Run time library which makes MKDIR
    // return EACCES when it should return EEXISTS
    // if it is some other error besides directory exists
    // then return false
    if( (errno != EEXIST)
#ifdef __BORLANDC__
        && (errno != EACCES)
#endif
      )
      {
      return false;
      }
    }
  return true;
}

// return true if the file exists
bool System::FileExists(const char* filename)
{
#ifdef _MSC_VER
# define access _access
#endif
#ifndef R_OK
# define R_OK 04
#endif
  if ( access(filename, R_OK) != 0 )
    {
    return false;
    }
  else
    {
    assert( !FileIsDirectory(filename) );
    return true;
    }
}

bool System::FileIsDirectory(const char* name)
{
  struct stat fs;
  if(stat(name, &fs) == 0)
    {
#if _WIN32
    return ((fs.st_mode & _S_IFDIR) != 0);
#else
    return S_ISDIR(fs.st_mode);
#endif
    }
  else
    {
    return false;
    }
}

const char *System::GetLastSystemError()
{
  int e = errno;
  return strerror(e);
}

bool System::GetPermissions(const char* file, unsigned short& mode)
{
  if ( !file )
    {
    return false;
    }

  struct stat st;
  if ( stat(file, &st) < 0 )
    {
    return false;
    }
  mode = st.st_mode;
  return true;
}

bool System::SetPermissions(const char* file, unsigned short mode)
{
  if ( !file )
    {
    return false;
    }
  if ( !System::FileExists(file) )
    {
    return false;
    }
  if ( chmod(file, mode) < 0 )
    {
    return false;
    }

  return true;
}

bool System::RemoveFile(const char* source)
{
#ifdef _WIN32
  unsigned short mode;
  if ( !System::GetPermissions(source, mode) )
    {
    return false;
    }
  /* Win32 unlink is stupid --- it fails if the file is read-only  */
  System::SetPermissions(source, S_IWRITE);
#endif
  bool res = unlink(source) != 0 ? false : true;
#ifdef _WIN32
  if ( !res )
    {
    System::SetPermissions(source, mode);
    }
#endif
  return res;
}

// return size of file; also returns zero if no file exists
unsigned long System::FileSize(const char* filename)
{
  struct stat fs;
  if (stat(filename, &fs) != 0) 
    {
    return 0;
    }
  else
    {
    return fs.st_size;
    }
}

}
