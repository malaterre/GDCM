
#ifndef __gdcmDictEntry_h
#define __gdcmDictEntry_h


#include "gdcmType.h"
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
 */
class GDCM_EXPORT DictEntry
{
public:
  DictEntry(const char *name, VR::VRType const &vr, VM::VMType const &vm /*, bool ret = false*/) {
    if(name) Name = name;
    ValueRepresentation = vr;
    ValueMultiplicity = vm;
    // Retired = ret;
  }
  // FIXME
  DictEntry(const char *name, const char *vr, const char *vm) {
    if(name) Name = name;
    ValueRepresentation = VR::GetVRType(vr);
    ValueMultiplicity = VM::GetVMType(vm);
  }

  friend std::ostream& operator<<(std::ostream& _os, const DictEntry &_val);

  VR::VRType GetVR() const { return ValueRepresentation; }

  VM::VMType GetVM() const { return ValueMultiplicity; }

  std::string GetName() const { return Name; }

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
