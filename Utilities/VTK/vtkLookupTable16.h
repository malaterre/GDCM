/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkLookupTable16.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkLookupTable16 - map scalar values into colors via a lookup table
// .SECTION Description
// vtkLookupTable16 is an object that is used by mapper objects to map scalar 
// values into rgba (red-green-blue-alpha transparency) color specification, 
// or rgba into scalar values. The color table can be created by direct 
// insertion of color values, or by specifying  hue, saturation, value, and 
// alpha range and generating a table.
//
// .SECTION Caveats
// You need to explicitely call Build() when constructing the LUT by hand.
//
// .SECTION See Also
// vtkLogLookupTable vtkWindowLevelLookupTable

#ifndef __vtkLookupTable16_h
#define __vtkLookupTable16_h

#include "vtkLookupTable.h"

class VTK_EXPORT vtkLookupTable16 : public vtkLookupTable
{
public:
  // Description:
  // Construct with range=[0,1]; and hsv ranges set up for rainbow color table 
  // (from red to blue).
  static vtkLookupTable16 *New();
  
  vtkTypeRevisionMacro(vtkLookupTable16,vtkLookupTable);
  void PrintSelf(ostream& os, vtkIndent indent);
  
private:
  vtkLookupTable16(const vtkLookupTable16&);  // Not implemented.
  void operator=(const vtkLookupTable16&);  // Not implemented.
};


#endif



