/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkGDCMReader.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkGDCMWriter - write DICOM files
// .SECTION Description
// vtkGDCMWriter is
// bla bla

// .SECTION See Also
// vtkImageWriter vtkMedicalImageProperties

#ifndef __vtkGDCMWriter_h
#define __vtkGDCMWriter_h

#include "vtkImageWriter.h"

struct vtkGDCMWriterInternals;
class vtkLookupTable;
class vtkMedicalImageProperties;
class VTK_EXPORT vtkGDCMWriter : public vtkImageWriter
{
public:
  static vtkGDCMWriter *New();
  vtkTypeRevisionMacro(vtkGDCMWriter,vtkImageWriter);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  virtual void SetLookupTable(vtkLookupTable*);
  vtkGetObjectMacro(LookupTable, vtkLookupTable);

  virtual void SetMedicalImageProperties(vtkMedicalImageProperties*);

protected:
  vtkGDCMWriter();
  ~vtkGDCMWriter();

private:
  vtkGDCMWriter(const vtkGDCMWriter&);  // Not implemented.
  void operator=(const vtkGDCMWriter&);  // Not implemented.

  //PIMPL
  vtkGDCMWriterInternals *Internals;

  // VTK structs:
  vtkLookupTable *LookupTable;
  vtkMedicalImageProperties *MedicalImageProperties;
};

#endif
