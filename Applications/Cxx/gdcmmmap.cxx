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
/*
 *  OS Specific: need a POSIX system with mmap functionality
 */
#include <sstream>
#include <fstream>
#include <iostream>

// fstat
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// mmap
#include <sys/mman.h>

#include "gdcmFile.h"
#include "gdcmObject.h"
#include "gdcmDataSet.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmSmartPointer.h"
#include "gdcmDeflateStream.h"
#include "gdcmDumper.h"
#include "gdcmDirectory.h"
#include "gdcmReader.h"
#include "gdcmSystem.h"

#include "gdcmUNExplicitDataElement.h"
#include "gdcmCP246ExplicitDataElement.h"
#include "gdcmExplicitImplicitDataElement.h"

/*
 * http://www.ecst.csuchico.edu/~beej/guide/ipc/mmap.html
 * http://www.dba-oracle.com/oracle_tips_mount_options.htm
 */

class membuf : public std::streambuf
{
public:
  membuf(char* mem, size_t length)
  {
    setg(mem, mem, mem + length);
    setp(mem, mem + length);
  }
  std::streampos seekpos(std::streampos pos, std::ios_base::openmode)
    {
    char *p = eback() + pos;
    if(p>=eback() && p <=egptr())
      {
      setg(eback(),p,egptr());
      return pos;
      }
    else
      return -1;
    }

  std::streampos seekoff(std::streamoff off,
    std::ios_base::seekdir dir, std::ios_base::openmode)
    {
    char *p;
    switch(dir)
      {
    case std::ios_base::beg:
      p = eback() + off;
      break;
    case std::ios_base::cur:
      p = gptr() + off;
      break;
    case std::ios_base::end:
      p = egptr() + off;
      break;
    default:
      p = 0;
      break;
      }
    if(p>=eback() && p <= egptr())
      {
      setg(eback(),p,egptr());
      return std::streampos(p-egptr());
      }
    else
      return -1;
    }
};

std::istream & DoTheMMapRead(std::istream &is)
{
  gdcm::Reader reader;
  reader.SetStream(is);
  reader.Read();

  gdcm::Dumper printer;
  printer.SetFile ( reader.GetFile() );
  //printer.Print( std::cout );

}

int DoOperation(std::string const & path)
{
  bool readonly = true;
  int flags = (readonly ? O_RDONLY : O_RDWR);

  int handle = ::open(path.c_str(), flags, S_IRWXU);

  bool success = true;
  struct stat info;
  success = ::fstat(handle, &info) != -1;
  off_t size = info.st_size;

  off_t offset = 0;
  char* hint = 0;
  void* data = ::mmap( hint, size,
    readonly ? PROT_READ : (PROT_READ | PROT_WRITE),
    readonly ? MAP_PRIVATE : MAP_SHARED,
    handle, offset );
  if (data == MAP_FAILED) {
    return 1;
  }
  char *chardata = reinterpret_cast<char*>(data);

  membuf mb( chardata, size );
  std::istream is(&mb) ;

  DoTheMMapRead(is);

  // cleanup
  assert( handle );
  bool error = false;
  error = ::munmap(data, size) != 0 || error;
  error = ::close(handle) != 0 || error;
  handle = 0;

  if ( error )  return 1;

  return 0;
}

int main(int argc, char *argv[])
{
  if( argc < 2 )
    {
    return 1;
    }
  std::string filename = argv[1];

  int res = 0;
  if( gdcm::System::FileIsDirectory( filename.c_str() ) )
    {
    gdcm::Directory d;
    d.Load(filename);
    gdcm::Directory::FilenamesType const &filenames = d.GetFilenames();
    for( gdcm::Directory::FilenamesType::const_iterator it = filenames.begin(); it != filenames.end(); ++it )
      {
      res += DoOperation(*it);
      }
    }
  else
    {
    res += DoOperation(filename);
    }

  return res;
}

