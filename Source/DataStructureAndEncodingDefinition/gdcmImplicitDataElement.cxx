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
    ValueField = new SequenceOfItems(TS::Implicit);
    }
  else
    {
    //assert( TagField != Tag(0x7fe0,0x0010) );
    if( ValueLengthField < 8 )
      {
      ValueField = new ByteValue;
      }
    else
      {
      // In the following we read 4 more bytes in the Value field
      // to find out if this is a SQ or not
      // there is still work to do to handle the PMS featured SQ
      // where item Start is in fact 0xfeff, 0x00e0 ... sigh
      const Tag itemStart(0xfffe, 0xe000);
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
      const Tag itemPMSStart(0xfeff, 0x00e0);
#endif
      gdcm::Tag item;
      item.Read(is);
      // Maybe this code can later be rewritten as I believe that seek back
      // is very slow...
      is.Seekg(-4, std::ios::cur );
      if( item == itemStart )
        {
        ValueField = new SequenceOfItems(TS::Implicit);
        }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
      else if ( item == itemPMSStart )
        {
        ValueField = new SequenceOfItems(TS::Explicit);
        SwapCode oldsw = is.GetSwapCode();
        assert( oldsw == SwapCode::LittleEndian );
        is.SetSwapCode( SwapCode::BigEndian );
        ValueField->SetLength(ValueLengthField); // perform realloc
        if( !ValueField->Read(is) )
          {
          assert(0 && "Should not happen");
          }
        is.SetSwapCode( oldsw );
        return is;
        }
#endif
      else
        {
        ValueField = new ByteValue;
        }
      }
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
  //if( !ValueLengthField.IsUndefined() && ValueLengthField >= 8 )
  //  {
  //  Value *p = ValueField;
  //  const ByteValue *bv = dynamic_cast<ByteValue*>(p);
  //  union { uint16_t group; char bytes[2]; } testSQ;
  //  bv->GetBuffer( testSQ.bytes, sizeof(testSQ) );
  //  if( testSQ.group == 0xfffe || testSQ.group == 0xfeff )
  //    {
  //    std::cerr << "Tag: " << TagField << " is a defined length SQ of " << ValueLengthField << "\n";
  //    }
  //  }
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
