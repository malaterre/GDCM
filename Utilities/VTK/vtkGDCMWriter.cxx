/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkGDCMWriter.h"

#include "vtkObjectFactory.h"
#include "vtkLookupTable.h"

#if (VTK_MAJOR_VERSION < 5)
#error Your VTK version is too old
#else
#include "vtkMedicalImageProperties.h"
#endif

#include "gdcmImageWriter.h"

struct vtkGDCMWriterInternals
{
  gdcm::ImageWriter DICOMWriter;
};

vtkCxxRevisionMacro(vtkGDCMWriter, "$Revision: 1.1 $")
vtkStandardNewMacro(vtkGDCMWriter)

vtkCxxSetObjectMacro(vtkGDCMWriter,LookupTable,vtkLookupTable);
vtkCxxSetObjectMacro(vtkGDCMWriter,MedicalImageProperties,vtkMedicalImageProperties);

vtkGDCMWriter::vtkGDCMWriter()
{
  this->Internals = new vtkGDCMWriterInternals;
  //this->ScalarArrayName = NULL;
  //this->SetScalarArrayName( "GDCM" );

  this->LookupTable = vtkLookupTable::New();
  this->MedicalImageProperties = vtkMedicalImageProperties::New();
}

vtkGDCMWriter::~vtkGDCMWriter()
{
  delete this->Internals;
  this->LookupTable->Delete();
  this->MedicalImageProperties->Delete();
}

//----------------------------------------------------------------------------
void vtkGDCMWriter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
  //this->Internals->DICOMWriter.Print(os);
}
