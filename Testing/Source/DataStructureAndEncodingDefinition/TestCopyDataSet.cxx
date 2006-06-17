#include "gdcmReader.h"
#include "gdcmDataSet.h"

int TestCopyDataSet(int, char *[])
{
  const char filename[] = GDCM_DATA_ROOT "/test.acr";
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    return 1;
    }

  const gdcm::DataSet &ds = reader.GetDataSet();
  std::cout << ds << std::endl;

  gdcm::DataSet ds_copy = ds;

  return 0;
}
