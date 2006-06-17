#include "vtkGDCMReader.h"

int TestvtkGDCMReader(int, char *[])
{
  vtkGDCMReader *reader = vtkGDCMReader::New();
  reader->Delete();

  return 0;
}
