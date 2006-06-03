#include "gdcmImplicitDataElement.h"
#include "gdcmValue.h"
#include "gdcmByteValue.h"

namespace gdcm
{

ImplicitDataElement::~ImplicitDataElement()
{
  delete ValueField;
}

//-----------------------------------------------------------------------------
std::istream &ImplicitDataElement::Read(std::istream &is,
    SC::SwapCode const &sc, bool readValue)
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  // Read Tag
  if( !TagField.Read(is, sc) )
    {
    assert(0 && "Should not happen");
    return is;
    }
  // Read Value Length
  if( !ValueLengthField.Read(is, sc) )
    {
    assert(0 && "Should not happen");
    return is;
    }
  if( ValueLengthField.IsUndefined() )
    {
    //assert( de.GetVR() == VR::SQ );
    //const Tag sdi(0xfffe,0xe0dd); // Sequence Delimitation Item
    //SequenceOfItems<ImplicitDataElement> si(ida.ValueLengthField);
    //Read(si);
    //gdcmDebugMacro( "SI: " << si );
    abort();
    }
  else
    {
    (void)readValue;
    // We have the length we should be able to read the value
    ValueField = new ByteValue;
    ValueField->SetLength(ValueLengthField); // perform realloc
    ValueField->Read(is, sc);
    //Seekg(ida.ValueLengthField, std::ios::cur);
    }

  return is;
}

//-----------------------------------------------------------------------------
const std::ostream &ImplicitDataElement::Write(std::ostream& os,
    SC::SwapCode const &sc) const
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  assert(0 && "Not Implemented");
  (void)os;
  (void)sc;
}

} // end namespace gdcm
