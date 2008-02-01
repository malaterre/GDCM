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
// .NAME vtkGDCMImageReader - read DICOM files
// .SECTION Description
// vtkGDCMImageReader is a source object that reads some DICOM files
// this reader is single threaded.
// .SECTION Implementation note: when FileLowerLeft is set to on the image is not flipped
// upside down as VTK would expect, use this option only if you know what you are doing

// .SECTION See Also
// vtkMedicalImageReader2 vtkMedicalImageProperties

#ifndef __vtkGDCMImageReader_h
#define __vtkGDCMImageReader_h

#include "vtkMedicalImageReader2.h"

//BTX
namespace gdcm { class ImageReader; }
//ETX
class vtkMatrix4x4;
class VTK_EXPORT vtkGDCMImageReader : public vtkMedicalImageReader2
{
public:
  static vtkGDCMImageReader *New();
  vtkTypeRevisionMacro(vtkGDCMImageReader,vtkMedicalImageReader2);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description: is the given file name a DICOM file?
  virtual int CanReadFile(const char* fname);

  // Description:
  // Valid extentsions
  virtual const char* GetFileExtensions()
    {
    // I would like to get rid of ACR so only allow dcm extension for now
    return ".dcm .DCM";
    }

  // Description: 
  // A descriptive name for this format
  virtual const char* GetDescriptiveName()
    {
    return "DICOM";
    }

  // Get the Image Position (Patient) as stored in the DICOM file
  // This is a read-only data member
  vtkGetObjectMacro(DirectionCosines, vtkMatrix4x4);

protected:
  vtkGDCMImageReader();
  ~vtkGDCMImageReader();

//BTX
  void FillMedicalImageInformation(const gdcm::ImageReader &reader);
//ETX
  int ProcessRequest(vtkInformation* request,
                                 vtkInformationVector** inputVector,
                                 vtkInformationVector* outputVector);
  int RequestInformation(vtkInformation *request,
                         vtkInformationVector **inputVector,
                         vtkInformationVector *outputVector);
  int RequestData(vtkInformation *request,
                  vtkInformationVector **inputVector,
                  vtkInformationVector *outputVector);

  virtual void ExecuteInformation();
  virtual void ExecuteData(vtkDataObject *out);

private:
  vtkGDCMImageReader(const vtkGDCMImageReader&);  // Not implemented.
  void operator=(const vtkGDCMImageReader&);  // Not implemented.

  vtkMatrix4x4 *DirectionCosines;
};
#endif

