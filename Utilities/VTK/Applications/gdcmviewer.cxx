#include "vtkGDCMReader.h"

#include "vtkXMLImageDataWriter.h"
#include "vtkPNGWriter.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImageViewer.h"
#include "vtkImageViewer2.h"
#include "vtkImageData.h"

int main(int argc, char *argv[])
{
  if( argc < 2 )
    {
    return 1;
    }

  const char *filename = argv[1];
  vtkGDCMReader *reader = vtkGDCMReader::New();
  reader->SetFileName( filename );

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();

  vtkImageViewer *viewer = vtkImageViewer::New();

  // For a single medical image, it would be more efficient to use
  // 0028|1050 [DS] [Window Center]
  // 0028|1051 [DS] [Window Width]
  // but gdcmviewer doesn't know about them :-(

  reader->Update();
  reader->GetOutput()->Print( cout );
  double *range = reader->GetOutput()->GetScalarRange();
  viewer->SetColorLevel (0.5 * (range[1] + range[0]));
  viewer->SetColorWindow (range[1] - range[0]);

  viewer->SetInputConnection ( reader->GetOutputPort() );
  viewer->SetupInteractor (iren);

  iren->Initialize();
  iren->Start();

  //if you wish you can export dicom to a vtk file
#if 0
  vtkXMLImageDataWriter *writer = vtkXMLImageDataWriter::New();
  writer->SetInputConnection( reader->GetOutputPort());
  writer->SetFileName( "debug.vtk" );
  writer->SetDataModeToBinary();
  writer->Write();
  writer->Delete();
#endif

#if 0
  vtkPNGWriter *writer = vtkPNGWriter::New();
  writer->SetInputConnection( reader->GetOutputPort() );
  writer->SetFileName( "debug.png" );
  writer->Write();
  writer->Delete();
#endif

  reader->Delete();
  iren->Delete();
  viewer->Delete();

  return 0;
}

