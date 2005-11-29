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
  const gdcm::Tag item(0xfffe, 0xe000);

  while( !is.eof() && is >> de_tag )
    {
    if( de_tag.GetTag() == item )
      {
      std::cout << is.Tellg() << std::endl;
      abort();
      }
    is >> de;
    //std::cout << de << std::endl;
    }
}

void TestPrint(const char *filename)
{
  std::cerr << filename << std::endl;
  gdcm::DICOMIStream Is;
  Is.SetFileName(filename);
  Is.Open();
  Is.Initialize();

  if( Is.GetNegociatedTS() == gdcm::DICOMIStream::Explicit )
    {
    PrintDataElements<gdcm::ExplicitDataElement>(Is);
    }
  else
    {
    PrintDataElements<gdcm::ImplicitDataElement>(Is);
    }
}

int TestAllPrint(int argc, char *argv[])
{
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
