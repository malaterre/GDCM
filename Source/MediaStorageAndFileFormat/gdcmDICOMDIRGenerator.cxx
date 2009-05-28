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
#include "gdcmDICOMDIRGenerator.h"
#include "gdcmFile.h"
#include "gdcmSmartPointer.h"

#include "gdcmUIDGenerator.h"
#include "gdcmFilename.h"
#include "gdcmScanner.h"
#include "gdcmAttribute.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmTag.h"
#include "gdcmVR.h"


namespace gdcm
{

class DICOMDIRGeneratorInternal
{
public:
  DICOMDIRGeneratorInternal():F(new File) {}
  SmartPointer<File> F;
  typedef Directory::FilenamesType  FilenamesType;
  FilenamesType fns;
};

bool TraverseDirectoryRecords(gdcm::Scanner const & scanner, const SequenceOfItems *sqi, VL start )
{
  unsigned int nitems = sqi->GetNumberOfItems();
  for(unsigned int i = 1; i <=nitems; ++i)
    {
    const Item &item = sqi->GetItem(i);
    const DataSet &ds = item.GetNestedDataSet();
    Attribute<0x4,0x1430> directoryrecordtype;
    directoryrecordtype.Set( ds );
    std::cout << "FOUND DIRECTORY TYPE:" << directoryrecordtype.GetValue() << std::endl;
    }
  return true;
}

template<uint16_t Group, uint16_t Element>
void SingleDataElementInserter(gdcm::DataSet &ds, gdcm::Scanner const & scanner)
{
  Attribute<Group,Element> patientsname;
  gdcm::Scanner::ValuesType patientsnames = scanner.GetValues( patientsname.GetTag() );
  unsigned int npatient = patientsnames.size();
  assert( npatient == 1 );
  gdcm::Scanner::ValuesType::const_iterator it = patientsnames.begin();
  patientsname.SetValue( it->c_str() );
  ds.Insert( patientsname.GetAsDataElement() );
}


/*
  (fffe,e000) na "Directory Record" PATIENT #=8           # u/l, 1 Item
  #  offset=$374
    (0004,1400) up 0                                        #   4, 1 OffsetOfTheNextDirectoryRecord
    (0004,1410) US 65535                                    #   2, 1 RecordInUseFlag
    (0004,1420) up 502                                      #   4, 1 OffsetOfReferencedLowerLevelDirectoryEntity
    (0004,1430) CS [PATIENT]                                #   8, 1 DirectoryRecordType
    (0010,0010) PN [Test^PixelSpacing]                      #  18, 1 PatientsName
    (0010,0020) LO [62354PQGRRST]                           #  12, 1 PatientID
    (0010,0030) DA (no value available)                     #   0, 0 PatientsBirthDate
    (0010,0040) CS (no value available)                     #   0, 0 PatientsSex
  (fffe,e00d) na "ItemDelimitationItem"                   #   0, 0 ItemDelimitationItem
*/
bool AddPatientDirectoryRecord(gdcm::DataSet &rootds, gdcm::Scanner const & scanner)
{
  const gdcm::DataElement &de = rootds.GetDataElement( Tag(0x4,0x1220) );
  SequenceOfItems * sqi = (SequenceOfItems*)de.GetSequenceOfItems();
  Item item;
  item.SetVLToUndefined();
  DataSet &ds = item.GetNestedDataSet();

  // (0004,1400) up 0                                        #   4, 1 OffsetOfTheNextDirectoryRecord
  // (0004,1410) US 65535                                    #   2, 1 RecordInUseFlag
  // (0004,1420) up 502                                      #   4, 1 OffsetOfReferencedLowerLevelDirectoryEntity
  // (0004,1430) CS [PATIENT]                                #   8, 1 DirectoryRecordType
  Attribute<0x4,0x1400> offsetofthenextdirectoryrecord = {0};
  ds.Insert( offsetofthenextdirectoryrecord.GetAsDataElement() );
  Attribute<0x4,0x1410> recordinuseflag = {0xFFFF};
  ds.Insert( recordinuseflag.GetAsDataElement() );
  Attribute<0x4,0x1420> offsetofreferencedlowerleveldirectoryentity = {0};
  ds.Insert( offsetofreferencedlowerleveldirectoryentity.GetAsDataElement() );
  Attribute<0x4,0x1430> directoryrecordtype;
  directoryrecordtype.SetValue( "PATIENT" );
  ds.Insert( directoryrecordtype.GetAsDataElement() );

  SingleDataElementInserter<0x10,0x10>(ds, scanner);
  SingleDataElementInserter<0x10,0x20>(ds, scanner);
  //SingleDataElementInserter<0x10,0x30>(ds, scanner);
  //SingleDataElementInserter<0x10,0x40>(ds, scanner);

  sqi->AddItem( item );
  return true;
}

/*
  (fffe,e000) na "Directory Record" STUDY #=10            # u/l, 1 Item
  #  offset=$502
    (0004,1400) up 0                                        #   4, 1 OffsetOfTheNextDirectoryRecord
    (0004,1410) US 65535                                    #   2, 1 RecordInUseFlag
    (0004,1420) up 748                                      #   4, 1 OffsetOfReferencedLowerLevelDirectoryEntity
    (0004,1430) CS [STUDY]                                  #   6, 1 DirectoryRecordType
    (0008,0020) DA [20050624]                               #   8, 1 StudyDate
    (0008,0030) TM [104221]                                 #   6, 1 StudyTime
    (0008,0050) SH [8-13547713751]                          #  14, 1 AccessionNumber
    (0008,1030) LO [Test support of different pixel spacing attributes] #  50, 1 StudyDescription
    (0020,000d) UI [1.3.6.1.4.1.5962.1.2.65535.1119624141.7160.0] #  44, 1 StudyInstanceUID
    (0020,0010) SH [734591762345]                           #  12, 1 StudyID
  (fffe,e00d) na "ItemDelimitationItem"                   #   0, 0 ItemDelimitationItem
*/
bool AddStudyDirectoryRecord(gdcm::DataSet &rootds, gdcm::Scanner const & scanner)
{
  const gdcm::DataElement &de = rootds.GetDataElement( Tag(0x4,0x1220) );
  SequenceOfItems * sqi = (SequenceOfItems*)de.GetSequenceOfItems();
  Item item;
  item.SetVLToUndefined();
  DataSet &ds = item.GetNestedDataSet();

  Attribute<0x4,0x1400> offsetofthenextdirectoryrecord = {0};
  ds.Insert( offsetofthenextdirectoryrecord.GetAsDataElement() );
  Attribute<0x4,0x1410> recordinuseflag = {0xFFFF};
  ds.Insert( recordinuseflag.GetAsDataElement() );
  Attribute<0x4,0x1420> offsetofreferencedlowerleveldirectoryentity = {0};
  ds.Insert( offsetofreferencedlowerleveldirectoryentity.GetAsDataElement() );
  Attribute<0x4,0x1430> directoryrecordtype;
  directoryrecordtype.SetValue( "STUDY" );
  ds.Insert( directoryrecordtype.GetAsDataElement() );

  SingleDataElementInserter<0x8,0x20>(ds, scanner);
  SingleDataElementInserter<0x8,0x30>(ds, scanner);
  SingleDataElementInserter<0x8,0x1030>(ds, scanner);
  SingleDataElementInserter<0x20,0xd>(ds, scanner);
  SingleDataElementInserter<0x20,0x10>(ds, scanner);
  SingleDataElementInserter<0x8,0x50>(ds, scanner);

  sqi->AddItem( item );
  return true;
}

/*
  (fffe,e000) na "Directory Record" SERIES #=11           # u/l, 1 Item
  #  offset=$748
    (0004,1400) up 1214                                     #   4, 1 OffsetOfTheNextDirectoryRecord
    (0004,1410) US 65535                                    #   2, 1 RecordInUseFlag
    (0004,1420) up 938                                      #   4, 1 OffsetOfReferencedLowerLevelDirectoryEntity
    (0004,1430) CS [SERIES]                                 #   6, 1 DirectoryRecordType
    (0008,0060) CS [CR]                                     #   2, 1 Modality
    (0008,0080) LO (no value available)                     #   0, 0 InstitutionName
    (0008,0081) ST (no value available)                     #   0, 0 InstitutionAddress
    (0008,103e) LO [Computed Radiography]                   #  20, 1 SeriesDescription
    (0008,1050) PN (no value available)                     #   0, 0 PerformingPhysiciansName
    (0020,000e) UI [1.3.6.1.4.1.5962.1.3.65535.4.1119624143.7187.0] #  46, 1 SeriesInstanceUID
    (0020,0011) IS [4]                                      #   2, 1 SeriesNumber
  (fffe,e00d) na "ItemDelimitationItem"                   #   0, 0 ItemDelimitationItem
*/
bool AddSeriesDirectoryRecord(gdcm::DataSet &rootds, gdcm::Scanner const & scanner)
{
  Attribute<0x20,0xe> seriesinstanceuid;
  gdcm::Scanner::ValuesType seriesinstanceuids = scanner.GetValues( seriesinstanceuid.GetTag() );
  unsigned int nseries = seriesinstanceuids.size();

  const gdcm::DataElement &de = rootds.GetDataElement( Tag(0x4,0x1220) );
  SequenceOfItems * sqi = (SequenceOfItems*)de.GetSequenceOfItems();

  gdcm::Scanner::ValuesType::const_iterator it = seriesinstanceuids.begin();
  for( ; it  != seriesinstanceuids.end(); ++it)
    {
    Item item;
    item.SetVLToUndefined();
    DataSet &ds = item.GetNestedDataSet();

    Attribute<0x4,0x1400> offsetofthenextdirectoryrecord = {0};
    ds.Insert( offsetofthenextdirectoryrecord.GetAsDataElement() );
    Attribute<0x4,0x1410> recordinuseflag = {0xFFFF};
    ds.Insert( recordinuseflag.GetAsDataElement() );
    Attribute<0x4,0x1420> offsetofreferencedlowerleveldirectoryentity = {0};
    ds.Insert( offsetofreferencedlowerleveldirectoryentity.GetAsDataElement() );
    Attribute<0x4,0x1430> directoryrecordtype;
    directoryrecordtype.SetValue( "SERIES" );
    ds.Insert( directoryrecordtype.GetAsDataElement() );
    seriesinstanceuid.SetValue( it->c_str() );
    ds.Insert( seriesinstanceuid.GetAsDataElement() );

    const char *seriesuid = it->c_str();
    gdcm::Scanner::TagToValue const &ttv = scanner.GetMappingFromTagToValue(seriesinstanceuid.GetTag(), seriesuid);
    Attribute<0x8,0x60> modality;
    if( ttv.find( modality.GetTag() ) != ttv.end() )
      {
      modality.SetValue( ttv.find(modality.GetTag())->second );
      ds.Insert( modality.GetAsDataElement() );
      }
    Attribute<0x20,0x11> seriesnumber;
    if( ttv.find( seriesnumber.GetTag() ) != ttv.end() )
      {
      seriesnumber.SetValue( atoi(ttv.find(seriesnumber.GetTag())->second) );
      ds.Insert( seriesnumber.GetAsDataElement() );
      }

    sqi->AddItem( item );
    }

  return true;
}

/*
  (fffe,e000) na "Directory Record" IMAGE #=13            # u/l, 1 Item
  #  offset=$1398  refFileID="IMAGES\DXIMAGE"
    (0004,1400) up 0                                        #   4, 1 OffsetOfTheNextDirectoryRecord
    (0004,1410) US 65535                                    #   2, 1 RecordInUseFlag
    (0004,1420) up 0                                        #   4, 1 OffsetOfReferencedLowerLevelDirectoryEntity
    (0004,1430) CS [IMAGE]                                  #   6, 1 DirectoryRecordType
    (0004,1500) CS [IMAGES\DXIMAGE]                         #  14, 2 ReferencedFileID
    (0004,1510) UI =DigitalXRayImageStorageForPresentation  #  28, 1 ReferencedSOPClassUIDInFile
    (0004,1511) UI [1.3.6.1.4.1.5962.1.1.65535.3.1.1119624143.7180.0] #  48, 1 ReferencedSOPInstanceUIDInFile
    (0004,1512) UI =LittleEndianExplicit                    #  20, 1 ReferencedTransferSyntaxUIDInFile
    (0008,0008) CS [ORIGINAL\PRIMARY]                       #  16, 2 ImageType
    (0020,0013) IS [1]                                      #   2, 1 InstanceNumber
    (0028,0004) CS [MONOCHROME2]                            #  12, 1 PhotometricInterpretation
    (0028,0008) IS [1]                                      #   2, 1 NumberOfFrames
    (0050,0004) CS (no value available)                     #   0, 0 CalibrationImage
  (fffe,e00d) na "ItemDelimitationItem"                   #   0, 0 ItemDelimitationItem
*/
bool AddImageDirectoryRecord(gdcm::DataSet &rootds, gdcm::Scanner const & scanner)
{
  Attribute<0x8,0x18> sopinstanceuid;
  gdcm::Scanner::ValuesType sopinstanceuids = scanner.GetValues( sopinstanceuid.GetTag() );
  unsigned int ninstance = sopinstanceuids.size();

  const gdcm::DataElement &de = rootds.GetDataElement( Tag(0x4,0x1220) );
  SequenceOfItems * sqi = (SequenceOfItems*)de.GetSequenceOfItems();

  gdcm::Scanner::ValuesType::const_iterator it = sopinstanceuids.begin();
  for( ; it  != sopinstanceuids.end(); ++it)
    {
    Item item;
    item.SetVLToUndefined();
    DataSet &ds = item.GetNestedDataSet();

    Attribute<0x4,0x1400> offsetofthenextdirectoryrecord = {0};
    ds.Insert( offsetofthenextdirectoryrecord.GetAsDataElement() );
    Attribute<0x4,0x1410> recordinuseflag = {0xFFFF};
    ds.Insert( recordinuseflag.GetAsDataElement() );
    Attribute<0x4,0x1420> offsetofreferencedlowerleveldirectoryentity = {0};
    ds.Insert( offsetofreferencedlowerleveldirectoryentity.GetAsDataElement() );
    Attribute<0x4,0x1430> directoryrecordtype;
    directoryrecordtype.SetValue( "IMAGE" );
    ds.Insert( directoryrecordtype.GetAsDataElement() );

    const char *sopuid = it->c_str();
    gdcm::Scanner::TagToValue const &ttv = scanner.GetMappingFromTagToValue(sopinstanceuid.GetTag(), sopuid);
    Attribute<0x0004,0x1500> referencedfileid;
    const char *fn_str = scanner.GetFilenameFromTagToValue(sopinstanceuid.GetTag(), sopuid);
    referencedfileid.SetNumberOfValues( 1 );
    gdcm::Filename fn = fn_str;
    referencedfileid.SetValue( fn.ToWindowsSlashes() );
    ds.Insert( referencedfileid.GetAsDataElement() );
    Attribute<0x0004,0x1510> referencedsopclassuidinfile;
    Attribute<0x8,0x16> sopclassuid;
    if( ttv.find( sopclassuid.GetTag() ) != ttv.end() )
      {
      referencedsopclassuidinfile.SetValue( ttv.find(sopclassuid.GetTag())->second );
      }
    ds.Insert( referencedsopclassuidinfile.GetAsDataElement() );
    Attribute<0x0004,0x1511> referencedsopinstanceuidinfile;
    Attribute<0x8,0x18> sopinstanceuid;
    if( ttv.find( sopinstanceuid.GetTag() ) != ttv.end() )
      {
      referencedsopinstanceuidinfile.SetValue( ttv.find(sopinstanceuid.GetTag())->second );
      }
    ds.Insert( referencedsopinstanceuidinfile.GetAsDataElement() );
    Attribute<0x0004,0x1512> referencedtransfersyntaxuidinfile;
    Attribute<0x2,0x10> transfersyntaxuid;
    if( ttv.find( transfersyntaxuid.GetTag() ) != ttv.end() )
      {
      referencedtransfersyntaxuidinfile.SetValue( ttv.find(transfersyntaxuid.GetTag())->second );
      }
    ds.Insert( referencedtransfersyntaxuidinfile.GetAsDataElement() );

    Attribute<0x20,0x13> instancenumber;
    if( ttv.find( instancenumber.GetTag() ) != ttv.end() )
      {
      instancenumber.SetValue( atoi(ttv.find(instancenumber.GetTag())->second) );
      }
    ds.Insert( instancenumber.GetAsDataElement() );

    //Attribute<0x8,0x8> imagetype;
    //gdcm::Scanner::ValuesType imagetypes = scanner.GetValues( imagetype.GetTag() );
    //gdcm::Scanner::ValuesType::const_iterator it = imagetypes.begin();
    //assert( imagetypes.size() == 1 );
    //imagetype.SetNumberOfValues( 1 );
    //imagetype.SetValue( it->c_str() );
    //ds.Replace( imagetype.GetAsDataElement() );

    sqi->AddItem( item );
    }

  return true;
}

DICOMDIRGenerator::DICOMDIRGenerator(  )
{
  Internals = new DICOMDIRGeneratorInternal;
}

DICOMDIRGenerator::~DICOMDIRGenerator(  )
{
  delete Internals;
}

void DICOMDIRGenerator::SetFilesames( FilenamesType const & fns )
{
  Internals->fns = fns;
}

bool DICOMDIRGenerator::Generate()
{
  gdcm::Scanner scanner;
  // <entry group="0002" element="0010" vr="UI" vm="1" name="Transfer Syntax UID"/>
  scanner.AddTag( Tag(0x02,0x10) );
  // <entry group="0010" element="0010" vr="PN" vm="1" name="Patient's Name"/>
  scanner.AddTag( Tag(0x10,0x10) );
  // <entry group="0010" element="0020" vr="LO" vm="1" name="Patient ID"/>
  scanner.AddTag( Tag(0x10,0x20) );
  // <entry group="0008" element="0060" vr="CS" vm="1" name="Modality"/>
  scanner.AddTag( Tag(0x8,0x60) );
  // <entry group="0020" element="0011" vr="IS" vm="1" name="Series Number"/>
  scanner.AddTag( Tag(0x20,0x11) );
  // <entry group="0008" element="0018" vr="UI" vm="1" name="SOP Instance UID"/>
  scanner.AddTag( Tag(0x8,0x18) );
  // <entry group="0008" element="0020" vr="DA" vm="1" name="Study Date"/>
  scanner.AddTag( Tag(0x8,0x20) );
  // <entry group="0008" element="0030" vr="TM" vm="1" name="Study Time"/>
  scanner.AddTag( Tag(0x8,0x30) );
  // <entry group="0008" element="1030" vr="LO" vm="1" name="Study Description"/>
  scanner.AddTag( Tag(0x8,0x1030) );
  // <entry group="0008" element="0050" vr="SH" vm="1" name="Accession Number"/>
  scanner.AddTag( Tag(0x8,0x50) );
  // <entry group="0020" element="0013" vr="IS" vm="1" name="Instance Number"/>
  scanner.AddTag( Tag(0x20,0x13) );
  // <entry group="0020" element="000d" vr="UI" vm="1" name="Study Instance UID"/>
  scanner.AddTag( Tag(0x20,0xd) );
  // <entry group="0020" element="0010" vr="SH" vm="1" name="Study ID"/>
  scanner.AddTag( Tag(0x20,0x10) );
  // <entry group="0020" element="000e" vr="UI" vm="1" name="Series Instance UID"/>
  scanner.AddTag( Tag(0x20,0xe) );
  // <entry group="0028" element="0004" vr="CS" vm="1" name="Photometric Interpretation"/>
  scanner.AddTag( Tag(0x28,0x4) );
  // <entry group="0028" element="0008" vr="IS" vm="1" name="Number of Frames"/>
  scanner.AddTag( Tag(0x28,0x8) );
  // <entry group="0050" element="0004" vr="CS" vm="1" name="Calibration Image"/>
  scanner.AddTag( Tag(0x50,0x4) );
  // <entry group="0010" element="0030" vr="DA" vm="1" name="Patient's Birth Date"/>
  scanner.AddTag( Tag(0x10,0x30) );
  // <entry group="0010" element="0040" vr="CS" vm="1" name="Patient's Sex"/>
  scanner.AddTag( Tag(0x10,0x40) );
  // <entry group="0008" element="0080" vr="LO" vm="1" name="Institution Name"/>
  scanner.AddTag( Tag(0x8,0x80) );
  // <entry group="0008" element="0016" vr="UI" vm="1" name="SOP Class UID"/>
  scanner.AddTag( Tag(0x8,0x16) );

  FilenamesType const &filenames = Internals->fns;
  if( !scanner.Scan( filenames ) )
    {
    return false;
    }

  scanner.Print( std::cout );

  // (0004,1220) SQ (Sequence with undefined length #=8)     # u/l, 1 DirectoryRecordSequence

  gdcm::DataSet &ds = GetFile().GetDataSet();

  Attribute<0x4,0x1130> filesetid;
  ds.Insert( filesetid.GetAsDataElement() );
  Attribute<0x4,0x1200> offsetofthefirstdirectoryrecordoftherootdirectoryentity = {0};
  ds.Insert( offsetofthefirstdirectoryrecordoftherootdirectoryentity.GetAsDataElement() );
  Attribute<0x4,0x1202> offsetofthelastdirectoryrecordoftherootdirectoryentity = { 0 };
  ds.Insert( offsetofthelastdirectoryrecordoftherootdirectoryentity.GetAsDataElement() );
  Attribute<0x4,0x1212> filesetconsistencyflag = {0};
  ds.Insert( filesetconsistencyflag.GetAsDataElement() );


  gdcm::DataElement de( Tag(0x4,0x1220) );

  SequenceOfItems * sqi = new SequenceOfItems;
  //DataElement de( sisq );
  de.SetVR( VR::SQ );
  de.SetValue( *sqi );
  de.SetVLToUndefined();

  ds.Insert( de );

  bool b;
  b = AddPatientDirectoryRecord(ds, scanner);
  b = AddStudyDirectoryRecord(ds, scanner);
  b = AddSeriesDirectoryRecord(ds, scanner);
  b = AddImageDirectoryRecord(ds, scanner);

/*
The DICOMDIR File shall use the Explicit VR Little Endian Transfer Syntax (UID=1.2.840.10008.1.2.1) to
encode the Media Storage Directory SOP Class. The DICOMDIR File shall comply with the DICOM File
Format specified in Section 7 of this Standard. In particular the:
a. SOP Class UID in the File Meta Information (header of the DICOMDIR File) shall have the
Value specified in PS 3.4 of this Standard for the Media Storage Directory SOP Class;
b. SOP Instance UID in the File Meta Information (header of the DICOMDIR File) shall contain
the File-set UID Value. The File-set UID is assigned by the Application Entity which created
the File-set (FSC role, see Section 8.3) with zero or more DICOM Files. This File-set UID
Value shall not be changed by any other Application Entities reading or updating the content of
the File-set.
*/
  FileMetaInformation &h = GetFile().GetHeader();
  gdcm::Attribute<0x2,0x2> at1;
  gdcm::MediaStorage ms = gdcm::MediaStorage::MediaStorageDirectoryStorage;
  const char* msstr = gdcm::MediaStorage::GetMSString(ms);
  at1.SetValue( msstr );
  h.Insert( at1.GetAsDataElement() );

  gdcm::Attribute<0x2,0x3> at2;
  gdcm::UIDGenerator uid;
  const char *mediastoragesopinstanceuid = uid.Generate();
  if( !gdcm::UIDGenerator::IsValid( mediastoragesopinstanceuid ) )
    {
    return 1;
    }
  at2.SetValue( mediastoragesopinstanceuid );
  h.Insert( at2.GetAsDataElement() );

  gdcm::TransferSyntax ts = gdcm::TransferSyntax::ExplicitVRLittleEndian;
  h.SetDataSetTransferSyntax( ts );

  std::cout << ds << std::endl;
  std::cout << h << std::endl;


  /* Very important step it should be the *VERY* last one */
  // We need to compute all offset, which can be only done when all attributes have been inserted.
  // Let's start with offsetofthefirstdirectoryrecordoftherootdirectoryentity :
  h.FillFromDataSet( ds );
  VL fmi_len = h.GetFullLength();
  VL fmi_len_offset = 0;
  gdcm::DataSet::ConstIterator it = ds.Begin();
  for( ; it != ds.End() && it->GetTag() != Tag(0x0004,0x1220); ++it)
    {
    const DataElement &de = *it;
    fmi_len_offset += de.GetLength<ExplicitDataElement>();
    }
  // Now add the partial length for attribute 0004,1220:
  fmi_len_offset += it->GetTag().GetLength();
  fmi_len_offset += it->GetVR().GetLength();
  fmi_len_offset += it->GetVR().GetLength();
  //std::cerr << fmi_len << " and " << fmi_len_offset << std::endl;
  offsetofthefirstdirectoryrecordoftherootdirectoryentity.SetValue( fmi_len + fmi_len_offset );
  ds.Replace( offsetofthefirstdirectoryrecordoftherootdirectoryentity.GetAsDataElement() );

  VL fmi_len_offset2 = 0;
{
  gdcm::DataSet::ConstIterator it = ds.Begin();
  for( ; it != ds.End() && it->GetTag() <= Tag(0x0004,0x1220); ++it)
    {
    const DataElement &de = *it;
    fmi_len_offset2 += de.GetLength<ExplicitDataElement>();
    }
}

{
  const gdcm::DataElement &de = ds.GetDataElement( Tag(0x4,0x1220) );
  const SequenceOfItems * sqi = de.GetSequenceOfItems();
  unsigned int n = sqi->GetNumberOfItems();
  const Item &item = sqi->GetItem( n ); // last item
  VL sub = item.GetLength<ExplicitDataElement>(); 
  // Let's substract item length as well as the item sequence delimiter end (tag + vl => 8)
  offsetofthelastdirectoryrecordoftherootdirectoryentity.SetValue( fmi_len + fmi_len_offset2 - sub - 8 );

  ds.Replace( offsetofthelastdirectoryrecordoftherootdirectoryentity.GetAsDataElement() );

  TraverseDirectoryRecords(scanner, sqi, offsetofthefirstdirectoryrecordoftherootdirectoryentity.GetValue() );
}

  return true;
}

void DICOMDIRGenerator::SetFile(const File& f)
{
  Internals->F = f;
}

File &DICOMDIRGenerator::GetFile()
{
  return *Internals->F;
}

} // end namespace gdcm
