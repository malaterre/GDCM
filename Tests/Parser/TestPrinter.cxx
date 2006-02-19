// generated file
#include "gdcmDataImages.h"

#include "gdcmPrinter.h"

void TestFilePrinter(const char *filename)
{
  //std ::cerr << "===============================================" << std::endl;
  //std::cerr << filename << std::endl;
  gdcm::Printer p;
  p.SetFileName(filename);
  p.Open();
  p.Initialize();
  p.Close();
}

int TestPrinter(int argc, char *argv[])
{
  //std::cerr << std::endl;
  if( argc == 2 )
    {
    const char *filename = argv[1];
    TestFilePrinter(filename);
    return 0;
    }

  // else
  int i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    TestFilePrinter( filename );
    ++i;
    }

  return 0;
}
