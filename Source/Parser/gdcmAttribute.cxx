#include "gdcmAttributeFactory.h"
#include "gdcmAttribute.h"
#include "gdcmVM.h"
#include "gdcmVR.h"
#include <string.h>

namespace gdcm
{
class AttributeFactoryInternal
  {
  public:
  AttributeFactory<VR::UL,VM::VM1_n> AF_UL;
  AttributeFactory<VR::US,VM::VM1_n> AF_US;
  AttributeFactory<VR::US,VM::VM1_n> AF_SS;
  };

Attribute::Attribute()
{
  VRField = VR::VR_END;
  VMField = VM::VM_END;
  AF = new AttributeFactoryInternal;
}

Attribute::~Attribute()
{
  delete AF;
}

void Attribute::SetVR(VR::VRType vr)
{
  VRField = vr;
}

void Attribute::SetVM(VM::VMType vm)
{
  VMField = vm;
}

void Attribute::SetLength(int len)
{
  switch(VRField)
    {
  case VR::UL:
    AF->AF_UL.SetLength(len);
    break;
  case VR::US:
    AF->AF_US.SetLength(len);
    break;
  case VR::SS:
    AF->AF_SS.SetLength(len);
    break;
  default:
    abort();
    }
}

void Attribute::Read(std::istream &_is)
{
  switch(VRField)
    {
  case VR::UL:
    AF->AF_UL.Read(_is);
    break;
  case VR::US:
    AF->AF_US.Read(_is);
    break;
  case VR::SS:
    AF->AF_SS.Read(_is);
    break;
  default:
    abort();
    }
}

//void Attribute::SetValue(const char *val)
//{
//  size_t len = strlen(val);
//  if( len )
//    {
//    char *value = new char[len+1];
//    memcpy(value, val, len);
//    delete[] Value;
//    Value = value;
//    Value[len] = '\0';
//    }
//  else
//    {
//    delete[] Value;
//    Value = 0;
//    }
//}
void Attribute::Print(std::ostream &_os) const
{
  switch(VRField)
    {
  case VR::UL:
      AF->AF_UL.Print(_os);
      break;
  case VR::US:
      AF->AF_US.Print(_os);
      break;
  case VR::SS:
      AF->AF_SS.Print(_os);
      break;
  default:
      abort();
    }
}

}
