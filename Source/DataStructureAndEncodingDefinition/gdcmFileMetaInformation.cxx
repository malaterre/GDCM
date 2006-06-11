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
    is.Read(vr_str, 2);
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
        //std::cout << ide << std::endl;
        DS->InsertDataElement( ide );
        }
      }
    // Before return the stream make sure to set it approprietly for the
    // user
    TS::TSType ts = GetTSType();
    is.SetSwapCode( TS::GetSwapCode(ts) );
    }
  else
    {
    gdcmWarningMacro( "No File Meta Information. Start with Tag: " << t );
    if( ! (t.GetGroup() % 2) )
      {
      // Purposely not Re-use ReadVR since we can read VR_END
      char vr_str[3];
      is.Read(vr_str, 2);
      vr_str[2] = '\0';
      VR::VRType vr = VR::GetVRTypeFromFile(vr_str);
      if( vr != VR::VR_END )
        {
        FakeTSType = TS::ExplicitVRLittleEndian;
        }
      else
        {
        assert( !(VR::IsSwap(vr_str)));
        is.Seekg(-2, std::ios::cur); // Seek back
        if( t.GetElement() == 0x0000 )
          {
          VL group_length;
          SwapCode sc;
          assert( is.GetSwapCode() == SwapCode::Unknown );
          group_length.Read(is);
          switch(group_length)
            {
          case 0x00040000 :
            sc = SwapCode::BadLittleEndian; // 3412
            break;
          case 0x04000000 :
            sc = SwapCode::BigEndian;       // 4321
            break;  
          case 0x00000400 :
            sc = SwapCode::BadBigEndian;    // 2143
            break;
          case 0x00000004 :
            sc = SwapCode::LittleEndian;    // 1234
            break;
          default:
            abort();
            }
          // Sekk back sizeof(Tag)+sizeof(VL)
          is.Seekg(-8, std::ios::cur); // Seek back
          is.SetSwapCode( sc );
          }
        }
      }
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
    uint16_t vl16;
    is.Read(vl16);
    vl = vl16;
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
    assert( FakeTSType == TS::TS_END );
    const gdcm::Tag t(0x0002,0x0010);
    const DataElement& de = DS->GetDataElement(t);
    TS::NegociatedType nt = DS->GetNegociatedType();
    std::string ts;
    if( nt == TS::Explicit )
      {
      const Value &v = dynamic_cast<const ExplicitDataElement&>(de).GetValue();
      const ByteValue &bv = dynamic_cast<const ByteValue&>(v);
      // Pad string with a \0
      ts = std::string(bv.GetPointer(), bv.GetLength());
      }
    else if( nt == TS::Implicit )
      {
      const Value &v = dynamic_cast<const ImplicitDataElement&>(de).GetValue();
      const ByteValue &bv = dynamic_cast<const ByteValue&>(v);
      // Pad string with a \0
      ts = std::string(bv.GetPointer(), bv.GetLength());
      }
    else
      {
      assert( 0 && "Cannot happen" );
      }
    gdcmDebugMacro( "TS: " << ts );
    return TS::GetTSType(ts.c_str());
    }

  return FakeTSType;
}

OStream &FileMetaInformation::Write(OStream &os) const
{
  return os;
}

} // end namespace gdcm
