#ifndef __gdcmAttribute_h
#define __gdcmAttribute_h

#include "gdcmAttributeFactory.h"
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
  //void SetValue(const char *val);

  void SetLength(int len);
  void Read(std::istream &_is);
  void Print(std::ostream &_os) const;

private:
  VR::VRType VRField;
  VM::VMType VMField;
  AttributeFactory<VR::UL,VM::VM1_n> AF_UL;
};

} // end namespace gdcm

#endif //__gdcmAttribute_h
