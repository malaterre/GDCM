#include "gdcmExplicitDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmSequenceOfItems.h"

namespace gdcm
{

//ExplicitDataElement(ExplicitDataElement const &)
//{
//}

ExplicitDataElement::~ExplicitDataElement()
{
  //FIXME
  //delete ValueField;
}

//-----------------------------------------------------------------------------
IStream &ExplicitDataElement::Read(IStream &is)
{
  // See PS 3.5, Date Element Structure With Explicit VR
  // Read Tag
  if( !TagField.Read(is) )
    {
    assert(0 && "Should not happen" );
    return is;
    }
  // Read VR
  if( !VRField.Read(is) )
    {
    assert(0 && "Should not happen" );
    return is;
    }
  // Read Value Length
  if( !ValueLengthField.Read(is) )
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
  if( !ValueField->Read(is) )
    {
    assert(0 && "Should not happen");
    return is;
    }

  return is;
}

//-----------------------------------------------------------------------------
const OStream &ExplicitDataElement::Write(OStream &os) const
{
  if( !TagField.Write(os) )
    {
    assert( 0 && "Should not happen" );
    return os;
    }
  if( !VRField.Write(os) )
    {
    assert( 0 && "Should not happen" );
    return os;
    }
  if( !ValueLengthField.Write(os) )
    {
    assert( 0 && "Should not happen" );
    return os;
    }
  // We have the length we should be able to write the value
  ValueField->Write(os);

  return os;
}

} // end namespace gdcm
