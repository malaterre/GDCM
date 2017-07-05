/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmEmptyMaskGenerator.h"

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
#include "gdcmTagKeywords.h"

namespace gdcm {

struct EmptyMaskGenerator::impl
{
  static const gdcm::Tag TSOPClassUID;
  static const gdcm::Tag TSOPInstanceUID;
  static const gdcm::Tag TSeriesInstanceUID;
  static const gdcm::Tag TFrameOfReferenceUID;

  SOPClassUIDMode mode;
  std::string inputdir;
  std::string outputdir;
  gdcm::UIDGenerator uid;
  std::map< std::string, std::string > seriesuidhash;
  std::map< std::string, std::string > framerefuidhash;
  gdcm::Scanner s;
  bool collectuids(gdcm::Tag const & tag, std::map< std::string, std::string > & hash);
  bool setup(const char * dirname, const char * outdir);
  bool setmask( gdcm::File & file );
  bool derive( const char * filename, gdcm::File & file );
  bool anonymizeattributes( const char * filename, gdcm::File & file );
  bool populateattributes( const char * filename, gdcm::File const & orifile, gdcm::File & file );
  bool setts( gdcm::File & file );
  bool run(const char * filename, const char * outfile);
};

const gdcm::Tag EmptyMaskGenerator::impl::TSOPClassUID = gdcm::Tag(0x0008,0x0016);
const gdcm::Tag EmptyMaskGenerator::impl::TSOPInstanceUID = gdcm::Tag(0x0008,0x0018);
const gdcm::Tag EmptyMaskGenerator::impl::TSeriesInstanceUID = gdcm::Tag(0x0020,0x000e);
const gdcm::Tag EmptyMaskGenerator::impl::TFrameOfReferenceUID = gdcm::Tag(0x0020,0x0052);

bool EmptyMaskGenerator::impl::collectuids( gdcm::Tag const & tag, std::map< std::string, std::string > & hash)
{
  gdcm::Scanner::ValuesType vt = s.GetValues(tag);
  for( gdcm::Scanner::ValuesType::const_iterator it = vt.begin();
    it != vt.end(); ++it )
    {
    const char * newuid = uid.Generate();
    hash.insert( std::make_pair( *it, newuid ) );
    }
  return true;
}

bool EmptyMaskGenerator::impl::setmask( gdcm::File & file )
{
  gdcm::DataSet& ds = file.GetDataSet();
  namespace kwd = gdcm::Keywords;
  kwd::ImageType imtype;
  kwd::ImageType copy;
  imtype.SetFromDataSet( ds );
  unsigned int nvalues = imtype.GetNumberOfValues();
  unsigned int newvalues = std::max( nvalues, 4u );
  copy.SetNumberOfValues( newvalues );
  // copy original ones:
  for( unsigned int i = 0u; i < nvalues; ++i )
    {
    copy.SetValue(i, imtype.GetValue(i) );
    }
  // Make up non empty values:
  static const gdcm::CSComp values[] = {"DERIVED","SECONDARY","OTHER"};
  for( unsigned int i = nvalues; i < 3u;  ++i )
    {
    copy.SetValue(i, values[i] );
    }
  // The fourth value is required to be set to 'MASK' for SD
  copy.SetValue( 3u, "MASK" );
  ds.Replace( copy.GetAsDataElement() );
  return true;
}

bool EmptyMaskGenerator::impl::setup(const char * dirname, const char * outdir)
{
  if( !gdcm::System::FileIsDirectory( dirname ) )
    return false;
  if( !gdcm::System::MakeDirectory( outdir ) )
    return false;
  gdcm::Directory d;
  // recursive search by default
  const unsigned int nfiles = d.Load( dirname, true );
  if( nfiles == 0 )
    {
    gdcmDebugMacro( "No files found in: " << dirname );
    return false;
    }
  gdcm::Directory::FilenamesType const & filenames = d.GetFilenames();

  s.AddTag( TSOPClassUID );
  s.AddTag( TSOPInstanceUID );
  s.AddTag( TSeriesInstanceUID );
  s.AddTag( TFrameOfReferenceUID );
  // reduce verbosity when looping over a set of files:
  gdcm::Trace::WarningOff();
  if( !s.Scan( filenames ) )
    {
    gdcmDebugMacro( "Scanner failure for directory: " << dirname );
    return false;
    }
  if( !collectuids( TSeriesInstanceUID, seriesuidhash ) ) return false;
  // Frame of Reference are relative to Series UID
  // http://dicom.nema.org/medical/Dicom/2015a/output/chtml/part03/sect_C.7.4.html
  if( !collectuids( TFrameOfReferenceUID, framerefuidhash ) ) return false;

  return true;
}

bool EmptyMaskGenerator::impl::derive( const char * filename, gdcm::File & file )
{
  gdcm::FileDerivation fd;
  const char * referencedsopclassuid = s.GetValue (filename, TSOPClassUID);
  const char * referencedsopinstanceuid = s.GetValue (filename, TSOPInstanceUID);
  if( !fd.AddReference( referencedsopclassuid, referencedsopinstanceuid ) )
    {
    gdcmDebugMacro( "Impossible to AddRef: " << filename );
    // This is not considered an error to not reference, eg. UID padded with 0
    }

  // CID 7202 Source Image Purposes of Reference
  // DCM 121321 Mask image for image processing operation
  fd.SetPurposeOfReferenceCodeSequenceCodeValue( 121321 );
  // CID 7203 Image Derivation
  // DCM 113047 Pixel by pixel mask
  fd.SetDerivationCodeSequenceCodeValue( 113047 );
  fd.SetDerivationDescription( "Empty Mask Derivation" );
  // always append derivation history to any existing one:
  fd.SetAppendDerivationHistory( true );
  fd.SetFile( file );
  if( !fd.Derive() )
    {
    gdcmDebugMacro( "Sorry could not derive using input info" );
    return false;
    }
  return true;
}

bool EmptyMaskGenerator::impl::anonymizeattributes( const char * filename, gdcm::File & file )
{
  gdcm::Anonymizer ano;
  ano.SetFile( file );
  ano.RemoveGroupLength();
  ano.RemovePrivateTags();
  namespace kwd = gdcm::Keywords;
  ano.Remove( kwd::WindowCenter::GetTag() );
  ano.Remove( kwd::WindowWidth::GetTag() );
  if( !ano.Replace (TSOPInstanceUID, uid.Generate()) ) return false;
  const char * oldseriesuid = s.GetValue (filename, TSeriesInstanceUID);
  const char * oldframerefuid = s.GetValue (filename, TFrameOfReferenceUID);
  if( oldseriesuid )
    {
    std::map< std::string, std::string >::const_iterator it1 = seriesuidhash.find( oldseriesuid );
    if( !ano.Replace (TSeriesInstanceUID, it1->second.c_str() ) ) return false;
    }
  if( oldframerefuid )
    {
    std::map< std::string, std::string >::const_iterator it2 = framerefuidhash.find( oldframerefuid );
    if( !ano.Replace (TFrameOfReferenceUID, it2->second.c_str() ) ) return false;
    }
  return true;
}

bool EmptyMaskGenerator::impl::populateattributes( const char * filename, gdcm::File const & orifile, gdcm::File & file )
{
  namespace kwd = gdcm::Keywords;
  gdcm::DataSet & ds = file.GetDataSet();

  // ContentDate
  char date[22];
  const size_t datelen = 8;
  gdcm::System::GetCurrentDateTime(date);
  kwd::ContentDate contentdate;
  // Do not copy the whole cstring:
  contentdate.SetValue( gdcm::DAComp( date, datelen ) );
  ds.Insert( contentdate.GetAsDataElement() );
  // ContentTime
  const size_t timelen = 6 + 1 + 6; // time + milliseconds
  kwd::ContentTime contenttime;
  // Do not copy the whole cstring:
  contenttime.SetValue( gdcm::TMComp(date+datelen, timelen) );
  ds.Insert( contenttime.GetAsDataElement() );

  const gdcm::DataSet & orids = orifile.GetDataSet();
  kwd::SeriesInstanceUID seriesinstanceuid;
  seriesinstanceuid.SetValue( uid.Generate() ); // In case original instance is missing Series Instance UID
  kwd::SeriesNumber seriesnumber = { 1 };
  const char * oldseriesuid = s.GetValue (filename, TSeriesInstanceUID);
  if( oldseriesuid )
    {
    std::map< std::string, std::string >::iterator it =
      seriesuidhash.find( oldseriesuid );
    seriesinstanceuid.SetValue( it->second.c_str() );
    std::map< std::string, std::string >::difference_type diff =
      std::distance(seriesuidhash.begin(),it);
    seriesnumber.SetValue( 1 + diff ); // Start at one
    }
  ds.Insert( seriesinstanceuid.GetAsDataElement() );
  ds.Insert( seriesnumber.GetAsDataElement() );
  kwd::FrameOfReferenceUID frameref;
  frameref.SetValue( uid.Generate() );
  const char * oldframerefuid = s.GetValue (filename, TFrameOfReferenceUID);
  if( oldframerefuid )
    {
    std::map< std::string, std::string >::const_iterator it = framerefuidhash.find( oldframerefuid );
    frameref.SetValue( it->second.c_str() );
    }
  ds.Insert( frameref.GetAsDataElement() );
  kwd::InstanceNumber instancenum = { 1 };
  if( orids.FindDataElement( instancenum.GetTag() ) )
    {
    instancenum.SetFromDataSet( orids );
    }
  else
    {
    static unsigned int counter = 0; // unsigned will wrap properly
    instancenum.SetValue( counter++ );
    }
  ds.Insert( instancenum.GetAsDataElement() );
  kwd::StudyInstanceUID studyinstanceuid;
  studyinstanceuid.SetFromDataSet( orids );
  ds.Insert( studyinstanceuid.GetAsDataElement() );
  kwd::StudyID studyid = { "ST1" };
  studyid.SetFromDataSet( orids );
  ds.Insert( studyid.GetAsDataElement() );
  kwd::PatientID patientid;
  patientid.SetFromDataSet( orids );
  ds.Insert( patientid.GetAsDataElement() );
  kwd::PositionReferenceIndicator pri;
  ds.Insert( pri.GetAsDataElement() );
  kwd::BodyPartExamined bodypartex;
  bodypartex.SetFromDataSet( orids );
  ds.Insert( bodypartex.GetAsDataElement() );
  // Sync with Body Part Examined:
  kwd::Laterality lat;
  if( orids.FindDataElement( lat.GetTag() ) )
    {
    lat.SetFromDataSet( orids );
    ds.Insert( lat.GetAsDataElement() );
    }
  kwd::PatientOrientation pator;
  pator.SetFromDataSet( orids );
  ds.Insert( pator.GetAsDataElement() );
  kwd::BurnedInAnnotation bia = { "NO" };
  ds.Insert( bia.GetAsDataElement() );
  kwd::ConversionType convtype = { "SYN" };
  ds.Insert( convtype.GetAsDataElement() );
  kwd::PresentationLUTShape plutshape = { "IDENTITY" }; // MONOCHROME2
  ds.Insert( plutshape.GetAsDataElement() );
  kwd::SOPClassUID sopclassuid;
  // gdcm will pick the Word in case Byte class is not compatible:
  gdcm::MediaStorage ms = gdcm::MediaStorage::MultiframeGrayscaleByteSecondaryCaptureImageStorage;
  sopclassuid.SetValue( ms.GetString() );
  ds.Insert( sopclassuid.GetAsDataElement() );
  return true;
}

bool EmptyMaskGenerator::impl::setts( gdcm::File & file )
{
  gdcm::FileMetaInformation & fmi = file.GetHeader();
  const gdcm::TransferSyntax & orits = fmi.GetDataSetTransferSyntax();
  gdcm::TransferSyntax::TSType newts = gdcm::TransferSyntax::ImplicitVRLittleEndian;
  if( orits.IsExplicit() )
    {
    newts = gdcm::TransferSyntax::ExplicitVRLittleEndian;
    }
  fmi.Clear();
  fmi.SetDataSetTransferSyntax( newts );
  return true;
}

bool EmptyMaskGenerator::impl::run(const char * filename, const char * outfile)
{
  if( !s.IsKey( filename ) )
    {
    gdcmErrorMacro( "Not DICOM file: " << filename );
    return false;
    }

  gdcm::ImageRegionReader irr;
  irr.SetFileName( filename );
  if( !irr.ReadInformation() )
    {
    gdcmErrorMacro( "Impossible to ReadInformation (not an image?): " << filename );
    return false;
    }
  size_t buflen = irr.ComputeBufferLength();
  gdcm::Image & img = irr.GetImage();
  if( img.GetPhotometricInterpretation() != gdcm::PhotometricInterpretation::MONOCHROME1
   && img.GetPhotometricInterpretation() != gdcm::PhotometricInterpretation::MONOCHROME2 )
    {
    gdcmErrorMacro( "Cannot process PhotometricInterpretation from: " << filename );
    return false;
    }

  if( mode == UseOriginalSOPClassUID )
    {
    gdcm::File & file = irr.GetFile();
    // derive operation needs to operate on original attributes (before anonymization):
    if( !derive( filename, file ) ) return false;
    // copy original attributes:
    if( !anonymizeattributes( filename, file ) ) return false;
    if( !setmask( file ) ) return false;
    if( !setts( file ) ) return false;

    gdcm::Writer w;
    w.SetFile( file );
    w.SetFileName( outfile );
    if( !w.Write() )
      {
      return false;
      }
    }
  else if ( mode == UseGrayscaleSecondaryImageStorage )
    {
    gdcm::ImageWriter w;
    gdcm::File & file = w.GetFile();
    if( !derive( filename, file ) ) return false;
    // create attributes:
    if( !populateattributes( filename, irr.GetFile(), file ) ) return false;
    if( !setmask( file ) ) return false;
    if( !setts( file ) ) return false;

    gdcm::PixelFormat & pf = img.GetPixelFormat();
    pf.SetPixelRepresentation(0); // always overwrite to unsigned
    img.SetSlope(1);
    img.SetIntercept(0);
    w.SetImage( img );
    w.SetFileName( outfile );
    // sentinel, SC is never acceptable:
    if( w.ComputeTargetMediaStorage() == gdcm::MediaStorage::SecondaryCaptureImageStorage )
      {
      gdcmErrorMacro( "Failure to compute MediaStorage: " << filename );
      return false;
      }
    if( !w.Write() )
      {
      return false;
      }
    }
  else
    {
    // possibly dead code, but make sure to report an error for invalid state:
    return false;
    }

  // now create the empty pixel data element, a chunk at a time:
  gdcm::FileStreamer fs;
  fs.SetTemplateFileName(outfile);
  fs.SetOutputFileName(outfile);
  gdcm::Tag pixeldata (0x7fe0, 0x0010);
  fs.CheckDataElement( pixeldata ); // double check generated output
  if( !fs.StartDataElement( pixeldata ) )
    {
    gdcmErrorMacro( "StartDataElement" );
    return false;
    }
    {
    const int chunk = 4096;
    char bytes[chunk] = {};
    const int nchunks = buflen / chunk;
    const int remain = buflen % chunk;
    for( int i = 0; i < nchunks; ++i )
      {
      // Read the source file into a byte array.
      fs.AppendToDataElement( pixeldata, bytes, chunk );
      }
    fs.AppendToDataElement( pixeldata, bytes, remain );
    }
  if( !fs.StopDataElement( pixeldata ) )
    {
    // Most likely an issue with Pixel Data Length computation:
    gdcmErrorMacro( "StopDataElement" );
    return false;
    }

  return true;
}

EmptyMaskGenerator::EmptyMaskGenerator():pimpl(new impl)
{
}

EmptyMaskGenerator::~EmptyMaskGenerator()
{
  delete pimpl;
}

void EmptyMaskGenerator::SetSOPClassUIDMode( SOPClassUIDMode mode )
{
  pimpl->mode = mode;
}

void EmptyMaskGenerator::SetInputDirectory(const char * dirname)
{
  if( dirname )
    pimpl->inputdir = dirname;
}

void EmptyMaskGenerator::SetOutputDirectory(const char * dirname)
{
  if( dirname )
    pimpl->outputdir = dirname;
}


bool EmptyMaskGenerator::Execute()
{
  const char * dirname = pimpl->inputdir.c_str();
  const char * outdir = pimpl->outputdir.c_str();
  if( !pimpl->setup(dirname, outdir) )
    {
    return false;
    }
  bool success = true;
  gdcm::Directory::FilenamesType const & filenames = pimpl->s.GetFilenames();
  for( gdcm::Directory::FilenamesType::const_iterator it =  filenames.begin(); it != filenames.end(); ++it )
    {
    const char * filename = it->c_str();
    gdcm::Filename fn( filename );
    std::string outfile = outdir;
    outfile += '/';
    outfile += fn.GetName();
    if( !pimpl->run( filename, outfile.c_str() ) )
      {
      gdcmErrorMacro( "Failure to EmptyMask" );
      // Since we may have failed in the middle of writing of the file, remove it:
      if( gdcm::System::FileExists(outfile.c_str()) && !gdcm::System::RemoveFile(outfile.c_str()) )
        {
        gdcmErrorMacro( "Failure to RemoveFile: " << outfile );
        // may want to call exit() here, since we failed to remove a file we created in this process:
        return false;
        }
      // declare failure to process a file, but continue main loop:
      success = false;
      }
    }
  return success;
}

} // end namespace gdcm
