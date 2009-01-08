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
// .NAME vtkGDCMImageWriter - write DICOM files
// .SECTION Description
// vtkGDCMImageWriter is a sink object that write DICOM files
// this writer is single threaded
//
// .SECTION FIXME vtkLookupTable is not taken into account...
//
// .SECTION NOTE We are not using the usual API SetFilePrefix / SetFilePattern, 
// but instead a list of filenames: see SetFileNames
// .SECTION Warning
// You need to specify the correct ImageFormat (taken from the reader)
// You need to explicitely specify the DirectionCosines (taken from the reader)
// .SECTION Bug
// You need to set the FileDimensionality to match the dim of your 
// data for now (generating a 2D series out of 3D volume is not 
// currently supported)
// .SECTION NOTE Shift/Scale are global to all DICOM files written for example
// as 2D slice, therefore the shift/scale operation might not be optimized for 
// all slices.
//
// .SECTION See Also
// vtkImageWriter vtkMedicalImageProperties

#ifndef __vtkGDCMImageWriter_h
#define __vtkGDCMImageWriter_h

#include "vtkImageWriter.h"

class vtkLookupTable;
class vtkMedicalImageProperties;
class vtkStringArray;
class vtkMatrix4x4;
class vtkStringArray;
class VTK_EXPORT vtkGDCMImageWriter : public vtkImageWriter
{
public:
  static vtkGDCMImageWriter *New();
  vtkTypeRevisionMacro(vtkGDCMImageWriter,vtkImageWriter);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  //virtual void SetLookupTable(vtkLookupTable*);
  //vtkGetObjectMacro(LookupTable, vtkLookupTable);

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

  // You need to manually specify the direction the image is in to write a valid DICOM file
  // since vtkImageData do not contains one
  virtual void SetDirectionCosines(vtkMatrix4x4 *matrix);
  vtkGetObjectMacro(DirectionCosines, vtkMatrix4x4);

  // Modality LUT
  vtkSetMacro(Shift, double);
  vtkGetMacro(Shift, double);
  vtkSetMacro(Scale, double);
  vtkGetMacro(Scale, double);

  vtkGetMacro(ImageFormat,int);
  vtkSetMacro(ImageFormat,int);

  // Description:
  // Set/Get whether the data comes from the file starting in the lower left
  // corner or upper left corner.
  vtkBooleanMacro(FileLowerLeft, int);
  vtkGetMacro(FileLowerLeft, int);
  vtkSetMacro(FileLowerLeft, int);

  vtkSetMacro(PlanarConfiguration,int);

protected:
  vtkGDCMImageWriter();
  ~vtkGDCMImageWriter();

#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
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
#else
  void WriteSlice(vtkImageData *data);
#endif /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/
  int WriteGDCMData(vtkImageData *data, int timeStep);

protected:
  virtual /*const*/ char *GetFileName();

private:
  vtkGDCMImageWriter(const vtkGDCMImageWriter&);  // Not implemented.
  void operator=(const vtkGDCMImageWriter&);  // Not implemented.

  // VTK structs:
  //vtkLookupTable *LookupTable;
  vtkMedicalImageProperties *MedicalImageProperties;
  vtkSetStringMacro(StudyUID);
  vtkSetStringMacro(SeriesUID);
  char *StudyUID;
  char *SeriesUID;

  int DataUpdateExtent[6];
  int ImageFormat;

  vtkStringArray *FileNames;
  vtkMatrix4x4 *DirectionCosines;

  double Shift;
  double Scale;
  int FileLowerLeft;
  int PlanarConfiguration;
};

#endif
