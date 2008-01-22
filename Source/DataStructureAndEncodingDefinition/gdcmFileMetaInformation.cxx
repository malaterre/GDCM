/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmFileMetaInformation.h"
#include "gdcmAttribute.h"
#include "gdcmVR.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmSwapper.h"

#include "gdcmTag.h"

namespace gdcm
{

void FileMetaInformation::FillFromDataSet(DataSet const &ds)
{
  // Example: CR-MONO1-10-chest.dcm is missing a file meta header:
  DataElement xde;
  // File Meta Information Version (0002,0001) -> computed
  if( !FindDataElement( Tag(0x0002, 0x0001) ) )
    {
    xde.SetTag( Tag(0x0002, 0x0001) );
    xde.SetVR( VR::OB );
    xde.SetByteValue( "\0\1", 2);
    Insert( xde );
    }
  // Media Storage SOP Class UID (0002,0002) -> see (0008,0016)
  if( !FindDataElement( Tag(0x0002, 0x0002) ) )
    {
    if( !ds.FindDataElement( Tag(0x0008, 0x0016) ) )
      {
      abort();
      }
    else
      {
      const DataElement& msclass = ds.GetDataElement( Tag(0x0008, 0x0016) );
      xde = msclass;
      xde.SetTag( Tag(0x0002, 0x0002) );
      if( msclass.GetVR() == VR::UN || msclass.GetVR() == VR::INVALID )
        {
        xde.SetVR( VR::UI );
        }
      Insert( xde );
      }
    }
  // Media Storage SOP Instance UID (0002,0003) -> see (0008,0018)
  if( !FindDataElement( Tag(0x0002, 0x0003) ) )
    {
    if( ds.FindDataElement( Tag(0x0008, 0x0018) ) )
      {
      const DataElement& msinst = ds.GetDataElement( Tag(0x0008, 0x0018) );
      xde = msinst;
      xde.SetTag( Tag(0x0002, 0x0003) );
      if( msinst.GetVR() == VR::UN )
        {
        xde.SetVR( VR::UI );
        }
      Insert( xde );
      }
    }
  // Transfer Syntax UID (0002,0010) -> ??? (computed at write time at most)
  // Implementation Class UID (0002,0012) -> ??
  // Implementation Version Name (0002,0013) -> ??
  if( !FindDataElement( Tag(0x0002, 0x0013) ) )
    {
    xde.SetTag( Tag(0x0002, 0x0013) );
    xde.SetVR( VR::SH );
    xde.SetByteValue( "2.0.0", 5);
    Insert( xde );
    }
  // Source Application Entity Title (0002,0016) -> ??
  if( !FindDataElement( Tag(0x0002, 0x0016) ) )
    {
    xde.SetTag( Tag(0x0002, 0x0016) );
    xde.SetVR( VR::AE );
    xde.SetByteValue( "GDCM", 4);
    Insert( xde );
    }
  // Do this one last !
  // (Meta) Group Length (0002,0000) -> computed
  //unsigned int glen = ComputeGroupLength( Tag(0x0002, 0x0000) );
  unsigned int glen = GetLength<ExplicitDataElement>();
  DataElement xgl( Tag(0x0002, 0x0000), 4, VR::UL );
  Element<VR::UL, VM::VM1> el = 
    reinterpret_cast< Element<VR::UL, VM::VM1>& > ( glen );
  std::stringstream ss;
  el.Write( ss );
  SmartPointer<ByteValue> bv = new ByteValue;
  bv->SetLength( 4 );
  bv->Read<SwapperNoOp>( ss );
  xgl.SetValue( *bv );
  Insert( xgl );

  assert( !IsEmpty() );
}

// FIXME
// This code should clearly be rewritten with some template meta programing to 
// enable reuse of code...
//
// \postcondition after the file meta information (well before the dataset...)
template <typename TSwap>
bool ReadExplicitDataElement(std::istream &is, ExplicitDataElement &de)
{
  // Read Tag
  std::streampos start = is.tellg();
  //std::cout << "Start: " << start << std::endl;
  Tag t;
  if( !t.template Read<TSwap>(is) )
    {
    assert(0 && "Should not happen" );
    return false;
    }
  //std::cout << "Tag: " << t << std::endl;
  if( t.GetGroup() != 0x0002 )
    {
    gdcmDebugMacro( "Done reading File Meta Information" );
    is.seekg( start, std::ios::beg );
    return false;
    }
  // Read VR
  VR vr;
  if( !vr.Read(is) )
    {
    is.seekg( start, std::ios::beg );
    return false;
    }
  //std::cout << "VR : " << vr << std::endl;
  // Read Value Length
  VL vl;
  if( vr & VR::VL32 )
    {
    if( !vl.template Read<TSwap>(is) )
      {
      assert(0 && "Should not happen");
      return false;
      }
    }
  else
    {
    // Value Length is stored on 16bits only
    vl.template Read16<TSwap>(is);
    }
  //gdcmDebugMacro( "VL : " << vl );
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
  if( !bv->template Read<TSwap>(is) )
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

template <typename TSwap>
bool ReadImplicitDataElement(std::istream &is, ImplicitDataElement &de)
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  std::streampos start = is.tellg();
  // Read Tag
  Tag t;
  if( !t.template Read<TSwap>(is) )
    {
    assert(0 && "Should not happen");
    return false;
    }
  //std::cout << "Tag: " << t << std::endl;
  if( t.GetGroup() != 0x0002 )
    {
    gdcmDebugMacro( "Done reading File Meta Information" );
    is.seekg( start, std::ios::beg );
    return false;
    }
  // Read Value Length
  VL vl;
  if( !vl.template Read<TSwap>(is) )
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
  if( !bv->template Read<TSwap>(is) )
    {
    assert(0 && "Should not happen");
    return false;
    }
  de.SetTag(t);
  de.SetVL(vl);
  de.SetValue(*bv);

  return true;
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
std::istream &FileMetaInformation::Read(std::istream &is)
{
  //ExplicitAttribute<0x0002,0x0000> metagl;
  //metagl.Read(is);

  // TODO: Can now load data from std::ios::cur to std::ios::cur + metagl.GetValue()

  ExplicitDataElement xde;
  Tag gl;
  gl.Read<SwapperNoOp>(is);
  if( gl.GetGroup() != 0x2 ) throw Exception( "INVALID" );
  if( gl.GetElement() != 0x0 ) throw Exception( "INVALID" );
  VR vr;
  vr.Read(is);
  if( vr == VR::INVALID ) throw Exception( "INVALID" );
  if( vr != VR::UL ) throw Exception( "INVALID" );
  // TODO FIXME: I should not do seekg for valid file this is costly
  is.seekg(-6,std::ios::cur);
  xde.Read<SwapperNoOp>(is);
  Insert( xde );
  // See PS 3.5, Data Element Structure With Explicit VR
  while( ReadExplicitDataElement<SwapperNoOp>(is, xde ) )
    {
    Insert( xde );
    }

  // Now is a good time to compute the transfer syntax:
  ComputeDataSetTransferSyntax();

  // we are at the end of the meta file information and before the dataset
  return is;
}

std::istream &FileMetaInformation::ReadCompat(std::istream &is)
{
  // First off save position in case we fail (no File Meta Information)
  // See PS 3.5, Data Element Structure With Explicit VR
  assert( IsEmpty() );
  std::streampos start = is.tellg();
  Tag t;
  t.Read<SwapperNoOp>(is);
  if( t.GetGroup() == 0x0002 )
    {
    // GE_DLX-8-MONO2-PrivateSyntax.dcm is in Implicit...
    return ReadCompatInternal<SwapperNoOp>(is);
    }
  else if( t.GetGroup() == 0x0200 ) // 
    {
    abort();
    return ReadCompatInternal<SwapperDoOp>(is);
    }
  else if( t.GetGroup() == 0x0800 ) // Good ol' ACR NEMA
    {
    is.seekg(-4, std::ios::cur); // Seek back
    //MetaInformationTS = TransferSyntax::Explicit;
    DataSetTS = TransferSyntax::ImplicitVRBigEndianACRNEMA;
    }
  else
    {
    is.seekg(-4, std::ios::cur); // Seek back
    //assert( t.GetElement() == 0x0 );
    throw Exception( "INVALID" ); // Does not start with a 0x0002 group element
    }
  return is;
}

template <typename TSwap>
std::istream &FileMetaInformation::ReadCompatInternal(std::istream &is)
{
  //assert( t.GetGroup() == 0x0002 );
//  if( t.GetGroup() == 0x0002 )
    {
    // Purposely not Re-use ReadVR since we can read VR_END
    char vr_str[2];
    is.read(vr_str, 2);
    if( VR::IsValid(vr_str) )
      {
      MetaInformationTS = TransferSyntax::Explicit;
      // Hourah !
      // Looks like an Explicit File Meta Information Header.
      is.seekg(-6, std::ios::cur); // Seek back
      //is.seekg(start, std::ios::beg); // Seek back
      std::streampos dpos = is.tellg();
      ExplicitDataElement xde;
      while( ReadExplicitDataElement<SwapperNoOp>(is, xde ) )
        {
        //std::cout << xde << std::endl;
        Insert( xde );
        }
      // Now is a good time to find out the dataset transfer syntax
      ComputeDataSetTransferSyntax();
      }
    else
      {
      MetaInformationTS = TransferSyntax::Implicit;
      gdcmDebugMacro( "Not Explicit" );
      // Ok this might be an implicit encoded Meta File Information header...
      // GE_DLX-8-MONO2-PrivateSyntax.dcm
      is.seekg(-6, std::ios::cur); // Seek back
      ImplicitDataElement ide;
      while( ReadImplicitDataElement<SwapperNoOp>(is, ide ) )
        {
        Insert(ide);
        }
      // Now is a good time to find out the dataset transfer syntax
      ComputeDataSetTransferSyntax();
      }
    }
//  else
//    {
//    gdcmDebugMacro( "No File Meta Information. Start with Tag: " << t );
//    is.seekg(-4, std::ios::cur); // Seek back
//    }

  // we are at the end of the meta file information and before the dataset
  return is;
}

//void FileMetaInformation::SetTransferSyntaxType(TS const &ts)
//{
//  //assert( DS == 0 );
//  //InternalTS = ts;
//}

// FIXME: If any boozoo ever write a SQ in the meta header
// we are in bad shape...
void FileMetaInformation::ComputeDataSetTransferSyntax()
{
  const Tag t(0x0002,0x0010);
  const DataElement &de = GetDataElement(t);
  //TransferSyntax::NegociatedType nt = GetNegociatedType();
  std::string ts;
//  if( const ExplicitDataElement *xde = dynamic_cast<const ExplicitDataElement*>(&de) )
    {
    const Value &v = de.GetValue();
    const ByteValue &bv = dynamic_cast<const ByteValue&>(v);
    // Pad string with a \0
    ts = std::string(bv.GetPointer(), bv.GetLength());
    }
//  else if( const ImplicitDataElement *ide = dynamic_cast<const ImplicitDataElement*>(&de) )
//    {
//    const Value &v = ide.GetValue();
//    const ByteValue &bv = dynamic_cast<const ByteValue&>(v);
//    // Pad string with a \0
//    ts = std::string(bv.GetPointer(), bv.GetLength());
//    }
//  else
//    {
//    assert( 0 && "Cannot happen" );
//    }
  gdcmDebugMacro( "TS: " << ts );
  TransferSyntax tst(TransferSyntax::GetTSType(ts.c_str()));
  assert( tst != TransferSyntax::TS_END );
  DataSetTS = tst;

  // postcondition
  DataSetTS.IsValid();
}

MediaStorage FileMetaInformation::GetMediaStorage() const
{
  // D 0002|0002 [UI] [Media Storage SOP Class UID]
  // [1.2.840.10008.5.1.4.1.1.12.1]
  // ==>       [X-Ray Angiographic Image Storage]
  const Tag t(0x0002,0x0002);
  if( !FindDataElement( t ) )
    {
    gdcmDebugMacro( "File Meta information is present but does not"
      " contains " << t );
    return MediaStorage::MS_END;
    }
  const DataElement &de = GetDataElement(t);
  std::string ts;
    {
    const Value &v = de.GetValue();
    const ByteValue &bv = dynamic_cast<const ByteValue&>(v);
    // Pad string with a \0
    ts = std::string(bv.GetPointer(), bv.GetLength());
    }
  // Paranoid check: if last character of a VR=UI is space let's pretend this is a \0
  char &last = ts[ts.size()-1];
  if( last == ' ' )
    {
    gdcmWarningMacro( "Media Storage Class UID: " << ts << " contained a trailing space character" );
    last = '\0';
    }
  gdcmDebugMacro( "TS: " << ts );
  MediaStorage ms = MediaStorage::GetMSType(ts.c_str());
  if( ms == MediaStorage::MS_END )
    {
    gdcmWarningMacro( "Media Storage Class UID: " << ts << " is unknow" );
    }
  return ms;
}

void FileMetaInformation::Default()
{
}

std::ostream &FileMetaInformation::Write(std::ostream &os) const
{
//  if( IsEmpty() )
//  {
//    std::cerr << "IsEmpty" << std::endl;
//    FileMetaInformation fmi;
//    fmi.Default();
//    //fmi.Write(os);
//    IOSerialize<SwapperNoOp>::Write(os,fmi);
//  }
//  else if( IsValid() )
  {
    this->DataSet::Write<ExplicitDataElement,SwapperNoOp>(os);
  }
//  else
//  {
//    abort();
//  }
#if 0
    // At least make sure to have group length
    //if( !DS->FindDataElement( Tag(0x0002, 0x0000) ) )
      {
      //if( DS->GetNegociatedType() == TransferSyntax::Explicit )
        {
        ExplicitDataElement xde( Tag(0x0002, 0x0000), 4, VR::UL );
        SmartPointer<ByteValue> bv = new ByteValue;
        bv->SetLength( 4 );
        uint32_t len = DS->GetLength();
        Element<VR::UL, VM::VM1> el = 
          reinterpret_cast< Element<VR::UL, VM::VM1>& > ( len );
        std::stringstream ss;
        el.Write( ss );
        bv->Read( ss );
        xde.SetValue( *bv );
        // This is the first element, so simply write the element and
        // then start writing the remaining of the File Meta Information
        xde.Write(os);
        }
      }

#endif
  return os;
}

} // end namespace gdcm

