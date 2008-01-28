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
// TODO: vtkLookupTable is not taken into account...
//
// NOTE:
// We are not using the usual API SetFilePrefix / SetFilePattern, but instead a list of filenames...

// .SECTION See Also
// vtkImageWriter vtkMedicalImageProperties

#ifndef __vtkGDCMImageWriter_h
#define __vtkGDCMImageWriter_h

#include "vtkImageWriter.h"

class vtkLookupTable;
class vtkMedicalImageProperties;
class vtkStringArray;
class VTK_EXPORT vtkGDCMImageWriter : public vtkImageWriter
{
public:
  static vtkGDCMImageWriter *New();
  vtkTypeRevisionMacro(vtkGDCMImageWriter,vtkImageWriter);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  virtual void SetLookupTable(vtkLookupTable*);
  vtkGetObjectMacro(LookupTable, vtkLookupTable);

  vtkGetObjectMacro(MedicalImageProperties, vtkMedicalImageProperties);
  virtual void SetMedicalImageProperties(vtkMedicalImageProperties*);

  virtual void SetFileNames(vtkStringArray*);
  vtkGetObjectMacro(FileNames, vtkStringArray);

  // I need that...
  virtual void Write();

  // Description:
  // Get the entension for this file format. 
  virtual const char* GetFileExtensions() {
    return ".dcm .DCM"; }

  // Description:
  // Get the name of this file format.
  virtual const char* GetDescriptiveName() {
    return "DICOM"; }

  //virtual void SetDirectionCosines(vtkMatrix4x4 *matrix);
  //vtkGetObjectMacro(DirectionCosines, vtkMatrix4x4);

  //vtkSetMacro(RescaleSlope, double);
  //vtkGetMacro(RescaleSlope, double);
  //vtkSetMacro(RescaleIntercept, double);
  //vtkGetMacro(RescaleIntercept, double);


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

protected:
  virtual /*const*/ char *GetFileName();

private:
  vtkGDCMImageWriter(const vtkGDCMImageWriter&);  // Not implemented.
  void operator=(const vtkGDCMImageWriter&);  // Not implemented.

  // VTK structs:
  vtkLookupTable *LookupTable;
  vtkMedicalImageProperties *MedicalImageProperties;

  int DataUpdateExtent[6];

  vtkStringArray *FileNames;
};

#endif
