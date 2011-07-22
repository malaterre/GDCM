#include "gdcmTesting.h"
#include "gdcmSurfaceWriter.h"
#include "gdcmSurfaceReader.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmFilename.h"
#include "gdcmSystem.h"
#include "gdcmAttribute.h"

namespace gdcm
{
int TestSurfaceWriter(const char *subdir, const char* filename)
{
  SurfaceReader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
      std::cerr << "Failed to read: " << filename << std::endl;
      return 1;
    }
    std::cout << "success to read: " << filename << std::endl;

  // Create directory first:
  std::string tmpdir = Testing::GetTempDirectory( subdir );
  if( !System::FileIsDirectory( tmpdir.c_str() ) )
    {
    System::MakeDirectory( tmpdir.c_str() );
    //return 1;
    }
  std::string outfilename = Testing::GetTempFilename( filename, subdir );
  SurfaceWriter writer;
  writer.SetFileName( outfilename.c_str() );
  SegmentReader::SegmentVector segments = reader.GetSegments();
  writer.SetSegments( segments );
  writer.SetNumberOfSurfaces( reader.GetNumberOfSurfaces() );

  DataSet &             ds  = writer.GetFile().GetDataSet();
  FileMetaInformation & fmi = writer.GetFile().GetHeader();

  // Transfert syntax
  fmi.SetDataSetTransferSyntax( gdcm::TransferSyntax::ImplicitVRLittleEndian );  // Type 1

  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }
  std::cout << "success to write: " << outfilename << std::endl;

  SurfaceReader reader2;
  reader2.SetFileName( outfilename.c_str() );
  if ( !reader2.Read() )
    {
      std::cerr << "Failed to read: " << outfilename << std::endl;
      return 1;
    }
    std::cout << "success to read: " << outfilename << std::endl;

    int             res = 0;
    const SegmentReader::SegmentVector segments2 = reader.GetSegments();
    //std::cerr << "Success to read image from file: " << filename << std::endl;
    const SmartPointer< Surface > surface        = segments2[0]->GetSurface(0);
    const DataElement &           pointCoordData = surface->GetPointCoordinatesData();
    const ByteValue *             buffer         = pointCoordData.GetByteValue();
    const unsigned long           len            = buffer->GetLength();

    // reuse the filename, since outfilename is simply the new representation of the old filename
    const char *ref = Testing::GetMD5FromFile(filename);

    char digest[33] = {};
    Testing::ComputeMD5(buffer->GetPointer(), len, digest);
    if( !ref )
      {
      // new regression image needs a md5 sum
      std::cout << "Missing md5 " << digest << " for: " << outfilename <<  std::endl;
      //assert(0);
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
      //assert(0);
#endif
      }
    return res;

#if 0
  // Ok we have now two files let's compare their md5 sum:
  char digest[33], outdigest[33];
  System::ComputeFileMD5(filename, digest);
  System::ComputeFileMD5(outfilename.c_str(), outdigest);
  if( strcmp(digest, outdigest) )
    {
    // too bad the file is not identical, so let's be paranoid and
    // try to reread-rewrite this just-writen file:
    // TODO: Copy file System::CopyFile( );
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
}

int TestSurfaceWriter(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return gdcm::TestSurfaceWriter(argv[0],filename);
    }

  // else
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += gdcm::TestSurfaceWriter(argv[0], filename );
    ++i;
    }

  return r;
}
