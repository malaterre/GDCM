#include "gdcmDataSet.h"
#include "gdcmDataElement.h"




int TestDataSet(int argc, char *argv[])
{
  gdcm::DataSet ds; 
  gdcm::DataElement d;
  ds.InsertDataElement(d);
  const gdcm::DataElement& r =
	  ds.GetDataElement( gdcm::Tag(0,0) );
  std::cout << r << std::endl;

  const gdcm::Tag t = gdcm::Tag(0x1234, 0x5678); 
  gdcm::DataElement d2(t);
  std::cout << d2 << std::endl;
  ds.InsertDataElement(d2);
  const gdcm::DataElement& r2 =
	  ds.GetDataElement( t );
  std::cout << r2 << std::endl;

  std::cout << "Print Dataset:" << std::endl;
  std::cout << "Size:" << ds.Size() << std::endl;
  std::cout << ds << std::endl;
  return 0;
}
