/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkImageYBRToRGB.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkImageYBRToRGB.h"

#include "vtkImageData.h"
#include "vtkImageProgressIterator.h"
#include "vtkMath.h"
#include "vtkObjectFactory.h"

vtkCxxRevisionMacro(vtkImageYBRToRGB, "$Revision: 1.31 $");
vtkStandardNewMacro(vtkImageYBRToRGB);

//----------------------------------------------------------------------------
vtkImageYBRToRGB::vtkImageYBRToRGB()
{
  this->SetNumberOfInputPorts(1);
  this->SetNumberOfOutputPorts(1);
}


//----------------------------------------------------------------------------
// This templated function executes the filter for any type of data.
template <class T>
void vtkImageYBRToRGBExecute(vtkImageYBRToRGB *self,
                             vtkImageData *inData,
                             vtkImageData *outData,
                             int outExt[6], int id, T *)
{
  vtkImageIterator<T> inIt(inData, outExt);
  vtkImageProgressIterator<T> outIt(outData, outExt, self, id);
  int idxC;
  
  // find the region to loop over
  int maxC = inData->GetNumberOfScalarComponents()-1;
  
  int R, G, B;
  // Loop through ouput pixels
  while (!outIt.IsAtEnd())
    {
    T* inSI = inIt.BeginSpan();
    T* outSI = outIt.BeginSpan();
    T* outSIEnd = outIt.EndSpan();
    while (outSI != outSIEnd)
      {
      // Pixel operation
      unsigned char a = (unsigned char)(*inSI); ++inSI;
      unsigned char b = (unsigned char)(*inSI); ++inSI;
      unsigned char c = (unsigned char)(*inSI); ++inSI;

      R = 38142 *(a-16) + 52298 *(c -128);
      G = 38142 *(a-16) - 26640 *(c -128) - 12845 *(b -128);
      B = 38142 *(a-16) + 66093 *(b -128);

      R = (R+16384)>>15;
      G = (G+16384)>>15;
      B = (B+16384)>>15;

      if (R < 0)   R = 0;
      if (G < 0)   G = 0;
      if (B < 0)   B = 0;
      if (R > 255) R = 255;
      if (G > 255) G = 255;
      if (B > 255) B = 255;

      // assign output.
      *outSI = (T)(R); ++outSI;
      *outSI = (T)(G); ++outSI;
      *outSI = (T)(B); ++outSI;
      
      for (idxC = 3; idxC <= maxC; idxC++)
        {
        *outSI++ = *inSI++;
        }
      }
    inIt.NextSpan();
    outIt.NextSpan();
    }
}

//----------------------------------------------------------------------------
void vtkImageYBRToRGB::ThreadedExecute (vtkImageData *inData, 
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
      vtkImageYBRToRGBExecute(this, inData, 
                              outData, outExt, id, static_cast<VTK_TT *>(0)));
    default:
      vtkErrorMacro(<< "Execute: Unknown ScalarType");
      return;
    }
}

//----------------------------------------------------------------------------
void vtkImageYBRToRGB::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

