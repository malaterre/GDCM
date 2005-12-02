#include "gdcmImplicitDataElement.h"
#include "gdcmSequenceItems.txx"
#include "gdcmDict.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
DICOMOStream& operator<<(DICOMOStream& _os, const ImplicitDataElement &_val)
{
  //const DataElement &de = _val;
  //_os << de;
  // See PS 3.5, 7.1.3 Date Element Structure With Implicit VR
  assert(0 && "Not Implemented");
  (void)_val;
  return _os;
}

//-----------------------------------------------------------------------------
DICOMIStream& operator>>(DICOMIStream& _os, ImplicitDataElement &_val)
{
  // See PS 3.5, 7.1.3 Date Element Structure With Implicit VR
  // Read Tag
  //if( !_os.Read(_val.TagField) ) return _os;
  //static Dict d;
  //const DictEntry &de = d.GetDictEntry(_val.TagField);
  // Read Value Length
  if( !(_os.Read(_val.ValueLengthField)) ) return _os;
  // THE WORST BUG EVER:
  if(_val.ValueLengthField == 13 )
    {
    const Tag theralys1(0x0008,0x0070);
    const Tag theralys2(0x0008,0x0080);
    if( _val.GetTag() != theralys1
     && _val.GetTag() != theralys2 )
      {
      std::cerr << "BUGGY HEADER (GE, 13)" << std::endl;
      _val.ValueLengthField = 10;
      }
    }
  if(_val.ValueLengthField == 0xFFFFFFFF)
    {
    //assert( de.GetVR() == VR::SQ );
    const Tag sdi(0xfffe,0xe0dd); // Sequence Delimitation Item
    SequenceItems<ImplicitDataElement> si(_val.ValueLengthField);
    _os >> si;
    //std::cout << "Debug:" << si << std::endl;
    }
  else
    {
    // We have the length we should be able to read the value
    if( _val.ValueLengthField < 0xfff )
      {
      _val.ValueField.SetLength(_val.ValueLengthField); // perform realloc
      _os.Read(_val.ValueField);
      }
    else
      _os.Seekg(_val.ValueLengthField, std::ios::cur);
    }
  return _os;
}

} // end namespace gdcm
