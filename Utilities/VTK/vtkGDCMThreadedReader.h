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
// .NAME vtkGDCMThreadedReader - read DICOM files
// .SECTION Description
// vtkGDCMThreadedReader is a source object that reads some DICOM files
// bla bla
// .FIXME
// For now I am doing a memcpy, without doing the Y-flip to please VTK !

// .SECTION See Also
// vtkMedicalImageReader2 vtkMedicalImageProperties

#ifndef __vtkGDCMThreadedReader_h
#define __vtkGDCMThreadedReader_h

#include "vtkMedicalImageReader2.h"

//BTX
namespace gdcm { class ImageReader; }
//ETX
class VTK_EXPORT vtkGDCMThreadedReader : public vtkMedicalImageReader2
{
public:
  static vtkGDCMThreadedReader *New();
  vtkTypeRevisionMacro(vtkGDCMThreadedReader,vtkMedicalImageReader2);
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
  vtkGDCMThreadedReader();
  ~vtkGDCMThreadedReader();

  int ProcessRequest(vtkInformation* request,
                                 vtkInformationVector** inputVector,
                                 vtkInformationVector* outputVector);
  int RequestInformation(vtkInformation *request,
                         vtkInformationVector **inputVector,
                         vtkInformationVector *outputVector);
  int RequestData(vtkInformation *request,
                  vtkInformationVector **inputVector,
                  vtkInformationVector *outputVector);

  // FIXME: remove those:
  virtual void ExecuteInformation();
  virtual void ExecuteData(vtkDataObject *out);

  void ReadFiles(unsigned int nfiles, const char *filenames[]);

private:
  vtkGDCMThreadedReader(const vtkGDCMThreadedReader&);  // Not implemented.
  void operator=(const vtkGDCMThreadedReader&);  // Not implemented.
};
#endif

