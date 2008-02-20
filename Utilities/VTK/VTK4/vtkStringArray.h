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
// .NAME vtkStringArray - 
// .SECTION Description
//
// .SECTION
//
// .SECTION See Also

#ifndef __vtkStringArray_h
#define __vtkStringArray_h

#include "vtkObject.h"

#include <string>

class vtkStringArrayInternals;
class VTK_EXPORT vtkStringArray : public vtkObject
{
public:
  static vtkStringArray *New();
  vtkTypeRevisionMacro(vtkStringArray,vtkObject);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

//BTX
  //std::string &GetValue(unsigned int i);
  vtkIdType InsertNextValue(std::string const & f);
//ETX
  const char *GetValue(unsigned int i);
  int GetNumberOfValues();
  vtkIdType InsertNextValue(const char *f);

  vtkIdType GetSize();

protected:
  vtkStringArray();
  ~vtkStringArray();

private:
  vtkStringArray(const vtkStringArray&);  // Not implemented.
  void operator=(const vtkStringArray&);  // Not implemented.

  vtkStringArrayInternals *Internal;
};

#endif
