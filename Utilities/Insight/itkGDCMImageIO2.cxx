/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "itkGDCMImageIO2.h"
#include "itkVersion.h"
#include <string.h>
#include "itkMetaDataObject.h" // ExposeMetaData

// GDCM
#include "gdcmFileMetaInformation.h"
#include "gdcmImageReader.h"
#include "gdcmImageWriter.h"
#include "gdcmUIDGenerator.h"
#include "gdcmGlobal.h"
#include "gdcmDicts.h"
#include "gdcmDictEntry.h"
#include "gdcmImageHelper.h"
#include "gdcmRescaler.h"
#include "gdcmStringFilter.h"
#include "gdcmDataSetHelper.h"

// KWSYS
#include <itksys/SystemTools.hxx>
#include <itksys/SystemTools.hxx>
#include <itksys/Base64.h>

// VNL
#include <vnl/vnl_vector.h>
#include <vnl/vnl_cross.h>

namespace itk
{

GDCMImageIO2::GDCMImageIO2()
{
  this->SetNumberOfDimensions(3);
  // UIDPrefix is the ITK root id tacked with a ".1"
  // allowing to designate a subspace of the id space for ITK generated DICOM
  gdcm::UIDGenerator::SetRoot( "1.2.826.0.1.3680043.2.1125" );

  // Set some file info ITK specific stuff:
  // echo "ITK" | od -b
  gdcm::FileMetaInformation::AppendImplementationClassUID( "111.124.113" );
  const std::string project_name = std::string("GDCM/ITK ") + Version::GetITKVersion();
  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle( project_name.c_str() );
  gdcm::Trace::WarningOff();
}

GDCMImageIO2::~GDCMImageIO2()
{
}

bool GDCMImageIO2::OpenGDCMFileForReading(std::ifstream& os,
                                         const char* filename)
{
  // Make sure that we have a file to
  if ( *filename == 0 )
    {
    itkExceptionMacro(<<"A FileName must be specified.");
    return false;
    }

  // Close file from any previous image
  if ( os.is_open() )
    {
    os.close();
    }

  // Open the new file for reading
  itkDebugMacro(<< "Initialize: opening file " << filename);

  // Actually open the file
  os.open( filename, std::ios::in | std::ios::binary );

  if ( os.fail() )
    {
    return false;
    }

  return true;
}


bool GDCMImageIO2::OpenGDCMFileForWriting(std::ofstream& os,
                                         const char* filename)
{
  // Make sure that we have a file to
  if ( *filename == 0 )
    {
    itkExceptionMacro(<<"A FileName must be specified.");
    return false;
    }

  // Close file from any previous image
  if ( os.is_open() )
    {
    os.close();
    }

  // Open the new file for writing
  itkDebugMacro(<< "Initialize: opening file " << filename);

#ifdef __sgi
  // Create the file. This is required on some older sgi's
  std::ofstream tFile(filename,std::ios::out);
  tFile.close();
#endif

  // Actually open the file
  os.open( filename, std::ios::out | std::ios::binary );

  if( os.fail() )
    {
    itkExceptionMacro(<< "Could not open file: "
                      << filename << " for writing."
                      << std::endl
                      << "Reason: "
                      << itksys::SystemTools::GetLastSystemError());
    return false;
    }


  return true;
}

// This method will only test if the header looks like a
// GDCM image file.
bool GDCMImageIO2::CanReadFile(const char* filename)
{
  std::ifstream file;

  if( !filename || !*filename )
    {
    itkDebugMacro(<<"No filename specified.");
    return false;
    }

  //Check for file existence:
  if ( ! this->OpenGDCMFileForReading(file, filename))
    {
    return false;
    }

  // Check to see if its a valid dicom file gdcm is able to read:
  // We are parsing the header one time here:
  gdcm::ImageReader reader;
  reader.SetFileName( filename );
  if( reader.Read() )
    {
    return true;
    }
  return false;
}

void GDCMImageIO2::Read(void* buffer)
{
  const char *filename = m_FileName.c_str();
  gdcm::ImageReader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    itkExceptionMacro(<< "Cannot read requested file");
    }

  const gdcm::Image &image = reader.GetImage();
  unsigned long len = image.GetBufferLength();

  const unsigned long numberOfBytesToBeRead =
    static_cast< unsigned long>( this->GetImageSizeInBytes() );
  assert( numberOfBytesToBeRead == len );

  image.GetBuffer((char*)buffer);
}

void GDCMImageIO2::InternalReadImageInformation(std::ifstream& file)
{
  //read header
  if ( ! this->OpenGDCMFileForReading(file, m_FileName.c_str()) )
    {
    itkExceptionMacro(<< "Cannot read requested file");
    }

  // In general this should be relatively safe to assume
  gdcm::ImageHelper::SetForceRescaleInterceptSlope(true);

  const char *filename = m_FileName.c_str();
  gdcm::ImageReader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    itkExceptionMacro(<< "Cannot read requested file");
    }
  const gdcm::Image &image = reader.GetImage();
  const gdcm::File &f = reader.GetFile();
  const gdcm::DataSet &ds = f.GetDataSet();
  const unsigned int *dims = image.GetDimensions();

  const gdcm::PixelFormat &pixeltype = image.GetPixelFormat();

  m_RescaleIntercept = image.GetIntercept();
  m_RescaleSlope = image.GetSlope();
  gdcm::Rescaler r;
  r.SetIntercept( m_RescaleIntercept );
  r.SetSlope( m_RescaleSlope );
  r.SetPixelFormat( pixeltype );
  gdcm::PixelFormat::ScalarType outputpt = r.ComputeInterceptSlopePixelType();

  assert( pixeltype <= outputpt );

  m_ComponentType = UNKNOWNCOMPONENTTYPE;
  switch( outputpt )
    {
    case gdcm::PixelFormat::INT8:
      m_ComponentType = ImageIOBase::CHAR; // Is it signed char ?
      break;
    case gdcm::PixelFormat::UINT8:
      m_ComponentType = ImageIOBase::UCHAR;
      break;
      /* INT12 / UINT12 should not happen anymore in any modern DICOM */
    case gdcm::PixelFormat::INT12:
      m_ComponentType = ImageIOBase::SHORT;
      break;
    case gdcm::PixelFormat::UINT12:
      m_ComponentType = ImageIOBase::USHORT;
      break;
    case gdcm::PixelFormat::INT16:
      m_ComponentType = ImageIOBase::SHORT;
      break;
    case gdcm::PixelFormat::UINT16:
      m_ComponentType = ImageIOBase::USHORT;
      break;
      // RT / SC have 32bits
    case gdcm::PixelFormat::INT32:
      m_ComponentType = ImageIOBase::INT;
      break;
    case gdcm::PixelFormat::UINT32:
      m_ComponentType = ImageIOBase::UINT;
      break;
      //case gdcm::PixelFormat::FLOAT16: // TODO
    case gdcm::PixelFormat::FLOAT32:
      m_ComponentType = ImageIOBase::FLOAT;
      break;
    case gdcm::PixelFormat::FLOAT64:
      m_ComponentType = ImageIOBase::DOUBLE;
      break;
    default:
      itkExceptionMacro( "Unhandled PixelFormat: \n" << gdcm::PixelFormat(outputpt) );
    }

  m_NumberOfComponents = pixeltype.GetSamplesPerPixel();
  if( image.GetPhotometricInterpretation() ==
    gdcm::PhotometricInterpretation::PALETTE_COLOR )
    {
    assert( m_NumberOfComponents == 1 );
    // TODO: need to do the LUT ourself...
    //itkExceptionMacro(<< "PALETTE_COLOR is not implemented yet");
    // AFAIK ITK user don't care about the palette so always apply it and fake a RGB image for them
    m_NumberOfComponents = 3;
    }
  if (m_NumberOfComponents == 1)
    {
    this->SetPixelType(SCALAR);
    }
  else
    {
    this->SetPixelType(RGB);
    }

  // set values in case we don't find them
  //this->SetNumberOfDimensions(  image.GetNumberOfDimensions() );
  m_Dimensions[0] = dims[0];
  m_Dimensions[1] = dims[1];

  const double *spacing = image.GetSpacing();
  m_Spacing[0] = spacing[0];
  m_Spacing[1] = spacing[1];
  m_Spacing[2] = spacing[2];

  const double *origin = image.GetOrigin();
  m_Origin[0] = origin[0];
  m_Origin[1] = origin[1];
  m_Origin[2] = origin[2];

  if( image.GetNumberOfDimensions() == 3 )
    {
    m_Dimensions[2] = dims[2];
    }
  else
    {
    m_Dimensions[2] = 1;
    }

  const double *dircos = image.GetDirectionCosines();
  vnl_vector<double> rowDirection(3), columnDirection(3);
  rowDirection[0] = dircos[0];
  rowDirection[1] = dircos[1];
  rowDirection[2] = dircos[2];
  columnDirection[0] = dircos[3];
  columnDirection[1] = dircos[4];
  columnDirection[2] = dircos[5];

  vnl_vector<double> sliceDirection = vnl_cross_3d(rowDirection, columnDirection);
  this->SetDirection(0, rowDirection);
  this->SetDirection(1, columnDirection);
  this->SetDirection(2, sliceDirection);

  //Now copying the gdcm dictionary to the itk dictionary:
  MetaDataDictionary & dico = this->GetMetaDataDictionary();

  gdcm::StringFilter sf;
  sf.SetFile( f );
  gdcm::DataSet::ConstIterator it = ds.Begin();

  // Copy of the header->content
  for(; it != ds.End(); ++it)
    {
    const gdcm::DataElement &ref = *it;
    const gdcm::Tag &tag = ref.GetTag();
    // Compute VR from the toplevel file, and the currently processed dataset:
    gdcm::VR vr = gdcm::DataSetHelper::ComputeVR(f, ds, tag);

    // Process binary field and encode them as mime64: only when we do not know of any better
    // representation. VR::US is binary, but user want ASCII representation.
    if ( vr & (gdcm::VR::OB | gdcm::VR::OF | gdcm::VR::OW | gdcm::VR::SQ | gdcm::VR::UN) )
      {
      // assert( vr & gdcm::VR::VRBINARY );
      /*
       * Old behavior was to skip SQ, Pixel Data element. I decided that it is not safe to mime64
       * VR::UN element. There used to be a bug in gdcm 1.2.0 and VR:UN element.
       */
      if ( tag.IsPublic() && vr != gdcm::VR::SQ && tag != gdcm::Tag(0x7fe0,0x0010) /* && vr != gdcm::VR::UN*/ )
        {
        const gdcm::ByteValue *bv = ref.GetByteValue();
        if( bv )
          {
          // base64 streams have to be a multiple of 4 bytes long
          int encodedLengthEstimate = 2 * bv->GetLength();
          encodedLengthEstimate = ((encodedLengthEstimate / 4) + 1) * 4;

          char *bin = new char[encodedLengthEstimate];
          unsigned int encodedLengthActual = static_cast<unsigned int>(
            itksysBase64_Encode(
              (const unsigned char *) bv->GetPointer(),
              static_cast< unsigned long>( bv->GetLength() ),
              (unsigned char *) bin,
              static_cast< int >( 0 ) ));
          std::string encodedValue(bin, encodedLengthActual);
          EncapsulateMetaData<std::string>(dico, tag.PrintAsPipeSeparatedString(), encodedValue);
          delete []bin;
          }
        }
      }
    else /* if ( vr & gdcm::VR::VRASCII ) */
      {
      // Only copying field from the public DICOM dictionary
      if( tag.IsPublic() )
        {
        EncapsulateMetaData<std::string>(dico, tag.PrintAsPipeSeparatedString(), sf.ToString( tag ) );
        }
      }

    }


  // Now is a good time to fill in the class member:
  char name[512];
  this->GetPatientName(name);
  this->GetPatientID(name);
  this->GetPatientSex(name);
  this->GetPatientAge(name);
  this->GetStudyID(name);
  this->GetPatientDOB(name);
  this->GetStudyDescription(name);
  this->GetBodyPart(name);
  this->GetNumberOfSeriesInStudy(name);
  this->GetNumberOfStudyRelatedSeries(name);
  this->GetStudyDate(name);
  this->GetModality(name);
  this->GetManufacturer(name);
  this->GetInstitution(name);
  this->GetModel(name);
  this->GetScanOptions(name);

}

void GDCMImageIO2::ReadImageInformation()
{
  std::ifstream file;
  this->InternalReadImageInformation(file);
}


bool GDCMImageIO2::CanWriteFile(const char* name)
{
  std::string filename = name;

  if(  filename == "" )
    {
    itkDebugMacro(<<"No filename specified.");
    return false;
    }

  std::string::size_type dcmPos = filename.rfind(".dcm");
  if ( (dcmPos != std::string::npos)
       && (dcmPos == filename.length() - 4) )
    {
    return true;
    }

  dcmPos = filename.rfind(".DCM");
  if ( (dcmPos != std::string::npos)
       && (dcmPos == filename.length() - 4) )
    {
    return true;
    }

  return false;
}

void GDCMImageIO2::WriteImageInformation()
{
}

void GDCMImageIO2::Write(const void* buffer)
{
  std::ofstream file;
  if ( !this->OpenGDCMFileForWriting(file, m_FileName.c_str()) )
    {
    return;
    }
  file.close();

  gdcm::ImageWriter writer;
  //this->SetNumberOfDimensions(3);
  gdcm::Image &image = writer.GetImage();
  image.SetNumberOfDimensions( 2 ); // good default
  image.SetDimension(0, m_Dimensions[0] );
  image.SetDimension(1, m_Dimensions[1] );
  //image.SetDimension(2, m_Dimensions[2] );
  image.SetSpacing(0, m_Spacing[0] );
  image.SetSpacing(1, m_Spacing[1] );
  if( m_NumberOfDimensions > 2 && m_Dimensions[2] != 1 )
    {
    // resize num of dim to 3:
    image.SetNumberOfDimensions( 3 );
    image.SetDimension(2, m_Dimensions[2] );
    }
  image.SetSpacing(2, m_Spacing[2] ); // should always valid...
  gdcm::PixelFormat pixeltype = gdcm::PixelFormat::UNKNOWN;
  switch (this->GetComponentType())
    {
  case ImageIOBase::CHAR:
    pixeltype = gdcm::PixelFormat::INT8;
    break;
  case ImageIOBase::UCHAR:
    pixeltype = gdcm::PixelFormat::UINT8;
    break;
  case ImageIOBase::SHORT:
    pixeltype = gdcm::PixelFormat::INT16;
    break;
  case ImageIOBase::USHORT:
    pixeltype = gdcm::PixelFormat::UINT16;
    break;
    //Disabling INT and UINT for now...
    //case ImageIOBase::INT:
    //case ImageIOBase::UINT:
    //case ImageIOBase::FLOAT:
    //case ImageIOBase::DOUBLE:
  default:
    itkExceptionMacro(<<"DICOM does not support this component type");
    }
  assert( pixeltype != gdcm::PixelFormat::UNKNOWN );
  gdcm::PhotometricInterpretation pi;
  if( this->GetNumberOfComponents() == 1 )
    {
    pi = gdcm::PhotometricInterpretation::MONOCHROME2;
    }
  else if( this->GetNumberOfComponents() == 3 )
    {
    pi = gdcm::PhotometricInterpretation::RGB;
    // (0028,0006) US 0                                        #   2, 1 PlanarConfiguration
    }
  else
    {
    itkExceptionMacro(<<"DICOM does not support this component type");
    }
  pixeltype.SetSamplesPerPixel( this->GetNumberOfComponents() );

  image.SetPhotometricInterpretation( pi );
  image.SetPixelFormat( pixeltype );
  unsigned long len = image.GetBufferLength();

  gdcm::ByteValue *bv = new gdcm::ByteValue(); // (char*)data->GetScalarPointer(), len );
  bv->SetLength( len ); // allocate !

  size_t numberOfBytes = this->GetImageSizeInBytes();
  assert( len == numberOfBytes );

  // only do a straight copy:
  char *pointer = (char*)bv->GetPointer();
  memcpy(pointer, buffer, numberOfBytes);

  gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
  pixeldata.SetValue( *bv );
  image.SetDataElement( pixeldata );

  const char *filename = m_FileName.c_str();
  writer.SetFileName( filename );
  if( !writer.Write() )
    {
    itkExceptionMacro(<<"DICOM does not support this component type");
    }
}

void GDCMImageIO2::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}

bool GDCMImageIO2::GetLabelFromTag( const std::string & tag,
                               std::string & labelId )
{
  gdcm::Tag t;
  t.ReadFromPipeSeparatedString( tag.c_str() );
  if( t.IsPublic() )
    {
    const gdcm::Global &g = gdcm::Global::GetInstance();
    const gdcm::Dicts &dicts = g.GetDicts();
    const gdcm::DictEntry &entry = dicts.GetDictEntry(t);
    labelId = entry.GetName();
    return true;
    }
  return false;
}

bool GDCMImageIO2::GetValueFromTag(const std::string & tag, std::string & value)
{
  MetaDataDictionary & dict = this->GetMetaDataDictionary();
  return ExposeMetaData<std::string>(dict, tag, value);
}

// Convenience methods to query patient and scanner information. These
// methods are here for compatibility with the DICOMImageIO2 class.
void GDCMImageIO2::GetPatientName( char *name)
{
  std::string value;
  GetValueFromTag("0010|0010",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetPatientID( char *name)
{
  std::string value;
  GetValueFromTag("0010|0020",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetPatientSex( char *name)
{
  std::string value;
  GetValueFromTag("0010|0040",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetPatientAge( char *name)
{
  std::string value;
  GetValueFromTag("0010|1010",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetStudyID( char *name)
{
  std::string value;
  GetValueFromTag("0020|0010",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetPatientDOB( char *name)
{
  std::string value;
  GetValueFromTag("0010|0030",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetStudyDescription( char *name)
{
  std::string value;
  GetValueFromTag("0008|1030",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetBodyPart( char *name)
{
  std::string value;
  GetValueFromTag("0018|0015",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetNumberOfSeriesInStudy( char *name)
{
  std::string value;
  GetValueFromTag("0020|1000",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetNumberOfStudyRelatedSeries( char *name)
{
  std::string value;
  GetValueFromTag("0020|1206",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetStudyDate( char *name)
{
  std::string value;
  GetValueFromTag("0008|0020",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetModality( char *name)
{
  std::string value;
  GetValueFromTag("0008|0060",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetManufacturer( char *name)
{
  std::string value;
  GetValueFromTag("0008|0070",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetInstitution( char *name)
{
  std::string value;
  GetValueFromTag("0008|0080",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetModel( char *name)
{
  std::string value;
  GetValueFromTag("0008|1090",value);
  strcpy (name, value.c_str());
}

void GDCMImageIO2::GetScanOptions( char *name)
{
  std::string value;
  GetValueFromTag("0018|0022",value);
  strcpy (name, value.c_str());
}


} // end namespace itk
