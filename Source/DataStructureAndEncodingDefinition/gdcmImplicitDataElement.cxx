#include "gdcmImplicitDataElement.h"
#include "gdcmValue.h"
#include "gdcmByteValue.h"
#include "gdcmSequenceOfItems.h"

#define GDCM_SUPPORT_BROKEN_IMPLEMENTATION

namespace gdcm
{

ImplicitDataElement::~ImplicitDataElement()
{
}

//-----------------------------------------------------------------------------
IStream &ImplicitDataElement::Read(IStream &is)
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  // Read Tag
  if( !TagField.Read(is) )
    {
    //assert(0 && "Should not happen");
    return is;
    }
  // Read Value Length
  if( !ValueLengthField.Read(is) )
    {
    assert(0 && "Should not happen");
    return is;
    }
  if( ValueLengthField.IsUndefined() )
    {
    //assert( de.GetVR() == VR::SQ );
    // FIXME what if I am reading the pixel data...
    assert( TagField != Tag(0x7fe0,0x0010) );
    ValueField = new SequenceOfItems;
    }
  else
    {
    //assert( TagField != Tag(0x7fe0,0x0010) );
    ValueField = new ByteValue;
    }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  // THE WORST BUG EVER. From GE Workstation
  if( ValueLengthField == 13 )
    {
    // Historically gdcm did not enforce proper length
    // thus Theralys started writing illegal DICOM images:
    const Tag theralys1(0x0008,0x0070);
    const Tag theralys2(0x0008,0x0080);
    if( TagField != theralys1
     && TagField != theralys2 )
      {
      gdcmWarningMacro( "BUGGY HEADER (GE, 13)" );
      ValueLengthField = 10;
      }
    }
#endif
  // We have the length we should be able to read the value
  ValueField->SetLength(ValueLengthField); // perform realloc
  if( !ValueField->Read(is) )
    {
    assert(0 && "Should not happen");
    return is;
    }
  //Seekg(ida.ValueLengthField, std::ios::cur);

  return is;
}

//-----------------------------------------------------------------------------
const OStream &ImplicitDataElement::Write(OStream &os) const
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  assert(0 && "Not Implemented");
  (void)os;
  return os;
}

} // end namespace gdcm
