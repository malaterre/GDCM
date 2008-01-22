/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkGDCMImageWriter - write DICOM files
// .SECTION Description
// vtkGDCMImageWriter is
// bla bla

// .SECTION See Also
// vtkImageWriter vtkMedicalImageProperties

#ifndef __vtkGDCMImageWriter_h
#define __vtkGDCMImageWriter_h

#include "vtkImageWriter.h"

class vtkLookupTable;
class vtkMedicalImageProperties;
class VTK_EXPORT vtkGDCMImageWriter : public vtkImageWriter
{
public:
  static vtkGDCMImageWriter *New();
  vtkTypeRevisionMacro(vtkGDCMImageWriter,vtkImageWriter);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  virtual void SetLookupTable(vtkLookupTable*);
  vtkGetObjectMacro(LookupTable, vtkLookupTable);

  virtual void SetMedicalImageProperties(vtkMedicalImageProperties*);

protected:
  vtkGDCMImageWriter();
  ~vtkGDCMImageWriter();

  int FillInputPortInformation(int port, vtkInformation *info);
  int RequestInformation(
    vtkInformation *request,
    vtkInformationVector **inputVector,
    vtkInformationVector *outputVector);
  int RequestUpdateExtent(
    vtkInformation *request,
    vtkInformationVector **inputVector,
    vtkInformationVector *outputVector);
  int RequestData(
    vtkInformation *request,
    vtkInformationVector **inputVector,
    vtkInformationVector *outputVector);
  int WriteGDCMData(vtkImageData *data, int timeStep);

private:
  vtkGDCMImageWriter(const vtkGDCMImageWriter&);  // Not implemented.
  void operator=(const vtkGDCMImageWriter&);  // Not implemented.

  // VTK structs:
  vtkLookupTable *LookupTable;
  vtkMedicalImageProperties *MedicalImageProperties;

  int DataUpdateExtent[6];
};

#endif
