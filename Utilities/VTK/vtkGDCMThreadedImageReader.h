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
// .NAME vtkGDCMThreadedImageReader - read DICOM files with multiple threads
// .SECTION Description
// vtkGDCMThreadedImageReader is a source object that reads some DICOM files
// This reader is threaded. Meaning that on a multiple core CPU with N cpu, it will
// read approx N times faster than when reading in a single thread.
//
// .SECTION Implementation note: when FileLowerLeft is set to on the image is not flipped
// upside down as VTK would expect, use this option only if you know what you are doing
//
// .SECTION FIXME: need to implement the other mode where FileLowerLeft is set to OFF
//
// .SECTION FIXME: you need to call SetFileName when reading a volume file (multiple slices DICOM)
// since SetFileNames expect each single file to be single slice (see parent class)

// .SECTION See Also
// vtkMedicalImageReader2 vtkMedicalImageProperties

#ifndef __vtkGDCMThreadedImageReader_h
#define __vtkGDCMThreadedImageReader_h

#include "vtkGDCMImageReader.h"

class VTK_EXPORT vtkGDCMThreadedImageReader : public vtkGDCMImageReader
{
public:
  static vtkGDCMThreadedImageReader *New();
  vtkTypeRevisionMacro(vtkGDCMThreadedImageReader,vtkGDCMImageReader);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  vtkGetMacro(Shift,double);
  vtkSetMacro(Shift,double);

  vtkGetMacro(Scale,double);
  vtkSetMacro(Scale,double);

protected:
  vtkGDCMThreadedImageReader();
  ~vtkGDCMThreadedImageReader();

#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
  int RequestInformation(vtkInformation *request,
                         vtkInformationVector **inputVector,
                         vtkInformationVector *outputVector);
  int RequestData(vtkInformation *request,
                  vtkInformationVector **inputVector,
                  vtkInformationVector *outputVector);
#else /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/
  void ExecuteInformation();
  void ExecuteData(vtkDataObject *out);
#endif /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/

  void ReadFiles(unsigned int nfiles, const char *filenames[]);

private:
  vtkGDCMThreadedImageReader(const vtkGDCMThreadedImageReader&);  // Not implemented.
  void operator=(const vtkGDCMThreadedImageReader&);  // Not implemented.
  double Shift;
  double Scale;
};
#endif

