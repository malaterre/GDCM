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

  while( is >> de_tag )
    {
    if( de_tag.GetTag() == item )
      {
      std::cout << is.Tellg() << std::endl;
      continue;
      }
    is >> de;
    std::cout << de << std::endl;
    }
}

template<class DEType>
void PrintDataElementsHeader(gdcm::DICOMIStream &is)
{
  DEType de;
  gdcm::DataElement &de_tag = de;
  const gdcm::Tag t(0x0002,0x0010);
  bool isImplicit = false;
  while( is >> de_tag )
    {
    if( de_tag.GetTag().GetGroup() > 0x0002 )
      {
      std::cerr << "Entering" << std::endl;
      int l = -4;
      is.Seekg(l, std::ios::cur );
      if( isImplicit )
        {
        std::cerr << "Implicit" << std::endl;
        PrintDataElements<gdcm::ImplicitDataElement>(is);
        }
      else
        PrintDataElements<gdcm::ExplicitDataElement>(is);
      break;
      }
    else
      {
      is >> de;
      if( de_tag.GetTag() == t )
        {
        gdcm::TS::TSType ts = gdcm::TS::GetTSType( de.GetValue().GetPointer() );
        isImplicit = gdcm::TS::IsImplicit( ts );
        std::cout << "IsImplicit:" << isImplicit << std::endl;
        }
      std::cout << de << std::endl;
      }
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
