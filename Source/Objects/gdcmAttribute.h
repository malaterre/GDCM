#ifndef __gdcmAttribute_h
#define __gdcmAttribute_h

#include "gdcmVR.h"
#include "gdcmVM.h"

namespace gdcm
{
/**
 * \brief Abstract Class for representing an Attribute (PN: Person Name, UL: Unsigned Long...)
 * \note see concrete sub classed
 */
class GDCM_EXPORT Attribute
{
public:
  Attribute();
  ~Attribute();
  void SetVR(VR::VRType vr);
  void SetVM(VM::VMType vm);
  /// Problem with \0 in the string ...
  void SetValue(const char *val);
  void Print(std::ostream &_os) const;

private:
  VR::VRType VRField;
  VM::VMType VMField;
  char* Value;
};

} // end namespace gdcm

#endif //__gdcmAttribute_h
