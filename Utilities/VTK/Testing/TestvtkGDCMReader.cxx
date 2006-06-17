#include "gdcmConfigure.h" // for GDCM_DATA_ROOT
#include "vtkGDCMReader.h"

#include "vtkPNGWriter.h"
#include "vtkImageData.h"

int TestvtkGDCMReader(int, char *[])
{
  const char filename[] = GDCM_DATA_ROOT "/test.acr";
  vtkGDCMReader *reader = vtkGDCMReader::New();
  reader->CanReadFile( filename );
  reader->SetFileName( filename );
  reader->Update();

  reader->GetOutput()->Print( cout );

  vtkPNGWriter *writer = vtkPNGWriter::New();
  writer->SetInputConnection( reader->GetOutputPort() );
  writer->SetFileName( "/tmp/test.png" );
  writer->Write();

  reader->Delete();
  writer->Delete();

  return 0;
}
