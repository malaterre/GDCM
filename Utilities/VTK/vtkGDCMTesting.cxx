/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkGDCMTesting.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkGDCMTesting.h"

#include "vtkObjectFactory.h"
#include "vtkToolkits.h"
#include "gdcmTesting.h"

vtkCxxRevisionMacro(vtkGDCMTesting, "$Revision: 1.31 $")
vtkStandardNewMacro(vtkGDCMTesting)

//----------------------------------------------------------------------------
vtkGDCMTesting::vtkGDCMTesting()
{
}

vtkGDCMTesting::~vtkGDCMTesting()
{
}

//----------------------------------------------------------------------------
const char *vtkGDCMTesting::GetVTKDataRoot()
{
#ifdef VTK_DATA_ROOT
  return VTK_DATA_ROOT;
#else
  return NULL;
#endif
}

//----------------------------------------------------------------------------
const char *vtkGDCMTesting::GetGDCMDataRoot()
{
#ifdef GDCM_BUILD_TESTING
  return gdcm::Testing::GetDataRoot();
#else
  return NULL;
#endif
}

//----------------------------------------------------------------------------
void vtkGDCMTesting::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

