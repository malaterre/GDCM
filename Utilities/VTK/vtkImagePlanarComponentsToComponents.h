/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkImagePlanarComponentsToComponents.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkImagePlanarComponentsToComponents - Converts planar comp to pixel comp
// .SECTION Description

// .SECTION See Also
//

#ifndef __vtkImagePlanarComponentsToComponents_h
#define __vtkImagePlanarComponentsToComponents_h

#include "vtkThreadedImageAlgorithm.h"

class VTK_EXPORT vtkImagePlanarComponentsToComponents : public vtkThreadedImageAlgorithm
{
public:
  static vtkImagePlanarComponentsToComponents *New();
  vtkTypeRevisionMacro(vtkImagePlanarComponentsToComponents,vtkThreadedImageAlgorithm);

  void PrintSelf(ostream& os, vtkIndent indent);

protected:
  vtkImagePlanarComponentsToComponents();
  ~vtkImagePlanarComponentsToComponents() {};

  void ThreadedExecute (vtkImageData *inData, vtkImageData *outData,
                       int ext[6], int id);
private:
  vtkImagePlanarComponentsToComponents(const vtkImagePlanarComponentsToComponents&);  // Not implemented.
  void operator=(const vtkImagePlanarComponentsToComponents&);  // Not implemented.
};

#endif

