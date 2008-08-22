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
#include "vtkGDCMImageWriter.h"

#include "vtkImageReader2Factory.h"
#include "vtkImageReader2.h"
#include "vtkImageData.h"
#include "vtkMINCImageReader.h"
#include "vtkMINCImageAttributes.h"
#include "vtkMedicalImageProperties.h"
#include "vtkTIFFReader.h"
#include "vtk_tiff.h" // ORIENTATION_BOTLEFT
#include "vtkGESignaReader.h"
#include "vtkImageExtractComponents.h"
#include "vtkImageRGBToYBR.h"
#include "vtkBMPReader.h"
#include "vtkLookupTable.h"
#include "vtkPointData.h"
#include "vtkStructuredPointsReader.h"
#include "vtkStructuredPoints.h"

#include "gdcmFilename.h"

int main(int argc, char *argv[])
{
  if( argc < 3 )
    {
    return 1;
    }
  const char *filename = argv[1];
  const char *outfilename = argv[2];

  vtkGDCMImageReader *reader = vtkGDCMImageReader::New();

  vtkImageReader2Factory* imgfactory = vtkImageReader2Factory::New();
  imgfactory->RegisterReader( reader );
  vtkImageReader2* imgreader =
    imgfactory->CreateImageReader2(filename);
  vtkStructuredPointsReader *datareader = vtkStructuredPointsReader::New();
  datareader->SetFileName( filename );
  int res = datareader->IsFileStructuredPoints();
  if( !imgreader && !res )
    {
    std::cerr << "could not find no reader to handle file: " << filename << std::endl;
    return 1;
    }
  imgfactory->Delete(); 

  vtkImageData *imgdata;
  if( imgreader )
    {
    imgreader->SetFileName(filename);
    imgreader->Update();
    imgdata = imgreader->GetOutput();
  std::cout << imgreader->GetClassName() << std::endl;
    }
  else if( res )
    {
    datareader->Update();
    imgdata = datareader->GetOutput();
    }

  vtkGDCMImageWriter * writer = vtkGDCMImageWriter::New();
  writer->SetFileName( outfilename );

  if( imgreader && imgreader->GetOutput()->GetNumberOfScalarComponents() == 4 )
    {
    std::cerr << "alpha channel will be lost" << std::endl;
    vtkImageExtractComponents *extract = vtkImageExtractComponents::New();
    extract->SetInput( imgreader->GetOutput() );
    extract->SetComponents( 0,1,2 );
    writer->SetInput( extract->GetOutput() );
    extract->Delete();
    }
  else
    {
    //writer->SetInput( imgreader->GetOutput() );
    writer->SetInput( imgdata );

#if 0
    vtkImageRGBToYBR * rgb2ybr = vtkImageRGBToYBR::New();
    rgb2ybr->SetInput( imgreader->GetOutput() );
    writer->SetInput( rgb2ybr->GetOutput() );
    writer->SetImageFormat( VTK_YBR );
#endif
    }

  // If input is 3D, let's write output as 3D if possible:
  if( imgdata->GetDimensions()[2] != 1 )
    {
    writer->SetFileDimensionality( 3 );
    }

  if( imgreader )
    {
    if( vtkGDCMImageReader * reader = vtkGDCMImageReader::SafeDownCast(imgreader) )
      {
      writer->SetMedicalImageProperties( reader->GetMedicalImageProperties() );
      writer->SetDirectionCosines( reader->GetDirectionCosines() );
      writer->SetShift( reader->GetShift() );
      writer->SetScale( reader->GetScale() );
      reader->GetMedicalImageProperties()->Print( std::cout );
      }
    else if( vtkBMPReader * reader = vtkBMPReader::SafeDownCast(imgreader) )
      {
      reader->Allow8BitBMPOn( );
      reader->Update( );
      //reader->GetLookupTable()->Print( std::cout );
      reader->GetOutput()->GetPointData()->GetScalars()->SetLookupTable( reader->GetLookupTable() );
      writer->SetImageFormat( VTK_LOOKUP_TABLE );
      }
    else if( vtkGESignaReader * reader = vtkGESignaReader::SafeDownCast(imgreader) )
      {
      writer->SetMedicalImageProperties( reader->GetMedicalImageProperties() );
      reader->GetMedicalImageProperties()->Print( std::cout );
      }
    else if( vtkMINCImageReader *reader = vtkMINCImageReader::SafeDownCast( imgreader ) )
      {
      writer->SetDirectionCosines( reader->GetDirectionCosines() );
      //writer->GetMedicalImageProperties()->SetModality( "MR" );
      // the following does not work with VTKData/Data/t3_grid_0.mnc
      //writer->SetScale( reader->GetRescaleSlope() );
      //writer->SetShift( reader->GetRescaleIntercept() );
      reader->GetImageAttributes()->PrintFileHeader();
      }
    else if( vtkTIFFReader *reader = vtkTIFFReader::SafeDownCast( imgreader ) )
      {
      // TIFF has resolution (spacing), and VTK make sure to set set in mm
      // For some reason vtkTIFFReader is all skrew up and will load the image in whatever orientation
      // as stored on file, thus this is up to the user to set it properly...
      // If anyone has any clue why...
      reader->SetOrientationType( ORIENTATION_BOTLEFT );
      }
    }
  // nothing special need to be done for vtkStructuredPointsReader 

  writer->Write();

  writer->GetInput()->Print( std::cout );

  writer->Delete();
  if( imgreader ) imgreader->Delete();
  datareader->Delete();
  reader->Delete();

  return 0;
}

