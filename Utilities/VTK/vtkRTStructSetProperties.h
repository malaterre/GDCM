/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkMedicalImageProperties.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkRTStructSetProperties - some rtstruct properties.
// .SECTION Description
//
// .SECTION See Also
// vtkMedicalImageReader2

#ifndef VTKRTSTRUCTSETPROPERTIES_H
#define VTKRTSTRUCTSETPROPERTIES_H

#include "vtkObject.h"
#include "gdcmDirectory.h"

class vtkRTStructSetPropertiesInternals;
class vtkAppendPolyData; // FIXME

class VTK_EXPORT vtkRTStructSetProperties : public vtkObject
{
public:
  static vtkRTStructSetProperties *New();
  vtkTypeRevisionMacro(vtkRTStructSetProperties,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Convenience method to reset all fields to an emptry string/value
  virtual void Clear();

  // Description:
  //
  vtkSetStringMacro(StructureSetLabel);
  vtkGetStringMacro(StructureSetLabel);

  vtkSetStringMacro(StructureSetName);
  vtkGetStringMacro(StructureSetName);

  vtkSetStringMacro(StructureSetDate);
  vtkGetStringMacro(StructureSetDate);

  vtkSetStringMacro(StructureSetTime);
  vtkGetStringMacro(StructureSetTime);

  vtkSetStringMacro(SOPInstanceUID);
  vtkGetStringMacro(SOPInstanceUID);

  vtkSetStringMacro(StudyInstanceUID);
  vtkGetStringMacro(StudyInstanceUID);

  vtkSetStringMacro(SeriesInstanceUID);
  vtkGetStringMacro(SeriesInstanceUID);

  vtkSetStringMacro(ReferenceSeriesInstanceUID);
  vtkGetStringMacro(ReferenceSeriesInstanceUID);

  vtkSetStringMacro(ReferenceFrameOfReferenceUID);
  vtkGetStringMacro(ReferenceFrameOfReferenceUID);

  // Description:
  // Copy the contents of p to this instance.
  virtual void DeepCopy(vtkRTStructSetProperties *p);

  void AddContourReferencedFrameOfReference( vtkIdType pdnum, const char *classuid , const char * instanceuid );
  const char *GetContourReferencedFrameOfReferenceClassUID( vtkIdType pdnum, vtkIdType id );
  const char *GetContourReferencedFrameOfReferenceInstanceUID( vtkIdType pdnum, vtkIdType id );
  vtkIdType GetNumberOfContourReferencedFrameOfReferences();
  vtkIdType GetNumberOfContourReferencedFrameOfReferences(vtkIdType pdnum);

  void AddReferencedFrameOfReference( const char *classuid , const char * instanceuid );
  const char *GetReferencedFrameOfReferenceClassUID( vtkIdType id );
  const char *GetReferencedFrameOfReferenceInstanceUID( vtkIdType id );
  vtkIdType GetNumberOfReferencedFrameOfReferences();

  void AddStructureSetROI( int roinumber,
    const char* refframerefuid,
    const char* roiname,
    const char* ROIGenerationAlgorithm);
  void AddStructureSetROIObservation( int refnumber,
    int observationnumber,
    const char *rtroiinterpretedtype,
    const char *roiinterpreter);

  vtkIdType GetNumberOfStructureSetROIs();
  int GetStructureSetObservationNumber(vtkIdType id);
  int GetStructureSetROINumber(vtkIdType id);
  const char *GetStructureSetROIRefFrameRefUID(vtkIdType);
  const char *GetStructureSetROIName(vtkIdType);
  const char *GetStructureSetROIGenerationAlgorithm(vtkIdType);
  const char *GetStructureSetRTROIInterpretedType(vtkIdType id);

  //the function LoadCTImageFromFiles gives us a list of images in IPP-sorted order for
  //constructing rt structures
  //(that need both the z position and the appropriate SOP Instance UID for a plane)
  //so, armed with that list of points and the list of images, the first point in
  //each polydata object can be appropriately compiled into the rtstruct
  //we use appendpolydata here-- each polydata is an organ
  //NOTE: the number of outputs for the appendpolydata MUST MATCH the organ vectors!
  // FIXME this function can not be wrap by vtk wrapper...
//BTX
  static vtkRTStructSetProperties* ProduceStructureSetProperties(const std::string& inDirectory,
     const std::string& inStructLabel, const std::string& inStructName,
     vtkAppendPolyData* inPolyData,//should also have colors
     gdcm::Directory::FilenamesType inROINames,
     gdcm::Directory::FilenamesType inROIAlgorithmName,
     gdcm::Directory::FilenamesType inROIType);
//ETX

protected:
  vtkRTStructSetProperties();
  ~vtkRTStructSetProperties();

  char *StructureSetLabel;
  char *StructureSetName;
  char *StructureSetDate;
  char *StructureSetTime;

  char *SOPInstanceUID;
  char *StudyInstanceUID;
  char *SeriesInstanceUID;

  char *ReferenceSeriesInstanceUID;
  char *ReferenceFrameOfReferenceUID;

  // Description:
  // PIMPL Encapsulation for STL containers
  //BTX
  vtkRTStructSetPropertiesInternals *Internals;
  //ETX

private:
  vtkRTStructSetProperties(const vtkRTStructSetProperties&); // Not implemented.
  void operator=(const vtkRTStructSetProperties&); // Not implemented.
};

#endif
