// generated file
#include "gdcmDataImages.h"

#include "gdcmFileSeeker.h"
#include "gdcmDataElement.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"

void CheckSeek(gdcm::FileSeeker &f)
{
  if( f.GetNegociatedTS() == gdcm::DICOMIStream::Explicit )
    {
    gdcm::ExplicitDataElement de;
    f.Read(de);
    std::cout << "DE: " << de << std::endl;
    }
  else
    {
    gdcm::ImplicitDataElement de;
    f.Read(de);
    std::cout << "DE: " << de << std::endl;
    }
}

void TestSeek(const char *filename)
{
  std::cerr << filename << std::endl;
  gdcm::FileSeeker f;
  f.SetFileName(filename);
  f.Open();
  f.Initialize();

  unsigned int n = f.GetNumberOfOffset();
  for(unsigned int i=0; i<n; i++)
    {
    std::streampos off = f.GetOffsetByNumber(i);
    f.Seekg(off, std::ios::beg);
    std::cout << "Offset: " << off << std::endl;
    CheckSeek(f);
    }

  // Check all DICOM files have a patient name
  //const gdcm::Tag patientName(0x0010, 0x0010);
  //assert(f.FindTag(patientName) == true );
  //test.acr does not have a patient name
  const gdcm::Tag pixel(0x7fe0,0x0010);
  //assert(f.FindTag(pixel) == true );

  f.Close();
}

int TestFileSeeker(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    TestSeek(filename);
    return 0;
    }

  // else
  int i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    TestSeek( filename );
    ++i;
    }

  return 0;
}
