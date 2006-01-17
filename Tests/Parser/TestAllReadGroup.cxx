// generated file
#include "gdcmDataImages.h"

#include "gdcmDICOMIStream.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmGroup.txx"

template<class DEType>
void ReadGroups(gdcm::DICOMIStream &is)
{
  while( !is.eof())
    {
    gdcm::Group<DEType> g;
    is.Read(g);
    std::cout << g << std::endl;
    }
}


void TestReadGroup(const char *filename)
{
  std::cerr << filename << std::endl;
  gdcm::DICOMIStream Is;
  Is.SetFileName(filename);
  Is.Open();
  Is.Initialize();

  if( Is.GetNegociatedTS() == gdcm::DICOMIStream::Explicit )
    {
    ReadGroups<gdcm::ExplicitDataElement>(Is);
    }
  else
    {
    ReadGroups<gdcm::ImplicitDataElement>(Is);
    }
  Is.Close();
}

int TestAllReadGroup(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    TestReadGroup(filename);
    return 0;
    }

  // else
  int i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    TestReadGroup( filename );
    ++i;
    }


  return 0;
}
