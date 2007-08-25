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
#ifndef __gdcmDictEntry_h
#define __gdcmDictEntry_h

#include "gdcmVR.h"
#include "gdcmVM.h"

#include <string>
#include <iostream>
#include <iomanip>

namespace gdcm
{
/**
 * \brief Class to represent an Entry in the Dict
 * Does not really exist within the DICOM definition, just a way to minimize 
 * storage and have a mapping from gdcm::Tag to the needed information
 * \note bla
 * TODO FIXME: Need a PublicDictEntry...indeed DictEntry has a notion of retired which
 * does not exist in PrivateDictEntry...
 */
class GDCM_EXPORT DictEntry
{
public:
  DictEntry(const char *name, VR::VRType const &vr, VM::VMType const &vm , bool ret = false) {
    if(name) Name = name;
    ValueRepresentation = vr;
    ValueMultiplicity = vm;
    Retired = ret;
  }
  // FIXME
  DictEntry(const char *name, const char *vr, const char *vm) {
    if(name) Name = name;
    ValueRepresentation = VR::GetVRType(vr);
    ValueMultiplicity = VM::GetVMType(vm);
  }

  friend std::ostream& operator<<(std::ostream& _os, const DictEntry &_val);

  const VR &GetVR() const { return ValueRepresentation; }
//  bool IsValid() const { return ValueRepresentation != VR::VR_END; }
//	  !Name.empty() /*&& ValueRepresentation && ValueMultiplicity*/; }

  VM::VMType GetVM() const { return ValueMultiplicity; }

  const char *GetName() const { return Name.c_str(); }

  // same as GetName but without spaces
  const char *GetKeyword() const { return ""; }

  const bool GetRetired() const { return Retired; }

private:
  std::string Name;
  VR ValueRepresentation;
  VM::VMType ValueMultiplicity;
  bool Retired;
};

class GDCM_EXPORT PrivateDictEntry : public DictEntry
{
public:
  PrivateDictEntry(const char *name, VR::VRType const &vr, VM::VMType const &vm , bool ret = false, const char *owner = 0):DictEntry(name,vr,vm,ret),Owner(owner) {}

  const char *GetOwner() const { return Owner.c_str(); }

private:
  // SIEMENS MED, GEMS_PETD_01 ...
  std::string Owner;
};

//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const DictEntry &_val)
{
  _os << _val.Name << "\t" << _val.ValueRepresentation << "\t" << _val.ValueMultiplicity;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmDictEntry_h
