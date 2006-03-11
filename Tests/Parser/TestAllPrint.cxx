// generated file
#include "gdcmDataImages.h"

#include "gdcmDataSet.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmTS.h"
#include "gdcmDICOMIStream.h"

template<class DEType>
void PrintDataElements(gdcm::DICOMIStream &is)
{
  DEType de;
  try
    {
    while( is.Read(de) )
      {
      std::cerr << de << std::endl;
      }
    }
  catch(std::exception &e)
    {
    std::cerr << "Exception:" << typeid(e).name() << std::endl;
    }
}

void TestPrint(const char *filename)
{
  std ::cerr << "===============================================" << std::endl;
  std::cerr << filename << std::endl;
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
  std::cerr << std::endl;
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
