#include "gdcmDataSet.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"

int TestDataSet(int , char *[])
{
  // Explicit
  typedef gdcm::ExplicitDataElement Explicit;
  Explicit de;
  gdcm::DataSet<Explicit> ds;
  ds.AddDataElement(gdcm::Tag(0,0), de);
  std::cout << ds << std::endl;

  // Implicit
  typedef gdcm::ImplicitDataElement Implicit;
  Implicit ide;
  gdcm::DataSet<Implicit> ds2;
  ds2.AddDataElement(gdcm::Tag(0,1), ide);
  std::cout << ds2 << std::endl;

  gdcm::IStream Is;
  Is.SetFileName("/tmp/Explicit.dcm");
  Is.Open();
  Is.ReadDICM();
  gdcm::Tag t;
  while( !Is.eof() )
    {
    Is.Read(t);
    if( Is.eof() ) break;
    Is >> de;
    std::cout << t << "," << de << std::endl;
    }
  Is.Close();

  //FIXME: This line should not compile:
  //gdcm::DataSet<int> dummy;

  return 0;
}
