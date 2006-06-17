#include "gdcmConfigure.h" // for GDCM_DATA_ROOT
#include "vtkGDCMReader.h"

int TestvtkGDCMReader(int, char *[])
{
  const char filename[] = GDCM_DATA_ROOT "/test.acr";
  vtkGDCMReader *reader = vtkGDCMReader::New();
  reader->CanReadFile( filename );
  reader->SetFileName( filename );
  reader->Update();

  reader->Delete();

  return 0;
}
