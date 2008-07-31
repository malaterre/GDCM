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
#include "vtkObjectFactory.h"

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
  
      const T* r = inIt.BeginSpan();
      const T* g = r + 307200/2;
      const T* b = g + 307200/2;
    T* outSI = outIt.BeginSpan();
  // Loop through ouput pixels
  while (!outIt.IsAtEnd())
    {
      //*outSI = *r;
 ++outSI;
 ++r;
      //*outSI = *g; 
++outSI; 
++g;
      //*outSI = *b;
 ++outSI;
 ++b;
    
//    T* inSI = inIt.BeginSpan();
//    T* outSI = outIt.BeginSpan();
//    T* outSIEnd = outIt.EndSpan();
//    while (outSI != outSIEnd)
//      {
//
//      char *p = dummy_buffer;
//      for (unsigned long j = 0; j < size; ++j)
//        {
//        *(p++) = *(r++);
//        *(p++) = *(g++);
//        *(p++) = *(b++);
//        }

    //  }
    //inIt.NextSpan();
    //outIt.NextSpan();
    }
}

//----------------------------------------------------------------------------
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

//----------------------------------------------------------------------------
void vtkImagePlanarComponentsToComponents::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

