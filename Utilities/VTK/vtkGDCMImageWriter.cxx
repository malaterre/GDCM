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
#include "vtkGDCMImageWriter.h"

#include "vtkObjectFactory.h"
#include "vtkInformationVector.h"
#include "vtkImageData.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformation.h"
#include "vtkLookupTable.h"

#if (VTK_MAJOR_VERSION < 5)
#error Your VTK version is too old
#else
#include "vtkMedicalImageProperties.h"
#endif

#include "gdcmImageWriter.h"
#include "gdcmByteValue.h"

//struct vtkGDCMImageWriterInternals
//{
//  gdcm::ImageWriter DICOMWriter;
//};

vtkCxxRevisionMacro(vtkGDCMImageWriter, "$Revision: 1.1 $")
vtkStandardNewMacro(vtkGDCMImageWriter)

vtkCxxSetObjectMacro(vtkGDCMImageWriter,LookupTable,vtkLookupTable);
vtkCxxSetObjectMacro(vtkGDCMImageWriter,MedicalImageProperties,vtkMedicalImageProperties);

vtkGDCMImageWriter::vtkGDCMImageWriter()
{
  //this->Internals = new vtkGDCMImageWriterInternals;
  //this->ScalarArrayName = NULL;
  //this->SetScalarArrayName( "GDCM" );

  this->LookupTable = vtkLookupTable::New();
  this->MedicalImageProperties = vtkMedicalImageProperties::New();
}

vtkGDCMImageWriter::~vtkGDCMImageWriter()
{
  //delete this->Internals;
  this->LookupTable->Delete();
  this->MedicalImageProperties->Delete();
}
//----------------------------------------------------------------------------
int vtkGDCMImageWriter::FillInputPortInformation(
  int port, vtkInformation *info)
{
  if (!this->Superclass::FillInputPortInformation(port, info))
    {
    return 0;
    }
  info->Set(vtkAlgorithm::INPUT_IS_REPEATABLE(), 1);
  return 1;
}
//---------------------------------------------------------------------------
int vtkGDCMImageWriter::RequestInformation(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *vtkNotUsed(outputVector))
{
  // Check to make sure that all input information agrees
  int mismatchedInputs = 0;

  double spacing[3];
  double origin[3];
  int extent[6];
  int components = 0;
  int dataType = 0;

  // For each connection on port 0, check agains the first connection
  for (int i = 0; i < this->GetNumberOfInputConnections(0); i++)
    {
    vtkInformation *inInfo = inputVector[0]->GetInformationObject(i);
    if (i == 0)
      {
      inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
      inInfo->Get(vtkDataObject::SPACING(), spacing);
      inInfo->Get(vtkDataObject::ORIGIN(), origin);
      components = inInfo->Get(vtkDataObject::FIELD_NUMBER_OF_COMPONENTS());
      dataType = inInfo->Get(vtkDataObject::FIELD_ARRAY_TYPE());
      continue;
      }

    if (memcmp(inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT()),
               extent, sizeof(extent)) ||
        memcmp(inInfo->Get(vtkDataObject::SPACING()), spacing,
               sizeof(spacing)) ||
        memcmp(inInfo->Get(vtkDataObject::ORIGIN()), origin,
               sizeof(origin)) ||
        inInfo->Get(vtkDataObject::FIELD_NUMBER_OF_COMPONENTS())
          != components ||
        inInfo->Get(vtkDataObject::FIELD_ARRAY_TYPE()) != dataType)
      {
      mismatchedInputs = 1;
      return 0;
      }
    }

  return 1;
}

//--------------------------------------------------------------------------
int vtkGDCMImageWriter::RequestUpdateExtent(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *vtkNotUsed(outputVector))
{
  // Set the UpdateExtent from the DataUpdateExtent for the current slice
  int n = inputVector[0]->GetNumberOfInformationObjects();
  for (int i = 0; i < n; i++)
    {
    vtkInformation *inInfo = inputVector[0]->GetInformationObject(i);
    inInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),
                this->DataUpdateExtent, 6);
    }

  return 1;
}

//--------------------------------------------------------------------------
int vtkGDCMImageWriter::RequestData(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector,
  vtkInformationVector* vtkNotUsed(outputVector))
{
  // Go through the inputs and write the data for each
  int numTimeSteps = inputVector[0]->GetNumberOfInformationObjects();

  for (int timeStep = 0; timeStep < numTimeSteps; timeStep++)
    {
    vtkInformation *inInfo =
      inputVector[0]->GetInformationObject(timeStep);
    vtkImageData *input =
      vtkImageData::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));

    // Error checking
    if (input == NULL)
      {
      // Close file, set GDCMFileID to zero
      //this->CloseFile(this->GDCMFileId);
      //this->GDCMFileId = 0;
      vtkErrorMacro(<<"Write: Please specify an input!");
      return 0;
      }

    // Call WriteGDCMData for each input
    if (this->WriteGDCMData(input, timeStep) == 0)
      {
      return 0;
      }
    }

  return 1;
}

//----------------------------------------------------------------------------
int vtkGDCMImageWriter::WriteGDCMData(vtkImageData *data, int timeStep)
{
  assert( timeStep >= 0 );
  data->Update();
  data->Print( std::cout );
  const char * filename = this->GetFileName();
  std::cerr << data->GetDataDimension() <<std::endl;
  gdcm::ImageValue image;
  image.SetNumberOfDimensions( 2 ); // good default
  const int *dims = data->GetDimensions();
  assert( dims[0] >= 0 && dims[1] >= 0 && dims[2] >= 0 );
  image.SetDimension(0, dims[0] );
  image.SetDimension(1, dims[1] );
  if( dims[2] > 1 )
    {
    // resize num of dim to 3:
    image.SetNumberOfDimensions( 3 );
    image.SetDimension(2, dims[2] );
    }
  // For now FileDimensionality should match File Dimension
  //this->FileDimensionality
  int scalarType = data->GetScalarType();
  gdcm::PixelFormat pixeltype = gdcm::PixelFormat::UNKNOWN;
  switch( scalarType )
    {
  case VTK_CHAR:
    pixeltype = gdcm::PixelFormat::INT8; // FIXME ??
    break;
  case VTK_SIGNED_CHAR:
    pixeltype = gdcm::PixelFormat::INT8;
    break;
  case VTK_UNSIGNED_CHAR:
    pixeltype = gdcm::PixelFormat::UINT8;
    break;
  case VTK_SHORT:
    pixeltype = gdcm::PixelFormat::INT16;
    break;
  case VTK_UNSIGNED_SHORT:
    pixeltype = gdcm::PixelFormat::UINT16;
    break;
  default:
    ;
    }

  pixeltype.SetSamplesPerPixel( data->GetNumberOfScalarComponents() );
//  if( image.GetPhotometricInterpretation() == 
//    gdcm::PhotometricInterpretation::PALETTE_COLOR )
//    {
//    assert( this->NumberOfScalarComponents == 1 );
//    this->NumberOfScalarComponents = 3;
//    }
  image.SetPixelFormat( pixeltype );
  unsigned long len = image.GetBufferLength();

  gdcm::ByteValue *bv = new gdcm::ByteValue( (char*)data->GetScalarPointer(), len );
  image.SetValue( *bv );
  gdcm::PhotometricInterpretation pi = gdcm::PhotometricInterpretation::MONOCHROME2;
  image.SetPhotometricInterpretation( pi );
  
  gdcm::ImageWriter writer;
  writer.SetFileName( filename );
  writer.SetImage( image );
  if( !writer.Write() )
    {
    return 0;
    }

  return 1;
}

//----------------------------------------------------------------------------
void vtkGDCMImageWriter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
  //this->Internals->DICOMWriter.Print(os);
}
