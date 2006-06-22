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
#include "vtkImageAppend.h"

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
  //this->FileLowerLeft = 1;
  if( image.GetPlanarConfiguration() )
    {
    int *dims = output->GetDimensions();
    assert( dims[2] );
    unsigned long size = dims[0]*dims[1]*dims[2];
    vtkImageData *red = vtkImageData::New();
    red->SetDimensions( dims );
    red->AllocateScalars();
    char *pred = static_cast<char*>(red->GetScalarPointer());
    memcpy(pred, pointer+0, size );
    vtkImageData *green = vtkImageData::New();
    green->SetDimensions( dims );
    green->AllocateScalars();
    char *pgreen = static_cast<char*>(green->GetScalarPointer());
    memcpy(pgreen, pointer+size, size );
    vtkImageData *blue = vtkImageData::New();
    blue->SetDimensions( dims );
    blue->AllocateScalars();
    char *pblue = static_cast<char*>(blue->GetScalarPointer());
    memcpy(pblue, pointer+2*size, size );

    vtkImageAppend *append = vtkImageAppend::New();
    append->AddInput(red);
    append->AddInput(green);
    append->AddInput(blue);
    append->Update();

    memcpy(pointer, append->GetOutput()->GetScalarPointer(), 3*size);
    red->Delete();
    green->Delete();
    blue->Delete();
    append->Delete();
    }

  return 1;
}

//----------------------------------------------------------------------------
void vtkGDCMReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
  //this->Internals->DICOMReader.Print(os);
}
