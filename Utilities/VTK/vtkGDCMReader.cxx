/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkGDCMReader.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkGDCMReader.h"

#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"

#include "gdcmImageReader.h"
#include <sstream>

vtkCxxRevisionMacro(vtkGDCMReader, "$Revision: 1.1 $");
vtkStandardNewMacro(vtkGDCMReader);

struct vtkGDCMReaderInternals
{
  gdcm::ImageReader DICOMReader;
};

vtkGDCMReader::vtkGDCMReader()
{
  this->Internals = new vtkGDCMReaderInternals;
  //this->ScalarArrayName = NULL;
  //this->SetScalarArrayName( "GDCM" );

  // vtkDataArray has an internal vtkLookupTable why not used it ?
  // vtkMedicalImageProperties is in the parent class
  //this->FileLowerLeft = 1;
}

vtkGDCMReader::~vtkGDCMReader()
{
  delete this->Internals;
}

int vtkGDCMReader::CanReadFile(const char* fname)
{
  this->Internals->DICOMReader.SetFileName( fname );
  if( this->Internals->DICOMReader.Read() )
    {
    return 0;
    }
  return 3;
}

//
void vtkGDCMReader::FillMedicalImageInformation()
{
  // For now only do:
  // PatientName, PatientID, PatientAge, PatientSex, PatientBirthDate,
  // StudyID
  std::ostringstream str;
  const gdcm::DataSet &ds = this->Internals->DICOMReader.GetDataSet();
  const gdcm::Tag patname(0x0010, 0x0010);
  if( ds.FindDataElement( patname ) )
    {
    const gdcm::DataElement& de = ds.GetDataElement( patname );
    }

/*
    {
    if (medprop->GetPatientName())
      {
      str.str("");
      str << medprop->GetPatientName();
      file->InsertValEntry(str.str(),0x0010,0x0010); // PN 1 Patient's Name
      }

    if (medprop->GetPatientID())
      {
      str.str("");
      str << medprop->GetPatientID();
      file->InsertValEntry(str.str(),0x0010,0x0020); // LO 1 Patient ID
      }

    if (medprop->GetPatientAge())
      {
      str.str("");
      str << medprop->GetPatientAge();
      file->InsertValEntry(str.str(),0x0010,0x1010); // AS 1 Patient's Age
      }

    if (medprop->GetPatientSex())
      {
      str.str("");
      str << medprop->GetPatientSex();
      file->InsertValEntry(str.str(),0x0010,0x0040); // CS 1 Patient's Sex
      }

    if (medprop->GetPatientBirthDate())
      {
      str.str("");
      str << medprop->GetPatientBirthDate();
      file->InsertValEntry(str.str(),0x0010,0x0030); // DA 1 Patient's Birth Date
      }

    if (medprop->GetStudyID())
      {
      str.str("");
      str << medprop->GetStudyID();
      file->InsertValEntry(str.str(),0x0020,0x0010); // SH 1 Study ID
      }
    }*/
}

//----------------------------------------------------------------------------
int vtkGDCMReader::RequestInformation(vtkInformation *request,
                                      vtkInformationVector **inputVector,
                                      vtkInformationVector *outputVector)
{
  this->Internals->DICOMReader.SetFileName( this->FileName );
  if( !this->Internals->DICOMReader.Read() )
    {
    return 0;
    }
  const gdcm::Image &image = this->Internals->DICOMReader.GetImage();
  const unsigned int *dims = image.GetDimensions();

  // Set the Extents.
  assert( image.GetNumberOfDimensions() >= 2 );
  this->DataExtent[0] = 0;
  this->DataExtent[1] = dims[0] - 1;
  this->DataExtent[2] = 0;
  this->DataExtent[3] = dims[1] - 1;
  if( image.GetNumberOfDimensions() == 2 )
    {
    this->DataExtent[4] = 0;
    this->DataExtent[5] = 0;
    }
  else
    {
    this->DataExtent[4] = 0;
    this->DataExtent[5] = dims[2] - 1;
    }
  //this->DataSpacing[0] = 1.;
  //this->DataSpacing[1] = -1.;
  //this->DataSpacing[2] = 1.;

  gdcm::PixelType pixeltype = image.GetPixelType();
  switch( pixeltype )
    {
  case gdcm::PixelType::INT8:
    this->DataScalarType = VTK_SIGNED_CHAR;
    break;
  case gdcm::PixelType::UINT8:
    this->DataScalarType = VTK_UNSIGNED_CHAR;
    break;
  case gdcm::PixelType::INT12:
    abort();
    this->DataScalarType = VTK_SHORT;
    break;
  case gdcm::PixelType::UINT12:
    abort();
    this->DataScalarType = VTK_UNSIGNED_SHORT;
    break;
  case gdcm::PixelType::INT16:
    this->DataScalarType = VTK_SHORT;
    break;
  case gdcm::PixelType::UINT16:
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

//  this->FileLowerLeftOn();

  return this->Superclass::RequestInformation(
    request, inputVector, outputVector);
}

//----------------------------------------------------------------------------
int vtkGDCMReader::RequestData(vtkInformation *vtkNotUsed(request),
                                vtkInformationVector **vtkNotUsed(inputVector),
                                vtkInformationVector *outputVector)
{
  const gdcm::Image &image = this->Internals->DICOMReader.GetImage();

  //this->UpdateProgress(0.2);

  // Make sure the output dimension is OK, and allocate its scalars

  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkImageData *output = vtkImageData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));
  int *dext = this->GetDataExtent();
  output->SetDimensions(
    dext[1] - dext[0] + 1, dext[3] - dext[2] + 1, dext[5] - dext[4] + 1);
  output->AllocateScalars();

  char * pointer = static_cast<char*>(output->GetScalarPointer());
  unsigned long len = image.GetBufferLength();
  char *tempimage = new char[len];
  image.GetBuffer(tempimage);

  const unsigned int *dims = image.GetDimensions();
  gdcm::PixelType pixeltype = image.GetPixelType();
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
        tempimage+((this->DataExtent[3] - i)+j*(dext[3]+1))*outsize, outsize);
      pointer += outsize;
      }
  }
  delete[] tempimage;

  return 1;
}

//----------------------------------------------------------------------------
void vtkGDCMReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
  //this->Internals->DICOMReader.Print(os);
}
