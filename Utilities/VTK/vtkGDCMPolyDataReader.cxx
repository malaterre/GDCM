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
#include "vtkGDCMPolyDataReader.h"

#include "vtkObjectFactory.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkPolyData.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkFloatArray.h"

#include "gdcmReader.h"

vtkCxxRevisionMacro(vtkGDCMPolyDataReader, "$Revision: 1.74 $");
vtkStandardNewMacro(vtkGDCMPolyDataReader);

vtkGDCMPolyDataReader::vtkGDCMPolyDataReader()
{
  this->FileName = NULL;
  this->SetNumberOfInputPorts(0);
}

vtkGDCMPolyDataReader::~vtkGDCMPolyDataReader()
{
  this->SetFileName(0);
}

int vtkGDCMPolyDataReader::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *outputVector)
{
  // get the info object
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  // get the ouptut
  vtkPolyData *output = vtkPolyData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));

  FILE *fp;
  vtkPoints *newPts, *mergedPts;
  vtkCellArray *newPolys, *mergedPolys;
  vtkFloatArray *newScalars=0, *mergedScalars=0;

  // All of the data in the first piece.
  if (outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_PIECE_NUMBER()) > 0)
    {
    return 0;
    }

  if (!this->FileName || (this->FileName && (0==strlen(this->FileName))))
    {
    vtkErrorMacro(<<"A FileName must be specified.");
    return 0;
    }

  gdcm::Reader reader;
  reader.SetFileName( this->FileName );
  if( !reader.Read() )
    {
    return 0;
    }

  


  return 1;
}

void vtkGDCMPolyDataReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "File Name: "
     << (this->FileName ? this->FileName : "(none)") << "\n";


}
