#include "gdcmExplicitDataElement.h"

namespace gdcm
{

//-----------------------------------------------------------------------------
void ExplicitDataElement::Read(std::istream &_is)
{
  (void)_is;
}

//-----------------------------------------------------------------------------
void ExplicitDataElement::Write(std::ostream &_os) const
{
  VR::Write(_os, VRField);
  // See PS 3.5, Date Element Structure With Explicit VR
  if( VRField == VR::OB
   || VRField == VR::OW
   || VRField == VR::OF
   || VRField == VR::SQ
   || VRField == VR::UN )
    {
    uint16_t check = 0x0;
    _os.write(reinterpret_cast<char*>(check), sizeof(check));
    // Write Value Length (32bits)
    _os.write(reinterpret_cast<char*>(ValueLengthField), sizeof(ValueLengthField));
    }
  else if( VRField == VR::UT )
    {
    uint16_t check = 0x0;
    _os.write(reinterpret_cast<char*>(check), sizeof(check));
    // Write Value Length (32bits)
    assert( ValueLengthField != 0xFFFFFFFF );
    _os.write(reinterpret_cast<char*>(ValueLengthField), sizeof(ValueLengthField));
    }
  else
    {
    uint16_t vl = ValueLengthField;
    // Write Value Length (16bits)
    _os.write(reinterpret_cast<char*>(vl), sizeof(vl));
    }
  // We have the length we should be able to write the value
  ValueField.Write(_os);

}

} // end namespace gdcm
