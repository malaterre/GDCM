/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
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
 * Except for the 128 bytes preamble and the 4 bytes prefix, the File Meta 
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
  // See PS 3.5, Data Element Structure With Explicit VR
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

TS FileMetaInformation::GetTransferSyntaxType() const
{
  if(DS)
    {
    const gdcm::Tag t(0x0002,0x0010);
    const DataElement &de = DS->GetDataElement(t);
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
    TS tst(TS::GetTSType(ts.c_str()));
    assert( tst != TS::TS_END );
    return tst;
    }

  return TS::TS_END;
}

TS::MSType FileMetaInformation::GetMediaStorageType() const
{
  // D 0002|0002 [UI] [Media Storage SOP Class UID]
  // [1.2.840.10008.5.1.4.1.1.12.1]
  // ==>       [X-Ray Angiographic Image Storage]
  if(DS)
    {
    const gdcm::Tag t(0x0002,0x0002);
    if( !DS->FindDataElement( t ) )
      {
      gdcmWarningMacro( "File Meta information is present but does not"
        " contains " << t );
      return TS::MS_END;
      }
    const DataElement &de = DS->GetDataElement(t);
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
    TS::MSType ms = TS::GetMSType(ts.c_str());
    if( ms == TS::MS_END )
      {
      gdcmWarningMacro( "Media Storage Class UID: " << ts << " is unknow" );
      }
    return ms;
    }

  return TS::MS_END;
}

OStream &FileMetaInformation::Write(OStream &os) const
{
  if( DS )
    {
    DS->Write(os);
    }

  return os;
}

} // end namespace gdcm
