#include "gdcmDataSet.txx"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"

int TestDataSet(int argc, char *argv[])
{
  const char *filename;
  const char *outfilename;
  if( argc < 2 )
    {
    // Very simple file: Explicit, Little endian...
    filename = GDCM_DATA_ROOT "/DermaColorLossLess.dcm";
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
  de.SetTag(gdcm::Tag(0,0));
  ds.AddDataElement(de);
  
  std::cout << ds << std::endl;

  // Implicit
  typedef gdcm::ImplicitDataElement Implicit;
  Implicit ide;
  gdcm::DataSet<Implicit> ds2;
  ide.SetTag(gdcm::Tag(0,1));
  ds2.AddDataElement(ide);
  std::cout << ds2 << std::endl;

  gdcm::DICOMIStream Is;
  Is.SetFileName(filename);
  Is.Open();
  if( !Is ) return 1;
  Is.Initialize();

  gdcm::DICOMOStream Os;
  Os.SetFileName(outfilename);
  Os.Open();
  if( !Os ) return 1;
  Os.WriteDICM();

  std::cout << "Printing result:" << std::endl;
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

  Is.Close();
  Os.Close();
  return 0;
}
