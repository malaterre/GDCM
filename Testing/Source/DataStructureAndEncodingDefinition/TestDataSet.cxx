#include "gdcmDataSet.h"
#include "gdcmDataElement.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"


int TestDataSet(int , char *[])
{
  gdcm::DataSet ds ( gdcm::TS::Implicit );
  std::cout << sizeof ds << std::endl;
  gdcm::ImplicitDataElement d;
  ds.InsertDataElement(d);
  const gdcm::DataElement& r =
	  ds.GetDataElement( gdcm::Tag(0,0) );
  std::cout << r << std::endl;

  const gdcm::Tag t = gdcm::Tag(0x1234, 0x5678);
  gdcm::ImplicitDataElement d2(t);
  std::cout << d2 << std::endl;
  ds.InsertDataElement(d2);
  const gdcm::DataElement& r2 =
	  ds.GetDataElement( t );
  std::cout << r2 << std::endl;

//  const gdcm::Tag t3 = gdcm::Tag(0x1234, 0x5679);
//  gdcm::ExplicitDataElement d3(t3);
//  std::cout << d3 << std::endl;
//  ds.InsertDataElement(d3);
//  const gdcm::DataElement& r3 =
//	  ds.GetDataElement( t3 );
//  std::cout << r3 << std::endl;

  std::cout << "Print Dataset:" << std::endl;
  std::cout << "Size:" << ds.Size() << std::endl;
  std::cout << ds << std::endl;

  return 0;
}

