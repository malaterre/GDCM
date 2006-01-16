#include "gdcmImplicitDataElement.h"
#include "gdcmSequenceOfItems.txx"
#include "gdcmDict.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
DICOMOStream& operator<<(DICOMOStream &_os, const ImplicitDataElement &_val)
{
  return _val.Write(_os);
}

DICOMOStream& ImplicitDataElement::Write(DICOMOStream& _os) const
{
  //const DataElement &de = 
  //_os << de;
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  assert(0 && "Not Implemented");
  return _os;
}

//-----------------------------------------------------------------------------
DICOMIStream& operator>>(DICOMIStream &_os, ImplicitDataElement &_val)
{
  return _val.Read(_os);
}

DICOMIStream& ImplicitDataElement::Read(DICOMIStream& _os)
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  // Read Tag
  //if( !_os.Read(TagField) ) return _os;
  //static Dict d;
  //const DictEntry &de = d.GetDictEntry(TagField);
  // Read Value Length
  if( !(_os.Read(ValueLengthField)) ) return _os;
  // THE WORST BUG EVER:
  if(ValueLengthField == 13 )
    {
    const Tag theralys1(0x0008,0x0070);
    const Tag theralys2(0x0008,0x0080);
    if( GetTag() != theralys1
     && GetTag() != theralys2 )
      {
      std::cerr << "BUGGY HEADER (GE, 13)" << std::endl;
      ValueLengthField = 10;
      }
    }
  if(ValueLengthField == 0xFFFFFFFF)
    {
    //assert( de.GetVR() == VR::SQ );
    const Tag sdi(0xfffe,0xe0dd); // Sequence Delimitation Item
    SequenceOfItems<ImplicitDataElement> si(ValueLengthField);
    _os >> si;
    //std::cout << "Debug:" << si << std::endl;
    }
  else
    {
    // We have the length we should be able to read the value
    if( ValueLengthField < 0xfff )
      {
      ValueField.SetLength(ValueLengthField); // perform realloc
      _os.Read(ValueField);
      }
    else
      _os.Seekg(ValueLengthField, std::ios::cur);
    }
  return _os;
}

} // end namespace gdcm
