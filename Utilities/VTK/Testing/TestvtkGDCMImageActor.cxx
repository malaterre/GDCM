/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmConfigure.h" // for GDCM_DATA_ROOT
#include "vtkGDCMReader.h"

#include "vtkPNGWriter.h"
#include "vtkImageData.h"
#include "vtkImageActor.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkInteractorStyleImage.h"
#include <vtksys/SystemTools.hxx>

#include "gdcmDataImages.h"

int TestvtkGDCMReadImageActor(const char *filename)
{
  vtkGDCMReader *reader = vtkGDCMReader::New();
  //reader->CanReadFile( filename );
  std::cerr << "Reading : " << filename << std::endl;
  reader->SetFileName( filename );
  reader->Update();

  reader->GetOutput()->Print( cout );


vtkImageActor *ia = vtkImageActor::New();
ia->SetInput( reader->GetOutput() );

//# Create the RenderWindow, Renderer and both Actors
vtkRenderer *ren1 = vtkRenderer::New();
vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer (ren1);
vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow (renWin);

// Add the actors to the renderer, set the background and size
ren1->AddActor (ia);
//ren1-> SetBackground 0.1 0.2 0.4
//renWin->SetSize (0,0);

      vtkInteractorStyleImage *style = vtkInteractorStyleImage::New();
      iren->SetInteractorStyle( style );
      style->Delete();
//# render the image
//iren AddObserver UserEvent {wm deiconify .vtkInteract}
//renWin->Render();
iren->Initialize();
iren->Start();


//set cam1 [ren1 GetActiveCamera]
//$cam1 Elevation -30
//$cam1 Roll -20
//ren1 ResetCameraClippingRange
//renWin Render

  reader->Delete();
  return 0; 
}

int TestvtkGDCMImageActor(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestvtkGDCMReadImageActor(filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    r += TestvtkGDCMReadImageActor( filename );
    ++i;
    }

  return r;
}
