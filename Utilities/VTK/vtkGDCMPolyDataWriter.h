/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkGDCMPolyDataWriter - writer DICOM PolyData files (Contour Data...)
// .SECTION Description
// For now only support RTSTRUCT (RT Structure Set Storage)
// .SECTION TODO
// Need to do the same job for DVH Sequence/DVH Data...
// .SECTION Warning
//
// .SECTION See Also
// vtkGDCMImageReader vtkMedicalImageReader2 vtkMedicalImageProperties


#ifndef VTKGDCMPOLYDATAWRITER_H
#define VTKGDCMPOLYDATAWRITER_H

#include "vtkPolyDataWriter.h"

class vtkMedicalImageProperties;
//BTX
namespace gdcm { class Reader; }
//ETX
class VTK_EXPORT vtkGDCMPolyDataWriter : public vtkPolyDataWriter
{
public:
  static vtkGDCMPolyDataWriter *New();
  vtkTypeRevisionMacro(vtkGDCMPolyDataWriter,vtkPolyDataWriter);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set/Get the filename of the file to be read
//  vtkSetStringMacro(FileName);
//  vtkGetStringMacro(FileName);

  // Description:
  // Get the medical image properties object
//  vtkGetObjectMacro(MedicalImageProperties, vtkMedicalImageProperties);

protected:
  vtkGDCMPolyDataWriter();
  ~vtkGDCMPolyDataWriter();

  void WriteData();
  void WriteRTSTRUCT(vtkPoints *pts, vtkCellArray *polys);

private:
  vtkGDCMPolyDataWriter(const vtkGDCMPolyDataWriter&);  // Not implemented.
  void operator=(const vtkGDCMPolyDataWriter&);  // Not implemented.
};

#endif
