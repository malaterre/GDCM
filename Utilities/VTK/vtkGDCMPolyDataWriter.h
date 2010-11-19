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
#include "vtkStdString.h"

class vtkMedicalImageProperties;
class vtkRTStructSetProperties;
//BTX
namespace gdcm { class File; }
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
  // Set/Get the directory containing the CT/MR series from which
  // this RT Struct was derived.
  // If this structure is set, then the vtkRTStructSetProperties
  // object is ignored in favor of the data derived from this CT/MR
  // series.  If you are writing an RT Struct from a 3D volume,
  // then you will need to initialize the rtstruct and use that directly.
  // Only one CT/MR series can be in this directory, and only the first
  // CT, followed by the first MR, series will be used, all others ignored.
  vtkSetStringMacro(DirectoryName);
  vtkGetStringMacro(DirectoryName);

  //if loading from a directory, the struct label and name must be set explicitly
  vtkSetStringMacro(StructLabel);
  vtkGetStringMacro(StructLabel);
  
  vtkSetStringMacro(StructName);
  vtkGetStringMacro(StructName);

  // Description:
  // Get the medical image properties object
//  vtkGetObjectMacro(MedicalImageProperties, vtkMedicalImageProperties);
  virtual void SetMedicalImageProperties(vtkMedicalImageProperties *pd);

  virtual void SetRTStructSetProperties(vtkRTStructSetProperties *pd);

  // make parent class public...
  void SetNumberOfInputPorts(int n);

protected:
  vtkGDCMPolyDataWriter();
  ~vtkGDCMPolyDataWriter();

  vtkMedicalImageProperties *MedicalImageProperties;
  vtkRTStructSetProperties *RTStructSetProperties;
  
  //unbelievable.  Still using char* after all these years.
  char* DirectoryName;
  char* StructLabel;
  char* StructName;

  void WriteData();
//BTX
  void WriteRTSTRUCTInfo(gdcm::File &file);
  void WriteRTSTRUCTData(gdcm::File &file, int num);
//ETX

private:
  vtkGDCMPolyDataWriter(const vtkGDCMPolyDataWriter&);  // Not implemented.
  void operator=(const vtkGDCMPolyDataWriter&);  // Not implemented.
};

#endif
