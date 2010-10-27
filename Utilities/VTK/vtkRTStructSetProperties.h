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

class vtkRTStructSetPropertiesInternals;

class VTK_IO_EXPORT vtkRTStructSetProperties : public vtkObject
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

  // Description:
  // Copy the contents of p to this instance.
  virtual void DeepCopy(vtkRTStructSetProperties *p);

  void AddReferencedFrameOfReference( const char *classuid , const char * instanceuid );
  const char *GetReferencedFrameOfReferenceClassUID( vtkIdType id );
  const char *GetReferencedFrameOfReferenceInstanceUID( vtkIdType id );
  vtkIdType GetNumberOfReferencedFrameOfReferences();

  void AddStructureSetROI( int roinumber,
    const char* refframerefuid,
    const char* roiname,
    const char* ROIGenerationAlgorithm);
  vtkIdType GetNumberOfStructureSetROIs();
  int GetStructureSetROINumber(vtkIdType id);
  const char *GetStructureSetROIRefFrameRefUID(vtkIdType);
  const char *GetStructureSetROIName(vtkIdType);
  const char *GetStructureSetROIGenerationAlgorithm(vtkIdType);

protected:
  vtkRTStructSetProperties();
  ~vtkRTStructSetProperties();

  char *StructureSetLabel;
  char *StructureSetName;
  char *StructureSetDate;
  char *StructureSetTime;

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
