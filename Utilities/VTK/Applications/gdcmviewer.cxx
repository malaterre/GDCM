/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkGDCMReader.h"

#include "vtkXMLImageDataWriter.h"
#include "vtkPNGWriter.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImageViewer.h"
#include "vtkImageViewer2.h"
#include "vtkImageData.h"
#include "vtkCommand.h"

//----------------------------------------------------------------------------
// Callback for the interaction
class vtkGDCMObserver : public vtkCommand
{
public:
  static vtkGDCMObserver *New() 
    { 
    return new vtkGDCMObserver; 
    }
  vtkGDCMObserver()
    {
    ImageViewer = NULL;
    }
  virtual void Execute(vtkObject *, unsigned long event, void* )
    {
    if ( this->ImageViewer )
      {
      if ( event == vtkCommand::CharEvent )
        {
        int max = ImageViewer->GetWholeZMax();
        int slice = (ImageViewer->GetZSlice() + 1) % ++max;
        ImageViewer->SetZSlice( slice );
        ImageViewer->Render();
        }
      }
    }
  vtkImageViewer *ImageViewer;
};


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

  //const char *viewer_type = argv[0];
  //assert( strcmp(viewer_type, "gdcmviewer"  ) == 0
  //     || strcmp(viewer_type, "gdcmviewer2" ) == 0 );
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

   // Here is where we setup the observer, 
   vtkGDCMObserver *obs = vtkGDCMObserver::New();
   obs->ImageViewer = viewer;
   iren->AddObserver(vtkCommand::CharEvent,obs);
   obs->Delete();

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

