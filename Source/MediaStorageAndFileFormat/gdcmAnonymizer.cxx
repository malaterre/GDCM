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
#include "gdcmAnonymizer.h"
#include "gdcmDicts.h"
#include "gdcmGlobal.h"

namespace gdcm
{
// PS 3.15 - 2008
// Table E.1-1
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
      }
    else if ( dictentry.GetVR() & VR::VRBINARY )
      {
      gdcmWarningMacro( "You need to explicitely specify the length for this type of vr: " << dictentry.GetVR() );
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

bool Anonymizer::BasicApplicationLevelConfidentialityProfile()
{
  //static Tag BasicApplicationLevelConfidentialityProfileAttributes[];
  static const unsigned int deidSize = sizeof(Tag);
  static const unsigned int numDeIds = sizeof(BasicApplicationLevelConfidentialityProfileAttributes) / deidSize;
  static const Tag *start = BasicApplicationLevelConfidentialityProfileAttributes;
  static const Tag *end = start + numDeIds;
  (void)end;

  //return std::binary_search(start, end, tag);
  return true;
}

} // end namespace gdcm

