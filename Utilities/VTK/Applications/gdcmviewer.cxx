/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkGDCMImageReader.h"
//#include "vtkGDCMThreadedImageReader.h"

#include "vtkXMLImageDataWriter.h"
#include "vtkPNGWriter.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImageViewer.h"
#include "vtkImageViewer2.h"
#include "vtkImageData.h"
#include "vtkCommand.h"
#include "vtkRenderer.h"
#include "vtkStringArray.h"
#include "vtkDebugLeaks.h"

#include "gdcmFilename.h"

#include <assert.h>
//----------------------------------------------------------------------------
// vtkImageViewer2 new interface wants SetSlice, but vtkImageViewer does not have
// this new interface (what a pain), so let's fake a new interface to
// vtkImageViewer without patching VTK 
class vtkGDCMImageViewer : public vtkImageViewer
{
public:
  vtkTypeRevisionMacro(vtkGDCMImageViewer,vtkImageViewer);

  static vtkGDCMImageViewer *New()
    { 
#ifdef VTK_DEBUG_LEAKS
    vtkDebugLeaks::ConstructClass("vtkGDCMImageViewer");
#endif
    return new vtkGDCMImageViewer; 
    }
  int GetSlice() { return this->GetZSlice(); }
  void SetSlice(int s) { this->SetZSlice(s); }

  int GetSliceMin() { return this->GetWholeZMin(); }
  int GetSliceMax() { return this->GetWholeZMax(); }
};
vtkCxxRevisionMacro(vtkGDCMImageViewer, "$Revision: 1.30 $");
vtkInstantiatorNewMacro(vtkGDCMImageViewer);

//----------------------------------------------------------------------------
// Callback for the interaction
template <typename TViewer>
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
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
        int max = ImageViewer->GetSliceMax();
        int slice = (ImageViewer->GetSlice() + 1) % ++max;
        ImageViewer->SetSlice( slice );
#else
        int max = ImageViewer->GetWholeZMax();
        int slice = (ImageViewer->GetZSlice() + 1 ) % ++max;
        ImageViewer->SetZSlice( slice );
        ImageViewer->GetRenderer()->ResetCameraClippingRange();
#endif
        ImageViewer->Render();
        }
      }
    }
  TViewer *ImageViewer;
};


// A feature in VS6 make it painfull to write template code
// that do not contain the template parameter in the function
// signature. Thus always pass parameter in the function:
template <typename TViewer>
void ExecuteViewer(TViewer *viewer, vtkStringArray *filenames)
{
  vtkGDCMImageReader *reader = vtkGDCMImageReader::New();
  if( filenames->GetSize() == 1 ) // Backward compatible...
    {
    reader->SetFileName( filenames->GetValue(0).c_str() );
    }
  else
    {
    reader->SetFileNames( filenames );
    }
  //reader->Update();
  //reader->GetOutput()->Print( std::cout );

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  // For a single medical image, it would be more efficient to use
  // 0028|1050 [DS] [Window Center]
  // 0028|1051 [DS] [Window Width]
  // but gdcmviewer doesn't know about them :-(

  reader->Update();
  //reader->Print( cout );
  //reader->GetOutput()->Print( cout );
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
  double *range = reader->GetOutput()->GetScalarRange();
#else
  float *range = reader->GetOutput()->GetScalarRange();
#endif /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/
  std::cerr << "Range: " << range[0] << " " << range[1] << std::endl;
  viewer->SetColorLevel (0.5 * (range[1] + range[0]));
  viewer->SetColorWindow (range[1] - range[0]);

#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
  viewer->SetInputConnection ( reader->GetOutputPort() );
#else
  viewer->SetInput( reader->GetOutput() );
#endif /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/
  viewer->SetupInteractor (iren);
  int dims[3];
  reader->GetOutput()->GetDimensions(dims);
  // Make sure to display on most screen
  dims[0] = (dims[0] < 600 ) ? dims[0] : 600;
  dims[1] = (dims[1] < 600 ) ? dims[1] : 600;
  viewer->Render(); // EXTREMELY IMPORTANT for vtkImageViewer2
  viewer->SetSize( dims );

  // Here is where we setup the observer, 
  vtkGDCMObserver<TViewer> *obs = vtkGDCMObserver<TViewer>::New();
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
}

int main(int argc, char *argv[])
{
  vtkStringArray *filenames = vtkStringArray::New();
  if( argc < 2 )
    {
    std::cerr << argv[0] << " filename1.dcm [filename2.dcm ...]\n";
    return 1;
    }
  else
    {
    for(int i=1; i < argc; ++i)
      {
      filenames->InsertNextValue( argv[i] );
      }
    //names->Print( std::cout );
    }


  gdcm::Filename viewer_type(argv[0]);
  //assert( strcmp(viewer_type, "gdcmviewer"  ) == 0
  //     || strcmp(viewer_type, "gdcmviewer2" ) == 0 );
  
  if( strcmp(viewer_type.GetName(), "gdcmviewer" ) == 0 )
    {
    vtkGDCMImageViewer *viewer = vtkGDCMImageViewer::New();
    ExecuteViewer<vtkGDCMImageViewer>(viewer, filenames);
    }
  else if( strcmp(viewer_type.GetName(), "gdcmviewer2" ) == 0 )
    {
    vtkImageViewer2 *viewer = vtkImageViewer2::New();
    ExecuteViewer<vtkImageViewer2>(viewer, filenames);
    }
  else
    {
    std::cerr << "Unhandled : " << viewer_type.GetName() << std::endl;
    filenames->Delete();
    return 1;
    }

  filenames->Delete();
  return 0;
}

