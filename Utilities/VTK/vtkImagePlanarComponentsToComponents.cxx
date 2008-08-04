/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkImagePlanarComponentsToComponents.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkImagePlanarComponentsToComponents.h"

#include "vtkImageData.h"
#include "vtkImageProgressIterator.h"
#include "vtkMath.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"

#include <assert.h>

vtkCxxRevisionMacro(vtkImagePlanarComponentsToComponents, "$Revision: 1.31 $")
vtkStandardNewMacro(vtkImagePlanarComponentsToComponents)

//----------------------------------------------------------------------------
vtkImagePlanarComponentsToComponents::vtkImagePlanarComponentsToComponents()
{
  this->SetNumberOfInputPorts(1);
  this->SetNumberOfOutputPorts(1);
}


//----------------------------------------------------------------------------
// This templated function executes the filter for any type of data.
template <class T>
void vtkImagePlanarComponentsToComponentsExecute(vtkImagePlanarComponentsToComponents *self,
                             vtkImageData *inData,
                             vtkImageData *outData,
                             int outExt[6], int id, T *)
{
  vtkImageIterator<T> inIt(inData, outExt);
  vtkImageProgressIterator<T> outIt(outData, outExt, self, id);
  int idxC;

  int maxC = inData->GetNumberOfScalarComponents();
  assert( maxC == 3 );
  
      //const T* r = inIt.BeginSpan();
      //const T* g = r + 307200/2;
      //const T* b = g + 307200/2;
    T* outSI = outIt.BeginSpan();
  // Loop through ouput pixels
    T* inSI = inIt.BeginSpan();
      T *r = (inSI + 0 * 307200); //++inSI;
      T *g = (inSI + 1 * 307200); //++inSI;
      T *b = (inSI + 2 * 307200); //++inSI;
  while (!outIt.IsAtEnd())
    {
    T* outSI = outIt.BeginSpan();
    T* outSIEnd = outIt.EndSpan();
    while (outSI != outSIEnd)
      {
      *outSI = 0; ++outSI;
      ++r;
      *outSI = 0; ++outSI;
      ++g;
      *outSI = 0; ++outSI;
      ++b;
      }
    //inIt.NextSpan();
    outIt.NextSpan();
    }
  //assert( inIt.IsAtEnd() );
     outSI = outIt.BeginSpan();
  memset(outSI, 0, 307200 * 3);
}

//----------------------------------------------------------------------------
/*
void vtkImagePlanarComponentsToComponents::ThreadedExecute (vtkImageData *inData, 
                                       vtkImageData *outData,
                                       int outExt[6], int id)
{
  vtkDebugMacro(<< "Execute: inData = " << inData 
    << ", outData = " << outData);
  
  // this filter expects that input is the same type as output.
  if (inData->GetScalarType() != outData->GetScalarType())
    {
    vtkErrorMacro(<< "Execute: input ScalarType, " << inData->GetScalarType()
    << ", must match out ScalarType " << outData->GetScalarType());
    return;
    }
  if (inData->GetScalarType() != VTK_UNSIGNED_CHAR )
    {
    return;
    }
  
  // need three components for input and output
  if (inData->GetNumberOfScalarComponents() < 3)
    {
    vtkErrorMacro("Input has too few components");
    return;
    }
  if (outData->GetNumberOfScalarComponents() < 3)
    {
    vtkErrorMacro("Output has too few components");
    return;
    }

  switch (inData->GetScalarType())
    {
    vtkTemplateMacro(
      vtkImagePlanarComponentsToComponentsExecute(this, inData, 
                              outData, outExt, id, static_cast<VTK_TT *>(0)));
    default:
      vtkErrorMacro(<< "Execute: Unknown ScalarType");
      return;
    }
}
*/
//
//----------------------------------------------------------------------------
int vtkImagePlanarComponentsToComponents::RequestData(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  char *outPtr;
  int idxX, idxY, idxZ;
  int maxX, maxY, maxZ;
  vtkIdType outIncX, outIncY, outIncZ;
  int *outExt;
  double sum;
  double yContrib, zContrib;
  double temp, temp2;
  unsigned long count = 0;
  unsigned long target;
  //
  // get the input
  vtkInformation* in1Info = inputVector[0]->GetInformationObject(0);
  vtkImageData *inData = vtkImageData::SafeDownCast(
    in1Info->Get(vtkDataObject::DATA_OBJECT()));
 
  vtkInformation *outInfo = outputVector->GetInformationObject(0);  
  vtkImageData *output = vtkImageData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));
  vtkImageData *data = this->AllocateOutputData(output);

  if (data->GetScalarType() != VTK_UNSIGNED_CHAR)
    {
    vtkErrorMacro("Execute: This source only outputs doubles");
    }
  
  outExt = data->GetExtent();
  
  // find the region to loop over
  maxX = outExt[1] - outExt[0];
  maxY = outExt[3] - outExt[2]; 
  maxZ = outExt[5] - outExt[4];
  
  // Get increments to march through data 
  data->GetContinuousIncrements(outExt, outIncX, outIncY, outIncZ);
  const char *inPtr = (char*)inData->GetScalarPointer(outExt[0],outExt[2],outExt[4]);
  outPtr = static_cast<char*>(data->GetScalarPointer(outExt[0],outExt[2],outExt[4]));
  
  target = static_cast<unsigned long>((maxZ+1)*(maxY+1)/50.0);
  target++;

  // Loop through ouput pixels

  unsigned long size = (maxX+1) * (maxY+1) * (maxZ+1);
  const char *r = inPtr;
  const char *g = inPtr + size;
  const char *b = inPtr + size + size;

  char *p = outPtr;
  for (unsigned long j = 0; j < size && !this->AbortExecute; ++j)
    {
    //this->UpdateProgress(count/(50.0*target));
    *(p++) = *(r++);
    *(p++) = *(g++);
    *(p++) = *(b++);
    }

  return 1;
}

//----------------------------------------------------------------------------
void vtkImagePlanarComponentsToComponents::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

