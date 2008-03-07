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
#include "vtkGDCMThreadedImageReader.h"
#include "vtkGDCMImageReader.h"
#include "vtkCommand.h"

#include "gdcmDirectory.h"
#include "gdcmSystem.h"
#include "gdcmImageReader.h"

#include "gdcmTesting.h"

#include "vtkPNGWriter.h"
#include "vtkStringArray.h"
#include "vtkStructuredPointsWriter.h"
#include "vtkImageData.h"
//#include <vtksys/SystemTools.hxx>

#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "vtkVolumeProperty.h"
//#include "vtkVolumeTextureMapper3D.h"
#include "vtkVolume.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"


class ProgressObserver : public vtkCommand
{
public:
  static ProgressObserver* New() {
    return new ProgressObserver;
  }

  virtual void Execute(vtkObject* caller, unsigned long event, void *callData)
    {
    if( event == vtkCommand::ProgressEvent )
      {
      std::cout << ((vtkGDCMThreadedImageReader*)caller)->GetProgress() << std::endl;
      }
    }
};


template <typename TReader>
int ExecuteInformation(const char *filename, TReader *vtkreader)
{
  gdcm::ImageReader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    return 0;
    }
  const gdcm::Image &image = reader.GetImage();
  const unsigned int *dims = image.GetDimensions();

  // Set the Extents.
  assert( image.GetNumberOfDimensions() >= 2 );
  int dataextent[6] = {};
  dataextent[0] = 0;
  dataextent[1] = dims[0] - 1;
  dataextent[2] = 0;
  dataextent[3] = dims[1] - 1;
  if( image.GetNumberOfDimensions() == 2 )
    {
    vtkStringArray *filenames = vtkreader->GetFileNames();
    if ( filenames && filenames->GetNumberOfValues() > 1 )
      {
      dataextent[4] = 0;
      dataextent[5] = filenames->GetNumberOfValues() - 1;
      }
    else
      {
      dataextent[4] = 0;
      dataextent[5] = 0;
      }
    }
  else
    {
    assert( image.GetNumberOfDimensions() == 3 );
    //this->FileDimensionality = 3;
    dataextent[4] = 0;
    dataextent[5] = dims[2] - 1;
    }
  //this->DataSpacing[0] = 1.;
  //this->DataSpacing[1] = -1.;
  //this->DataSpacing[2] = 1.;

  gdcm::PixelFormat pixeltype = image.GetPixelFormat();
  int datascalartype = VTK_VOID;
  switch( pixeltype )
    {
  case gdcm::PixelFormat::INT8:
    datascalartype = VTK_CHAR;
    break;
  case gdcm::PixelFormat::UINT8:
    datascalartype = VTK_UNSIGNED_CHAR;
    break;
  case gdcm::PixelFormat::INT16:
    datascalartype = VTK_SHORT;
    break;
  case gdcm::PixelFormat::UINT16:
    datascalartype = VTK_UNSIGNED_SHORT;
    break;
  default:
    ;
    }

  unsigned int numberOfScalarComponents = pixeltype.GetSamplesPerPixel();

  vtkreader->SetDataExtent( dataextent );
  vtkreader->SetDataScalarType ( datascalartype );
  vtkreader->SetNumberOfScalarComponents( numberOfScalarComponents );

  return 1;
}

template <typename TReader>
int TestvtkGDCMThreadedImageRead(const char *filename)
{
  TReader *reader = TReader::New();
  reader->FileLowerLeftOn();
  //reader->CanReadFile( filename );
  std::cerr << "Reading : " << filename << std::endl;

  const char *refimage = NULL;
  if( gdcm::System::FileIsDirectory( filename ) )
    {
    gdcm::Directory d;
    d.Load( filename );
    gdcm::Directory::FilenamesType l = d.GetFilenames();
    const unsigned int nfiles = l.size();
    vtkStringArray *sarray = vtkStringArray::New();
    for(unsigned int i = 0; i < nfiles; ++i)
      {
      sarray->InsertNextValue( l[i] );
      }
    assert( sarray->GetNumberOfValues() == (int)nfiles );
    reader->SetFileNames( sarray );
    sarray->Delete();
    refimage = sarray->GetValue( 0 ); // Ok since sarray is ref count
    }
  else
    {
    reader->SetFileName( filename );
    refimage = filename;
    }

  // In all cases we need to explicitely say what the image type is:
  if( !ExecuteInformation<TReader>(refimage, reader) )
    {
    std::cerr << "file: " << refimage << " is not an image. giving up" << std::endl;
    reader->Delete();
    return 0;
    }


  ProgressObserver *obs = ProgressObserver::New();
  //reader->AddObserver( vtkCommand::ProgressEvent, obs);
  reader->Update();
  obs->Delete();

  reader->GetOutput()->Print( cout );

/*
  vtkPNGWriter *writer = vtkPNGWriter::New();
  writer->SetInputConnection( reader->GetOutputPort() );
  std::string pngfile = vtksys::SystemTools::GetFilenamePath( filename );
  pngfile = "/tmp/png";
  pngfile += '/';
  pngfile += vtksys::SystemTools::GetFilenameWithoutExtension( filename );
  pngfile += ".png";
  writer->SetFileName( pngfile.c_str() );
  writer->Write();
  writer->Delete();
*/
  vtkStructuredPointsWriter *writer = vtkStructuredPointsWriter::New();
  writer->SetInput( reader->GetOutput() );
  writer->SetFileName( "TestvtkGDCMThreadedImageReader.vtk" );
  writer->SetFileTypeToBinary();
  //writer->Write();
  writer->Delete();

#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
  double *s = reader->GetOutput()->GetScalarRange();
#else
  float *s = reader->GetOutput()->GetScalarRange();
#endif
  std::cout << s[0] << " " << s[1] << std::endl;

/*
  // Create transfer functions for opacity and color
  vtkPiecewiseFunction *opacityTransferFunction = vtkPiecewiseFunction::New();
  opacityTransferFunction->AddPoint(  600 , 0.0);
  opacityTransferFunction->AddPoint( 2000 , 1.0);

  vtkColorTransferFunction *colorTransferFunction = vtkColorTransferFunction::New();
  //colorTransferFunction ->ClampingOff();
  //colorTransferFunction ->AddHSVPoint(      0.0, 0.01, 1.0, 1.0);
  //colorTransferFunction ->AddHSVPoint(   1000.0, 0.50, 1.0, 1.0);
  //colorTransferFunction ->AddHSVPoint(   2000.0, 0.99, 1.0, 1.0);
  //colorTransferFunction ->SetColorSpaceToHSV();
  colorTransferFunction ->AddRGBPoint  (    s[0], 0.0, 0.0, 0.0);
  colorTransferFunction ->AddRGBPoint  (    (s[0] + s[1]) / 8., 0.25, 0.25, 0.25);
  colorTransferFunction ->AddRGBPoint  (    (s[0] + s[1]) / 4., 0.5, 0.25, 0.25);
  colorTransferFunction ->AddRGBPoint  (    s[1], 1.0, 1.0, 1.0);
  //colorTransferFunction ->AddRGBPoint  ( 3.* (s[0] + s[1]) / 4 , 1.0, 0.0, 0.0);
  //colorTransferFunction ->AddRGBPoint  (  (s[0] + s[1]) / 2, 0.0, 0.0, 1.0);
  //colorTransferFunction ->AddRGBPoint  ( 1.*(s[0] + s[1]) / 4 , 0.0, 1.0, 0.0);
  //colorTransferFunction ->AddRGBPoint  (  s[0], 0.0, 0.2, 0.0);

  // Create properties, mappers, volume actors, and ray cast function
  vtkVolumeProperty *volumeProperty = vtkVolumeProperty::New();
  volumeProperty ->SetColor( colorTransferFunction);
  volumeProperty ->SetScalarOpacity (opacityTransferFunction);

  vtkVolumeTextureMapper3D *volumeMapper = vtkVolumeTextureMapper3D::New();
  volumeMapper ->SetInputConnection (reader->GetOutputPort());
  volumeMapper ->SetSampleDistance (0.25);

  vtkVolume *volume = vtkVolume::New();
  volume ->SetMapper (volumeMapper);
  volume ->SetProperty (volumeProperty);

  // Okay now the graphics stuff
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin ->ReportGraphicErrorsOn();
  renWin ->AddRenderer (ren1);
  renWin ->SetSize (256, 256);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren ->SetRenderWindow (renWin);

  //ren1 ->SetBackground (0.1, 0.2, 0.4);
  ren1-> AddViewProp (volume);
  renWin->Render();
  ren1 ->ResetCameraClippingRange();

  iren->Initialize();
  iren->Start();
*/
  reader->Delete();

  return 0; 
}

int TestvtkGDCMThreadedImageReader(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestvtkGDCMThreadedImageRead<vtkGDCMThreadedImageReader>(filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestvtkGDCMThreadedImageRead<vtkGDCMThreadedImageReader>( filename );
    ++i;
    }

  return r;
}
