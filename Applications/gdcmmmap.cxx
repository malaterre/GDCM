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

namespace gdcm
{

std::istream & DoTheMMapRead(std::istream &is)
{
  //gdcm::File file;
  SmartPointer<File> F(new File);

  bool haspreamble = true;
  try
    {
    F->GetHeader().GetPreamble().Read( is );
    }
  catch( std::exception &ex )
    {
    // return to beginning of file, hopefully this file is simply missing preamble
    is.seekg(0, std::ios::beg);
    haspreamble = false;
    }
  catch( ... )
    {
    abort();
    }

  bool hasmetaheader = true;
  try
    {
    if( haspreamble )
      {
      try
        {
        F->GetHeader().Read( is );
        }
      catch( std::exception &ex )
        {
        // Weird implicit meta header:
        is.seekg(128+4, std::ios::beg );
        try
          {
          F->GetHeader().ReadCompat(is);
          }
        catch( std::exception &ex )
          {
          // Ok I get it now... there is absolutely no meta header, giving up
          hasmetaheader = false;
          }
        }
      }
    else
      F->GetHeader().ReadCompat(is);
    }
  catch( std::exception &ex )
    {
    // Same player play again:
    is.seekg(0, std::ios::beg );
    hasmetaheader = false;
    }
  catch( ... )
    {
    // Ooops..
    abort();
    }

  const TransferSyntax &ts = F->GetHeader().GetDataSetTransferSyntax();
  if( !ts.IsValid() )
    {
    throw Exception( "Meta Header issue" );
    }

  //std::cerr << ts.GetNegociatedType() << std::endl;
  //std::cerr << TransferSyntax::GetTSString(ts) << std::endl;
  // Special case where the dataset was compressed using the deflate
  // algorithm
  if( ts == TransferSyntax::DeflatedExplicitVRLittleEndian )
    {
    gzistream gzis(is.rdbuf());
    // FIXME: we also know in this case that we are dealing with Explicit:
    assert( ts.GetNegociatedType() == TransferSyntax::Explicit );
    F->GetDataSet().Read<ExplicitDataElement,SwapperNoOp>(gzis);
    is.seekg(0, std::ios::end);
    is.peek();

    return is;
    }

  try
    {
    if( ts.GetSwapCode() == SwapCode::BigEndian )
      {
      //US-RGB-8-epicard.dcm is big endian
      if( ts.GetNegociatedType() == TransferSyntax::Implicit )
        {
        // There is no such thing as Implicit Big Endian... oh well
        // LIBIDO-16-ACR_NEMA-Volume.dcm 
        F->GetDataSet().Read<ImplicitDataElement,SwapperDoOp>(is);
        }
      else
        {
        F->GetDataSet().Read<ExplicitDataElement,SwapperDoOp>(is);
        }
      }
    else // LittleEndian
      {
      if( ts.GetNegociatedType() == TransferSyntax::Implicit )
        {
        F->GetDataSet().Read<ImplicitDataElement,SwapperNoOp>(is);
        }
      else
        {
        F->GetDataSet().Read<ExplicitDataElement,SwapperNoOp>(is);
        }
      }
    }
  // Only catch parse exception at this point
  catch( ParseException &ex )
    {
    if( ex.GetLastElement().GetVR() == VR::UN && ex.GetLastElement().IsUndefinedLength() )
      {
      // non CP 246
      // P.Read( is );
      is.clear();
      if( haspreamble )
        {
        is.seekg(128+4, std::ios::beg);
        }
      else
        {
        is.seekg(0, std::ios::beg);
        }
      if( hasmetaheader )
        {
        // FIXME: we are reading twice the same meta-header, we succedeed the first time...
        // We should be able to seek to proper place instead of re-reading
        FileMetaInformation header;
        header.Read(is);
        }

      // GDCM 1.X
      gdcmWarningMacro( "Attempt to read non CP 246" );
      F->GetDataSet().Clear(); // remove garbage from 1st attempt...
      F->GetDataSet().Read<CP246ExplicitDataElement,SwapperNoOp>(is);
      }
    else if( ex.GetLastElement().GetVR() == VR::UN )
      {
      // P.Read( is );
      is.clear();
      if( haspreamble )
        {
        is.seekg(128+4, std::ios::beg);
        }
      else
        {
        is.seekg(0, std::ios::beg);
        }
      if( hasmetaheader )
        {
        // FIXME: we are reading twice the same meta-header, we succedeed the first time...
        // We should be able to seek to proper place instead of re-reading
        FileMetaInformation header;
        header.Read(is);
        }

      // GDCM 1.X
      gdcmWarningMacro( "Attempt to read GDCM 1.X wrongly encoded");
      F->GetDataSet().Clear(); // remove garbage from 1st attempt...
      F->GetDataSet().Read<UNExplicitDataElement,SwapperNoOp>(is);
      // This file can only be rewritten as implicit...
      }
    else if ( ex.GetLastElement().GetTag() == Tag(0xfeff,0x00e0) )
      {
      // Famous philips where some private sequence were byteswapped !
      // eg. PHILIPS_Intera-16-MONO2-Uncompress.dcm
      // P.Read( is );
      is.clear();
      if( haspreamble )
        {
        is.seekg(128+4, std::ios::beg);
        }
      else
        {
        is.seekg(0, std::ios::beg);
        }
      if( hasmetaheader )
        {
        // FIXME: we are reading twice the same meta-header, we succedeed the first time...
        // We should be able to seek to proper place instead of re-reading
        FileMetaInformation header;
        header.Read(is);
        }

      // 
      gdcmWarningMacro( "Attempt to read Philips with ByteSwap private sequence wrongly encoded");
      F->GetDataSet().Clear(); // remove garbage from 1st attempt...
      abort();  // TODO FIXME
      }
    else
      {
      // Let's try again with an ExplicitImplicitDataElement:
      if( ts.GetSwapCode() == SwapCode::LittleEndian &&
        ts.GetNegociatedType() == TransferSyntax::Explicit )
        {
        // P.Read( is );
        if( haspreamble )
          {
          is.seekg(128+4, std::ios::beg);
          }
        else
          {
          is.seekg(0, std::ios::beg);
          }
        if( hasmetaheader )
          {
          // FIXME: we are reading twice the same meta-header, we succedeed the first time...
          // We should be able to seek to proper place instead of re-reading
          FileMetaInformation header;
          header.ReadCompat(is);
          }

        // Philips
        gdcmWarningMacro( "Attempt to read the file as mixture of explicit/implicit");
        F->GetDataSet().Clear(); // remove garbage from 1st attempt...
        F->GetDataSet().Read<ExplicitImplicitDataElement,SwapperNoOp>(is);
        // This file can only be rewritten as implicit...
        }
      }
    }

    //assert( Stream.eof() );
//    }
//  catch( std::exception &ex )
//    {
//    std::cerr << ex.what() << std::endl;
//    return false;
//    }


  //std::cout << F->GetDataSet() << std::endl;

  Dumper printer;
  printer.SetFile ( *F );
  //printer.Print( std::cout );

  // FIXME : call this function twice...
  //Stream.close();
  return is;
}

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

  gdcm::DoTheMMapRead(is);

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

