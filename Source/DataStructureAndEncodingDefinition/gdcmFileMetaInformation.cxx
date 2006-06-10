#include "gdcmFileMetaInformation.h"
#include "gdcmVR.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmByteValue.h"

namespace gdcm
{

FileMetaInformation::~FileMetaInformation()
{
  delete DS;
}

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
/// \TODO FIXME
/// For now I do a Seek back of 6 bytes. It would be better to finish reading 
/// the first element of the FMI so that I can read the group length and 
/// therefore compare it against the actual value we found...
// \postcondition NegociatedTS and IStream::SwapCode are Unknown
// \postcondition NegociatedTS and IStream::SwapCode are set
IStream &FileMetaInformation::Read(IStream &is)
{
  // First off save position in case we fail (no File Meta Information)
  // See PS 3.5, Date Element Structure With Explicit VR
  assert( is.GetSwapCode()        == SwapCode::Unknown );
  assert( !DS || DS->GetNegociatedType() == TS::Unknown );
  std::streampos start = is.Tellg();
  Tag t;
  t.Read(is);
  //assert( t.GetGroup() == 0x0002 );
  if( t.GetGroup() == 0x0002 )
    {
    // Purposely not Re-use ReadVR since we can read VR_END
    char vr_str[2];
    is.SetWidth(2);
    is >> vr_str;
    if( VR::IsValid(vr_str) )
      {
      // Looks like an Explicit File Meta Information Header.
      // Hourah !
      is.Seekg(-6, std::ios::cur); // Seek back
      DS = new DataSet( TS::Explicit );
      ExplicitDataElement xde;
      while( ReadExplicitDataElement(is, xde ) )
        {
        //std::cout << xde << std::endl;
        DS->InsertDataElement( xde );
        }
      //std::cout << DS->Size() << std::endl;
      }
    else
      {
      gdcmWarningMacro( "Not Explicit" );
      // Ok this might be an implicit encoded Meta File Information header...
      // GE_DLX-8-MONO2-PrivateSyntax.dcm
      is.Seekg(-6, std::ios::cur); // Seek back
      DS = new DataSet( TS::Implicit );
      ImplicitDataElement ide;
      while( ReadImplicitDataElement(is, ide ) )
        {
        std::cout << ide << std::endl;
        }
      }
    }
  else
    {
    gdcmWarningMacro( "No File Meta Information. Start with Tag: " << t );
    is.Seekg(-4, std::ios::cur); // Seek back
    }

  return is;
}

// \postcondition after the file meta information (well before the dataset)
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
    is.Seekg( start, std::ios::beg );
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

bool FileMetaInformation::ReadImplicitDataElement(IStream &is,
  ImplicitDataElement &de)
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  std::streampos start = is.Tellg();
  // Read Tag
  Tag t;
  if( !t.Read(is) )
    {
    assert(0 && "Should not happen");
    return false;
    }
  //std::cout << "Tag: " << t << std::endl;
  if( t.GetGroup() != 0x0002 )
    {
    gdcmDebugMacro( "Done reading File Meta Information" );
    is.Seekg( start, std::ios::beg );
    return false;
    }
  // Read Value Length
  VL vl;
  if( !vl.Read(is) )
    {
    assert(0 && "Should not happen");
    return false;
    }
  ByteValue *bv = 0;
  if( vl.IsUndefined() )
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
  de.SetTag(t);
  de.SetVL(vl);
  de.SetValue(*bv);

  return true;
}

TS::TSType FileMetaInformation::GetTSType()
{
  if(DS)
    {
    const gdcm::Tag t(0x0002,0x0010);
    const DataElement& de = DS->GetDataElement(t);
    TS::NegociatedType nt = DS->GetNegociatedType();
    const char *ts = 0;
    if( nt == TS::Explicit )
      {
      const Value &v = dynamic_cast<const ExplicitDataElement&>(de).GetValue();
      const ByteValue &bv = dynamic_cast<const ByteValue&>(v);
      ts = bv.GetPointer();
      }
    else if( nt == TS::Implicit )
      {
      const Value &v = dynamic_cast<const ImplicitDataElement&>(de).GetValue();
      const ByteValue &bv = dynamic_cast<const ByteValue&>(v);
      ts = bv.GetPointer();
      }
    else
      {
      assert( 0 && "Cannot happen" );
      }
    gdcmWarningMacro( "TS: " << ts );
    return TS::GetTSType(ts);
    }
  return TS::TS_END;
}

OStream &FileMetaInformation::Write(OStream &os) const
{
  return os;
}

} // end namespace gdcm
