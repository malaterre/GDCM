/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
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
#include "gdcmDataSetHelper.h"
#include "gdcmUIDGenerator.h"
#include "gdcmAttribute.h"
#include "gdcmDummyValueGenerator.h"
#include "gdcmDicts.h"
#include "gdcmType.h"
#include "gdcmDefs.h"
#include "gdcmCryptographicMessageSyntax.h"
#include "gdcmEvent.h"
#include "gdcmAnonymizeEvent.h"

namespace gdcm
{
// PS 3.15 - 2008
// Table E.1-1
// BALCPA
static Tag BasicApplicationLevelConfidentialityProfileAttributes[] = {
//    Attribute Name                                Tag
/*    Accession Number                                                      */ Tag(0x0008,0x0050),
/*    Acquisition Comments                                                  */ Tag(0x0018,0x4000),
/*    Acquisition Context Sequence                                          */ Tag(0x0040,0x0555),
/*    Acquisition Date                                                      */ Tag(0x0008,0x0022),
/*    Acquisition DateTime                                                  */ Tag(0x0008,0x002A),
/*    Acquisition Device Processing Description                             */ Tag(0x0018,0x1400),
/*    Acquisition Protocol Description                                      */ Tag(0x0018,0x9424),
/*    Acquisition Time                                                      */ Tag(0x0008,0x0032),
/*    Actual Human Performers Sequence                                      */ Tag(0x0040,0x4035),
/*    Additional Patient's History                                          */ Tag(0x0010,0x21B0),
/*    Address (Trial)                                                       */ Tag(0x0040,0xA353),
/*    Admission ID                                                          */ Tag(0x0038,0x0010),
/*    Admitting Date                                                        */ Tag(0x0038,0x0020),
/*    Admitting Diagnoses Code Sequence                                     */ Tag(0x0008,0x1084),
/*    Admitting Diagnoses Description                                       */ Tag(0x0008,0x1080),
/*    Admitting Time                                                        */ Tag(0x0038,0x0021),
/*    Affected SOP Instance UID                                             */ Tag(0x0000,0x1000),
/*    Allergies                                                             */ Tag(0x0010,0x2110),
/*    Arbitrary                                                             */ Tag(0x4000,0x0010),
/*    Author Observer Sequence                                              */ Tag(0x0040,0xA078),
/*    Branch of Service                                                     */ Tag(0x0010,0x1081),
/*    Cassette ID                                                           */ Tag(0x0018,0x1007),
/*    Comments on the Performed Procedure Step                              */ Tag(0x0040,0x0280),
/*    Concatenation UID                                                     */ Tag(0x0020,0x9161),
/*    Confidentiality Constraint on Patient Data Description                */ Tag(0x0040,0x3001),
/*    Consulting Physician Identification Sequence                          */ Tag(0x0008,0x009D),
/*    Consulting Physician's Name                                           */ Tag(0x0008,0x009C),
/*    Content Creator's Name                                                */ Tag(0x0070,0x0084),
/*    Content Creator's Identification Code Sequence                        */ Tag(0x0070,0x0086),
/*    Content Date                                                          */ Tag(0x0008,0x0023),
/*    Content Sequence                                                      */ Tag(0x0040,0xA730),
/*    Content Time                                                          */ Tag(0x0008,0x0033),
/*    Context Group Extension Creator UID                                   */ Tag(0x0008,0x010D),
/*    Contrast Bolus Agent                                                  */ Tag(0x0018,0x0010),
/*    Contribution Description                                              */ Tag(0x0018,0xA003),
/*    Country of Residence                                                  */ Tag(0x0010,0x2150),
/*    Creator Version UID                                                   */ Tag(0x0008,0x9123),
/*    Current Observer (Trial)                                              */ Tag(0x0040,0xA307),
/*    Current Patient Location                                              */ Tag(0x0038,0x0300),
/*    Curve Data                                                               Tag(0x50xx,0xxxxx), */
/*    Curve Date                                                            */ Tag(0x0008,0x0025),
/*    Curve Time                                                            */ Tag(0x0008,0x0035),
/*    Custodial Organization Sequence                                       */ Tag(0x0040,0xA07C),
/*    Data Set Trailing Padding                                             */ Tag(0xFFFC,0xFFFC),
/*    Derivation Description                                                */ Tag(0x0008,0x2111),
/*    Detector ID                                                           */ Tag(0x0018,0x700A),
/*    Device Serial Number                                                  */ Tag(0x0018,0x1000),
/*    Device UID                                                            */ Tag(0x0018,0x1002),
/*    Digital Signature UID                                                 */ Tag(0x0400,0x0100),
/*    Digital Signatures Sequence                                           */ Tag(0xFFFA,0xFFFA),
/*    Dimension Organization UID                                            */ Tag(0x0020,0x9164),
/*    Discharge Diagnosis Description                                       */ Tag(0x0038,0x0040),
/*    Distribution Address                                                  */ Tag(0x4008,0x011A),
/*    Distribution Name                                                     */ Tag(0x4008,0x0119),
/*    Dose Reference UID                                                    */ Tag(0x300A,0x0013),
/*    End Acquisition DateTime                                              */ Tag(0x0018,0x9517),
/*    Ethnic Group                                                          */ Tag(0x0010,0x2160),
/*    Expected Completion DateTime                                          */ Tag(0x0040,0x4011),
/*    Failed SOP Instance UID List                                          */ Tag(0x0008,0x0058),
/*    Fiducial UID                                                          */ Tag(0x0070,0x031A),
/*    Filler Order Number / Imaging Service Request                         */ Tag(0x0040,0x2017),
/*    Frame Comments                                                        */ Tag(0x0020,0x9158),
/*    Frame of Reference UID                                                */ Tag(0x0020,0x0052),
/*    Gantry ID                                                             */ Tag(0x0018,0x1008),
/*    Generator ID                                                          */ Tag(0x0018,0x1005),
/*    Graphic Annotation Sequence                                           */ Tag(0x0070,0x0001),
/*    Human Performers Name                                                 */ Tag(0x0040,0x4037),
/*    Human Performers Organization                                         */ Tag(0x0040,0x4036),
/*    Icon Image Sequence(see Note 12)                                      */ Tag(0x0088,0x0200),
/*    Identifying Comments                                                  */ Tag(0x0008,0x4000),
/*    Image Comments                                                        */ Tag(0x0020,0x4000),
/*    Image Presentation Comments                                           */ Tag(0x0028,0x4000),
/*    Imaging Service Request Comments                                      */ Tag(0x0040,0x2400),
/*    Impressions                                                           */ Tag(0x4008,0x0300),
/*    Instance Coercion DateTime                                            */ Tag(0x0008,0x0015),
/*    Instance Creator UID                                                  */ Tag(0x0008,0x0014),
/*    Institution Address                                                   */ Tag(0x0008,0x0081),
/*    Institution Code Sequence                                             */ Tag(0x0008,0x0082),
/*    Institution Name                                                      */ Tag(0x0008,0x0080),
/*    Institutional Department Name                                         */ Tag(0x0008,0x1040),
/*    Insurance Plan Identification                                         */ Tag(0x0010,0x1050),
/*    Intended Recipients of Results Identification Sequence                */ Tag(0x0040,0x1011),
/*    Interpretation Approver Sequence                                      */ Tag(0x4008,0x0111),
/*    Interpretation Author                                                 */ Tag(0x4008,0x010C),
/*    Interpretation Diagnosis Description                                  */ Tag(0x4008,0x0115),
/*    Interpretation ID Issuer                                              */ Tag(0x4008,0x0202),
/*    Interpretation Recorder                                               */ Tag(0x4008,0x0102),
/*    Interpretation Text                                                   */ Tag(0x4008,0x010B),
/*    Interpretation Transcriber                                            */ Tag(0x4008,0x010A),
/*    Irradiation Event UID                                                 */ Tag(0x0008,0x3010),
/*    Issuer of Admission ID                                                */ Tag(0x0038,0x0011),
/*    Issuer of Patient ID                                                  */ Tag(0x0010,0x0021),
/*    Issuer of Service Episode ID                                          */ Tag(0x0038,0x0061),
/*    Large Palette Color Lookup Table UID                                  */ Tag(0x0028,0x1214),
/*    Last Menstrual Date                                                   */ Tag(0x0010,0x21D0),
/*    MAC                                                                   */ Tag(0x0400,0x0404),
/*    Media Storage SOP Instance UID                                        */ Tag(0x0002,0x0003),
/*    Medical Alerts                                                        */ Tag(0x0010,0x2000),
/*    Medical Record Locator                                                */ Tag(0x0010,0x1090),
/*    Military Rank                                                         */ Tag(0x0010,0x1080),
/*    Modified Attributes Sequence                                          */ Tag(0x0400,0x0550),
/*    Modified Image Description                                            */ Tag(0x0020,0x3406),
/*    Modifying Device ID                                                   */ Tag(0x0020,0x3401),
/*    Modifying Device Manufacturer                                         */ Tag(0x0020,0x3404),
/*    Name of Physician(s) Reading Study                                    */ Tag(0x0008,0x1060),
/*    Names of Intended Recipient of Results                                */ Tag(0x0040,0x1010),
/*    Observation Date (Trial)                                              */ Tag(0x0040,0xA192),
/*    Observation Subject UID (Trial)                                       */ Tag(0x0040,0xA402),
/*    Observation Time (Trial)                                              */ Tag(0x0040,0xA193),
/*    Observation UID                                                       */ Tag(0x0040,0xA171),
/*    Occupation                                                            */ Tag(0x0010,0x2180),
/*    Operators' Identification Sequence                                    */ Tag(0x0008,0x1072),
/*    Operators' Name                                                       */ Tag(0x0008,0x1070),
/*    Original Attributes Sequence                                          */ Tag(0x0400,0x0561),
/*    Order Callback Phone Number                                           */ Tag(0x0040,0x2010),
/*    Order Callback Telecom Information                                    */ Tag(0x0040,0x2011),
/*    Order Entered By                                                      */ Tag(0x0040,0x2008),
/*    Order Enterer Location                                                */ Tag(0x0040,0x2009),
/*    Other Patient IDs                                                     */ Tag(0x0010,0x1000),
/*    Other Patient IDs Sequence                                            */ Tag(0x0010,0x1002),
/*    Other Patient Names                                                   */ Tag(0x0010,0x1001),

/*    Overlay Comments                                                       Tag(0x60xx,0x4000), */
/*    Overlay Data                                                           Tag(0x60xx,0x3000), */

/*    Overlay Date                                                          */ Tag(0x0008,0x0024),
/*    Overlay Time                                                          */ Tag(0x0008,0x0034),
/*    Palette Color Lookup Table UID                                        */ Tag(0x0028,0x1199),
/*    Participant Sequence                                                  */ Tag(0x0040,0xA07A),
/*    Patient Address                                                       */ Tag(0x0010,0x1040),
/*    Patient Comments                                                      */ Tag(0x0010,0x4000),
/*    Patient ID                                                            */ Tag(0x0010,0x0020),
/*    Patient Sex Neutered                                                  */ Tag(0x0010,0x2203),
/*    Patient State                                                         */ Tag(0x0038,0x0500),
/*    Patient Transport Arrangements                                        */ Tag(0x0040,0x1004),
/*    Patient's Age                                                         */ Tag(0x0010,0x1010),
/*    Patient's Birth Date                                                  */ Tag(0x0010,0x0030),
/*    Patient's Birth Name                                                  */ Tag(0x0010,0x1005),
/*    Patient's Birth Time                                                  */ Tag(0x0010,0x0032),
/*    Patient's Institution Residence                                       */ Tag(0x0038,0x0400),
/*    Patient's Insurance Plan Code Sequence                                */ Tag(0x0010,0x0050),
/*    Patient's Mother's Birth Name                                         */ Tag(0x0010,0x1060),
/*    Patient's Name                                                        */ Tag(0x0010,0x0010),
/*    Patient's Primary Language Code Sequence                              */ Tag(0x0010,0x0101),
/*    Patient's Primary Language Modifier Code Sequence                     */ Tag(0x0010,0x0102),
/*    Patient's Religious Preference                                        */ Tag(0x0010,0x21F0),
/*    Patient's Sex                                                         */ Tag(0x0010,0x0040),
/*    Patient's Size                                                        */ Tag(0x0010,0x1020),
/*    Patient's Telecom Information                                         */ Tag(0x0010,0x2155),
/*    Patient's Telephone Numbers                                           */ Tag(0x0010,0x2154),
/*    Patient's Weight                                                      */ Tag(0x0010,0x1030),
/*    Performed Location                                                    */ Tag(0x0040,0x0243),
/*    Performed Procedure Step Description                                  */ Tag(0x0040,0x0254),
/*    Performed Procedure Step End Date                                     */ Tag(0x0040,0x0250),
/*    Performed Procedure Step End DateTime                                 */ Tag(0x0040,0x4051),
/*    Performed Procedure Step End Time                                     */ Tag(0x0040,0x0251),
/*    Performed Procedure Step ID                                           */ Tag(0x0040,0x0253),
/*    Performed Procedure Step Start Date                                   */ Tag(0x0040,0x0244),
/*    Performed Procedure Step Start DateTime                               */ Tag(0x0040,0x4050),
/*    Performed Procedure Step Start Time                                   */ Tag(0x0040,0x0245),
/*    Performed Station AE Title                                            */ Tag(0x0040,0x0241),
/*    Performed Station Geographic Location Code Sequence                   */ Tag(0x0040,0x4030),
/*    Performed Station Name                                                */ Tag(0x0040,0x0242),
/*    Performed Station Name Code Sequence                                  */ Tag(0x0040,0x4028),
/*    Performing Physician Identification Sequence                          */ Tag(0x0008,0x1052),
/*    Performing Physicians' Name                                           */ Tag(0x0008,0x1050),
/*    Person Address                                                        */ Tag(0x0040,0x1102),
/*    Person Identification Code Sequence                                   */ Tag(0x0040,0x1101),
/*    Person Name                                                           */ Tag(0x0040,0xA123),
/*    Person's Telecom Information                                          */ Tag(0x0040,0x1104),
/*    Person's Telephone Numbers                                            */ Tag(0x0040,0x1103),
/*    Physician Approving Interpretation                                    */ Tag(0x4008,0x0114),
/*    Physician(s) Reading Study Identification Sequence                    */ Tag(0x0008,0x1062),
/*    Physician(s) of Record                                                */ Tag(0x0008,0x1048),
/*    Physician(s) of Record Identification Sequence                        */ Tag(0x0008,0x1049),
/*    Placer Order Number / Imaging Service Request                         */ Tag(0x0040,0x2016),
/*    Plate ID                                                              */ Tag(0x0018,0x1004),
/*    Pre-Medication                                                        */ Tag(0x0040,0x0012),
/*    Pregnancy Status                                                      */ Tag(0x0010,0x21C0),
/*    Presentation Display Collection UID                                   */ Tag(0x0070,0x1101),
/*    Presentation Sequence Collection UID                                  */ Tag(0x0070,0x1102),
/*    Procedure Step Cancellation DateTime                                  */ Tag(0x0040,0x4052),
/*    Protocol Name                                                         */ Tag(0x0018,0x1030),
/*    Reason for Omission Description                                       */ Tag(0x300C,0x0113),
/*    Reason for the Imaging Service Request                                */ Tag(0x0040,0x2001),
/*    Reason for Study                                                      */ Tag(0x0032,0x1030),
/*    Referenced Digital Signature Sequence                                 */ Tag(0x0400,0x0402),
/*    Referenced Frame of Reference UID                                     */ Tag(0x3006,0x0024),
/*    Referenced General Purpose Scheduled Procedure Step Transaction UID   */ Tag(0x0040,0x4023),
/*    Referenced Image Sequence                                             */ Tag(0x0008,0x1140),
/*    Referenced Observation UID (Trial)                                    */ Tag(0x0040,0xA172),
/*    Referenced Patient Alias Sequence                                     */ Tag(0x0038,0x0004),
/*    Referenced Patient Photo Sequence                                     */ Tag(0x0010,0x1100),
/*    Referenced Patient Sequence                                           */ Tag(0x0008,0x1120),
/*    Referenced Performed Procedure Step Sequence                          */ Tag(0x0008,0x1111),
/*    Referenced SOP Instance MAC Sequence                                  */ Tag(0x0400,0x0403),
/*    Referenced SOP Instance UID                                           */ Tag(0x0008,0x1155),
/*    Referenced SOP Instance UID in File                                   */ Tag(0x0004,0x1511),
/*    Referenced Study Sequence                                             */ Tag(0x0008,0x1110),
/*    Referring Physician's Address                                         */ Tag(0x0008,0x0092),
/*    Referring Physician Identification Sequence                           */ Tag(0x0008,0x0096),
/*    Referring Physician's Name                                            */ Tag(0x0008,0x0090),
/*    Referring Physician's Telephone Numbers                               */ Tag(0x0008,0x0094),
/*    Region of Residence                                                   */ Tag(0x0010,0x2152),
/*    Related Frame of Reference UID                                        */ Tag(0x3006,0x00C2),
/*    Request Attributes Sequence                                           */ Tag(0x0040,0x0275),
/*    Requested Contrast Agent                                              */ Tag(0x0032,0x1070),
/*    Requested Procedure Comments                                          */ Tag(0x0040,0x1400),
/*    Requested Procedure Description                                       */ Tag(0x0032,0x1060),
/*    Requested Procedure ID                                                */ Tag(0x0040,0x1001),
/*    Requested Procedure Location                                          */ Tag(0x0040,0x1005),
/*    Requested SOP Instance UID                                            */ Tag(0x0000,0x1001),
/*    Requesting Physician                                                  */ Tag(0x0032,0x1032),
/*    Requesting Service                                                    */ Tag(0x0032,0x1033),
/*    Responsible Organization                                              */ Tag(0x0010,0x2299),
/*    Responsible Person                                                    */ Tag(0x0010,0x2297),
/*    Results Comments                                                      */ Tag(0x4008,0x4000),
/*    Results Distribution List Sequence                                    */ Tag(0x4008,0x0118),
/*    Results ID Issuer                                                     */ Tag(0x4008,0x0042),
/*    Reviewer Name                                                         */ Tag(0x300E,0x0008),
/*    Scheduled Human Performers Sequence                                   */ Tag(0x0040,0x4034),
/*    Scheduled Patient Institution Residence                               */ Tag(0x0038,0x001E),
/*    Scheduled Performing Physician Identification Sequence                */ Tag(0x0040,0x000B),
/*    Scheduled Performing Physician Name                                   */ Tag(0x0040,0x0006),
/*    Scheduled Procedure Step End Date                                     */ Tag(0x0040,0x0004),
/*    Scheduled Procedure Step End Time                                     */ Tag(0x0040,0x0005),
/*    Scheduled Procedure Step Description                                  */ Tag(0x0040,0x0007),
/*    Scheduled Procedure Step Location                                     */ Tag(0x0040,0x0011),
/*    Scheduled Procedure Step Modification DateTime                        */ Tag(0x0040,0x4010),
/*    Scheduled Procedure Step Start Date                                   */ Tag(0x0040,0x0002),
/*    Scheduled Procedure Step Start DateTime                               */ Tag(0x0040,0x4005),
/*    Scheduled Procedure Step Start Time                                   */ Tag(0x0040,0x0003),
/*    Scheduled Station AE Title                                            */ Tag(0x0040,0x0001),
/*    Scheduled Station Geographic Location Code Sequence                   */ Tag(0x0040,0x4027),
/*    Scheduled Station Name                                                */ Tag(0x0040,0x0010),
/*    Scheduled Station Name Code Sequence                                  */ Tag(0x0040,0x4025),
/*    Scheduled Study Location                                              */ Tag(0x0032,0x1020),
/*    Scheduled Study Location AE Title                                     */ Tag(0x0032,0x1021),
/*    Series Date                                                           */ Tag(0x0008,0x0021),
/*    Series Description                                                    */ Tag(0x0008,0x103E),
/*    Series Instance UID                                                   */ Tag(0x0020,0x000E),
/*    Series Time                                                           */ Tag(0x0008,0x0031),
/*    Service Episode Description                                           */ Tag(0x0038,0x0062),
/*    Service Episode ID                                                    */ Tag(0x0038,0x0060),
/*    Smoking Status                                                        */ Tag(0x0010,0x21A0),
/*    SOP Instance UID                                                      */ Tag(0x0008,0x0018),
/*    Source Image Sequence                                                 */ Tag(0x0008,0x2112),
/*    Source Serial Number                                                  */ Tag(0x3008,0x0105),
/*    Special Needs                                                         */ Tag(0x0038,0x0050),
/*    Start Acquisition DateTime                                            */ Tag(0x0018,0x9516),
/*    Station Name                                                          */ Tag(0x0008,0x1010),
/*    Storage Media File-set UID                                            */ Tag(0x0088,0x0140),
/*    Study Comments                                                        */ Tag(0x0032,0x4000),
/*    Study Date                                                            */ Tag(0x0008,0x0020),
/*    Study Description                                                     */ Tag(0x0008,0x1030),
/*    Study ID                                                              */ Tag(0x0020,0x0010),
/*    Study ID Issuer                                                       */ Tag(0x0032,0x0012),
/*    Study Instance UID                                                    */ Tag(0x0020,0x000D),
/*    Study Time                                                            */ Tag(0x0008,0x0030),
/*    Synchronization Frame of Reference UID                                */ Tag(0x0020,0x0200),
/*    Target UID                                                            */ Tag(0x0018,0x2042),
/*    Telephone Number (Trial)                                              */ Tag(0x0040,0xA354),
/*    Template Extension Creator UID                                        */ Tag(0x0040,0xDB0D),
/*    Template Extension Organization UID                                   */ Tag(0x0040,0xDB0C),
/*    Text Comments                                                         */ Tag(0x4000,0x4000),
/*    Text String                                                           */ Tag(0x2030,0x0020),
/*    Timezone Offset From UTC                                              */ Tag(0x0008,0x0201),
/*    Topic Author                                                          */ Tag(0x0088,0x0910),
/*    Topic Keywords                                                        */ Tag(0x0088,0x0912),
/*    Topic Subject                                                         */ Tag(0x0088,0x0906),
/*    Topic Title                                                           */ Tag(0x0088,0x0904),
/*    Tracking UID                                                          */ Tag(0x0062,0x0021),
/*    Transaction UID                                                       */ Tag(0x0008,0x1195),
/*    UID                                                                   */ Tag(0x0040,0xA124),
/*    Verbal Source (Trial)                                                 */ Tag(0x0040,0xA352),
/*    Verbal Source Identifier Code Sequence (Trial)                        */ Tag(0x0040,0xA358),
/*    Verifying Observer Identification Code Sequence                       */ Tag(0x0040,0xA088),
/*    Verifying Observer Name                                               */ Tag(0x0040,0xA075),
/*    Verifying Observer Sequence                                           */ Tag(0x0040,0xA073),
/*    Verifying Organization                                                */ Tag(0x0040,0xA027),
/*    Visit Comments                                                        */ Tag(0x0038,0x4000)
};


Anonymizer::~Anonymizer()
{
}

bool Anonymizer::Empty( Tag const &t)
{
  // There is a secret code path to make it work for VR::SQ since operation is just 'make empty'
  return Replace(t, "", 0);
}

bool Anonymizer::Remove( Tag const &t )
{
  DataSet &ds = F->GetDataSet();
  if(ds.FindDataElement(t))
    return ds.Remove( t ) == 1;
  else
    return true;
}

bool Anonymizer::Replace( Tag const &t, const char *value )
{
  VL::Type len = 0; //to avoid the size_t warning on 64 bit windows
  if( value )
    {
    len = (VL::Type)strlen( value );//strlen returns size_t, but it should be VL::Type
    //strlen shouldn't be more than 4gb anyway
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
          if( de.GetVR() == VR::SQ )
            {
            if( vl == 0 && value && *value == 0 )
              {
              DataElement de2( t );
              de2.SetVR( VR::SQ );
              ds.Replace( de2 );
              return true;
              }
            gdcmDebugMacro( "Cannot replace a VR:SQ" );
            return false;
            }
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
      // Make the VR::SQ empty
      if( dictentry.GetVR() == VR::SQ && vl == 0 && value && *value == 0 )
        {
        DataElement de( t );
        de.SetVR( VR::SQ );
        //de.SetByteValue( "", 0 );
        ds.Replace( de );
        }
      else
        {
        // Let's give up !
        gdcmWarningMacro( "Cannot process tag: " << t << " with vr: " << dictentry.GetVR() );
        }
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
        gdcmWarningMacro( "You need to explicitly specify the length for this type of vr: " << dictentry.GetVR() );
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
      if( value )
        {
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
        const VL::Type paddedSize = (VL::Type) padded.size();//casting to avoid size_t warning on 64
        de.SetByteValue( padded.c_str(), paddedSize );
        ds.Replace( de );
        ret = true;
        }
      }
    }
  return ret;
}

static bool Anonymizer_RemoveRetired(File const &file, DataSet &ds)
{
  static const Global &g = GlobalInstance;
  static const Dicts &dicts = g.GetDicts();
  static const Dict &pubdict = dicts.GetPublicDict();
  DataSet::Iterator it = ds.Begin();
  for( ; it != ds.End(); )
    {
    const DataElement &de1 = *it;
    // std::set::erase invalidate iterator, so we need to make a copy first:
    DataSet::Iterator dup = it;
    ++it;
    if( de1.GetTag().IsPublic() )
      {
      const DictEntry &entry = pubdict.GetDictEntry( de1.GetTag() );
      if( entry.GetRetired() )
        {
        ds.GetDES().erase(dup);
        }
      }
    else
      {
      const DataElement &de = *dup;
      VR vr = DataSetHelper::ComputeVR(file, ds, de.GetTag() );
      if( vr.Compatible(VR::SQ) )
        {
        SmartPointer<SequenceOfItems> sq = de.GetValueAsSQ();
        if( sq )
          {
          SequenceOfItems::SizeType n = sq->GetNumberOfItems();
          for( SequenceOfItems::SizeType i = 1; i <= n; i++) // item starts at 1, not 0
            {
            Item &item = sq->GetItem( i );
            DataSet &nested = item.GetNestedDataSet();
            Anonymizer_RemoveRetired( file, nested );
            }
          DataElement de_dup = *dup;
          de_dup.SetValue( *sq );
          de_dup.SetVLToUndefined(); // FIXME
          ds.Replace( de_dup );
          }
        }
      }
    }
  return true;
}

bool Anonymizer::RemoveRetired()
{
  DataSet &ds = F->GetDataSet();
  return Anonymizer_RemoveRetired(*F, ds);
}

static bool Anonymizer_RemoveGroupLength(File const &file, DataSet &ds)
{
  DataSet::Iterator it = ds.Begin();
  for( ; it != ds.End(); )
    {
    const DataElement &de1 = *it;
    // std::set::erase invalidate iterator, so we need to make a copy first:
    DataSet::Iterator dup = it;
    ++it;
    if( de1.GetTag().IsGroupLength() )
      {
      ds.GetDES().erase(dup);
      }
    else
      {
      const DataElement &de = *dup;
      VR vr = DataSetHelper::ComputeVR(file, ds, de.GetTag() );
      if( vr.Compatible(VR::SQ) )
        {
        SmartPointer<SequenceOfItems> sq = de.GetValueAsSQ();
        if( sq )
          {
          SequenceOfItems::SizeType n = sq->GetNumberOfItems();
          for( SequenceOfItems::SizeType i = 1; i <= n; i++) // item starts at 1, not 0
            {
            Item &item = sq->GetItem( i );
            DataSet &nested = item.GetNestedDataSet();
            Anonymizer_RemoveGroupLength( file, nested );
            }
          DataElement de_dup = *dup;
          de_dup.SetValue( *sq );
          de_dup.SetVLToUndefined(); // FIXME
          ds.Replace( de_dup );
          }
        }
      }
    }
  return true;
}

bool Anonymizer::RemoveGroupLength()
{
  DataSet &ds = F->GetDataSet();
  return Anonymizer_RemoveGroupLength(*F, ds);
}

static bool Anonymizer_RemovePrivateTags(File const &file, DataSet &ds)
{
  DataSet::Iterator it = ds.Begin();
  for( ; it != ds.End(); )
    {
    const DataElement &de1 = *it;
      // std::set::erase invalidate iterator, so we need to make a copy first:
      DataSet::Iterator dup = it;
      ++it;
    if( de1.GetTag().IsPrivate() )
      {
      ds.GetDES().erase(dup);
      }
    else
      {
      const DataElement &de = *dup;
      VR vr = DataSetHelper::ComputeVR(file, ds, de.GetTag() );
      if( vr.Compatible(VR::SQ) )
        {
        SmartPointer<SequenceOfItems> sq = de.GetValueAsSQ();
        if( sq )
          {
          SequenceOfItems::SizeType n = sq->GetNumberOfItems();
          for( SequenceOfItems::SizeType i = 1; i <= n; i++) // item starts at 1, not 0
            {
            Item &item = sq->GetItem( i );
            DataSet &nested = item.GetNestedDataSet();
            Anonymizer_RemovePrivateTags( file, nested );
            }
          DataElement de_dup = *dup;
          de_dup.SetValue( *sq );
          de_dup.SetVLToUndefined(); // FIXME
          ds.Replace( de_dup );
          }
        }
      }
    }
  return true;
}

bool Anonymizer::RemovePrivateTags()
{
  DataSet &ds = F->GetDataSet();
  return Anonymizer_RemovePrivateTags(*F, ds);
}

/*
 * Implementation note:
 * In order to implement the dummy 'memory' we use a static std::map
 * this works great but we cannot be thread safe.
 * In order to be thread safe, we would need to externalize this map generation
 * maybe using a Scanner do the operation once (Scanner is doing) the merging
 * automatically...
 * this is left as an exercise for the reader :)
 */
bool Anonymizer::BasicApplicationLevelConfidentialityProfile(bool deidentify)
{
  this->InvokeEvent( StartEvent() );
  bool ret;
  if( deidentify )
    ret = BasicApplicationLevelConfidentialityProfile1();
  else
    ret = BasicApplicationLevelConfidentialityProfile2();
  this->InvokeEvent( EndEvent() );
  return ret;
}

std::vector<Tag> Anonymizer::GetBasicApplicationLevelConfidentialityProfileAttributes()
{
  static const unsigned int deidSize = sizeof(Tag);
  static const unsigned int numDeIds = sizeof(BasicApplicationLevelConfidentialityProfileAttributes) / deidSize;
  static const Tag *start = BasicApplicationLevelConfidentialityProfileAttributes;
  static const Tag *end = start + numDeIds;
  return std::vector<Tag>(start, end);
}

bool Anonymizer::CheckIfSequenceContainsAttributeToAnonymize(File const &file, SequenceOfItems* sqi) const
{
  static const unsigned int deidSize = sizeof(Tag);
  static const unsigned int numDeIds = sizeof(BasicApplicationLevelConfidentialityProfileAttributes) / deidSize;
  static const Tag *start = BasicApplicationLevelConfidentialityProfileAttributes;
  static const Tag *end = start + numDeIds;

  bool found = false;
  for(const Tag *ptr = start ; ptr != end && !found ; ++ptr)
    {
    const Tag& tag = *ptr;
    found = sqi->FindDataElement( tag );
    }
  // ok we can exit.
  if( found ) return true;

  // now look into sub-sequence:
  SequenceOfItems::SizeType n = sqi->GetNumberOfItems();
  for( SequenceOfItems::SizeType i = 1; i <= n; i++) // item starts at 1, not 0
    {
    Item &item = sqi->GetItem( i );
    DataSet &nested = item.GetNestedDataSet();
    DataSet::Iterator it = nested.Begin();
    for( ; it != nested.End() && !found; ++it)
      {
      const DataElement &de = *it;
      VR vr = DataSetHelper::ComputeVR(file, nested, de.GetTag() );
      SmartPointer<SequenceOfItems> sqi2 = 0;
      if( vr == VR::SQ )
        {
        sqi2 = de.GetValueAsSQ();
        }
      if( sqi2 )
        {
        found = CheckIfSequenceContainsAttributeToAnonymize(file, sqi2);
        }
      }
    }

  return found;
}

// Implementation note:
// This function trigger:
// 1 StartEvent
// 1 EndEvent
// 6 IterationEvent
// N AnonymizeEvent (depend on number of tag found)
bool Anonymizer::BasicApplicationLevelConfidentialityProfile1()
{
  static const unsigned int deidSize = sizeof(Tag);
  static const unsigned int numDeIds = sizeof(BasicApplicationLevelConfidentialityProfileAttributes) / deidSize;
  static const Tag *start = BasicApplicationLevelConfidentialityProfileAttributes;
  static const Tag *end = start + numDeIds;
  if( !CMS )
    {
    gdcmErrorMacro( "Need a certificate" );
    return false;
    }

  CryptographicMessageSyntax &p7 = *CMS;
  //p7.SetCertificate( this->x509 );

  DataSet &ds = F->GetDataSet();
  if(  ds.FindDataElement( Tag(0x0400,0x0500) )
    || ds.FindDataElement( Tag(0x0012,0x0062) )
    || ds.FindDataElement( Tag(0x0012,0x0063) ) )
    {
    gdcmDebugMacro( "EncryptedContentTransferSyntax Attribute is present !" );
    return false;
    }
#if 0
  if( !ds.FindDataElement( Tag(0x0008,0x0018) )
    || ds.GetDataElement( Tag(0x0008,0x0018) ).IsEmpty() )
    {
    return false;
    }
#endif

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
  SmartPointer<SequenceOfItems> sq1 = new SequenceOfItems();
  sq1->SetLengthToUndefined();

  // Create a *single* item
  Item item1;
  item1.SetVLToUndefined();
  DataSet &encryptedds = item1.GetNestedDataSet();
  // Loop over root level attributes:
  for(const Tag *ptr = start ; ptr != end ; ++ptr)
    {
    const Tag& tag = *ptr;
    if( ds.FindDataElement( tag ) )
      encryptedds.Insert( ds.GetDataElement( tag ) );
    }
  this->InvokeEvent( IterationEvent() );
  // Check that root level sequence do not contains any of those attributes
{
  DataSet::ConstIterator it = ds.Begin();
  for( ; it != ds.End(); ++it )
    {
    const DataElement &de = *it;
    //const SequenceOfItems *sqi = de.GetSequenceOfItems();
    SmartPointer<SequenceOfItems> sqi = 0;
    VR vr = DataSetHelper::ComputeVR(*F, ds, de.GetTag() );
    if( vr == VR::SQ )
      {
      sqi = de.GetValueAsSQ();
      }
    if( sqi )
      {
      bool found
        = CheckIfSequenceContainsAttributeToAnonymize(*F, sqi);
      if( found )
        {
        // A special Tag was found within the SQ,let's store the entire Sequence of Item:
        if( !encryptedds.FindDataElement( de.GetTag() ) )
          {
          // What if we found a Patient Name within a Content Sequence
          // we do not need to insert twice this DICOM Attribute
          encryptedds.Insert( de );
          }
        else
          {
          assert( de == encryptedds.GetDataElement( de.GetTag() ) );
          }
        }
      }
    }
}

  this->InvokeEvent( IterationEvent() );
  sq1->AddItem(item1);

  DataElement des( Tag(0x0400,0x0550) );
  des.SetVR(VR::SQ);
  des.SetValue(*sq1);
  des.SetVLToUndefined();

  std::ostringstream os;
  des.Write<ExplicitDataElement,SwapperNoOp>(os);

  std::string encrypted_str = os.str();

  // Note: 1. Content encryption may require that the content (the DICOM Data Set) be padded to a
  // multiple of some block size. This shall be performed according to the Content-encryption
  // Process defined in RFC-2630.
  size_t encrypted_len = encrypted_str.size() * 20; // this is really overestimated

  char *orig = new char[ encrypted_len ];
  char *buf = new char[ encrypted_len ];
  memset( buf, 0, encrypted_len );
  memset( orig, 0, encrypted_len );
  memcpy( orig, encrypted_str.c_str(), encrypted_str.size() );

  size_t encrypted_len2 = encrypted_len;
  bool b = p7.Encrypt( buf, encrypted_len, orig, encrypted_str.size() );
  if( !b )
  {
    delete[] orig;
    delete[] buf;
    gdcmErrorMacro( "Problem with Encrypt" );
    return false;
  }
  assert( encrypted_len <= encrypted_len2 );
  (void)encrypted_len2;//warning removal

    {
    // Create a Sequence
    SmartPointer<SequenceOfItems> sq = new SequenceOfItems();
    sq->SetLengthToUndefined();

    // FIXME: should be user configurable:
    //TransferSyntax encrypted_ts = TransferSyntax::ImplicitVRLittleEndian;
    TransferSyntax encrypted_ts = TransferSyntax::ExplicitVRLittleEndian;
    // <entry group="0400" element="0510" vr="UI" vm="1" name="Encrypted Content Transfer Syntax UID"/>
    DataElement encrypted_ts_de( Tag(0x400,0x510) );
    encrypted_ts_de.SetVR( Attribute<0x0400, 0x0510>::GetVR() );
    const VL::Type encryptedStrLen = (VL::Type)strlen(encrypted_ts.GetString());
    encrypted_ts_de.SetByteValue( encrypted_ts.GetString(), encryptedStrLen );
    // <entry group="0400" element="0520" vr="OB" vm="1" name="Encrypted Content"/>
    DataElement encrypted_de( Tag(0x400,0x520) );
    encrypted_de.SetVR( Attribute<0x0400, 0x0520>::GetVR() );
    const VL::Type encryptedLenSize = (VL::Type)encrypted_len;
    encrypted_de.SetByteValue( (char*)buf, encryptedLenSize );
    delete[] buf;
    delete[] orig;

    // Create an item
    Item item2;
    item2.SetVLToUndefined();
    DataSet &nds = item2.GetNestedDataSet();
    nds.Insert(encrypted_ts_de);
    nds.Insert(encrypted_de);

    sq->AddItem(item2);

    // 4. All instances of the Encrypted Attributes Data Set shall be encoded
    // with a DICOM Transfer Syntax, encrypted, and stored in the dataset to be
    // protected as an Item of the Encrypted Attributes Sequence (0400,0500).
    // The encryption shall be done using RSA [RFC 2313] for the key transport
    // of the content-encryption keys. A de-identifier conforming to this
    // security profile may use either AES or Triple-DES for
    // content-encryption. The AES key length may be any length allowed by the
    // RFCs. The Triple-DES key length is 168 bits as defined by ANSI X9.52.
    // Encoding shall be performed according to the specifications for RSA Key
    // Transport and Triple DES Content Encryption in RFC-3370 and for AES
    // Content Encryption in RFC-3565.

    // 5. No requirements on the size of the asymmetric key pairs used for RSA
    // key transport are defined in this confidentiality scheme.
    // Implementations claiming conformance to the Basic Application Level
    // Confidentiality Profile as a de-identifier shall always protect (e.g.
    // encrypt and replace) the SOP Instance UID (0008,0018) Attribute as well
    // as all references to other SOP Instances, whether contained in the main
    // dataset or embedded in an Item of a Sequence of Items, that could
    // potentially be used by unauthorized entities to identify the patient.

    // Insert sequence into data set
    DataElement subdes( Tag(0x0400,0x0500) );
    subdes.SetVR(VR::SQ);
    subdes.SetValue(*sq);
    subdes.SetVLToUndefined();

    ds.Insert(subdes);
    }
  this->InvokeEvent( IterationEvent() );

  // 2. Each Attribute to be protected shall then either be removed from the
  // dataset, or have its value replaced by a different "replacement value"
  // which does not allow identification of the patient.

  //for(const Tag *ptr = start ; ptr != end ; ++ptr)
  //  {
  //  const Tag& tag = *ptr;
  //  // FIXME Type 1 !
  //  if( ds.FindDataElement( tag ) ) BALCPProtect(F->GetDataSet(), tag);
  //  }
  // Check that root level sequence do not contains any of those attributes
  try
  {
    RecurseDataSet( F->GetDataSet() );
  }
  catch(std::exception &ex)
  {
  gdcmDebugMacro( "Problem during RecurseDataSet");
  (void)ex; //to get rid of the warning.  TODO: spit out the exception
  return false;
  }
catch(...)
{
  gdcmDebugMacro( "Unknown Problem during RecurseDataSet" );
  return false;
}

  this->InvokeEvent( IterationEvent() );

  // Group Length are removed since PS 3.3-2008
  RemoveGroupLength();

  // 3. At the discretion of the de-identifier, Attributes may be added to the
  // dataset to be protected.  ...

  // 6. The attribute Patient Identity Removed (0012,0062) shall be replaced or
  // added to the dataset with a value of YES, and a value inserted in
  // De-identification Method (0012,0063) or De-identification Method Code
  // Sequence (0012,0064).
  Replace( Tag(0x0012,0x0062), "YES");
  Replace( Tag(0x0012,0x0063), "BASIC APPLICATION LEVEL CONFIDENTIALITY PROFILE");

  this->InvokeEvent( IterationEvent() );

#if 0
  // Since the de-identified SOP Instance is a significantly altered version of
  // the original Data Set, it is a new SOP Instance, with a SOP Instance UID
  // that differs from the original Data Set.
  UIDGenerator uid;
  if( ds.FindDataElement( Tag(0x0008,0x0018) ) )
    {
    Replace( Tag(0x008,0x0018), uid.Generate() );
    }

  this->InvokeEvent( IterationEvent() );
#endif

  return true;
}


bool IsVRUI(Tag const &tag)
{
  static const Global &g = Global::GetInstance();
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

static const Tag SpecialTypeTags[] = {
/*   Patient's Name          */ Tag(0x0010,0x0010),
/*   Patient ID              */ Tag(0x0010,0x0020),
/*   Study ID                */ Tag(0x0020,0x0010),
/*   Series Number           */ Tag(0x0020,0x0011)
};

bool Anonymizer::CanEmptyTag(Tag const &tag, const IOD &iod) const
{
  static const Global &g = Global::GetInstance();
  //static const Dicts &dicts = g.GetDicts();
  static const Defs &defs = g.GetDefs();
  const DataSet &ds = F->GetDataSet(); (void)ds;
  //Type told = defs.GetTypeFromTag(*F, tag);
  Type t = iod.GetTypeFromTag(defs, tag);
  //assert( t == told );

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

  // http://groups.google.com/group/comp.protocols.dicom/browse_thread/thread/b1b23101bb655b81
/*
...
3. It is the responsibility of the de-identifier to ensure the
consistency of dummy values for Attributes
such as Study Instance UID (0020,000D) or Frame of Reference UID
(0020,0052) if multiple related
SOP Instances are protected.
...

I think it would also make sense to quote the following attributes:
* Patient ID,
* Study ID,
* Series Number.
It is required they have consistent values when one is about to
generate a DICOMDIR

=> Sup 142
*/
  static const unsigned int deidSize = sizeof(Tag);
  static const unsigned int numDeIds = sizeof(SpecialTypeTags) / deidSize;

  bool b = std::binary_search(SpecialTypeTags, SpecialTypeTags + numDeIds, tag);

  // This is a Type 3 attribute but with VR=UI
  // <entry group="0008" element="0014" vr="UI" vm="1" name="Instance Creator UID"/>
  //assert( dicts.GetDictEntry(tag).GetVR() != VR::UI );
  return !b;
}

Anonymizer::DummyMapNonUIDTags Anonymizer::dummyMapNonUIDTags;
Anonymizer::DummyMapUIDTags Anonymizer::dummyMapUIDTags;

void Anonymizer::ClearInternalUIDs()
{
  dummyMapNonUIDTags.clear();
  dummyMapUIDTags.clear();
}

bool Anonymizer::BALCPProtect(DataSet &ds, Tag const & tag, IOD const & iod)
{
  // \precondition
  assert( ds.FindDataElement(tag) );

  AnonymizeEvent ae;
  ae.SetTag( tag );
  this->InvokeEvent( ae );


  bool canempty = CanEmptyTag( tag, iod );
  if( !canempty )
    {
    DataElement copy;
    copy = ds.GetDataElement( tag );

    if ( IsVRUI( tag ) )
      {
      std::string UIDToAnonymize = "";
      UIDGenerator uid;

      if( !copy.IsEmpty() )
        {
        if( const ByteValue *bv = copy.GetByteValue() )
          {
          UIDToAnonymize = std::string( bv->GetPointer(), bv->GetLength() );
          }
        }

      std::string anonymizedUID = "";
      if( !UIDToAnonymize.empty() )
        {
        if ( dummyMapUIDTags.count( UIDToAnonymize ) == 0 )
          {
          anonymizedUID = uid.Generate();
          dummyMapUIDTags[ UIDToAnonymize ] = anonymizedUID;
          }
        else
          {
          anonymizedUID = dummyMapUIDTags[ UIDToAnonymize ];
          }
        }
      else
        {
        // gdcmData/LEADTOOLS_FLOWERS-16-MONO2-JpegLossless.dcm
        // has an empty 0008,0018 attribute, let's try to handle creating new UID
        anonymizedUID = uid.Generate();
        }

      copy.SetByteValue( anonymizedUID.c_str(), (uint32_t)anonymizedUID.size() );
      ds.Replace( copy );
      }
    else
      {
      TagValueKey tvk;
      tvk.first = tag;

      assert( dummyMapNonUIDTags.count( tvk ) == 0 || dummyMapNonUIDTags.count( tvk ) == 1 );
      if( dummyMapNonUIDTags.count( tvk ) == 0 )
        {
        const char *ret = DummyValueGenerator::Generate( tvk.second.c_str() );
        if( ret )
          {
          dummyMapNonUIDTags[ tvk ] = ret;
          }
        else
          dummyMapNonUIDTags[ tvk ] = "";
        }

      std::string &v = dummyMapNonUIDTags[ tvk ];
      copy.SetByteValue( v.c_str(), (uint32_t)v.size() );
      }
      ds.Replace( copy );
    }
  else
    {
    //Empty( tag );
    DataElement copy = ds.GetDataElement( tag );
    copy.Empty();
    ds.Replace( copy );
    }
  return true;
}

void Anonymizer::RecurseDataSet( DataSet & ds )
{
  if( ds.IsEmpty() ) return;

  static const unsigned int deidSize = sizeof(Tag);
  static const unsigned int numDeIds = sizeof(BasicApplicationLevelConfidentialityProfileAttributes) / deidSize;
  static const Tag *start = BasicApplicationLevelConfidentialityProfileAttributes;
  static const Tag *end = start + numDeIds;

  static const Global &g = Global::GetInstance();
  static const Defs &defs = g.GetDefs();
  const IOD& iod = defs.GetIODFromFile(*F);

  for(const Tag *ptr = start ; ptr != end ; ++ptr)
    {
    const Tag& tag = *ptr;
    // FIXME Type 1 !
    if( ds.FindDataElement( tag ) )
      {
      BALCPProtect(ds, tag, iod);
      }
    }

  DataSet::ConstIterator it = ds.Begin();
  for( ; it != ds.End(); /*++it*/ )
    {
    assert( it != ds.End() );
    DataElement de = *it; ++it;
    //const SequenceOfItems *sqi = de.GetSequenceOfItems();
    VR vr = DataSetHelper::ComputeVR(*F, ds, de.GetTag() );
    SmartPointer<SequenceOfItems> sqi = 0;
    if( vr == VR::SQ )
      {
      sqi = de.GetValueAsSQ();
      }
    if( sqi )
      {
      de.SetValue( *sqi ); // EXTREMELY IMPORTANT #2912092
      de.SetVLToUndefined();
      assert( sqi->IsUndefinedLength() );
      //de.GetVL().SetToUndefined();
      //sqi->SetLengthToUndefined();
      SequenceOfItems::SizeType n = sqi->GetNumberOfItems();
      for( SequenceOfItems::SizeType i = 1; i <= n; ++i )
        {
        Item &item = sqi->GetItem( i );
        DataSet &nested = item.GetNestedDataSet();
        RecurseDataSet( nested );
        }
      }
    ds.Replace( de );
    }

}

//void Anonymizer::SetAESKey(AES const &aes)
//{
//  AESKey = aes;
//}
//
//const AES &Anonymizer::GetAESKey() const
//{
//  return AESKey;
//}

bool Anonymizer::BasicApplicationLevelConfidentialityProfile2()
{
  if( !CMS )
    {
    gdcmErrorMacro( "Need a certificate" );
    return false;
    }
  // 1. The application shall decrypt, using its recipient key, one instance of
  // the Encrypted Content (0400,0520) Attribute within the Encrypted
  // Attributes Sequence (0400,0500) and decode the resulting block of bytes
  // into a DICOM dataset using the Transfer Syntax specified in the Encrypted
  // Content Transfer Syntax UID (0400,0510). Re-identifiers claiming
  // conformance to this profile shall be capable of decrypting the Encrypted
  // Content using either AES or Triple-DES in all possible key lengths
  // specified in this profile
  CryptographicMessageSyntax &p7 = *CMS;
  //p7.SetCertificate( this->x509 );

  DataSet &ds = F->GetDataSet();
  if( !ds.FindDataElement( Tag(0x0400,0x0500) ) )
    {
    gdcmDebugMacro( "Could not find EncryptedAttributesSQ" );
    return false;
    }
  const DataElement &EncryptedAttributesSequence = ds.GetDataElement( Tag(0x0400,0x0500) );
  //const SequenceOfItems *sq = EncryptedAttributesSequence.GetSequenceOfItems();
  SmartPointer<SequenceOfItems> sq = EncryptedAttributesSequence.GetValueAsSQ();
  const Item &item1 = sq->GetItem(1);
  const DataSet &nds1 = item1.GetNestedDataSet();
  if( !nds1.FindDataElement( Tag(0x0400,0x0510) )
    || nds1.GetDataElement( Tag(0x0400,0x0510) ).IsEmpty() )
    {
    gdcmDebugMacro( "Missing EncryptedContentTransferSyntax Attribute" );
    return false;
    }

  const DataElement &EncryptedContentTransferSyntax = nds1.GetDataElement( Tag(0x0400,0x0510) );

  std::string ts( EncryptedContentTransferSyntax.GetByteValue()->GetPointer(),
    EncryptedContentTransferSyntax.GetByteValue()->GetLength() );

  if( TransferSyntax::GetTSType( ts.c_str() ) != TransferSyntax::ExplicitVRLittleEndian )
    {
    gdcmDebugMacro( "Only ExplicitVRLittleEndian is supported" );
    return false;
    }

  if( !nds1.FindDataElement( Tag(0x0400,0x0520) )
    || nds1.GetDataElement( Tag(0x0400,0x0520) ).IsEmpty() )
    {
    gdcmDebugMacro( "Missing EncryptedContent Attribute" );
    return false;
    }

  const DataElement &EncryptedContent = nds1.GetDataElement( Tag(0x0400,0x0520) );
  const ByteValue *bv = EncryptedContent.GetByteValue();

  size_t encrypted_len = bv->GetLength();
  char *orig = new char[ encrypted_len ];
  char *buf = new char[ encrypted_len ];
  memcpy(orig, bv->GetPointer(), encrypted_len );

  size_t encrypted_len2 = encrypted_len;
  bool b = p7.Decrypt( buf, encrypted_len, orig, encrypted_len);
  if( !b )
    {
    // ooops
    gdcmDebugMacro( "Could not decrypt" );
    return false;
    }
  assert( encrypted_len <= encrypted_len2 );
  (void)encrypted_len2;//warning removal

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
  assert( (size_t)ss.tellg() <= encrypted_len );
  // TODO: check that for i = ss.tellg() to encrypted_len, ss[i] == 0
  delete[] buf;
  delete[] orig;

  // 2. The application shall move all Attributes contained in the single item
  // of the Modified Attributes Sequence (0400,0550) of the decoded dataset
  // into the main dataset, replacing dummy value Attributes that may be
  // present in the main dataset.
  //assert( dummy.GetVR() == VR::SQ );
{
  //const SequenceOfItems *sqi = dummy.GetSequenceOfItems();
  SmartPointer<SequenceOfItems> sqi = dummy.GetValueAsSQ();
  assert( sqi && sqi->GetNumberOfItems() == 1 );
  Item const & item2 = sqi->GetItem( 1 );
  const DataSet &nds2 = item2.GetNestedDataSet();
  DataSet::ConstIterator it = nds2.Begin();
  for( ; it != nds2.End(); ++it )
    {
    ds.Replace( *it );
    }

  // FIXME the above Replace assume that the encrypted content will replace
  // any dummy values. What if the anonymizer was dumb and forgot
  // to encrypt say UID 8,18 ? We would be left with the Instance UID
  // of the encrypted one ?
  if( !nds2.FindDataElement( Tag(0x8,0x18) ) )
    {
    MediaStorage ms;
    ms.SetFromFile( *F );
    if( ms != MediaStorage::MediaStorageDirectoryStorage )
      {
      gdcmErrorMacro( "Could not find Instance UID" );
      return false;
      }
    }
}

  // 3. The attribute Patient Identity Removed (0012,0062) shall be replaced or
  // added to the dataset with a value of NO and De-identification Method
  // (0012,0063) and De-identification Method Code Sequence (0012,0064) shall
  // be removed.
  //Replace( Tag(0x0012,0x0062), "NO");
  Remove( Tag(0x0012,0x0062) );
  Remove( Tag(0x0012,0x0063) );

  Remove( Tag(0x0400,0x0500) ); // ??

  return true;
}

void Anonymizer::SetCryptographicMessageSyntax(CryptographicMessageSyntax *cms)
{
  CMS = cms;
}

const CryptographicMessageSyntax *Anonymizer::GetCryptographicMessageSyntax() const
{
  return CMS;
}

} // end namespace gdcm
