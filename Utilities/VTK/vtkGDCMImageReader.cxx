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

#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDemandDrivenPipeline.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkMedicalImageProperties.h"
#include "vtkStringArray.h"

#include "gdcmImageReader.h"
#include "gdcmDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmSwapper.h"

#include <sstream>

vtkCxxRevisionMacro(vtkGDCMImageReader, "$Revision: 1.1 $");
vtkStandardNewMacro(vtkGDCMImageReader);

//struct vtkGDCMImageReaderInternals
//{
//  gdcm::ImageReader DICOMReader;
//};

vtkGDCMImageReader::vtkGDCMImageReader()
{
  //this->Internals = new vtkGDCMImageReaderInternals;
  //this->ScalarArrayName = NULL;
  //this->SetScalarArrayName( "GDCM" );

  // vtkDataArray has an internal vtkLookupTable why not used it ?
  // vtkMedicalImageProperties is in the parent class
  //this->FileLowerLeft = 1;
}

vtkGDCMImageReader::~vtkGDCMImageReader()
{
  //delete this->Internals;
}

void vtkGDCMImageReader::ExecuteInformation()
{
  std::cerr << "ExecuteInformation" << std::endl;
}

void vtkGDCMImageReader::ExecuteData(vtkDataObject *output)
{
  std::cerr << "ExecuteData" << std::endl;
}

int vtkGDCMImageReader::CanReadFile(const char* fname)
{
  gdcm::ImageReader reader;
  reader.SetFileName( fname );
  if( reader.Read() )
    {
    return 0;
    }
  return 3;
}

//----------------------------------------------------------------------------
int vtkGDCMImageReader::ProcessRequest(vtkInformation* request,
                                 vtkInformationVector** inputVector,
                                 vtkInformationVector* outputVector)
{
  // generate the data
  if(request->Has(vtkDemandDrivenPipeline::REQUEST_DATA()))
    {
    return this->RequestData(request, inputVector, outputVector);
    }

  // execute information
  if(request->Has(vtkDemandDrivenPipeline::REQUEST_INFORMATION()))
    {
    return this->RequestInformation(request, inputVector, outputVector);
    }

  return this->Superclass::ProcessRequest(request, inputVector, outputVector);
}


const char *GetStringValueFromTag(const gdcm::Tag& t, const gdcm::DataSet& ds)
{
  static std::string buffer;
  buffer = "";  // cleanup previous call

  if( ds.FindDataElement( t ) )
    {
    const gdcm::DataElement& de = ds.GetDataElement( t );
    const gdcm::ByteValue *bv = de.GetByteValue();
    if( bv ) // Can be Type 2
      {
      buffer = std::string( bv->GetPointer(), bv->GetLength() );
      // Will be padded with at least on \0
      }
    }

  // Since return is a const char* the very first \0 will be considered
  return buffer.c_str();
}

//
void vtkGDCMImageReader::FillMedicalImageInformation(const gdcm::ImageReader &reader)
{
  const gdcm::File &file = reader.GetFile();
  const gdcm::DataSet &ds = file.GetDataSet();

  // $ grep "vtkSetString\|DICOM" vtkMedicalImageProperties.h 
  // For ex: DICOM (0010,0010) = DOE,JOHN
  this->MedicalImageProperties->SetPatientName( GetStringValueFromTag( gdcm::Tag(0x0010,0x0010), ds) );
  // For ex: DICOM (0010,0020) = 1933197
  this->MedicalImageProperties->SetPatientID( GetStringValueFromTag( gdcm::Tag(0x0010,0x0020), ds) );
  // For ex: DICOM (0010,1010) = 031Y
  this->MedicalImageProperties->SetPatientAge( GetStringValueFromTag( gdcm::Tag(0x0010,0x1010), ds) );
  // For ex: DICOM (0010,0040) = M
  this->MedicalImageProperties->SetPatientSex( GetStringValueFromTag( gdcm::Tag(0x0010,0x0040), ds) );
  // For ex: DICOM (0010,0030) = 19680427
  this->MedicalImageProperties->SetPatientBirthDate( GetStringValueFromTag( gdcm::Tag(0x0010,0x0030), ds) );
  // For ex: DICOM (0008,0022) = 20030617
  this->MedicalImageProperties->SetAcquisitionDate( GetStringValueFromTag( gdcm::Tag(0x0008,0x0022), ds) );
  // For ex: DICOM (0008,0032) = 162552.0705 or 230012, or 0012
  this->MedicalImageProperties->SetAcquisitionTime( GetStringValueFromTag( gdcm::Tag(0x0008,0x0032), ds) );
  // For ex: DICOM (0008,0023) = 20030617
  this->MedicalImageProperties->SetImageDate( GetStringValueFromTag( gdcm::Tag(0x0008,0x0023), ds) );
  // For ex: DICOM (0008,0033) = 162552.0705 or 230012, or 0012
  this->MedicalImageProperties->SetImageTime( GetStringValueFromTag( gdcm::Tag(0x0008,0x0033), ds) );
  // For ex: DICOM (0020,0013) = 1
  this->MedicalImageProperties->SetImageNumber( GetStringValueFromTag( gdcm::Tag(0x0020,0x0013), ds) );
  // For ex: DICOM (0020,0011) = 902
  this->MedicalImageProperties->SetSeriesNumber( GetStringValueFromTag( gdcm::Tag(0x0020,0x0011), ds) );
  // For ex: DICOM (0008,103e) = SCOUT
  this->MedicalImageProperties->SetSeriesDescription( GetStringValueFromTag( gdcm::Tag(0x0008,0x103e), ds) );
  // For ex: DICOM (0020,0010) = 37481
  this->MedicalImageProperties->SetStudyID( GetStringValueFromTag( gdcm::Tag(0x0020,0x0010), ds) );
  // For ex: DICOM (0008,1030) = BRAIN/C-SP/FACIAL
  this->MedicalImageProperties->SetStudyDescription( GetStringValueFromTag( gdcm::Tag(0x0008,0x1030), ds) );
  // For ex: DICOM (0008,0060)= CT
  this->MedicalImageProperties->SetModality( GetStringValueFromTag( gdcm::Tag(0x0008,0x0060), ds) );
  // For ex: DICOM (0008,0070) = Siemens
  this->MedicalImageProperties->SetManufacturer( GetStringValueFromTag( gdcm::Tag(0x0008,0x0070), ds) );
  // For ex: DICOM (0008,1090) = LightSpeed QX/i
  this->MedicalImageProperties->SetManufacturerModelName( GetStringValueFromTag( gdcm::Tag(0x0008,0x1090), ds) );
  // For ex: DICOM (0008,1010) = LSPD_OC8
  this->MedicalImageProperties->SetStationName( GetStringValueFromTag( gdcm::Tag(0x0008,0x1010), ds) );
  // For ex: DICOM (0008,0080) = FooCity Medical Center
  this->MedicalImageProperties->SetInstitutionName( GetStringValueFromTag( gdcm::Tag(0x0008,0x0080), ds) );
  // For ex: DICOM (0018,1210) = Bone
  this->MedicalImageProperties->SetConvolutionKernel( GetStringValueFromTag( gdcm::Tag(0x0018,0x1210), ds) );
  // For ex: DICOM (0018,0050) = 0.273438
  this->MedicalImageProperties->SetSliceThickness( GetStringValueFromTag( gdcm::Tag(0x0018,0x0050), ds) );
  // For ex: DICOM (0018,0060) = 120
  this->MedicalImageProperties->SetKVP( GetStringValueFromTag( gdcm::Tag(0x0018,0x0060), ds) );
  // For ex: DICOM (0018,1120) = 15
  this->MedicalImageProperties->SetGantryTilt( GetStringValueFromTag( gdcm::Tag(0x0018,0x1120), ds) );
  // For ex: DICOM (0018,0081) = 105
  this->MedicalImageProperties->SetEchoTime( GetStringValueFromTag( gdcm::Tag(0x0018,0x0081), ds) );
  // For ex: DICOM (0018,0091) = 35
  this->MedicalImageProperties->SetEchoTrainLength( GetStringValueFromTag( gdcm::Tag(0x0018,0x0091), ds) );
  // For ex: DICOM (0018,0080) = 2040
  this->MedicalImageProperties->SetRepetitionTime( GetStringValueFromTag( gdcm::Tag(0x0018,0x0080), ds) );
  // For ex: DICOM (0018,1150) = 5
  this->MedicalImageProperties->SetExposureTime( GetStringValueFromTag( gdcm::Tag(0x0018,0x1150), ds) );
  // For ex: DICOM (0018,1151) = 400
  this->MedicalImageProperties->SetXRayTubeCurrent( GetStringValueFromTag( gdcm::Tag(0x0018,0x1151), ds) );
  // For ex: DICOM (0018,1152) = 114
  this->MedicalImageProperties->SetExposure( GetStringValueFromTag( gdcm::Tag(0x0018,0x1152), ds) );

  // TODO
  // virtual void AddWindowLevelPreset(double w, double l);
  // (0028,1050) DS [   498\  498]                           #  12, 2 WindowCenter
  // (0028,1051) DS [  1063\ 1063]                           #  12, 2 WindowWidth
  gdcm::Tag twindowcenter(0x0028,0x1050);
  gdcm::Tag twindowwidth(0x0028,0x1051);
  if( ds.FindDataElement( twindowcenter ) && ds.FindDataElement( twindowwidth) )
    {
    const gdcm::DataElement& windowcenter = ds.GetDataElement( twindowcenter );
    const gdcm::DataElement& windowwidth = ds.GetDataElement( twindowwidth );
    const gdcm::ByteValue *bvwc = windowcenter.GetByteValue();
    const gdcm::ByteValue *bvww = windowwidth.GetByteValue();
    if( bvwc && bvww ) // Can be Type 2
      {
      //gdcm::Attributes<0x0028,0x1050> at;
      gdcm::Element<gdcm::VR::DS,gdcm::VM::VM1_n> elwc;
      std::stringstream ss;
      bvwc->Write<gdcm::SwapperNoOp>( ss );
      //elwc.Read( ss );
      ss.str( "" );
      gdcm::Element<gdcm::VR::DS,gdcm::VM::VM1_n> elww;
      bvww->Write<gdcm::SwapperNoOp>( ss );
      //elww.Read( ss );
      // assert( elww.GetLength() == elwc.GetLength() );
      for(unsigned int i = 0; i < elwc.GetLength(); ++i)
        {
        this->MedicalImageProperties->AddWindowLevelPreset( elww.GetValue(i), elwc.GetValue(i) );
        }
      }
    }

}

//----------------------------------------------------------------------------
int vtkGDCMImageReader::RequestInformation(vtkInformation *request,
                                      vtkInformationVector **inputVector,
                                      vtkInformationVector *outputVector)
{
  // Let's read the first file :
  const char *filename;
  if( this->FileName )
    {
    filename = this->FileName;
    }
  else
    {
    assert( this->FileNames && this->FileNames->GetNumberOfValues() >= 1 );
    filename = this->FileNames->GetValue( 0 ).c_str();
    }
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
  this->DataExtent[0] = 0;
  this->DataExtent[1] = dims[0] - 1;
  this->DataExtent[2] = 0;
  this->DataExtent[3] = dims[1] - 1;
  if( image.GetNumberOfDimensions() == 2 )
    {
    // This is just so much painfull to deal with DICOM / VTK
    // they simply assume that number of file is equal to the dimension
    // of the last axe (see vtkImageReader2::SetFileNames )
    if ( this->FileNames && this->FileNames->GetNumberOfValues() > 1 )
      {
      this->DataExtent[4] = 0;
      //this->DataExtent[5] = this->FileNames->GetNumberOfValues() - 1;
      }
    else
      {
      this->DataExtent[4] = 0;
      this->DataExtent[5] = 0;
      }
    }
  else
    {
    assert( image.GetNumberOfDimensions() == 3 );
    this->FileDimensionality = 3;
    this->DataExtent[4] = 0;
    this->DataExtent[5] = dims[2] - 1;
    }
  const double *spacing = image.GetSpacing();
  this->DataSpacing[0] = spacing[0];
  this->DataSpacing[1] = spacing[1];
  //this->DataSpacing[2] = 1.;

  gdcm::PixelFormat pixeltype = image.GetPixelFormat();
  switch( pixeltype )
    {
  case gdcm::PixelFormat::INT8:
    this->DataScalarType = VTK_SIGNED_CHAR;
    break;
  case gdcm::PixelFormat::UINT8:
    this->DataScalarType = VTK_UNSIGNED_CHAR;
    break;
  case gdcm::PixelFormat::INT12:
    abort();
    this->DataScalarType = VTK_SHORT;
    break;
  case gdcm::PixelFormat::UINT12:
    abort();
    this->DataScalarType = VTK_UNSIGNED_SHORT;
    break;
  case gdcm::PixelFormat::INT16:
    this->DataScalarType = VTK_SHORT;
    break;
  case gdcm::PixelFormat::UINT16:
    this->DataScalarType = VTK_UNSIGNED_SHORT;
    break;
  default:
    ;
    }

  this->NumberOfScalarComponents = pixeltype.GetSamplesPerPixel();
  if( image.GetPhotometricInterpretation() == 
    gdcm::PhotometricInterpretation::PALETTE_COLOR )
    {
    assert( this->NumberOfScalarComponents == 1 );
    this->NumberOfScalarComponents = 3;
    }

  int numvol = 1;
  this->SetNumberOfOutputPorts(numvol);
  // For each output:
  for(int i = 0; i < numvol; ++i)
    {
    // Allocate !
    if( !this->GetOutput(i) )
      {
      vtkImageData *img = vtkImageData::New();
      this->GetExecutive()->SetOutputData(i, img );
      img->Delete();
      }
    vtkInformation *outInfo = outputVector->GetInformationObject(i);
    outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), this->DataExtent, 6);
    //outInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), this->DataExtent, 6);

    outInfo->Set(vtkDataObject::SPACING(), this->DataSpacing, 3);
    outInfo->Set(vtkDataObject::ORIGIN(), this->DataOrigin, 3);
    vtkDataObject::SetPointDataActiveScalarInfo(outInfo, this->DataScalarType, this->NumberOfScalarComponents);
    }

  // Ok let's fill in the 'extra' info:
  FillMedicalImageInformation(reader);

//  return this->Superclass::RequestInformation(
//    request, inputVector, outputVector);
  return 1;
}

int LoadSingleFile(const char *filename, int *dext, char *pointer)
{
  gdcm::ImageReader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    return 0;
    }

  const gdcm::Image &image = reader.GetImage();
  unsigned long len = image.GetBufferLength();
  char *tempimage = new char[len];
  image.GetBuffer(tempimage);

  const unsigned int *dims = image.GetDimensions();
  gdcm::PixelFormat pixeltype = image.GetPixelFormat();
  long outsize = pixeltype.GetPixelSize()*(dext[1] - dext[0] + 1);
  //std::cerr << "dext: " << dext[2] << " " << dext[3] << std::endl;
  //std::cerr << "dext: " << dext[4] << " " << dext[5] << std::endl;
  //memcpy(pointer, tempimage, len);
  for(int j = dext[4]; j <= dext[5]; ++j)
  {
    //std::cerr << j << std::endl;
    for(int i = dext[2]; i <= dext[3]; ++i)
      {
      //memcpy(pointer, tempimage+i*outsize, outsize);
      //memcpy(pointer, tempimage+(this->DataExtent[3] - i)*outsize, outsize);
      //memcpy(pointer, tempimage+(i+j*(dext[3]+1))*outsize, outsize);
      memcpy(pointer,
        tempimage+((dext[3] - i)+j*(dext[3]+1))*outsize, outsize);
      pointer += outsize;
      }
  }
  delete[] tempimage;

  return 1; // success
}

//----------------------------------------------------------------------------
int vtkGDCMImageReader::RequestData(vtkInformation *vtkNotUsed(request),
                                vtkInformationVector **vtkNotUsed(inputVector),
                                vtkInformationVector *outputVector)
{

  //this->UpdateProgress(0.2);

  // Make sure the output dimension is OK, and allocate its scalars

  for(int i = 0; i < this->GetNumberOfOutputPorts(); ++i)
  {
  // Copy/paste from vtkImageAlgorithm::AllocateScalars. Cf. "this needs to be fixed -Ken"
    vtkStreamingDemandDrivenPipeline *sddp = 
      vtkStreamingDemandDrivenPipeline::SafeDownCast(this->GetExecutive());
    if (sddp)
      {
      int extent[6];
      sddp->GetOutputInformation(i)->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),extent);
      this->GetOutput(i)->SetExtent(extent);
      }
    this->GetOutput(i)->AllocateScalars();
  }


//  vtkInformation *outInfo = outputVector->GetInformationObject(0);
//  vtkImageData *output = vtkImageData::SafeDownCast(
//    outInfo->Get(vtkDataObject::DATA_OBJECT()));
  int *dext = this->GetDataExtent();
//  output->SetDimensions(
//    dext[1] - dext[0] + 1, dext[3] - dext[2] + 1, dext[5] - dext[4] + 1);
//  output->AllocateScalars();

  vtkImageData *output = this->GetOutput(0);
  char * pointer = static_cast<char*>(output->GetScalarPointer());
  if( this->FileName )
    {
    const char *filename = this->FileName;
    LoadSingleFile( filename, dext, pointer );
    return 1;
    }
  else
    {
    assert( this->FileNames && this->FileNames->GetNumberOfValues() >= 1 );
    }

  // Load each 2D files
  for(int j = dext[4]; j <= dext[5]; ++j)
    {
    gdcm::ImageReader reader;
    const char *filename;
    filename = this->FileNames->GetValue( j ).c_str();
    //std::cerr << "Reader:" << j << " -> " << filename << std::endl;
    reader.SetFileName( filename );
    if( !reader.Read() )
      {
      // TODO need to do some cleanup...
      return 0;
      }

    const gdcm::Image &image = reader.GetImage();
    unsigned long len = image.GetBufferLength();
    char *tempimage = new char[len];
    image.GetBuffer(tempimage);

    const unsigned int *dims = image.GetDimensions();
    gdcm::PixelFormat pixeltype = image.GetPixelFormat();
    long outsize = pixeltype.GetPixelSize()*(dext[1] - dext[0] + 1);
    //std::cerr << "dext: " << dext[2] << " " << dext[3] << std::endl;
    //std::cerr << "dext: " << dext[4] << " " << dext[5] << std::endl;
#if 0
    memcpy(pointer, tempimage, len);
    pointer += len;
#else
    //std::cerr << j << std::endl;
    for(int i = dext[2]; i <= dext[3]; ++i)
      {
      //memcpy(pointer, tempimage+i*outsize, outsize);
      //memcpy(pointer, tempimage+(this->DataExtent[3] - i)*outsize, outsize);
      //memcpy(pointer, tempimage+(i+j*(dext[3]+1))*outsize, outsize);
      memcpy(pointer,
        tempimage+((dext[3] - i)+j*(dext[3]+1))*outsize, outsize);
      pointer += outsize;
      }
#endif
    delete[] tempimage;
    }

  return 1;
}

//----------------------------------------------------------------------------
void vtkGDCMImageReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

