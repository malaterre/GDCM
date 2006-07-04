#include "gdcmReader.h"
#include "gdcmFileMetaInformation.h"

#include "gdcmDataImages.h"

int TestRead(const char* filename)
{
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  std::cerr << "Success to read: " << filename << std::endl;

  const gdcm::FileMetaInformation &h = reader.GetHeader();
  std::cout << h << std::endl;

  const gdcm::DataSet &ds = reader.GetDataSet();
  std::cout << ds << std::endl;

  return 0;
}

int TestReader(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestRead(filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    r += TestRead( filename );
    ++i;
    }

  return r;
}
