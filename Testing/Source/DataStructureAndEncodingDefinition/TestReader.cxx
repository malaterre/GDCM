#include "gdcmReader.h"

int TestReader(int argc, char *argv[])
{
  if( argc < 2 )
    return 1;

  std::string filename = argv[1];
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    return 1;
    }

  const gdcm::DataSet &ds = reader.GetDataSet();
  std::cout << ds << std::endl;

  return 0;
}
