/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmDirectory.h"

#include <iterator>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>  //stat function

#ifdef _MSC_VER
  #include <windows.h>
  #include <direct.h>
#else
  #include <dirent.h>
  #include <sys/types.h>
#endif

namespace gdcm
{
bool Directory::IsDirectory(FilenameType const &name)
{
  struct stat fs;
  assert( name[name.size()-1] != '/' );
  if ( stat(name.c_str(), &fs) == 0 )
    {
#if _WIN32
    return ((fs.st_mode & _S_IFDIR) != 0);
#else
    return S_ISDIR(fs.st_mode);
#endif
    }
  else
    {
    //const char *str = strerror(errno);
    //gdcmErrorMacro( str );
    return false;
    }
}

unsigned int Directory::Explore(FilenameType const &name, bool recursive)
{
  unsigned int nFiles = 0;
  std::string fileName;
  //std::string dirName = Util::NormalizePath(Toplevel);
  std::string dirName = name;
  // FIXME: IsDirectory( dirName )
  Directories.push_back( dirName );
#ifdef _MSC_VER
  WIN32_FIND_DATA fileData;
  assert( Toplevel[Toplevel.size()-1] == '/' );
  const FilenameType firstfile = Toplevel+"*";
  HANDLE hFile = FindFirstFile(firstfile.c_str(), &fileData);

  for(BOOL b = (hFile != INVALID_HANDLE_VALUE); b;
    b = FindNextFile(hFile, &fileData))
    {
    fileName = fileData.cFileName;
    if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
      {
      // Need to check for . and .. to avoid infinite loop
      if ( fileName != "." && fileName != ".." && recursive )
        {
        nFiles += Explore(name+fileName,recursive);
        }
      }
    else
      {
      Filenames.push_back(name+fileName);
      nFiles++;
      }
    }
  DWORD dwError = GetLastError();
  if (hFile != INVALID_HANDLE_VALUE) FindClose(hFile);
  if (dwError != ERROR_NO_MORE_FILES)
    {
    //gdcmErrorMacro("FindNextFile error. Error is " << dwError);
    return 0;
    }

#else
  // Real POSIX implementation: scandir is a BSD extension only, and doesn't
  // work on debian for example

  DIR* dir = opendir(dirName.c_str());
  if (!dir)
    {
    return 0;
    }

  // According to POSIX, the dirent structure contains a field char d_name[]
  // of unspecified size, with at most NAME_MAX characters preceeding the
  // terminating null character. Use of other fields will harm the  porta-
  // bility of your programs.

  struct stat buf;
  dirent *d;
  dirName.append("/");
  assert( dirName[dirName.size()-1] == '/' );
  for (d = readdir(dir); d; d = readdir(dir))
    {
    fileName = dirName + d->d_name;
    if( stat(fileName.c_str(), &buf) != 0 )
      {
      //const char *str = strerror(errno);
      //gdcmErrorMacro( str );
      abort();
      }
    if ( S_ISREG(buf.st_mode) )    //is it a regular file?
      {
      Filenames.push_back( fileName );
      nFiles++;
      }
    else if ( S_ISDIR(buf.st_mode) ) //directory?
      {
      // discard . and ..
      if( strcmp( d->d_name, "." ) == 0
        || strcmp( d->d_name, ".." ) == 0 )
        continue;
      assert( d->d_name[0] != '.' ); // hidden directory ??
      if ( recursive )
        {
        nFiles += Explore( fileName, recursive);
        }
      }
    else
      {
      std::cerr << "Unexpected error" << std::endl;
      return 0;
      }
    }
  if( closedir(dir) != 0 )
    {
    //const char *str = strerror(errno);
    //gdcmErrorMacro( str );
    abort();
    }
#endif

  return nFiles;
}

void Directory::Print(std::ostream &_os)
{
  // FIXME Both structures are FilenamesType I could factorize the code
  _os << "Directories: ";
  if( Directories.empty() )
    _os << "(None)" << std::endl;
  else
    {
    std::copy(Directories.begin(), Directories.end(), 
      std::ostream_iterator<std::string>(_os << std::endl, "\n"));
    }
  _os << "Filenames: ";
  if( Filenames.empty() )
    _os << "(None)" << std::endl;
  else
    {
    std::copy(Filenames.begin(), Filenames.end(), 
      std::ostream_iterator<std::string>(_os << std::endl, "\n"));
    }
}

} // end namespace gdcm
