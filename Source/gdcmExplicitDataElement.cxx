#include "gdcmExplicitDataElement.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
gdcm::OStream& operator<<(gdcm::OStream& _os, ExplicitDataElement &_val)
{
  _os.Write(_val.VRField);
  // See PS 3.5, Date Element Structure With Explicit VR
  if( _val.VRField == VR::OB
   || _val.VRField == VR::OW
   || _val.VRField == VR::OF
   || _val.VRField == VR::SQ
   || _val.VRField == VR::UN )
    {
    uint16_t check = 0x0;
    _os.Write(check);
    // Write Value Lenght (32bits)
    _os.Write(_val.ValueLengthField);
    }
  else if( _val.VRField == VR::UT )
    {
    uint16_t check = 0x0;
    _os.Write(check);
    // Write Value Lenght (32bits)
    assert( _val.ValueLengthField != 0xFFFFFFFF );
    _os.Write(_val.ValueLengthField);
    }
  else
    {
    uint16_t vl = _val.ValueLengthField;
    // Write Value Lenght (16bits)
    _os.Write(vl);
    }
  // We have the length we should be able to write the value
  _os.Write(_val.ValueField);
  return _os;
}

//-----------------------------------------------------------------------------
gdcm::IStream& operator>>(gdcm::IStream& _os, ExplicitDataElement &_val)
{
  // Read VR
  _os.Read(_val.VRField);
  // See PS 3.5, Date Element Structure With Explicit VR
  if( _val.VRField == VR::OB
   || _val.VRField == VR::OW
   || _val.VRField == VR::OF
   || _val.VRField == VR::SQ
   || _val.VRField == VR::UN )
    {
    uint16_t check;
    _os.Read(check);
    assert( check == 0x0 );
    // Read Value Lenght (32bits)
    _os.Read(_val.ValueLengthField);
    }
  else if( _val.VRField == VR::UT )
    {
    uint16_t check;
    _os.Read(check);
    assert( check == 0x0 );
    // Read Value Lenght (32bits)
    _os.Read(_val.ValueLengthField);
    assert( _val.ValueLengthField != 0xFFFFFFFF );
    }
  else
    {
    uint16_t vl;
    // Read Value Lenght (16bits)
    _os.Read(vl);
    _val.ValueLengthField = vl;
    }
  // Read the Value
  if( _val.ValueLengthField != 0xFFFFFFFF )
    {
    // We have the length we should be able to read the value
    _os.Read(_val.ValueField, _val.ValueLengthField);
    }
  else
    {
    Tag t;
    Tag sdi = Tag(0xfffe,0xe0dd); // Sequence Delimitation Item
    ExplicitDataElement dummy;
    while(t != sdi )
      {
      _os.Read(t);
      _os >> dummy;
      _val.ValueLengthField+=t.GetLength()+dummy.GetLength();
      }
    }
  return _os;
}

} // end namespace gdcm
