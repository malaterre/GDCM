#include "gdcmExplicitDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmSequenceOfItems.h"

namespace gdcm
{

ExplicitDataElement::~ExplicitDataElement()
{
  delete ValueField;
}

//-----------------------------------------------------------------------------
std::istream &ExplicitDataElement::Read(std::istream &is, 
                                        SC::SwapCode const &sc)
{
  // See PS 3.5, Date Element Structure With Explicit VR
  // Read Tag
  if( !TagField.Read(is, sc) )
    {
    assert(0 && "Should not happen" );
    return is;
    }
  // Read VR
  if( !VRField.Read(is,sc) )
    {
    assert(0 && "Should not happen" );
    return is;
    }
  // Read Value Length
  if( !ValueLengthField.Read(is, sc) )
    {
    assert(0 && "Should not happen");
    return is;
    }
  // Read the Value
  if( VRField == VR::SQ )
    {
    // Check wether or not this is an undefined length sequence
    ValueField = new SequenceOfItems;
    }
  else if( ValueLengthField.IsUndefined() )
    {
    // Ok this is Pixel Data fragmented...
    //const Tag pixelData(0x7fe0,0x0010);
    assert( VRField == VR::OB 
         || VRField == VR::OW );
    //assert( xda.TagField == pixelData );
    //SequenceOfItems<ExplicitDataElement> si;
    //Read(si);
    abort();
    }
  else
    {
    ValueField = new ByteValue;
    }
  // We have the length we should be able to read the value
  ValueField->SetLength(ValueLengthField); // perform realloc
  if( !ValueField->Read(is, sc) )
    {
    assert(0 && "Should not happen");
    return is;
    }

  return is;
}

//-----------------------------------------------------------------------------
const std::ostream &ExplicitDataElement::Write(std::ostream &os, 
                                               SC::SwapCode const &sc) const
{
  if( !TagField.Write(os, sc) )
    {
    assert( 0 && "Should not happen" );
    return os;
    }
  if( !VRField.Write(os, sc) )
    {
    assert( 0 && "Should not happen" );
    return os;
    }
  // See PS 3.5, Date Element Structure With Explicit VR
  if( VRField == VR::OB
   || VRField == VR::OW
   || VRField == VR::OF
   || VRField == VR::SQ
   || VRField == VR::UN )
    {
    uint16_t check = 0x0;
    os.write(reinterpret_cast<char*>(check), sizeof(check));
    // Write Value Length (32bits)
    ValueLengthField.Write(os, sc);
    }
  else if( VRField == VR::UT )
    {
    uint16_t check = 0x0;
    os.write(reinterpret_cast<char*>(check), sizeof(check));
    // Write Value Length (32bits)
    assert( !ValueLengthField.IsUndefined() );
    ValueLengthField.Write(os, sc);
    }
  else
    {
    uint16_t vl = ValueLengthField;
    // Write Value Length (16bits)
    os.write(reinterpret_cast<char*>(vl), sizeof(vl));
    }
  // We have the length we should be able to write the value
  ValueField->Write(os, sc);

  return os;
}

} // end namespace gdcm
