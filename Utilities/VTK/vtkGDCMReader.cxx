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

vtkCxxRevisionMacro(vtkGDCMReader, "$Revision: 1.20 $");
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
}

vtkGDCMReader::~vtkGDCMReader()
{
  delete this->Internals;
}

int vtkGDCMReader::CanReadFile(const char* fname)
{
  this->Internals->DICOMReader.SetFileName( fname );
  if( Internals->DICOMReader.Read() )
    {
    return 0;
    }
  return 3;
}

//----------------------------------------------------------------------------
int vtkGDCMReader::RequestInformation(vtkInformation *request,
                                      vtkInformationVector **inputVector,
                                      vtkInformationVector *outputVector)
{
  this->Internals->DICOMReader.SetFileName( this->FileName );
  if( !Internals->DICOMReader.Read() )
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

  return this->Superclass::RequestInformation(
    request, inputVector, outputVector);
}

//----------------------------------------------------------------------------
int vtkGDCMReader::RequestData(vtkInformation *vtkNotUsed(request),
                                vtkInformationVector **vtkNotUsed(inputVector),
                                vtkInformationVector *outputVector)
{
  (void)outputVector;
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
  image.GetBuffer(pointer);

  return 1;
}

//----------------------------------------------------------------------------
void vtkGDCMReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
  //this->Internals->DICOMReader.Print(os);
}
