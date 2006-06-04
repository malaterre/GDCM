#include "gdcmFileMetaInformation.h"
#include "gdcmVR.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmByteValue.h"

namespace gdcm
{

/*
 * Except for the 128 byte preamble and the 4 byte prefix, the File Meta 
 * Information shall be encoded using the Explicit VR Little Endian Transfer
 * Syntax (UID=1.2.840.10008.1.2.1) as defined in DICOM PS 3.5.
 * Values of each File Meta Element shall be padded when necessary to achieve
 * an even length as specified in PS 3.5 by their corresponding Value
 * Representation. For compatibility with future versions of this Standard, 
 * any Tag (0002,xxxx) not defined in Table 7.1-1 shall be ignored.
 * Values of all Tags (0002,xxxx) are reserved for use by this Standard and
 * later versions of DICOM.
 * Note: PS 3.5 specifies that Elements with Tags (0001,xxxx), (0003,xxxx),
 * (0005,xxxx), and (0007,xxxx) shall not be used.
 */
IStream& FileMetaInformation::Read(IStream &is)
{
  // First off save position in case we fail (no File Meta Information)
  // See PS 3.5, Date Element Structure With Explicit VR
  ExplicitDataElement de;
  while( ReadExplicitDataElement(is, de ) )
    {
    std::cout << de << std::endl;
    }

  return is;
}

// \postcondition after the file meta information (well before the 
// dataset)
bool FileMetaInformation::ReadExplicitDataElement(IStream &is,
  ExplicitDataElement &de)
{
  // Read Tag
  std::streampos start = is.Tellg();
  //std::cout << "Start: " << start << std::endl;
  Tag t;
  if( !t.Read(is) )
    {
    assert(0 && "Should not happen" );
    return false;
    }
  //std::cout << "Tag: " << t << std::endl;
  if( t.GetGroup() != 0x0002 )
    {
    gdcmDebugMacro( "Done reading File Meta Information" );
    is.Seekg( start, std::ios::beg );
    return false;
    }
  // Read VR
  VR vr;
  if( !vr.Read(is) )
    {
    assert(0 && "Should not happen" );
    return false;
    }
  //std::cout << "VR : " << vr << std::endl;
  // Read Value Length
  VL vl;
  if( vr == VR::OB
   || vr == VR::OW
   || vr == VR::OF
   || vr == VR::SQ
   || vr == VR::UN )
    {
    if( !vl.Read(is) )
      {
      assert(0 && "Should not happen");
      return false;
      }
    }
  else
    {
    union { uint16_t vl; char vl_str[2]; } uvl;
    is.Read(uvl.vl_str,2);
    //ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem((uint16_t*)(&vl_str),
    //  SwapCode, 1);
    assert( uvl.vl != static_cast<uint16_t>(-1) );
    vl = uvl.vl;
    }
  gdcmDebugMacro( "VL : " << vl );
  // Read the Value
  ByteValue *bv = NULL;
  if( vr == VR::SQ )
    {
    assert(0 && "Should not happen");
    return false;
    }
  else if( vl.IsUndefined() )
    {
    assert(0 && "Should not happen");
    return false;
    }
  else
    {
    bv = new ByteValue;
    }
  // We have the length we should be able to read the value
  bv->SetLength(vl); // perform realloc
  if( !bv->Read(is) )
    {
    assert(0 && "Should not happen");
    return false;
    }
  //std::cout << "Value : ";
  //bv->Print( std::cout );
  //std::cout << std::endl;

  de.SetTag(t);
  de.SetVR(vr);
  de.SetVL(vl);
  de.SetValue(*bv);

  return true;
}

OStream &FileMetaInformation::Write(OStream &os) const
{
  return os;
}

} // end namespace gdcm
