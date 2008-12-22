/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
 */
#include "gdcmUIDGenerator.h"
#include "gdcmWriter.h"
#include "gdcmAttribute.h"
#include "gdcmSystem.h"

#include <poppler/poppler-config.h>
#include <poppler/PDFDoc.h>
#include <poppler/UnicodeMap.h>
#include <poppler/PDFDocEncoding.h>
#include <poppler/GlobalParams.h>

#include <string>

std::string getInfoDate(Dict *infoDict, const char *key)
{
  Object obj;
  char *s;
  int year, mon, day, hour, min, sec, n;
  struct tm tmStruct;
  char buf[256];
  std::string out;

  if (infoDict->lookup((char*)key, &obj)->isString())
    {
    s = obj.getString()->getCString();
    if (s[0] == 'D' && s[1] == ':')
      {
      s += 2;
      }
    if ((n = sscanf(s, "%4d%2d%2d%2d%2d%2d",
          &year, &mon, &day, &hour, &min, &sec)) >= 1)
      {
      switch (n)
        {
      case 1: mon = 1;
      case 2: day = 1;
      case 3: hour = 0;
      case 4: min = 0;
      case 5: sec = 0;
        }
      tmStruct.tm_year = year - 1900;
      tmStruct.tm_mon = mon - 1;
      tmStruct.tm_mday = day;
      tmStruct.tm_hour = hour;
      tmStruct.tm_min = min;
      tmStruct.tm_sec = sec;
      tmStruct.tm_wday = -1;
      tmStruct.tm_yday = -1;
      tmStruct.tm_isdst = -1;
/*
      // compute the tm_wday and tm_yday fields
      if (mktime(&tmStruct) != (time_t)-1 &&
        strftime(buf, sizeof(buf), "%c", &tmStruct)) {
        fputs(buf, stdout);
      } else {
        fputs(s, stdout);
      }
      } else {
        fputs(s, stdout);
*/
      }
    //fputc('\n', stdout);
    char date[18];
    time_t t = mktime(&tmStruct);
    if( t != -1 )
      {
      if( gdcm::System::FormatDateTime(date, t) )
        out = date;
      }
    }
  obj.free();
  return out;
}

std::string getInfoString(Dict *infoDict, const char *key, UnicodeMap *uMap)
{
  Object obj;
  GooString *s1;
  GBool isUnicode;
  Unicode u;
  char buf[8];
  int i, n;
  std::string out;

  if (infoDict->lookup((char*)key, &obj)->isString())
    {
    s1 = obj.getString();
    if ((s1->getChar(0) & 0xff) == 0xfe &&
      (s1->getChar(1) & 0xff) == 0xff)
      {
      isUnicode = gTrue;
      i = 2;
      }
    else 
      {
      isUnicode = gFalse;
      i = 0;
      }
    while (i < obj.getString()->getLength())
      {
      if (isUnicode)
        {
        u = ((s1->getChar(i) & 0xff) << 8) |
          (s1->getChar(i+1) & 0xff);
        i += 2;
        }
      else
        {
        u = pdfDocEncoding[s1->getChar(i) & 0xff];
        ++i;
        }
      n = uMap->mapUnicode(u, buf, sizeof(buf));
      //fwrite(buf,1,n,stdout);
      out.append( std::string(buf, n) );
      }
    }
  obj.free();
  return out;
}

int main (int argc, char *argv[])
{
  if( argc < 1 )
    {
    return 1;
    }
  GooString *ownerPW, *userPW;
  GooString *fileName;
  PDFDoc *doc;
  Object info;
  UnicodeMap *uMap;
  ownerPW = NULL;
  userPW = NULL;
#ifdef LIBPOPPLER_GLOBALPARAMS_CSTOR_HAS_PARAM
  globalParams = new GlobalParams(0);
#else
  globalParams = new GlobalParams();
#endif
  uMap = globalParams->getTextEncoding();

  const char *filename = argv[1];
  const char *outfilename = argv[2];
  fileName = new GooString( filename );
  Object obj;

  obj.initNull();
  doc = new PDFDoc(fileName, ownerPW, userPW);

  if (!doc->isOk())
    {
    return 1;
    }

  doc->getDocInfo(&info);
  if (!info.isDict())
    {
    return 1;
    }
    std::string title    = getInfoString(info.getDict(), "Title",    uMap);
std::cout << "title:" << title.size() << std::endl;
    std::string subject  = getInfoString(info.getDict(), "Subject",  uMap);
    std::string keywords = getInfoString(info.getDict(), "Keywords", uMap);
    std::string author   = getInfoString(info.getDict(), "Author",   uMap);
    std::string creator  = getInfoString(info.getDict(), "Creator",  uMap);
    std::string producer = getInfoString(info.getDict(), "Producer", uMap);
    std::string creationdate = getInfoDate(info.getDict(),   "CreationDate");
    std::string moddate      = getInfoDate(info.getDict(),   "ModDate");
  info.free();

  gdcm::Writer writer;
  gdcm::DataElement de( gdcm::Tag( 0x42,0x11) );
  de.SetVR( gdcm::VR::OB );
  std::ifstream is;
  is.open (filename, std::ios::binary );


  // get length of file:
  is.seekg (0, std::ios::end);
  int length = is.tellg();
  is.seekg (0, std::ios::beg);

  char *buffer = new char [length];

  // read data as a block:
  is.read (buffer,length);
  is.close();

  de.SetByteValue( buffer, length );
  delete[] buffer;

  gdcm::FileMetaInformation &fmi = writer.GetFile().GetHeader();
  gdcm::TransferSyntax ts = gdcm::TransferSyntax::ExplicitVRLittleEndian;
  fmi.SetDataSetTransferSyntax( ts );
  gdcm::DataSet &ds = writer.GetFile().GetDataSet();
  ds.Insert( de );

  gdcm::UIDGenerator uid;
{
    const char *sop = uid.Generate();
    gdcm::DataElement de( gdcm::Tag(0x0008,0x0018) );
    de.SetByteValue( sop, strlen(sop) );
    de.SetVR( gdcm::Attribute<0x0008, 0x0018>::GetVR() );
    ds.Insert( de );
}

  gdcm::MediaStorage ms = gdcm::MediaStorage::EncapsulatedPDFStorage;
    {
    gdcm::DataElement de( gdcm::Tag(0x0008, 0x0016) );
    const char* msstr = gdcm::MediaStorage::GetMSString(ms);
    de.SetByteValue( msstr, strlen(msstr) );
    de.SetVR( gdcm::Attribute<0x0008, 0x0016>::GetVR() );
    ds.Insert( de );
    }

  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle( "gdcmpdf" );

  char date[18];
  const size_t datelen = 8;
  bool b = gdcm::System::GetCurrentDateTime(date);
  std::cout << date << std::endl;

{
  gdcm::Attribute<0x0008, 0x005> at;
  const char s[]="ISO_IR 100";
  at.SetNumberOfValues( 1 );
  at.SetValue( s );
  ds.Insert( at.GetAsDataElement() );
}
{
  gdcm::Attribute<0x0008, 0x0012> at;
  std::string tmp( date, datelen );
  at.SetValue( tmp.c_str() );
  ds.Insert( at.GetAsDataElement() );
}

  const size_t timelen = 6; // get rid of milliseconds
{
  gdcm::Attribute<0x0008, 0x0013> at;
  std::string tmp( date+datelen, timelen);
  at.SetValue( tmp.c_str() );
  ds.Insert( at.GetAsDataElement() );
}
//(0008,0020) DA (no value available)                     #   0, 0 StudyDate
{
  gdcm::Attribute<0x0008, 0x0020> at;
  ds.Insert( at.GetAsDataElement() );
}
//(0008,0023) DA (no value available)                     #   0, 0 ContentDate
{
  gdcm::Attribute<0x0008, 0x0023> at;
  std::string tmp( creationdate.c_str(), datelen );
  at.SetValue( tmp.c_str() );
  ds.Insert( at.GetAsDataElement() );
}
//(0008,002a) DT (no value available)                     #   0, 0 AcquisitionDatetime
{
  gdcm::Attribute<0x0008, 0x002a> at;
  ds.Insert( at.GetAsDataElement() );
}
//(0008,0030) TM (no value available)                     #   0, 0 StudyTime
{
  gdcm::Attribute<0x0008, 0x0030> at;
  ds.Insert( at.GetAsDataElement() );
}
//(0008,0033) TM (no value available)                     #   0, 0 ContentTime
{
  gdcm::Attribute<0x0008, 0x0033> at;
  std::string tmp( creationdate.c_str() + datelen, timelen);
  at.SetValue( tmp.c_str() );
  ds.Insert( at.GetAsDataElement() );
}
//(0008,0050) SH (no value available)                     #   0, 0 AccessionNumber
{
  gdcm::Attribute<0x0008, 0x0050> at;
  ds.Insert( at.GetAsDataElement() );
}
//(0008,0060) CS [OT]                                     #   2, 1 Modality
{
  gdcm::Attribute<0x0008, 0x0060> at;
  at.SetValue( "OT" );
  ds.Insert( at.GetAsDataElement() );
}
//(0008,0064) CS [WSD]                                    #   4, 1 ConversionType
{
  gdcm::Attribute<0x0008, 0x0064> at;
  at.SetValue( "WSD" );
  ds.Insert( at.GetAsDataElement() );
}
//(0008,0070) LO (no value available)                     #   0, 0 Manufacturer
{
  gdcm::Attribute<0x0008, 0x0070> at;
  at.SetValue( creator.c_str() );
  ds.Insert( at.GetAsDataElement() );
}
//(0008,0090) PN (no value available)                     #   0, 0 ReferringPhysiciansName
{
  gdcm::Attribute<0x0008, 0x0090> at;
  ds.Insert( at.GetAsDataElement() );
}
//(0010,0010) PN (no value available)                     #   0, 0 PatientsName
{
  gdcm::Attribute<0x0010, 0x0010> at;
  at.SetValue( author.c_str() );
  ds.Insert( at.GetAsDataElement() );
}
//(0010,0020) LO (no value available)                     #   0, 0 PatientID
{
  gdcm::Attribute<0x0010, 0x0020> at;
  ds.Insert( at.GetAsDataElement() );
}
//(0010,0030) DA (no value available)                     #   0, 0 PatientsBirthDate
{
  gdcm::Attribute<0x0010, 0x0030> at;
  ds.Insert( at.GetAsDataElement() );
}
//(0010,0040) CS (no value available)                     #   0, 0 PatientsSex
{
  gdcm::Attribute<0x0010, 0x0040> at;
  ds.Insert( at.GetAsDataElement() );
}
{
  gdcm::Attribute<0x0018, 0x1020> at;
  at.SetNumberOfValues( 1 );
  at.SetValue( producer.c_str() );
  ds.Insert( at.GetAsDataElement() );
}
//(0020,000d) UI [1.2.276.0.7230010.3.1.4.8323329.511.1228064157.1] #  48, 1 StudyInstanceUID
{
  gdcm::Attribute<0x0020, 0x000d> at;
  at.SetValue( uid.Generate() );
  ds.Insert( at.GetAsDataElement() );
}
//(0020,000e) UI [1.2.276.0.7230010.3.1.4.8323329.511.1228064157.2] #  48, 1 SeriesInstanceUID
{
  gdcm::Attribute<0x0020, 0x000e> at;
  at.SetValue( uid.Generate() );
  ds.Insert( at.GetAsDataElement() );
}
//(0020,0010) SH (no value available)                     #   0, 0 StudyID
{
  gdcm::Attribute<0x0020, 0x0010> at;
  ds.Insert( at.GetAsDataElement() );
}
//(0020,0011) IS [1]                                      #   2, 1 SeriesNumber
{
  gdcm::Attribute<0x0020, 0x0011> at = { 1 };
  ds.Insert( at.GetAsDataElement() );
}
//(0020,0013) IS [1]                                      #   2, 1 InstanceNumber
{
  gdcm::Attribute<0x0020, 0x0013> at = { 1 };
  ds.Insert( at.GetAsDataElement() );
}
//(0028,0301) CS [YES]                                    #   4, 1 BurnedInAnnotation
{
  gdcm::Attribute<0x0028, 0x0301> at;
  at.SetValue( "YES" );
  ds.Insert( at.GetAsDataElement() );
}
//(0040,a043) SQ (Sequence with explicit length #=0)      #   0, 1 ConceptNameCodeSequence
//(fffe,e0dd) na (SequenceDelimitationItem for re-encod.) #   0, 0 SequenceDelimitationItem
{
  gdcm::Attribute<0x0040, 0xa043> at;
  gdcm::DataElement de( at.GetTag() );
  de.SetVR( at.GetVR() );
  //ds.Insert( at.GetAsDataElement() );
  ds.Insert( de );
}
//(0042,0010) ST (no value available)                     #   0, 0 DocumentTitle
{
  gdcm::Attribute<0x0042, 0x0010> at;
  at.SetValue( title.c_str() );
  ds.Insert( at.GetAsDataElement() );
}
//(0042,0011) OB 25\50\44\46\2d\31\2e\34\0a\25\e7\f3\cf\d3\0a\32\34\35\38\38\20\30... # 6861900, 1 EncapsulatedDocument
//(0042,0012) LO [application/pdf]                        #  16, 1 MIMETypeOfEncapsulatedDocument
{
  gdcm::Attribute<0x0042, 0x0012> at;
  at.SetValue( "application/pdf" );
  ds.Insert( at.GetAsDataElement() );
}


  writer.SetFileName( outfilename );
  if( !writer.Write() )
  {
  return 1;
  }

  return 0;
}

