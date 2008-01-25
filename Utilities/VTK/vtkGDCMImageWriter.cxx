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

vtkCxxRevisionMacro(vtkGDCMImageWriter, "$Revision: 1.1 $")
vtkStandardNewMacro(vtkGDCMImageWriter)

vtkCxxSetObjectMacro(vtkGDCMImageWriter,LookupTable,vtkLookupTable);
vtkCxxSetObjectMacro(vtkGDCMImageWriter,MedicalImageProperties,vtkMedicalImageProperties);

vtkGDCMImageWriter::vtkGDCMImageWriter()
{
  //this->ScalarArrayName = NULL;
  //this->SetScalarArrayName( "GDCM" );
  this->DataUpdateExtent[0] = 0;
  this->DataUpdateExtent[1] = 0;
  this->DataUpdateExtent[2] = 0;
  this->DataUpdateExtent[3] = 0;
  this->DataUpdateExtent[4] = 0;
  this->DataUpdateExtent[5] = 0;

  this->LookupTable = vtkLookupTable::New();
  this->MedicalImageProperties = vtkMedicalImageProperties::New();
}

vtkGDCMImageWriter::~vtkGDCMImageWriter()
{
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

void vtkGDCMImageWriter::Write()
{
  if (this->GetFileName() == 0)
    {
    vtkErrorMacro("Write: You must supply a file name.");
    return;
    }

  // Get the first input and update its information.
  vtkImageData *input = this->GetImageDataInput(0);

  if (input == 0)
    {
    vtkErrorMacro("Write: No input supplied.");
    return;
    }

  input->UpdateInformation();

  // Update the rest.
  this->UpdateInformation();

  // Get the whole extent of the input
  input->GetWholeExtent(this->DataUpdateExtent);

  int dimIndex = 2;
  int firstSlice = this->DataUpdateExtent[2*dimIndex];
  int lastSlice = this->DataUpdateExtent[2*dimIndex+1];

  // Go through data slice-by-slice using file-order slices
  for (int slice = firstSlice; slice <= lastSlice; slice++)
    {
    // Set the DataUpdateExtent to the slice extent we want to write
    this->DataUpdateExtent[2*dimIndex] = slice;
    this->DataUpdateExtent[2*dimIndex+1] = slice;
    this->Modified();

    // Call Update to execute pipeline and write slice to disk.
    this->Update();

    }

}

void SetStringValueFromTag(const char *s, const gdcm::Tag& t, gdcm::DataSet& ds)
{
  if( s && *s )
    {
    gdcm::DataElement de( t );
    de.SetByteValue( s, strlen( s ) );
    ds.Insert( de );
    }
}


//----------------------------------------------------------------------------
int vtkGDCMImageWriter::WriteGDCMData(vtkImageData *data, int timeStep)
{
  assert( timeStep >= 0 );
  int inWholeExt[6];
  data->GetWholeExtent(inWholeExt);
  int inExt[6];
  data->GetUpdateExtent(inExt);
  vtkIdType inInc[3];
  data->GetIncrements(inInc);

  //data->Update();
  data->Print( std::cout );
  const char * filename = this->GetFileName();
  std::cerr << data->GetDataDimension() <<std::endl;
  gdcm::ImageValue image;
  image.SetNumberOfDimensions( 2 ); // good default
  const int *dims = data->GetDimensions();
  assert( dims[0] >= 0 && dims[1] >= 0 && dims[2] >= 0 );
  image.SetDimension(0, dims[0] );
  image.SetDimension(1, dims[1] );
  const double *spacing = data->GetSpacing();
  image.SetSpacing(0, spacing[0] );
  image.SetSpacing(1, spacing[1] );
  if( dims[2] > 1 )
    {
    // resize num of dim to 3:
    image.SetNumberOfDimensions( 3 );
    image.SetDimension(2, dims[2] );
    image.SetSpacing(2, spacing[2] );
    }
  // TODO: need to do Origin / Image Position (Patient)
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
    abort();
    }

  gdcm::PhotometricInterpretation pi;
  if( data->GetNumberOfScalarComponents() == 1 )
    {
    pi = gdcm::PhotometricInterpretation::MONOCHROME2;
    }
  else if( data->GetNumberOfScalarComponents() == 3 )
    {
    pi = gdcm::PhotometricInterpretation::RGB;
    // (0028,0006) US 0                                        #   2, 1 PlanarConfiguration
    }
  else
    {
    return 0;
    }
  pixeltype.SetSamplesPerPixel( data->GetNumberOfScalarComponents() );
  image.SetPhotometricInterpretation( pi );
  image.SetPixelFormat( pixeltype );
  unsigned long len = image.GetBufferLength();

  gdcm::ByteValue *bv = new gdcm::ByteValue( (char*)data->GetScalarPointer(), len );
  // re shuffle the line within ByteValue:
  //
  char *pointer = (char*)bv->GetPointer();
  const char *tempimage = (char*)data->GetScalarPointer();
  int *dext = data->GetExtent();
  long outsize = pixeltype.GetPixelSize()*(dext[1] - dext[0] + 1);
  for(int j = dext[4]; j <= dext[5]; ++j)
    {
    for(int i = dext[2]; i <= dext[3]; ++i)
      {
      memcpy(pointer,
        tempimage+((dext[3] - i)+j*(dext[3]+1))*outsize, outsize);
      pointer += outsize;
      }
    }

  image.SetValue( *bv );
  //image.Print( std::cerr );

  gdcm::ImageWriter writer;
  writer.SetFileName( filename );
  writer.SetImage( image );

  gdcm::File& file = writer.GetFile();
  gdcm::DataSet& ds = file.GetDataSet();
  // For ex: DICOM (0010,0010) = DOE,JOHN
  SetStringValueFromTag(this->MedicalImageProperties->GetPatientName(), gdcm::Tag(0x0010,0x0010), ds);
  // For ex: DICOM (0010,0020) = 1933197
  SetStringValueFromTag( this->MedicalImageProperties->GetPatientID(), gdcm::Tag(0x0010,0x0020), ds);
  // For ex: DICOM (0010,1010) = 031Y
  SetStringValueFromTag( this->MedicalImageProperties->GetPatientAge(), gdcm::Tag(0x0010,0x1010), ds);
  // For ex: DICOM (0010,0040) = M
  SetStringValueFromTag( this->MedicalImageProperties->GetPatientSex(), gdcm::Tag(0x0010,0x0040), ds);
  // For ex: DICOM (0010,0030) = 19680427
  SetStringValueFromTag( this->MedicalImageProperties->GetPatientBirthDate(), gdcm::Tag(0x0010,0x0030), ds);
  // For ex: DICOM (0008,0022) = 20030617
  SetStringValueFromTag( this->MedicalImageProperties->GetAcquisitionDate(), gdcm::Tag(0x0008,0x0022), ds);
  // For ex: DICOM (0008,0032) = 162552.0705 or 230012, or 0012
  SetStringValueFromTag( this->MedicalImageProperties->GetAcquisitionTime(), gdcm::Tag(0x0008,0x0032), ds);
  // For ex: DICOM (0008,0023) = 20030617
  SetStringValueFromTag( this->MedicalImageProperties->GetImageDate(), gdcm::Tag(0x0008,0x0023), ds);
  // For ex: DICOM (0008,0033) = 162552.0705 or 230012, or 0012
  SetStringValueFromTag( this->MedicalImageProperties->GetImageTime(), gdcm::Tag(0x0008,0x0033), ds);
  // For ex: DICOM (0020,0013) = 1
  SetStringValueFromTag( this->MedicalImageProperties->GetImageNumber(), gdcm::Tag(0x0020,0x0013), ds);
  // For ex: DICOM (0020,0011) = 902
  SetStringValueFromTag( this->MedicalImageProperties->GetSeriesNumber(), gdcm::Tag(0x0020,0x0011), ds);
  // For ex: DICOM (0008,103e) = SCOUT
  SetStringValueFromTag( this->MedicalImageProperties->GetSeriesDescription(), gdcm::Tag(0x0008,0x103e), ds);
  // For ex: DICOM (0020,0010) = 37481
  SetStringValueFromTag( this->MedicalImageProperties->GetStudyID(), gdcm::Tag(0x0020,0x0010), ds);
  // For ex: DICOM (0008,1030) = BRAIN/C-SP/FACIAL
  SetStringValueFromTag( this->MedicalImageProperties->GetStudyDescription(), gdcm::Tag(0x0008,0x1030), ds);
  // For ex: DICOM (0008,0060)= CT
  SetStringValueFromTag( this->MedicalImageProperties->GetModality(), gdcm::Tag(0x0008,0x0060), ds);
  // For ex: DICOM (0008,0070) = Siemens
  SetStringValueFromTag( this->MedicalImageProperties->GetManufacturer(), gdcm::Tag(0x0008,0x0070), ds);
  // For ex: DICOM (0008,1090) = LightSpeed QX/i
  SetStringValueFromTag( this->MedicalImageProperties->GetManufacturerModelName(), gdcm::Tag(0x0008,0x1090), ds);
  // For ex: DICOM (0008,1010) = LSPD_OC8
  SetStringValueFromTag( this->MedicalImageProperties->GetStationName(), gdcm::Tag(0x0008,0x1010), ds);
  // For ex: DICOM (0008,0080) = FooCity Medical Center
  SetStringValueFromTag( this->MedicalImageProperties->GetInstitutionName(), gdcm::Tag(0x0008,0x0080), ds);
  // For ex: DICOM (0018,1210) = Bone
  SetStringValueFromTag( this->MedicalImageProperties->GetConvolutionKernel(), gdcm::Tag(0x0018,0x1210), ds);
  // For ex: DICOM (0018,0050) = 0.273438
  SetStringValueFromTag( this->MedicalImageProperties->GetSliceThickness(), gdcm::Tag(0x0018,0x0050), ds);
  // For ex: DICOM (0018,0060) = 120
  SetStringValueFromTag( this->MedicalImageProperties->GetKVP(), gdcm::Tag(0x0018,0x0060), ds);
  // For ex: DICOM (0018,1120) = 15
  SetStringValueFromTag( this->MedicalImageProperties->GetGantryTilt(), gdcm::Tag(0x0018,0x1120), ds);
  // For ex: DICOM (0018,0081) = 105
  SetStringValueFromTag( this->MedicalImageProperties->GetEchoTime(), gdcm::Tag(0x0018,0x0081), ds);
  // For ex: DICOM (0018,0091) = 35
  SetStringValueFromTag( this->MedicalImageProperties->GetEchoTrainLength(), gdcm::Tag(0x0018,0x0091), ds);
  // For ex: DICOM (0018,0080) = 2040
  SetStringValueFromTag( this->MedicalImageProperties->GetRepetitionTime(), gdcm::Tag(0x0018,0x0080), ds);
  // For ex: DICOM (0018,1150) = 5
  SetStringValueFromTag( this->MedicalImageProperties->GetExposureTime(), gdcm::Tag(0x0018,0x1150), ds);
  // For ex: DICOM (0018,1151) = 400
  SetStringValueFromTag( this->MedicalImageProperties->GetXRayTubeCurrent(), gdcm::Tag(0x0018,0x1151), ds);
  // For ex: DICOM (0018,1152) = 114
  SetStringValueFromTag( this->MedicalImageProperties->GetExposure(), gdcm::Tag(0x0018,0x1152), ds);

  // TODO / FIXME Window Level / Window Center
  // ...
  //
  //
  //
  //
  // Let's try to fake out the SOP Class UID here:
  gdcm::MediaStorage ms = gdcm::MediaStorage::SecondaryCaptureImageStorage;
  ms.GuessFromModality( this->MedicalImageProperties->GetModality() ); // Will override SC only if something is found...
  assert( gdcm::MediaStorage::IsImage( ms ) );
  gdcm::DataElement de( gdcm::Tag(0x0008, 0x0016 ) );
  const char* msstr = gdcm::MediaStorage::GetMSString(ms);
  de.SetByteValue( msstr, strlen(msstr) );
  ds.Insert( de );

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
