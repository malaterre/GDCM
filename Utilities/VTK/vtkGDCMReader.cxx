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

#include "gdcmReader.h"

vtkCxxRevisionMacro(vtkGDCMReader, "$Revision: 1.20 $");
vtkStandardNewMacro(vtkGDCMReader);

using gdcm::Reader;
struct vtkGDCMReaderInternals
{
  Reader DICOMReader;
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
  return this->Superclass::RequestInformation(
    request, inputVector, outputVector);
}

//----------------------------------------------------------------------------
int vtkGDCMReader::RequestData(vtkInformation *vtkNotUsed(request),
                                vtkInformationVector **vtkNotUsed(inputVector),
                                vtkInformationVector *outputVector)
{
  (void)outputVector;
  //char *dest = static_cast<char *>(data->GetScalarPointer());
  //memcpy(dest, Internals->DicomImage.GetPointer(), 2 );

  return 1;
}

//----------------------------------------------------------------------------
void vtkGDCMReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
