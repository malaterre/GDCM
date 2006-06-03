#include "gdcmImplicitDataElement.h"

namespace gdcm
{

//-----------------------------------------------------------------------------
std::istream &ImplicitDataElement::Read(std::istream &is)
{
#if 0
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  // Read Tag
  if( !TagField.Read(is) )
    {
    assert(0 && "Should not happen");
    return is;
    }
  // Read Value Length
  if( !(Read(ida.ValueLengthField)) )
    {
    }
  if(ida.ValueLengthField == 0xFFFFFFFF)
    {
    //assert( de.GetVR() == VR::SQ );
    const Tag sdi(0xfffe,0xe0dd); // Sequence Delimitation Item
    SequenceOfItems<ImplicitDataElement> si(ida.ValueLengthField);
    Read(si);
    gdcmDebugMacro( "SI: " << si );
    }
  else
    {
    // We have the length we should be able to read the value
    bool needReading = true;
    if( ReadForPrinting )
      {
      needReading = ida.ValueLengthField < 0xfff;
      }
    if( needReading )
      {
      ida.ValueField.SetLength(ida.ValueLengthField); // perform realloc
      Read(ida.ValueField);
      }
    else
      {
      //gdcmWarningMacro( "Seeking long field: " << ida.GetTag() << " l= " 
      //  << ida.ValueLengthField );
      ida.ValueField.Clear();
      Seekg(ida.ValueLengthField, std::ios::cur);
      }
    }
#endif
  return is;
}

//-----------------------------------------------------------------------------
const std::ostream &ImplicitDataElement::Write(std::ostream& _os) const
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  assert(0 && "Not Implemented");
  (void)_os;
}

} // end namespace gdcm
