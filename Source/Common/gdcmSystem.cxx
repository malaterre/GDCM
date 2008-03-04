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
#include "gdcmTrace.h"
#include "gdcmFilename.h"
#include "gdcmException.h"

#include "md5/md5.h"
#include "uuid/uuid.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>

// gettimeofday
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#include <time.h>
#ifdef HAVE_WINSOCK_H
#include <winsock.h>
#endif
#include <stdio.h> // snprintf
#ifdef _WIN32
#define snprintf _snprintf
#endif


#include <iostream>

namespace gdcm
{

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
  assert( read == file_size );

  md5_state_t state;
  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)buffer, file_size);
  md5_finish(&state, digest);
  /*printf("MD5 (\"%s\") = ", test[i]); */
  for (int di = 0; di < 16; ++di)
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
    //assert( !FileIsDirectory(filename) );
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
size_t System::FileSize(const char* filename)
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

/**
 * \brief Encode the mac address on a fixed length string of 15 characters.
 * we save space this way.
 */
inline int getlastdigit(unsigned char *data, unsigned long size)
{
  int extended, carry = 0;
  for(unsigned int i=0;i<size;i++)
    {
    extended = (carry << 8) + data[i];
    data[i] = extended / 10;
    carry = extended % 10;
    }
  return carry;
}

int System::EncodeBytes(char *out, unsigned char *data, int size)
{
  bool zero = false;
  int res;
  std::string sres;
  unsigned char buffer[32];
  unsigned char *addr = buffer;
  memcpy(addr, data, size);
  while(!zero)
    {
    res = getlastdigit(addr, size);
    sres.insert(sres.begin(), '0' + res);
    zero = true;
    for(int i = 0; i < size; ++i)
      {
      zero = zero && (addr[i] == 0);
      }
    }

  //return sres;
  strcpy(out, sres.c_str()); //, sres.size() );
  return sres.size();
}

int System::GetHardwareAddress(unsigned char addr[6])
{
  int stat = uuid_get_node_id(addr);
  /*
  // For debugging you need to consider the worse case where hardware addres is max number:
  addr[0] = 255;
  addr[1] = 255;
  addr[2] = 255;
  addr[3] = 255;
  addr[4] = 255;
  addr[5] = 255;
  */
  if (stat == 1) // success
    {
    return stat;
    }
  // else
  gdcmWarningMacro("Problem in finding the MAC Address");
  return 0;
}

int System::GetCurrentDateTime(char date[18])
{
  const size_t maxsize = 40;
  char tmp[maxsize];
  long milliseconds;
  time_t timep;

  struct timeval tv;
  uuid_gettimeofday (&tv, NULL);
  timep = tv.tv_sec;
  // Compute milliseconds from microseconds.
  milliseconds = tv.tv_usec / 1000;
  // Obtain the time of day, and convert it to a tm struct.
  struct tm *ptm = localtime (&timep);
  // Format the date and time, down to a single second.
  size_t ret = strftime (tmp, sizeof (tmp), "%Y%m%d%H%M%S", ptm);
  if( ret == 0 || ret >= maxsize )
    {
    //return "";
    return 0;
    }

  // Add milliseconds
  const size_t maxsizall = 18;
  //char tmpAll[maxsizall];
  int ret2 = snprintf(date,maxsizall,"%s%03ld",tmp,milliseconds);
  assert( ret2 >= 0 );
  if( (unsigned int)ret2 >= maxsizall )
    {
    //return "";
    return 0;
    }

  // Ok !
  return 1;
}

int System::StrCaseCmp(const char *s1, const char *s2)
{
  while (*s1 && (tolower(*s1) == tolower(*s2)))
   {
     s1++;
     s2++;
   }

 return tolower(*s1) - tolower(*s2);
}

} // end namespace gdcm
