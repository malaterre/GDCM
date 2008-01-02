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
// .NAME vtkGDCMReader - read DICOM files
// .SECTION Description
// vtkGDCMReader is a source object that reads some DICOM files
// bla bla

// .SECTION See Also
// vtkMedicalImageReader2 vtkMedicalImageProperties

#ifndef __vtkGDCMReader_h
#define __vtkGDCMReader_h

#include "vtkMedicalImageReader2.h"

//struct vtkGDCMReaderInternals;
namespace gdcm { class ImageReader; }
class VTK_EXPORT vtkGDCMReader : public vtkMedicalImageReader2
{
public:
  static vtkGDCMReader *New();
  vtkTypeRevisionMacro(vtkGDCMReader,vtkMedicalImageReader2);
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

protected:
  vtkGDCMReader();
  ~vtkGDCMReader();

  void FillMedicalImageInformation(const gdcm::ImageReader &reader);
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
  vtkGDCMReader(const vtkGDCMReader&);  // Not implemented.
  void operator=(const vtkGDCMReader&);  // Not implemented.

  //PIMPL
  //vtkGDCMReaderInternals *Internals;
};
#endif

