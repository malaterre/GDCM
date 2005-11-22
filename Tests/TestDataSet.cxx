#include "gdcmDataSet.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"

int TestDataSet(int argc, char *argv[])
{
  const char *filename;
  const char *outfilename;
  if( argc < 2 )
    {
    filename = "/tmp/Explicit.dcm";
    outfilename = "/tmp/Explicit2.dcm";
    }
  else if( argc == 3 )
    {
    filename = argv[1];
    outfilename = argv[2];
    }
  else
    return 1;

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

  gdcm::DICOMIStream Is;
  Is.SetFileName(filename);
  Is.Open();
  Is.Initialize();

  gdcm::DICOMOStream Os;
  Os.SetFileName(outfilename);
  Os.Open();
  Os.WriteDICM();

  std::cout << "Printint result:" << std::endl;
  gdcm::DataElement &de_tag = de;
  while( Is >> de_tag )
    {
    Is >> de;
    assert( !(Is.eof()));
    std::cout << de << std::endl;
    Os << de;
    //de_tag.SetTag(gdcm::Tag(0x1234, 0x5678));
    }
  //Is >> ds;
  //std::cout << ds << std::endl;
  //Is.Close();

  //FIXME: This line should not compile:
  //gdcm::DataSet<int> dummy;

  return 0;
}
