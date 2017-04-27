/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImage.h"
#include "gdcmImageWriter.h"
#include "gdcmFileDerivation.h"
#include "gdcmUIDGenerator.h"
#include "gdcmImageRegionReader.h"
#include "gdcmDirectory.h"
#include "gdcmScanner.h"
#include "gdcmFilename.h"
#include "gdcmFileStreamer.h"
#include "gdcmAnonymizer.h"
#include "gdcmAttribute.h"

static gdcm::Tag t1(0x8,0x16);
static gdcm::Tag t2(0x8,0x18);
static gdcm::Tag t3(0x20,0xe);
static gdcm::Tag t4(0x20,0x52);
 
static bool EmptyMaskDICOMFile( gdcm::UIDGenerator & uid, const gdcm::Scanner & s,
  const std::map< std::string, std::string > & seriesuidhash,
  const std::map< std::string, std::string > & framerefuidhash,
  const char * outfile, const char * filename )
{
  if( s.IsKey( filename ) )
  {
    gdcm::ImageRegionReader irr;
    irr.SetFileName( filename );
    const bool b3 = irr.ReadInformation();
    (void)b3;
    size_t buflen = irr.ComputeBufferLength();

    // Step 2: DERIVED object
    gdcm::FileDerivation fd;
    const char * ReferencedSOPClassUID =  s.GetValue (filename, t1);
    const char * ReferencedSOPInstanceUID =  s.GetValue (filename, t2);
    if( !fd.AddReference( ReferencedSOPClassUID, ReferencedSOPInstanceUID ) )
    {
      //std::cerr << "AddRef: " << (ReferencedSOPClassUID ? ReferencedSOPClassUID : "") << "," << (ReferencedSOPInstanceUID ? ReferencedSOPInstanceUID : "") << std::endl;
      std::cerr << "AddRef: " << filename << std::endl;
      // This is not considered an error to not reference, eg. UID padded with 0
    }

    // CID 7202 Source Image Purposes of Reference
    // DCM 121321 Mask image for image processing operation
    fd.SetPurposeOfReferenceCodeSequenceCodeValue( 121321 );
    // CID 7203 Image Derivation
    // DCM 113047 Pixel by pixel mask
    fd.SetDerivationCodeSequenceCodeValue( 113047 );
    fd.SetDerivationDescription( "Empty Mask Derivation" );
    fd.SetAppendDerivationHistory( true );
    fd.SetFile( irr.GetFile() );
    if( !fd.Derive() )
    {
      std::cerr << "Sorry could not derive using input info" << std::endl;
      return false;
    }

    gdcm::Anonymizer ano;
    ano.SetFile( fd.GetFile() );
    ano.RemoveGroupLength();
    ano.Replace (t2, uid.Generate());
    const char * oldseriesuid =  s.GetValue (filename, t3);
    const char * oldframerefuid =  s.GetValue (filename, t4);
    if( oldseriesuid )
    {
      std::map< std::string, std::string >::const_iterator it1 = seriesuidhash.find( oldseriesuid );
      ano.Replace (t3, it1->second.c_str() );
    }
    if( oldframerefuid )
    {
      std::map< std::string, std::string >::const_iterator it2 = framerefuidhash.find( oldframerefuid );
      ano.Replace (t4, it2->second.c_str() );
    }

    {
      gdcm::DataSet& ds = ano.GetFile().GetDataSet();
      gdcm::Attribute<0x0008,0x0008> at3;
      gdcm::Attribute<0x0008,0x0008> at4;
      at3.SetFromDataSet( ds );
      unsigned int nvalues = at3.GetNumberOfValues();
      unsigned int newvalues = std::max( nvalues, 4u );
      at4.SetNumberOfValues( newvalues );
      // copy original ones:
      for( unsigned int i = 0u; i < nvalues; ++i )
      {
        at4.SetValue(i, at3.GetValue(i) );
      }
      // Make up non empty values:
      static const gdcm::CSComp values[] = {"DERIVED","SECONDARY","OTHER"};
      for( unsigned int i = nvalues; i < 3u;  ++i )
      {
        at4.SetValue(i, values[i] );
      }
      // why not:
      at4.SetValue( 3u, "MASK" );
      ds.Replace( at4.GetAsDataElement() );
    }

    gdcm::File & file = ano.GetFile();
    gdcm::FileMetaInformation & fmi = file.GetHeader();
    const gdcm::TransferSyntax & orits = fmi.GetDataSetTransferSyntax();
    gdcm::TransferSyntax::TSType newts = gdcm::TransferSyntax::ImplicitVRLittleEndian;
    if( orits.IsExplicit() )
    {
      newts = gdcm::TransferSyntax::ExplicitVRLittleEndian;
    }
    fmi.Clear();
    fmi.SetDataSetTransferSyntax( newts );

    gdcm::Writer w;
    w.SetFile( ano.GetFile() );

    // Set the filename:
    w.SetFileName( outfile );
    if( !w.Write() )
    {
      return false;
    }
    gdcm::FileStreamer fs;
    fs.SetTemplateFileName(outfile);
    fs.SetOutputFileName(outfile);
    gdcm::Tag pixeldata (0x7fe0, 0x0010);
    fs.CheckDataElement( pixeldata );
    if( !fs.StartDataElement( pixeldata ) )
    {
      std::cerr << "StartDataElement" << std::endl;
      return false;
    }
    {
      const size_t chunk = 4096;
      char bytes[chunk] = {};
      const size_t nchunks = buflen / chunk;
      const size_t remain = buflen % chunk;
      for( size_t i = 0; i < nchunks; ++i )
      {
        // Read the source file into a byte array.
        fs.AppendToDataElement( pixeldata, bytes, chunk );
      }
      fs.AppendToDataElement( pixeldata, bytes, remain );
    }
    if( !fs.StopDataElement( pixeldata ) )
    {
      // Most likely an issue with Pixel Data Length computation:
      std::cerr << "StopDataElement" << std::endl;
      return false;
    }
  }
  else
  {
    std::cerr << "Not DICOM file: " << filename << std::endl;
    return false;
  }
  return true;
}

int main(int, char *argv[])
{
  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle( "EmptyMask" );
  const char * dirname = argv[1];
  const char * outdir = argv[2];
  gdcm::System::FileIsDirectory( dirname );
  gdcm::System::MakeDirectory( outdir );
  gdcm::Directory d;
  const unsigned int nfiles = d.Load( dirname, true );
  (void)nfiles;
  gdcm::Directory::FilenamesType const & filenames = d.GetFilenames();

  gdcm::Trace::WarningOff();
  gdcm::Trace::ErrorOff();

  gdcm::Scanner s;
  s.AddTag( t1 );
  s.AddTag( t2 );
  s.AddTag( t3 );
  s.AddTag( t4 );
  const bool b2 = s.Scan( filenames );
  (void)b2;
  gdcm::UIDGenerator uid;
  int ret = 0;
  std::map< std::string, std::string > seriesuidhash;
  {
    gdcm::Scanner::ValuesType vt = s.GetValues(t3);
    for(
        gdcm::Scanner::ValuesType::const_iterator it = vt.begin();
        it != vt.end(); ++it )
    {
      const char * newseriesuid = uid.Generate();
      seriesuidhash.insert( 
          std::make_pair( *it, newseriesuid ) );
    }
  }
  std::map< std::string, std::string > framerefuidhash;
  {
    gdcm::Scanner::ValuesType vt = s.GetValues(t4);
    // Frame of Reference are relative to Series UID
    // http://dicom.nema.org/medical/Dicom/2015a/output/chtml/part03/sect_C.7.4.html
    for(
        gdcm::Scanner::ValuesType::const_iterator it = vt.begin();
        it != vt.end(); ++it )
    {
      const char * newframerefuid = uid.Generate();
      framerefuidhash.insert( 
          std::make_pair( *it, newframerefuid ) );
    }
  }
  for( gdcm::Directory::FilenamesType::const_iterator it =  filenames.begin(); it != filenames.end(); ++it )
  {
    const char * filename = it->c_str();
    gdcm::Filename fn( filename );
    std::string outfile = outdir;
    outfile += '/';
    outfile += fn.GetName();
    if( !EmptyMaskDICOMFile( uid, s, seriesuidhash, framerefuidhash, outfile.c_str(), filename ) )
    {
      std::cerr << "Failure to EmptyMask" << std::endl;
      gdcm::System::RemoveFile(outfile.c_str());
      ret = 1;
    }
  }

  return ret;
}
