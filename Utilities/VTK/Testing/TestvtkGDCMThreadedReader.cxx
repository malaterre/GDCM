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
#include "vtkGDCMThreadedReader.h"
#include "vtkGDCMReader.h"

#include "gdcmDirectory.h"
#include "gdcmImageReader.h"

#include "gdcmDataImages.h" // generated file

#include "vtkPNGWriter.h"
#include "vtkStringArray.h"
#include "vtkStructuredPointsWriter.h"
#include "vtkImageData.h"
#include <vtksys/SystemTools.hxx>

template <typename TReader>
void ExecuteInformation(const char *filename, TReader *vtkreader)
{
  gdcm::ImageReader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    //return 0;
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

  gdcm::PixelType pixeltype = image.GetPixelType();
  int datascalartype = VTK_VOID;
  switch( pixeltype )
    {
  case gdcm::PixelType::INT8:
    datascalartype = VTK_SIGNED_CHAR;
    break;
  case gdcm::PixelType::UINT8:
    datascalartype = VTK_UNSIGNED_CHAR;
    break;
  case gdcm::PixelType::INT16:
    datascalartype = VTK_SHORT;
    break;
  case gdcm::PixelType::UINT16:
    datascalartype = VTK_UNSIGNED_SHORT;
    break;
  default:
    ;
    }

  unsigned int numberOfScalarComponents = pixeltype.GetSamplesPerPixel();
  if( image.GetPhotometricInterpretation() == 
    gdcm::PhotometricInterpretation::PALETTE_COLOR )
    {
    assert( numberOfScalarComponents == 1 );
    numberOfScalarComponents = 3;
    }

  vtkreader->SetDataExtent( dataextent );
  vtkreader->SetDataScalarType ( datascalartype );
}

template <typename TReader>
int TestvtkGDCMThreadedRead(const char *filename)
{
  TReader *reader = TReader::New();
  //reader->CanReadFile( filename );
  std::cerr << "Reading : " << filename << std::endl;

  const char *refimage = NULL;
  if( gdcm::Directory::IsDirectory( filename ) )
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
  ExecuteInformation<TReader>(refimage, reader);


  reader->Update();

  //reader->GetOutput()->Print( cout );

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
  writer->SetFileName( "TestvtkGDCMThreadedReader.vtk" );
  writer->SetFileTypeToBinary();
  //writer->Write();
  writer->Delete();

  reader->Delete();

  return 0; 
}

int TestvtkGDCMThreadedReader(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestvtkGDCMThreadedRead<vtkGDCMThreadedReader>(filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    r += TestvtkGDCMThreadedRead<vtkGDCMThreadedReader>( filename );
    ++i;
    }

  return r;
}
