#include "gdcmExplicitDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmSequenceOfFragments.h"

namespace gdcm
{

ExplicitDataElement::~ExplicitDataElement()
{
}

//-----------------------------------------------------------------------------
IStream &ExplicitDataElement::Read(IStream &is)
{
  // See PS 3.5, Date Element Structure With Explicit VR
  // Read Tag
  if( !TagField.Read(is) )
    {
    if( !is.Eof() ) // FIXME This should not be needed
      {
    assert(0 && "Should not happen" );
      }
    return is;
    }
  // Read VR
    const Tag itemDelItem(0xfffe,0xe00d);
    if( TagField == itemDelItem )
      {
      VL vl;
      vl.Read(is);
      if( vl != 0 )
        {
        gdcmWarningMacro( "ouh les cornes" );
        }
      return is;
      }
    if( TagField == Tag(0x00ff, 0x4aa5) )
      {
    assert(0 && "Should not happen" );
    //  char c;
    //  is.Read(&c, 1);
    //  std::cerr << "Debug: " << c << std::endl;
      }
  if( !VRField.Read(is) )
    {
    assert(0 && "Should not happen" );
    return is;
    }
  // Read Value Length
  if( VRField == VR::OB
   || VRField == VR::OW
   || VRField == VR::OF
   || VRField == VR::SQ
   || VRField == VR::UN )
    {
    if( !ValueLengthField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    }
  else
    {
    // FIXME: Poorly written:
    uint16_t vl16;
    is.Read(vl16);
    ValueLengthField = vl16;
    }
  // Read the Value
  //assert( ValueField == 0 );
  if( VRField == VR::SQ )
    {
    // Check wether or not this is an undefined length sequence
    ValueField = new SequenceOfItems;
    }
  else if( ValueLengthField.IsUndefined() )
    {
    // Ok this is Pixel Data fragmented...
    const Tag pixelData(0x7fe0,0x0010);
    assert( TagField == pixelData );
    assert( VRField == VR::OB
         || VRField == VR::OW );
    //assert( xda.TagField == pixelData );
    //SequenceOfItems<ExplicitDataElement> si;
    //Read(si);
    ValueField = new SequenceOfFragments;
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
