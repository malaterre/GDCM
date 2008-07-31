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

//#include "vtkThreadedImageAlgorithm.h"
#include "vtkImageAlgorithm.h"

//class VTK_EXPORT vtkImagePlanarComponentsToComponents : public vtkThreadedImageAlgorithm
class VTK_EXPORT vtkImagePlanarComponentsToComponents : public vtkImageAlgorithm
{
public:
  static vtkImagePlanarComponentsToComponents *New();
  //vtkTypeRevisionMacro(vtkImagePlanarComponentsToComponents,vtkThreadedImageAlgorithm);
  vtkTypeRevisionMacro(vtkImagePlanarComponentsToComponents,vtkImageAlgorithm);

  void PrintSelf(ostream& os, vtkIndent indent);

protected:
  vtkImagePlanarComponentsToComponents();
  ~vtkImagePlanarComponentsToComponents() {};

//  void ThreadedExecute (vtkImageData *inData, vtkImageData *outData,
//                       int ext[6], int id);
//  virtual int RequestInformation (vtkInformation *, vtkInformationVector**, vtkInformationVector *);
  virtual int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkImagePlanarComponentsToComponents(const vtkImagePlanarComponentsToComponents&);  // Not implemented.
  void operator=(const vtkImagePlanarComponentsToComponents&);  // Not implemented.
};

#endif

