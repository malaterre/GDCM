#include "gdcmImageReader.h"

#include "gdcmDataImages.h"

int TestImageRead(const char* filename)
{
  gdcm::ImageReader reader;

  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    std::cerr << "Failed to read image from file: " << filename << std::endl;
    return 1;
    }

  //reader.GetPointer();
  std::cerr << "Success to read image from file: " << filename << std::endl;

  return 0;
}

int TestImageReader(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestImageRead(filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    r += TestImageRead( filename );
    ++i;
    }

  return r;
}
