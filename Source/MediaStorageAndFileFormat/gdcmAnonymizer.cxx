/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmAnonymizer.h"
#include "gdcmGlobal.h"
#include "gdcmStringFilter.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmSwapper.h"
#include "gdcmAES.h"
#include "gdcmUIDGenerator.h"
#include "gdcmAttribute.h"
#include "gdcmDummyValueGenerator.h"
#include "gdcmDicts.h"
#include "gdcmType.h"
#include "gdcmDefs.h"

namespace gdcm
{
// PS 3.15 - 2008
// Table E.1-1
// BALCPA
static Tag BasicApplicationLevelConfidentialityProfileAttributes[] = {
//              Attribute Name                                            Tag
/*              Instance Creator UID                                  */ Tag(0x0008,0x0014),
/*              SOP Instance UID                                      */ Tag(0x0008,0x0018),
/*              Accession Number                                      */ Tag(0x0008,0x0050),
/*              Institution Name                                      */ Tag(0x0008,0x0080),
/*              Institution Address                                   */ Tag(0x0008,0x0081),
/*              Referring Physician's Name                            */ Tag(0x0008,0x0090),
/*              Referring Physician's Address                         */ Tag(0x0008,0x0092),
/*              Referring Physician's Telephone Numbers               */ Tag(0x0008,0x0094),
/*              Station Name                                          */ Tag(0x0008,0x1010),
/*              Study Description                                     */ Tag(0x0008,0x1030),
/*              Series Description                                    */ Tag(0x0008,0x103E),
/*              Institutional Department Name                         */ Tag(0x0008,0x1040),
/*              Physician(s) of Record                                */ Tag(0x0008,0x1048),
/*              Performing Physicians' Name                           */ Tag(0x0008,0x1050),
/*              Name of Physician(s) Reading Study                    */ Tag(0x0008,0x1060),
/*              Operators' Name                                       */ Tag(0x0008,0x1070),
/*              Admitting Diagnoses Description                       */ Tag(0x0008,0x1080),
/*              Referenced SOP Instance UID                           */ Tag(0x0008,0x1155),
/*              Derivation Description                                */ Tag(0x0008,0x2111),
/*              Patient's Name                                        */ Tag(0x0010,0x0010),
/*              Patient ID                                            */ Tag(0x0010,0x0020),
/*              Patient's Birth Date                                  */ Tag(0x0010,0x0030),
/*              Patient's Birth Time                                  */ Tag(0x0010,0x0032),
/*              Patient's Sex                                         */ Tag(0x0010,0x0040),
/*              Other Patient Ids                                     */ Tag(0x0010,0x1000),
/*              Other Patient Names                                   */ Tag(0x0010,0x1001),
/*              Patient's Age                                         */ Tag(0x0010,0x1010),
/*              Patient's Size                                        */ Tag(0x0010,0x1020),
/*              Patient's Weight                                      */ Tag(0x0010,0x1030),
/*              Medical Record Locator                                */ Tag(0x0010,0x1090),
/*              Ethnic Group                                          */ Tag(0x0010,0x2160),
/*              Occupation                                            */ Tag(0x0010,0x2180),
/*              Additional Patient's History                          */ Tag(0x0010,0x21B0),
/*              Patient Comments                                      */ Tag(0x0010,0x4000),
/*              Device Serial Number                                  */ Tag(0x0018,0x1000),
/*              Protocol Name                                         */ Tag(0x0018,0x1030),
/*              Study Instance UID                                    */ Tag(0x0020,0x000D),
/*              Series Instance UID                                   */ Tag(0x0020,0x000E),
/*              Study ID                                              */ Tag(0x0020,0x0010),
/*              Frame of Reference UID                                */ Tag(0x0020,0x0052),
/*              Synchronization Frame of Reference UID                */ Tag(0x0020,0x0200),
/*              Image Comments                                        */ Tag(0x0020,0x4000),
/*              Request Attributes Sequence                           */ Tag(0x0040,0x0275),
/*              UID                                                   */ Tag(0x0040,0xA124),
/*              Content Sequence                                      */ Tag(0x0040,0xA730),
/*              Storage Media File-set UID                            */ Tag(0x0088,0x0140),
/*              Referenced Frame of Reference UID                     */ Tag(0x3006,0x0024),
/*              Related Frame of Reference UID                        */ Tag(0x3006,0x00C2)
};


Anonymizer::~Anonymizer()
{
}

bool Anonymizer::Empty( Tag const &t)
{
  return Replace(t, "", 0);
}

bool Anonymizer::Remove( Tag const &t )
{
  if( t.GetGroup() < 0x0008 ) return false;
  DataSet &ds = F->GetDataSet();
  return ds.Remove( t ) == 1;
}

bool Anonymizer::Replace( Tag const &t, const char *value )
{
  size_t len = 0;
  if( value )
    {
    len = strlen( value );
    }
  return Replace( t, value, len );
}

bool Anonymizer::Replace( Tag const &t, const char *value, VL const & vl )
{
  if( t.GetGroup() < 0x0008 ) return false;
  static const Global &g = GlobalInstance;
  static const Dicts &dicts = g.GetDicts();
  DataSet &ds = F->GetDataSet();
  // Let's do the private tag:
  bool ret = false;
  if ( t.IsPrivate() )
    {
    // Only one operation is allowed: making a private tag empty ...
    if ( vl == 0 )
      {
      if( ds.FindDataElement( t ) )
        {
        DataElement de ( ds.GetDataElement(t) );
        if ( de.GetVR() != VR::INVALID )
          {
          assert( de.GetVR() != VR::SQ );
          }
        de.SetByteValue( "", vl );
        ds.Insert( de );
        ret = true;
        }
      else
        {
        // TODO
        assert( 0 && "TODO" );
        ret = false;
        }
      }
    }
  else
    {
    // Ok this is a public element
    assert( t.IsPublic() );
    const DictEntry &dictentry = dicts.GetDictEntry(t);
    if ( dictentry.GetVR() == VR::INVALID 
      || dictentry.GetVR() == VR::UN 
      || dictentry.GetVR() == VR::SQ
    )
      {
      // Let's give up !
      gdcmWarningMacro( "Cannot process tag: " << t << " with vr: " << dictentry.GetVR() );
      //ret = false;
      }
    else if ( dictentry.GetVR() & VR::VRBINARY )
      {
      if( vl == 0 )
        {
        DataElement de( t );
        if( ds.FindDataElement( t ) )
          {
          de.SetVR( ds.GetDataElement(t).GetVR() );
          }
        else
          {
          de.SetVR( dictentry.GetVR() );
          }
        de.SetByteValue( "", 0 );
        ds.Replace( de );
        ret = true;
        }
      else
        {
        gdcmWarningMacro( "You need to explicitely specify the length for this type of vr: " << dictentry.GetVR() );
        ret = false;
        }
#if 0
      StringFilter sf;
      sf.SetFile( *F );
      std::string s = sf.FromString(t, value, vl);
      DataElement de( t );
      if( ds.FindDataElement( t ) )
        {
        de.SetVR( ds.GetDataElement(t).GetVR() );
        }
      else
        {
        de.SetVR( dictentry.GetVR() );
        }
      de.SetByteValue( s.c_str(), s.size() );
      ds.Replace( de );
      ret = true;
#endif
      }
    else
      {
      // vr from dict seems to be ascii, so it seems resonable to write a ByteValue here:
      assert( dictentry.GetVR() & VR::VRASCII );
      assert( value );
      std::string padded( value, vl );
      // All ASCII VR needs to be padded with a space
      if( vl.IsOdd() )
        {
        if( dictentry.GetVR() == VR::UI )
          {
          // \0 is automatically added when using a ByteValue
          }
        else
          {
          padded += " ";
          }
        }
      // Hum, we could have cases where a public element would not be known, in which case
      // it is a good idea to first check for the VR as found in the file:
      DataElement de( t );
      if( ds.FindDataElement( t ) )
        {
        de.SetVR( ds.GetDataElement(t).GetVR() );
        }
      else
        {
        de.SetVR( dictentry.GetVR() );
        }
      de.SetByteValue( padded.c_str(), padded.size() );
      ds.Replace( de );
      ret = true;
      }
    }
  return ret;
}

bool Anonymizer::RemoveRetired()
{
  static const Global &g = GlobalInstance;
  static const Dicts &dicts = g.GetDicts();
  static const Dict &pubdict = dicts.GetPublicDict();

  DataSet &ds = F->GetDataSet();
  DataSet::Iterator it = ds.Begin();
  for( ; it != ds.End(); )
    {
    const DataElement &de = *it;
    if( de.GetTag().IsPublic() )
      {
      const DictEntry &entry = pubdict.GetDictEntry( de.GetTag() );
      if( entry.GetRetired() )
        {
        // std::set::erase invalidate iterator, so we need to make a copy first:
        DataSet::Iterator dup = it;
        ++it;
        ds.GetDES().erase(dup);
        }
      else
        {
      ++it;
        }
      }
    else
      {
      ++it;
      }
    }

  return true;
}

bool Anonymizer::RemoveGroupLength()
{
  DataSet &ds = F->GetDataSet();
  DataSet::Iterator it = ds.Begin();
  for( ; it != ds.End(); )
    {
    const DataElement &de = *it;
    if( de.GetTag().IsGroupLength() )
      {
      // std::set::erase invalidate iterator, so we need to make a copy first:
      DataSet::Iterator dup = it;
      ++it;
      ds.GetDES().erase(dup);
      }
    else
      {
      ++it;
      }
    }

  return true;
}

bool Anonymizer::RemovePrivateTags()
{
  DataSet &ds = F->GetDataSet();
  DataSet::Iterator it = ds.Begin();
  for( ; it != ds.End(); )
    {
    const DataElement &de = *it;
    if( de.GetTag().IsPrivate() )
      {
      // std::set::erase invalidate iterator, so we need to make a copy first:
      DataSet::Iterator dup = it;
      ++it;
      ds.GetDES().erase(dup);
      }
    else
      {
      ++it;
      }
    }

  return true;
}

bool Anonymizer::BasicApplicationLevelConfidentialityProfile(bool deidentify)
{
  if( deidentify )
    return BasicApplicationLevelConfidentialityProfile1();
  return BasicApplicationLevelConfidentialityProfile2();
}

bool Anonymizer::BasicApplicationLevelConfidentialityProfile1()
{
  static const unsigned int deidSize = sizeof(Tag);
  static const unsigned int numDeIds = sizeof(BasicApplicationLevelConfidentialityProfileAttributes) / deidSize;
  static const Tag *start = BasicApplicationLevelConfidentialityProfileAttributes;
  static const Tag *end = start + numDeIds;

  DataSet &ds = F->GetDataSet();

  // PS 3.15
  // E.1 BASIC APPLICATION LEVEL CONFIDENTIALITY PROFILE
  // An Application may claim conformance to the Basic Application Level Confidentiality Profile as a deidentifier
  // if it protects all Attributes that might be used by unauthorized entities to identify the patient.
  // Protection in this context is defined as the following process:

  // 1. The application may create one or more instances of the Encrypted Attributes Data Set and copy
  // Attributes to be protected into the (single) item of the Modified Attributes Sequence (0400,0550) of
  // one or more of the Encrypted Attributes Data Set instances.

  // Create an instance of the Encrypted Attributes DataSet
  // Modified Attributes Sequence (0400,0550) 1 Sequence of Items containing all Attributes
  // that were removed or replaced by "dummy values" in the main dataset during deidentification
  // of the SOP instance. Upon reversal of the de-identification process, the
  // Attributes are copied back into the main dataset, replacing any dummy values that
  // might have been created. Only a single Item shall be present.

  // Create a Sequence
  SmartPointer<SequenceOfItems> sq = new SequenceOfItems();
  sq->SetLengthToUndefined();

  // Create a *single* item
  Item it;
  it.SetVLToUndefined();
  DataSet &encryptedds = it.GetNestedDataSet();
  for(const Tag *ptr = start ; ptr != end ; ++ptr)
    {
    const Tag& tag = *ptr;
    if( ds.FindDataElement( tag ) )
      encryptedds.Insert( ds.GetDataElement( tag ) );
    }

  sq->AddItem(it);

  DataElement des( Tag(0x0400,0x0550) );
  des.SetVR(VR::SQ);
  des.SetValue(*sq);
  des.SetVLToUndefined();

  std::ostringstream os;
  des.Write<ExplicitDataElement,SwapperNoOp>(os);

  std::string encrypted_str = os.str();
  //std::cout << "Size:" <<  encrypted_str.size() << std::endl;
  size_t encrypted_len = encrypted_str.size();

  // Note: 1. Content encryption may require that the content (the DICOM Data Set) be padded to a
  // multiple of some block size. This shall be performed according to the Content-encryption
  // Process defined in RFC-2630.
  if( encrypted_len % 16 != 0 )
    {
    encrypted_len = ((encrypted_len / 16) + 1) * 16;
    }
  unsigned char *orig = new unsigned char[ encrypted_len ];
  unsigned char *buf = new unsigned char[ encrypted_len ];
  memset( buf, 0, encrypted_len );
  memset( orig, 0, encrypted_len );
  memcpy( orig, encrypted_str.c_str(), encrypted_str.size() );

  const AES& aes = AESKey;
  unsigned char iv[16] = {}; // FIXME ???
  aes.CryptCbc( AES::ENCRYPT, encrypted_len, iv, orig, buf );
  unsigned char key[ 256/ 8] = {};

    {
    // Create a Sequence
    SmartPointer<SequenceOfItems> sq = new SequenceOfItems();
    sq->SetLengthToUndefined();

    // FIXME: should be user configurable:
    TransferSyntax encrypted_ts = TransferSyntax::ImplicitVRLittleEndian;
    // <entry group="0400" element="0510" vr="UI" vm="1" name="Encrypted Content Transfer Syntax UID"/>
    DataElement encrypted_ts_de( Tag(0x400,0x510) );
    encrypted_ts_de.SetByteValue( encrypted_ts.GetString(), strlen(encrypted_ts.GetString()) );
    // <entry group="0400" element="0520" vr="OB" vm="1" name="Encrypted Content"/>
    DataElement encrypted_de( Tag(0x400,0x520) );
    encrypted_de.SetByteValue( (char*)buf, encrypted_len );
    delete[] buf;
    delete[] orig;

    // Create an item
    Item it;
    it.SetVLToUndefined();
    DataSet &nds = it.GetNestedDataSet();
    nds.Insert(encrypted_ts_de);
    nds.Insert(encrypted_de);

    sq->AddItem(it);

    // 4. All instances of the Encrypted Attributes Data Set shall be encoded with a DICOM Transfer Syntax,
    // encrypted, and stored in the dataset to be protected as an Item of the Encrypted Attributes Sequence
    // (0400,0500). The encryption shall be done using RSA [RFC 2313] for the key transport of the
    // content-encryption keys. A de-identifier conforming to this security profile may use either AES or
    // Triple-DES for content-encryption. The AES key length may be any length allowed by the RFCs. The
    // Triple-DES key length is 168 bits as defined by ANSI X9.52. Encoding shall be performed according
    // to the specifications for RSA Key Transport and Triple DES Content Encryption in RFC-3370 and for
    // AES Content Encryption in RFC-3565.

    // 5. No requirements on the size of the asymmetric key pairs used for RSA key transport are defined in
    // this confidentiality scheme. Implementations claiming conformance to the Basic Application Level
    // Confidentiality Profile as a de-identifier shall always protect (e.g. encrypt and replace) the SOP
    // Instance UID (0008,0018) Attribute as well as all references to other SOP Instances, whether
    // contained in the main dataset or embedded in an Item of a Sequence of Items, that could potentially
    // be used by unauthorized entities to identify the patient.

    // Insert sequence into data set
    DataElement des( Tag(0x0400,0x0500) );
    des.SetVR(VR::SQ);
    des.SetValue(*sq);
    des.SetVLToUndefined();

    ds.Insert(des);
    }

  // 2. Each Attribute to be protected shall then either be removed from the dataset, or have its value
  // replaced by a different "replacement value" which does not allow identification of the patient.

  for(const Tag *ptr = start ; ptr != end ; ++ptr)
    {
    const Tag& tag = *ptr;
    // FIXME Type 1 !
    if( ds.FindDataElement( tag ) ) BALCPProtect(tag);
    }

  // Group Length are removed since PS 3.3-2008
  RemoveGroupLength();

  // 3. At the discretion of the de-identifier, Attributes may be added to the dataset to be protected.
  // ...

  // 6. The attribute Patient Identity Removed (0012,0062) shall be replaced or added to the dataset with a
  // value of YES, and a value inserted in De-identification Method (0012,0063) or De-identification
  // Method Code Sequence (0012,0064).
  Replace( Tag(0x0012,0x0062), "YES");
  Replace( Tag(0x0012,0x0063), "BASIC APPLICATION LEVEL CONFIDENTIALITY PROFILE");


  // Since the de-identified SOP Instance is a significantly altered version of the original Data Set, it is
  // a new SOP Instance, with a SOP Instance UID that differs from the original Data Set.
  UIDGenerator uid;
  Replace( Tag(0x008,0x0018), uid.Generate() );

  return true;
}


bool IsVRUI(Tag const &tag)
{
  static const Global &g = GlobalInstance;
  static const Dicts &dicts = g.GetDicts();
  const DictEntry &dictentry = dicts.GetDictEntry(tag);
  if( dictentry.GetVR() == VR::UI ) return true;
  //if( tag == Tag(0x0020,0x000d)   // Study Instance UID : UI
  // || tag == Tag(0x0020,0x0052)   // 
  // || tag == Tag(0x0020,0x000e) ) // Series Instance UID : UI
  //  {
  //  return true;
  //  }
  return false;
}

bool Anonymizer::CanEmptyTag(Tag const &tag)
{
  static const Global &g = GlobalInstance;
  static const Dicts &dicts = g.GetDicts();
  static const Defs &defs = g.GetDefs();
  DataSet &ds = F->GetDataSet();
  Type t = defs.GetTypeFromTag(ds, tag);
  gdcmDebugMacro( "Type for tag=" << tag << " is " << t );

  //assert( t != Type::UNKNOWN );

  if( t == Type::T1 || t == Type::T1C )
    {
    return false;
    }
  // What if we are dealing with a Standard Extended SOP class
  // eg. gdcmData/05115014-mr-siemens-avanto-syngo-with-palette-icone.dcm
  // where Attribute is not present in standard DICOM IOD - (0x0088,0x0140) UI Storage Media FileSet UID
  if( t == Type::UNKNOWN )
    {
    return true;
    }
  
  // This is a Type 3 attribute but with VR=UI
  // <entry group="0008" element="0014" vr="UI" vm="1" name="Instance Creator UID"/>
  //assert( dicts.GetDictEntry(tag).GetVR() != VR::UI );
  return true;
}

bool Anonymizer::BALCPProtect(Tag const & tag)
{
  typedef std::pair< Tag, std::string > TagValueKey;
  typedef std::map< TagValueKey, std::string > DummyMap;
  static DummyMap dummymap;
  gdcm::UIDGenerator uid;

  DataSet &ds = F->GetDataSet();

  bool canempty = CanEmptyTag( tag );
  if( !canempty )
    {
    TagValueKey tvk;
    tvk.first = tag;
    DataElement copy = ds.GetDataElement( tag );
    // gdcmData/LEADTOOLS_FLOWERS-16-MONO2-JpegLossless.dcm
    // has an empty 0008,0018 attribute, let's try to handle that:
    if( !copy.IsEmpty() )
      {
      if( ByteValue *bv = copy.GetByteValue() )
        {
        tvk.second = std::string( bv->GetPointer(), bv->GetLength() );
        }
      }
    assert( dummymap.count( tvk ) == 0 || dummymap.count( tvk ) == 1 );
    if( dummymap.count( tvk ) == 0 )
      {
      // Generate a new (single) dummy value:
      if( IsVRUI( tag ) )
        {
        dummymap[ tvk ] = uid.Generate();
        }
      else
        {
        dummymap[ tvk ] = DummyValueGenerator::Generate( tvk.second.c_str() );
        }
      }
    std::string &v = dummymap[ tvk ];
    copy.SetByteValue( v.c_str(), v.size() );
    ds.Replace( copy );
    }
  else
    {
    Empty( tag );
    }
  return true;
}

void Anonymizer::SetAESKey(AES const &aes)
{
  AESKey = aes;
}

const AES &Anonymizer::GetAESKey() const
{
  return AESKey;
}

bool Anonymizer::BasicApplicationLevelConfidentialityProfile2()
{
  // 1. The application shall decrypt, using its recipient key, one instance of the Encrypted Content
  // (0400,0520) Attribute within the Encrypted Attributes Sequence (0400,0500) and decode the resulting
  // block of bytes into a DICOM dataset using the Transfer Syntax specified in the Encrypted Content
  // Transfer Syntax UID (0400,0510). Re-identifiers claiming conformance to this profile shall be capable
  // of decrypting the Encrypted Content using either AES or Triple-DES in all possible key lengths
  // specified in this profile
  const AES& aes = AESKey;

  DataSet &ds = F->GetDataSet();
  const DataElement &EncryptedAttributesSequence = ds.GetDataElement( Tag(0x0400,0x0500) );
  const SequenceOfItems *sq = EncryptedAttributesSequence.GetSequenceOfItems();
  const Item &item = sq->GetItem(1);
  const DataSet &nds = item.GetNestedDataSet();
  const DataElement &EncryptedContent = nds.GetDataElement( Tag(0x0400,0x0520) );
  const ByteValue *bv = EncryptedContent.GetByteValue();
  
  size_t encrypted_len = bv->GetLength();
  assert( bv->GetLength() % 16 == 0 );
  unsigned char *orig = new unsigned char[ bv->GetLength() ];
  unsigned char *buf = new unsigned char[ bv->GetLength() ];
  memcpy(orig, bv->GetPointer(), encrypted_len );
  unsigned char iv[16] = {}; // FIXME ???
  aes.CryptCbc( AES::DECRYPT, encrypted_len, iv, orig, buf );

  std::stringstream ss;
  ss.str( std::string((char*)buf, encrypted_len) );
  DataSet des;
  DataElement dummy;
  try
    {
    dummy.Read<ExplicitDataElement, SwapperNoOp>(ss);
    }
  //catch( std::Exception  & e)
  catch( ... )
    {
  delete[] buf;
  delete[] orig;

    return false;
    }
  des.Insert( dummy );
  //des.Read<ExplicitDataElement,SwapperNoOp>(ss);
  //des.ReadNested<ExplicitDataElement,SwapperNoOp>(ss);

  //std::cout << des << std::endl; 
  //std::cout << dummy << std::endl; 
  //std::cout << ss.tellg() << std::endl; 
  assert( ss.tellg() <= encrypted_len );
  // TODO: check that for i = ss.tellg() to encrypted_len, ss[i] == 0
  delete[] buf;
  delete[] orig;

  // 2. The application shall move all Attributes contained in the single item of the Modified Attributes
  // Sequence (0400,0550) of the decoded dataset into the main dataset, replacing¿dummy value¿
  // Attributes that may be present in the main dataset.
  //assert( dummy.GetVR() == VR::SQ );
{
  const SequenceOfItems *sqi = dummy.GetSequenceOfItems();
  assert( sqi );
  Item const & item = sqi->GetItem( 1 );
  const DataSet &nds = item.GetNestedDataSet();
  DataSet::ConstIterator it = nds.Begin();
  for( ; it !=  nds.End(); ++it )
    {
    ds.Replace( *it );
    }
}

  // 3. The attribute Patient Identity Removed (0012,0062) shall be replaced or added to the dataset with a
  // value of NO and De-identification Method (0012,0063) and De-identification Method Code Sequence
  // (0012,0064) shall be removed.
  //Replace( Tag(0x0012,0x0062), "NO");
  Remove( Tag(0x0012,0x0062) );
  Remove( Tag(0x0012,0x0063) );

  Remove( Tag(0x0400,0x0500) ); // ??

  return true;
}

} // end namespace gdcm

