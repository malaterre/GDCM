#include "gdcmAttribute.h"
#include <string.h>

namespace gdcm
{

Attribute::Attribute()
{
  VRField = VR::VR_END;
  VMField = VM::VM_END;
  Value   = 0;
}

Attribute::~Attribute()
{
  delete[] Value;
}

void Attribute::SetVR(VR::VRType vr)
{
  VRField = vr;
}

void Attribute::SetVM(VM::VMType vm)
{
  VMField = vm;
}

void Attribute::SetValue(const char *val)
{
  size_t len = strlen(val);
  if( len )
    {
    char *value = new char[len+1];
    memcpy(value, val, len);
    delete[] Value;
    Value = value;
    Value[len] = '\0';
    }
  else
    {
    delete[] Value;
    Value = 0;
    }
}
void Attribute::Print(std::ostream &_os) const
{
  abort();
}

}
