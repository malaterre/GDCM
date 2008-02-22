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
#include "gdcmImageReader.h"
#include "gdcmImageWriter.h"
#include "gdcmFilename.h"
#include "gdcmSystem.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmTesting.h"

int TestImageWrite(const char* filename)
{
  gdcm::ImageReader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    const gdcm::FileMetaInformation &header = reader.GetFile().GetHeader();
    gdcm::MediaStorage ms = header.GetMediaStorage();
    bool isImage = gdcm::MediaStorage::IsImage( ms );
    if( isImage )
      {
      std::cerr << "Failed to read: " << filename << std::endl;
      return 1;
      }
    else
      {
      // not an image give up...
      return 0;
      }
    }

  gdcm::Filename out(filename);
  std::string tmpdir = "/tmp/debug";
  std::string outfilename = tmpdir;
  outfilename += "/";
  outfilename += out.GetName();
  if( !gdcm::System::FileIsDirectory( tmpdir.c_str() ) )
    {
    if( !gdcm::System::MakeDirectory( tmpdir.c_str() ) )
      {
      std::cerr << "Error cannot execute test" << std::endl;
      std::cerr << "Last error was: " << gdcm::System::GetLastSystemError()
        << std::endl;
      return 1;
      }
    }

  gdcm::ImageWriter writer;
  writer.SetFileName( outfilename.c_str() );
  writer.SetImage( reader.GetImage() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }
  std::cout << "success: " << outfilename << std::endl;

  // Let's read that file back in !
  gdcm::ImageReader reader2;

  reader2.SetFileName( outfilename.c_str() );
  if ( reader2.Read() )
    {
    int res = 0;
    const gdcm::Image &img = reader2.GetImage();
    //std::cerr << "Success to read image from file: " << filename << std::endl;
    unsigned long len = img.GetBufferLength();
    if ( img.GetPhotometricInterpretation() ==
      gdcm::PhotometricInterpretation::PALETTE_COLOR )
      {
      len *= 3;
      }
    char* buffer = new char[len];
    img.GetBuffer(buffer);
    // On big Endian system we have byteswapped the buffer (duh!)
    // Since the md5sum is byte based there is now way it would detect
    // that the file is written in big endian word, so comparing against
    // a md5sum computed on LittleEndian would fail. Thus we need to
    // byteswap (again!) here:
#ifdef GDCM_WORDS_BIGENDIAN
    if( img.GetPixelType().GetBitsAllocated() == 16 )
      {
      assert( !(len % 2) );
      assert( img.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::MONOCHROME1
        || img.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::MONOCHROME2 );
      gdcm::ByteSwap<unsigned short>::SwapRangeFromSwapCodeIntoSystem(
        (unsigned short*)buffer, gdcm::SwapCode::LittleEndian, len/2);
      }
#endif
    // reuse the filename, since outfilename is simply the new representation of the old filename
    const char *ref = gdcm::Testing::GetMD5FromFile(filename);

    char digest[33];
    gdcm::System::ComputeMD5(buffer, len, digest);
    if( !ref )
      {
      // new regression image needs a md5 sum
      std::cout << "Missing md5 " << digest << " for: " << outfilename <<  std::endl;
      //abort();
      res = 1;
      }
    else if( strcmp(digest, ref) )
      {
      std::cerr << "Problem reading image from: " << outfilename << std::endl;
      std::cerr << "Found " << digest << " instead of " << ref << std::endl;
      res = 1;
#if 0
      std::ofstream debug("/tmp/dump.gray");
      debug.write(buffer, len);
      debug.close();
      //abort();
#endif
      }
    delete[] buffer;
    return res;
    }

#if 0
  // Ok we have now two files let's compare their md5 sum:
  char digest[33], outdigest[33];
  gdcm::System::ComputeFileMD5(filename, digest);
  gdcm::System::ComputeFileMD5(outfilename.c_str(), outdigest);
  if( strcmp(digest, outdigest) )
    {
    // too bad the file is not identical, so let's be paranoid and
    // try to reread-rewrite this just-writen file:
    // TODO: Copy file gdcm::System::CopyFile( );
    if( TestImageWrite( outfilename.c_str() ) )
      {
      std::cerr << filename << " and "
        << outfilename << " are different\n";
      return 1;
      }
    // In theory I need to compare the two documents to check they
    // are identical... TODO
    std::cerr << filename << " and "
      << outfilename << " should be compatible\n";
    return 0;
    }
  else
    {
    std::cerr << filename << " and "
      << outfilename << " are identical\n";
    return 0;
    }
#endif
  return 0;
}

int TestImageWriter(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestImageWrite(filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestImageWrite( filename );
    ++i;
    }

  return r;
}

