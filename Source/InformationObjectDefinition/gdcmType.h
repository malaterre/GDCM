/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmType_h
#define __gdcmType_h

#include "gdcmTypes.h"

#include <iostream>

namespace gdcm
{

class GDCM_EXPORT Type
{
public:
  typedef enum {
	  T1 = 0,
	  T1C,
    INVALID
  } TypeType;

  Type(TypeType type = INVALID) : TypeField(type) { }

  operator TypeType () const { return TypeField; }
  friend std::ostream &operator<<(std::ostream &os, const Type &vr);

private:
  TypeType TypeField;
};
//-----------------------------------------------------------------------------
inline std::ostream &operator<<(std::ostream &_os, const Type &val)
{
  //_os << VR::GetVRStringFromFile(val.VRField);
  return _os;
}

} // end namespace gdcm

#endif //__gdcmType_h
