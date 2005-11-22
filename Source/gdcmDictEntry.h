
#ifndef __gdcmDictEntry_h
#define __gdcmDictEntry_h

/**
 * \brief Class to represent an Entry in the Dict
 * Does not really exist within the DICOM definition, just a way to minize storage
 * and have a mapping from gdcm::Tag to the needed information
 * \note bla
 */

#include "gdcmType.h"
#include "gdcmVR.h"
#include "gdcmVM.h"
#include <iostream>
#include <iomanip>

namespace gdcm
{
class DictEntry
{
public:
  DictEntry(const char *name, VR::VRType const &vr, VM::VMType const &vm /*, bool ret = false*/) {
    Name = name;
    ValueRepresentation = vr;
    ValueMultiplicity = vm;
    // Retired = ret;
  }
  // FIXME
  DictEntry(const char *name, const char *vr, const char *vm) {
    Name = name;
    ValueRepresentation = VR::GetVRType(vr);
    ValueMultiplicity = VM::GetVMType(vm);
  }

  friend std::ostream& operator<<(std::ostream& _os, const DictEntry &_val);

  VR::VRType GetVR() { return ValueRepresentation; }

  VM::VMType GetVM() { return ValueMultiplicity; }

private:
  std::string Name;
  VR::VRType ValueRepresentation;
  VM::VMType ValueMultiplicity;
  //bool Retired;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const DictEntry &_val)
{
  _os << _val.Name << "\t" << _val.ValueRepresentation << "\t" << _val.ValueMultiplicity;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmDictEntry_h
