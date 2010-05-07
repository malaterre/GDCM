/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkGDCMTesting.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkGDCMTesting - GDCM Testing
// .SECTION Description
// GDCM Testing

// .SECTION See Also
// vtkTesting

#ifndef VTKGDCMTESTING_H
#define VTKGDCMTESTING_H

#include "vtkObject.h"

class VTK_EXPORT vtkGDCMTesting : public vtkObject
{
public:
  static vtkGDCMTesting *New();
  vtkTypeRevisionMacro(vtkGDCMTesting,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  static const char *GetVTKDataRoot();
  static const char *GetGDCMDataRoot();

protected:
  vtkGDCMTesting();
  ~vtkGDCMTesting();

private:
  vtkGDCMTesting(const vtkGDCMTesting&);  // Not implemented.
  void operator=(const vtkGDCMTesting&);  // Not implemented.
};

#endif

