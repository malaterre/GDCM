// generated file
#include "gdcmDataImages.h"

#include "gdcmDataSet.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmTS.h"

template<class DEType>
void PrintDataElements(gdcm::DICOMIStream &is)
{
  DEType de;
  gdcm::DataElement &de_tag = de;
  std ::cerr << "---------------" << std::endl;;
  while( !is.eof() && is >> de_tag )
    {
    is >> de;
    std::cout << de << std::endl;
    }
  std ::cerr << "---------------" << std::endl;;
}

void TestPrint(const char *filename)
{
  std ::cerr << "===============================================  " 
             << filename << std::endl;
  gdcm::DICOMIStream Is;
  Is.SetFileName(filename);
  Is.Open();
  Is.Initialize();

  if( Is.GetNegociatedTS() == gdcm::DICOMIStream::Explicit )
    {
    std ::cerr << "==gdcm::DICOMIStream::Explicit==" << std::endl;
    PrintDataElements<gdcm::ExplicitDataElement>(Is);
    }
  else
    {
    std ::cerr << "==gdcm::DICOMIStream::Implicit==" << std::endl;
    PrintDataElements<gdcm::ImplicitDataElement>(Is);
    }
  Is.Close();
}

int TestAllPrint(int argc, char *argv[])
{
  std::cerr << std::endl << "--> in TestAllPrint " << std::endl;
  if( argc == 2 )
    {
    const char *filename = argv[1];
    TestPrint(filename);
    return 0;
    }

  // else
  int i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    TestPrint( filename );
    ++i;
    }

  return 0;
}
