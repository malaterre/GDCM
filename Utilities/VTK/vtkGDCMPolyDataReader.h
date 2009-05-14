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
// .NAME vtkGDCMPolyDataReader - read DICOM PolyData files (Contour Data...)
// .SECTION Description
// For now only support RTSTRUCT (RTStructureSetStorage)
// See Contour Data
// .SECTION TODO
// Need to do the same job for DVH Sequence/DVH Data...
//
// .SECTION See Also
// vtkMedicalImageReader2 vtkMedicalImageProperties vtkGDCMImageReader


#ifndef __vtkGDCMPolyDataReader_h
#define __vtkGDCMPolyDataReader_h

#include "vtkPolyDataAlgorithm.h"
#include "gdcmTypes.h" // GDCM_EXPORT

class vtkMedicalImageProperties;
//BTX
namespace gdcm { class Reader; }
//ETX
class GDCM_EXPORT vtkGDCMPolyDataReader : public vtkPolyDataAlgorithm
{
public:
  static vtkGDCMPolyDataReader *New();
  vtkTypeRevisionMacro(vtkGDCMPolyDataReader,vtkPolyDataAlgorithm);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set/Get the filename of the file to be read
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  // Description:
  // Get the medical image properties object
  vtkGetObjectMacro(MedicalImageProperties, vtkMedicalImageProperties);

protected:
  vtkGDCMPolyDataReader();
  ~vtkGDCMPolyDataReader();

  char *FileName;
  vtkMedicalImageProperties *MedicalImageProperties;
//BTX
  void FillMedicalImageInformation(const gdcm::Reader &reader);
//ETX

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  int RequestInformation(
    vtkInformation *vtkNotUsed(request),
    vtkInformationVector **vtkNotUsed(inputVector),
    vtkInformationVector *outputVector);
//BTX
  int RequestInformation_RTStructureSetStorage(gdcm::Reader const & reader);
  int RequestData_RTStructureSetStorage(gdcm::Reader const &reader, vtkInformationVector *outputVector);
  int RequestInformation_HemodynamicWaveformStorage(gdcm::Reader const & reader);
  int RequestData_HemodynamicWaveformStorage(gdcm::Reader const &reader, vtkInformationVector *outputVector);
//ETX

private:
  vtkGDCMPolyDataReader(const vtkGDCMPolyDataReader&);  // Not implemented.
  void operator=(const vtkGDCMPolyDataReader&);  // Not implemented.
};

#endif
