/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkGDCMMedicalImageProperties.h"
#include "vtkObjectFactory.h"

//----------------------------------------------------------------------------
vtkCxxRevisionMacro(vtkGDCMMedicalImageProperties, "1.21")
vtkStandardNewMacro(vtkGDCMMedicalImageProperties)

class vtkGDCMMedicalImagePropertiesInternals
{
};

//----------------------------------------------------------------------------
vtkGDCMMedicalImageProperties::vtkGDCMMedicalImageProperties()
{
  this->Internals = new vtkGDCMMedicalImagePropertiesInternals;
}

//----------------------------------------------------------------------------
vtkGDCMMedicalImageProperties::~vtkGDCMMedicalImageProperties()
{
  if (this->Internals)
    {
    delete this->Internals;
    this->Internals = NULL;
    }
  this->Clear();
}

//----------------------------------------------------------------------------
void vtkGDCMMedicalImageProperties::Clear()
{
  this->Superclass::Clear();
}

//----------------------------------------------------------------------------
void vtkGDCMMedicalImageProperties::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

