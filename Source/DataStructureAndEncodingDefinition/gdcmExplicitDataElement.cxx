#include "gdcmExplicitDataElement.h"
#include "gdcmValue.h"

namespace gdcm
{

//-----------------------------------------------------------------------------
std::istream &ExplicitDataElement::Read(std::istream &is, 
                                        SC::SwapCode const &sc)
{
  (void)sc;
  return is;
}

//-----------------------------------------------------------------------------
const std::ostream &ExplicitDataElement::Write(std::ostream &_os, 
                                               SC::SwapCode const &sc) const
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
    ValueLengthField.Write(_os, sc);
    }
  else if( VRField == VR::UT )
    {
    uint16_t check = 0x0;
    _os.write(reinterpret_cast<char*>(check), sizeof(check));
    // Write Value Length (32bits)
    assert( !ValueLengthField.IsUndefined() );
    ValueLengthField.Write(_os, sc);
    }
  else
    {
    uint16_t vl = ValueLengthField;
    // Write Value Length (16bits)
    _os.write(reinterpret_cast<char*>(vl), sizeof(vl));
    }
  // We have the length we should be able to write the value
  ValueField->Write(_os, sc);

  return _os;
}

} // end namespace gdcm
