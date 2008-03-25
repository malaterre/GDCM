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
#include "vtkGDCMImageReader.h"

#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkMedicalImageProperties.h"
#include "vtkStringArray.h"
#include "vtkPointData.h"
#include "vtkLookupTable.h"
#include "vtkWindowLevelLookupTable.h"
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDemandDrivenPipeline.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#endif /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/
#include "vtkMatrix4x4.h"
#include "vtkUnsignedCharArray.h"
#include "vtkBitArray.h"

#include "gdcmImageReader.h"
#include "gdcmDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmSwapper.h"

#include <sstream>

vtkCxxRevisionMacro(vtkGDCMImageReader, "$Revision: 1.1 $")
vtkStandardNewMacro(vtkGDCMImageReader)

// Output Ports are as follow:
// #0: The image/volume (root PixelData element)
// #1: (if present): the Icon Image (0088,0200)
// #2-xx: (if present): the Overlay (60xx,3000)

#define IconImagePortNumber 1
#define OverlayPortNumber   2

vtkGDCMImageReader::vtkGDCMImageReader()
{
  // vtkDataArray has an internal vtkLookupTable why not used it ?
  // vtkMedicalImageProperties is in the parent class
  //this->FileLowerLeft = 1;
  this->DirectionCosines = vtkMatrix4x4::New();
  this->DirectionCosines->SetElement(0,0,1);
  this->DirectionCosines->SetElement(1,0,0);
  this->DirectionCosines->SetElement(2,0,0);
  this->DirectionCosines->SetElement(0,1,0);
  this->DirectionCosines->SetElement(1,1,1);
  this->DirectionCosines->SetElement(2,1,0);
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
#else
  this->MedicalImageProperties = vtkMedicalImageProperties::New();
#endif
#if ( VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 0 )
#else
  this->FileNames = NULL; //vtkStringArray::New();
#endif
  this->LoadOverlays = 1;
  this->LoadIconImage = 1;
  this->NumberOfOverlays = 0;
  this->NumberOfIconImages = 0;
  memset(this->IconImageDataExtent,0,6*sizeof(int));
  this->ImageFormat = 0; // INVALID
  this->ApplyInverseVideo = 0;
  this->ApplyLookupTable = 0;
  this->ApplyYBRToRGB = 0;
  this->ApplyPlanarConfiguration = 1;
}

vtkGDCMImageReader::~vtkGDCMImageReader()
{
  //delete this->Internals;
  this->DirectionCosines->Delete();
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
#else
  this->MedicalImageProperties->Delete();
#endif
#if ( VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 0 )
#else
  if( this->FileNames )
    {
    this->FileNames->Delete();
    }
#endif
}

#if ( VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 0 )
#else
void vtkGDCMImageReader::SetFileNames(vtkStringArray *filenames)
{
  if (filenames == this->FileNames)
    {
    return;
    }
  if (this->FileNames)
    {
    this->FileNames->Delete();
    this->FileNames = 0;
    }
  if (filenames)
    {
    this->FileNames = filenames;
    this->FileNames->Register(this);
    if (this->FileNames->GetNumberOfValues() > 0)
      {
      this->DataExtent[4] = 0;
      this->DataExtent[5] = this->FileNames->GetNumberOfValues() - 1;
      }
    if (this->FilePrefix)
      {
      delete [] this->FilePrefix;
      this->FilePrefix = NULL;
      }
    if (this->FileName)
      {
      delete [] this->FileName;
      this->FileName = NULL;
      }
    }

  this->Modified();
}
#endif

#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
#else
void vtkGDCMImageReader::ExecuteInformation()
{
  //std::cerr << "ExecuteInformation" << std::endl;

  // FIXME: I think it only apply to VTK 4.2...
  vtkImageData *output = this->GetOutput();
  output->SetUpdateExtentToWholeExtent(); // pipeline is not reexecuting properly without that...

  int res = RequestInformationCompat();
  if( !res )
    {
    vtkErrorMacro( "ExecuteInformation failed" );
    return;
    }

  int numvol = 1;
  if( this->LoadIconImage )
    {
    numvol = 2;
    }
  if( this->LoadOverlays )
    {
    // If not icon found, we still need to be associated to port #2:
    numvol = 3;
    }
  this->SetNumberOfOutputs(numvol);

  // vtkImageReader2::ExecuteInformation only allocate first output
  this->vtkImageReader2::ExecuteInformation();
  // Let's do the other ones ourselves:
  for (int i=1; i<numvol; i++)
    {
    if (!this->Outputs[i])
      {
      vtkImageData * img = vtkImageData::New();
      this->SetNthOutput(i, img);
      img->Delete();
      }
    vtkImageData *output = this->GetOutput(i);
    switch(i)
      {
    case 0:
      output->SetWholeExtent(this->DataExtent);
      output->SetSpacing(this->DataSpacing);
      output->SetOrigin(this->DataOrigin);

      output->SetScalarType(this->DataScalarType);
      output->SetNumberOfScalarComponents(this->NumberOfScalarComponents);
      break;
    case IconImagePortNumber:
      output->SetWholeExtent(this->IconImageDataExtent);
      output->SetScalarType( VTK_UNSIGNED_CHAR );
      output->SetNumberOfScalarComponents( 1 );
      break;
    //case OverlayPortNumber:
    default:
      output->SetWholeExtent(this->DataExtent[0],this->DataExtent[1],
        this->DataExtent[2],this->DataExtent[3],
        0,0
      );
      //output->SetSpacing(this->DataSpacing);
      //output->SetOrigin(this->DataOrigin);
      output->SetScalarType(VTK_UNSIGNED_CHAR);
      output->SetNumberOfScalarComponents(1);
      break;
      }

    }
}

void vtkGDCMImageReader::ExecuteData(vtkDataObject *output)
{
  //std::cerr << "ExecuteData" << std::endl;
  // In VTK 4.2 AllocateOutputData is reexecuting ExecuteInformation which is bad !
  //vtkImageData *data = this->AllocateOutputData(output);
  vtkImageData *res = vtkImageData::SafeDownCast(output);
  res->SetExtent(res->GetUpdateExtent());
  res->AllocateScalars();

  if( this->LoadIconImage )
    {
    vtkImageData *res = vtkImageData::SafeDownCast(this->Outputs[IconImagePortNumber]);
    res->SetUpdateExtentToWholeExtent();

    res->SetExtent(res->GetUpdateExtent());
    res->AllocateScalars();
    }
  if( this->LoadOverlays )
    {
    vtkImageData *res = vtkImageData::SafeDownCast(this->Outputs[OverlayPortNumber]);
    res->SetUpdateExtentToWholeExtent();

    res->SetExtent(res->GetUpdateExtent());
    res->AllocateScalars();
    }
  //int * updateExtent = data->GetUpdateExtent();
  //std::cout << "UpdateExtent:" << updateExtent[4] << " " << updateExtent[5] << std::endl;
  RequestDataCompat();
}

#endif /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/

int vtkGDCMImageReader::CanReadFile(const char* fname)
{
  gdcm::ImageReader reader;
  reader.SetFileName( fname );
  if( reader.Read() )
    {
    return 0;
    }
  return 3;
}

//----------------------------------------------------------------------------
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
int vtkGDCMImageReader::ProcessRequest(vtkInformation* request,
                                 vtkInformationVector** inputVector,
                                 vtkInformationVector* outputVector)
{
  // generate the data
  if(request->Has(vtkDemandDrivenPipeline::REQUEST_DATA()))
    {
    return this->RequestData(request, inputVector, outputVector);
    }

  // execute information
  if(request->Has(vtkDemandDrivenPipeline::REQUEST_INFORMATION()))
    {
    return this->RequestInformation(request, inputVector, outputVector);
    }

  return this->Superclass::ProcessRequest(request, inputVector, outputVector);
}
#endif /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/


//----------------------------------------------------------------------------
const char *GetStringValueFromTag(const gdcm::Tag& t, const gdcm::DataSet& ds)
{
  static std::string buffer;
  buffer = "";  // cleanup previous call

  if( ds.FindDataElement( t ) )
    {
    const gdcm::DataElement& de = ds.GetDataElement( t );
    const gdcm::ByteValue *bv = de.GetByteValue();
    if( bv ) // Can be Type 2
      {
      buffer = std::string( bv->GetPointer(), bv->GetLength() );
      // Will be padded with at least one \0
      }
    }

  // Since return is a const char* the very first \0 will be considered
  return buffer.c_str();
}

//----------------------------------------------------------------------------
void vtkGDCMImageReader::FillMedicalImageInformation(const gdcm::ImageReader &reader)
{
  const gdcm::File &file = reader.GetFile();
  const gdcm::DataSet &ds = file.GetDataSet();

  // $ grep "vtkSetString\|DICOM" vtkMedicalImageProperties.h 
  // For ex: DICOM (0010,0010) = DOE,JOHN
  this->MedicalImageProperties->SetPatientName( GetStringValueFromTag( gdcm::Tag(0x0010,0x0010), ds) );
  // For ex: DICOM (0010,0020) = 1933197
  this->MedicalImageProperties->SetPatientID( GetStringValueFromTag( gdcm::Tag(0x0010,0x0020), ds) );
  // For ex: DICOM (0010,1010) = 031Y
  this->MedicalImageProperties->SetPatientAge( GetStringValueFromTag( gdcm::Tag(0x0010,0x1010), ds) );
  // For ex: DICOM (0010,0040) = M
  this->MedicalImageProperties->SetPatientSex( GetStringValueFromTag( gdcm::Tag(0x0010,0x0040), ds) );
  // For ex: DICOM (0010,0030) = 19680427
  this->MedicalImageProperties->SetPatientBirthDate( GetStringValueFromTag( gdcm::Tag(0x0010,0x0030), ds) );
#if ( VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 0 )
  // For ex: DICOM (0008,0020) = 20030617
  this->MedicalImageProperties->SetStudyDate( GetStringValueFromTag( gdcm::Tag(0x0008,0x0020), ds) );
#endif
  // For ex: DICOM (0008,0022) = 20030617
  this->MedicalImageProperties->SetAcquisitionDate( GetStringValueFromTag( gdcm::Tag(0x0008,0x0022), ds) );
#if ( VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 0 )
  // For ex: DICOM (0008,0030) = 162552.0705 or 230012, or 0012
  this->MedicalImageProperties->SetStudyTime( GetStringValueFromTag( gdcm::Tag(0x0008,0x0030), ds) );
#endif
  // For ex: DICOM (0008,0032) = 162552.0705 or 230012, or 0012
  this->MedicalImageProperties->SetAcquisitionTime( GetStringValueFromTag( gdcm::Tag(0x0008,0x0032), ds) );
  // For ex: DICOM (0008,0023) = 20030617
  this->MedicalImageProperties->SetImageDate( GetStringValueFromTag( gdcm::Tag(0x0008,0x0023), ds) );
  // For ex: DICOM (0008,0033) = 162552.0705 or 230012, or 0012
  this->MedicalImageProperties->SetImageTime( GetStringValueFromTag( gdcm::Tag(0x0008,0x0033), ds) );
  // For ex: DICOM (0020,0013) = 1
  this->MedicalImageProperties->SetImageNumber( GetStringValueFromTag( gdcm::Tag(0x0020,0x0013), ds) );
  // For ex: DICOM (0020,0011) = 902
  this->MedicalImageProperties->SetSeriesNumber( GetStringValueFromTag( gdcm::Tag(0x0020,0x0011), ds) );
  // For ex: DICOM (0008,103e) = SCOUT
  this->MedicalImageProperties->SetSeriesDescription( GetStringValueFromTag( gdcm::Tag(0x0008,0x103e), ds) );
  // For ex: DICOM (0020,0010) = 37481
  this->MedicalImageProperties->SetStudyID( GetStringValueFromTag( gdcm::Tag(0x0020,0x0010), ds) );
  // For ex: DICOM (0008,1030) = BRAIN/C-SP/FACIAL
  this->MedicalImageProperties->SetStudyDescription( GetStringValueFromTag( gdcm::Tag(0x0008,0x1030), ds) );
  // For ex: DICOM (0008,0060)= CT
  this->MedicalImageProperties->SetModality( GetStringValueFromTag( gdcm::Tag(0x0008,0x0060), ds) );
  // For ex: DICOM (0008,0070) = Siemens
  this->MedicalImageProperties->SetManufacturer( GetStringValueFromTag( gdcm::Tag(0x0008,0x0070), ds) );
  // For ex: DICOM (0008,1090) = LightSpeed QX/i
  this->MedicalImageProperties->SetManufacturerModelName( GetStringValueFromTag( gdcm::Tag(0x0008,0x1090), ds) );
  // For ex: DICOM (0008,1010) = LSPD_OC8
  this->MedicalImageProperties->SetStationName( GetStringValueFromTag( gdcm::Tag(0x0008,0x1010), ds) );
  // For ex: DICOM (0008,0080) = FooCity Medical Center
  this->MedicalImageProperties->SetInstitutionName( GetStringValueFromTag( gdcm::Tag(0x0008,0x0080), ds) );
  // For ex: DICOM (0018,1210) = Bone
  this->MedicalImageProperties->SetConvolutionKernel( GetStringValueFromTag( gdcm::Tag(0x0018,0x1210), ds) );
  // For ex: DICOM (0018,0050) = 0.273438
  this->MedicalImageProperties->SetSliceThickness( GetStringValueFromTag( gdcm::Tag(0x0018,0x0050), ds) );
  // For ex: DICOM (0018,0060) = 120
  this->MedicalImageProperties->SetKVP( GetStringValueFromTag( gdcm::Tag(0x0018,0x0060), ds) );
  // For ex: DICOM (0018,1120) = 15
  this->MedicalImageProperties->SetGantryTilt( GetStringValueFromTag( gdcm::Tag(0x0018,0x1120), ds) );
  // For ex: DICOM (0018,0081) = 105
  this->MedicalImageProperties->SetEchoTime( GetStringValueFromTag( gdcm::Tag(0x0018,0x0081), ds) );
  // For ex: DICOM (0018,0091) = 35
  this->MedicalImageProperties->SetEchoTrainLength( GetStringValueFromTag( gdcm::Tag(0x0018,0x0091), ds) );
  // For ex: DICOM (0018,0080) = 2040
  this->MedicalImageProperties->SetRepetitionTime( GetStringValueFromTag( gdcm::Tag(0x0018,0x0080), ds) );
  // For ex: DICOM (0018,1150) = 5
  this->MedicalImageProperties->SetExposureTime( GetStringValueFromTag( gdcm::Tag(0x0018,0x1150), ds) );
  // For ex: DICOM (0018,1151) = 400
  this->MedicalImageProperties->SetXRayTubeCurrent( GetStringValueFromTag( gdcm::Tag(0x0018,0x1151), ds) );
  // For ex: DICOM (0018,1152) = 114
  this->MedicalImageProperties->SetExposure( GetStringValueFromTag( gdcm::Tag(0x0018,0x1152), ds) );

  // virtual void AddWindowLevelPreset(double w, double l);
  // (0028,1050) DS [   498\  498]                           #  12, 2 WindowCenter
  // (0028,1051) DS [  1063\ 1063]                           #  12, 2 WindowWidth
  gdcm::Tag twindowcenter(0x0028,0x1050);
  gdcm::Tag twindowwidth(0x0028,0x1051);
  if( ds.FindDataElement( twindowcenter ) && ds.FindDataElement( twindowwidth) )
    {
    const gdcm::DataElement& windowcenter = ds.GetDataElement( twindowcenter );
    const gdcm::DataElement& windowwidth = ds.GetDataElement( twindowwidth );
    const gdcm::ByteValue *bvwc = windowcenter.GetByteValue();
    const gdcm::ByteValue *bvww = windowwidth.GetByteValue();
    if( bvwc && bvww ) // Can be Type 2
      {
      //gdcm::Attributes<0x0028,0x1050> at;
      gdcm::Element<gdcm::VR::DS,gdcm::VM::VM1_n> elwc;
      std::stringstream ss1;
      std::string swc = std::string( bvwc->GetPointer(), bvwc->GetLength() );
      ss1.str( swc );
      gdcm::VR vr = gdcm::VR::DS;
      unsigned int vrsize = vr.GetSizeof();
      unsigned int count = gdcm::VM::GetNumberOfElementsFromArray(swc.c_str(), swc.size());
      elwc.SetLength( count * vrsize );
      elwc.Read( ss1 );
      std::stringstream ss2;
      std::string sww = std::string( bvww->GetPointer(), bvww->GetLength() );
      ss2.str( sww );
      gdcm::Element<gdcm::VR::DS,gdcm::VM::VM1_n> elww;
      elww.SetLength( count * vrsize );
      elww.Read( ss2 );
      //assert( elww.GetLength() == elwc.GetLength() );
      for(unsigned int i = 0; i < elwc.GetLength(); ++i)
        {
        this->MedicalImageProperties->AddWindowLevelPreset( elww.GetValue(i), elwc.GetValue(i) );
        }
      }
    }
  gdcm::Tag twindowexplanation(0x0028,0x1055);
  if( ds.FindDataElement( twindowexplanation ) )
    {
    const gdcm::DataElement& windowexplanation = ds.GetDataElement( twindowexplanation );
    const gdcm::ByteValue *bvwe = windowexplanation.GetByteValue();
    if( bvwe ) // Can be Type 2
      {
      int n = this->MedicalImageProperties->GetNumberOfWindowLevelPresets();
      gdcm::Element<gdcm::VR::LO,gdcm::VM::VM1_n> elwe; // window explanation
      gdcm::VR vr = gdcm::VR::LO;
      std::stringstream ss;
      ss.str( "" );
      std::string swe = std::string( bvwe->GetPointer(), bvwe->GetLength() );
      unsigned int count = gdcm::VM::GetNumberOfElementsFromArray(swe.c_str(), swe.size());
      // I found a case with only one W/L but two comments: WINDOW1\WINDOW2
      // SIEMENS-IncompletePixelData.dcm
      assert( count >= n );
      elwe.SetLength( count * vr.GetSizeof() );
      ss.str( swe );
      elwe.Read( ss );
      for(int i = 0; i < n; ++i)
        {
        this->MedicalImageProperties->SetNthWindowLevelPresetComment(i, elwe.GetValue(i).c_str() );
        }
      }
    }

}

//----------------------------------------------------------------------------
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
int vtkGDCMImageReader::RequestInformation(vtkInformation *request,
                                      vtkInformationVector **inputVector,
                                      vtkInformationVector *outputVector)
{
  int res = RequestInformationCompat();
  if( !res )
    {
    vtkErrorMacro( "RequestInformationCompat failed: " << res );
    return 0;
    }

  int numvol = 1;
  if( this->LoadIconImage )
    {
    numvol = 2;
    }
  if( this->LoadOverlays )
    {
    // If no icon found, we still need to be associated to port #2:
    numvol = 3;
    }
  this->SetNumberOfOutputPorts(numvol);
  // For each output:
  for(int i = 0; i < numvol; ++i)
    {
    // Allocate !
    if( !this->GetOutput(i) )
      {
      vtkImageData *img = vtkImageData::New();
      this->GetExecutive()->SetOutputData(i, img );
      img->Delete();
      }
    vtkInformation *outInfo = outputVector->GetInformationObject(i);
    switch(i)
      {
    // root Pixel Data
    case 0:
      outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), this->DataExtent, 6);
      //outInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), this->DataExtent, 6);
      outInfo->Set(vtkDataObject::SPACING(), this->DataSpacing, 3);
      outInfo->Set(vtkDataObject::ORIGIN(), this->DataOrigin, 3);
      vtkDataObject::SetPointDataActiveScalarInfo(outInfo, this->DataScalarType, this->NumberOfScalarComponents);
      break;
    // Icon Image
    case IconImagePortNumber:
      outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), this->IconImageDataExtent, 6);
      vtkDataObject::SetPointDataActiveScalarInfo(outInfo, VTK_UNSIGNED_CHAR, 1);
      break;
    // Overlays:
    //case OverlayPortNumber:
    default:
      outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), 
        this->DataExtent[0], this->DataExtent[1], 
        this->DataExtent[2], this->DataExtent[3],
        0,0 );
      vtkDataObject::SetPointDataActiveScalarInfo(outInfo, VTK_UNSIGNED_CHAR, 1);
      break;
      }
    }

  //return res;
  return 1;
}
#endif

int vtkGDCMImageReader::RequestInformationCompat()
{
  // FIXME, need to implement the other modes too:
  if( this->ApplyLookupTable || this->ApplyYBRToRGB || this->ApplyInverseVideo )
    {
    //cerr << "ApplyLookupTable/ApplyYBRToRGB/ApplyInverseVideo not compatible" << endl;
    return 0;
    }
  // I do not think this one will ever be implemented:
  if( !this->ApplyPlanarConfiguration )
    {
    //cerr << "ApplyPlanarConfiguration not compatible" << endl;
    return 0;
    }

  // Let's read the first file :
  const char *filename;
  if( this->FileName )
    {
    filename = this->FileName;
    }
  else
    {
    assert( this->FileNames && this->FileNames->GetNumberOfValues() >= 1 );
    filename = this->FileNames->GetValue( 0 );
    }
  gdcm::ImageReader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    //cerr << "ImageReader failed" << endl;
    return 0;
    }
  const gdcm::Image &image = reader.GetImage();
  const unsigned int *dims = image.GetDimensions();

  // Set the Extents.
  assert( image.GetNumberOfDimensions() >= 2 );
  this->DataExtent[0] = 0;
  this->DataExtent[1] = dims[0] - 1;
  this->DataExtent[2] = 0;
  this->DataExtent[3] = dims[1] - 1;
  if( image.GetNumberOfDimensions() == 2 )
    {
    // This is just so much painfull to deal with DICOM / VTK
    // they simply assume that number of file is equal to the dimension
    // of the last axe (see vtkImageReader2::SetFileNames )
    if ( this->FileNames && this->FileNames->GetNumberOfValues() > 1 )
      {
      this->DataExtent[4] = 0;
      //this->DataExtent[5] = this->FileNames->GetNumberOfValues() - 1;
      }
    else
      {
      this->DataExtent[4] = 0;
      this->DataExtent[5] = 0;
      }
    }
  else
    {
    assert( image.GetNumberOfDimensions() == 3 );
    this->FileDimensionality = 3;
    this->DataExtent[4] = 0;
    this->DataExtent[5] = dims[2] - 1;
    }
  gdcm::MediaStorage ms;
  ms.SetFromFile( reader.GetFile() );
  assert( gdcm::MediaStorage::IsImage( ms ) );
  // There is no point in adding world info to a SC object since noone but GDCM can use this info...
  if( ms != gdcm::MediaStorage::SecondaryCaptureImageStorage )
    {
    const double *spacing = image.GetSpacing();
    assert( spacing );
    this->DataSpacing[0] = spacing[0];
    this->DataSpacing[1] = spacing[1];
    //this->DataSpacing[2] = 1.;

    const double *origin = image.GetOrigin();
    if( origin )
      {
      this->DataOrigin[0] = origin[0];
      this->DataOrigin[1] = origin[1];
      this->DataOrigin[2] = origin[2];
      }

    const double *dircos = image.GetDirectionCosines();
    if( dircos )
      {
      this->DirectionCosines->SetElement(0,0, dircos[0]);
      this->DirectionCosines->SetElement(1,0, dircos[1]);
      this->DirectionCosines->SetElement(2,0, dircos[2]);
      this->DirectionCosines->SetElement(0,1, dircos[3]);
      this->DirectionCosines->SetElement(1,1, dircos[4]);
      this->DirectionCosines->SetElement(2,1, dircos[5]);
      }
    // Need to set the rest to 0 ???
    }

  const gdcm::PixelFormat &pixeltype = image.GetPixelFormat();
  switch( pixeltype )
    {
  case gdcm::PixelFormat::INT8:
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
    this->DataScalarType = VTK_SIGNED_CHAR;
#else
    this->DataScalarType = VTK_CHAR;
#endif
    break;
  case gdcm::PixelFormat::UINT8:
    this->DataScalarType = VTK_UNSIGNED_CHAR;
    break;
  case gdcm::PixelFormat::INT16:
    this->DataScalarType = VTK_SHORT;
    break;
  case gdcm::PixelFormat::UINT16:
    this->DataScalarType = VTK_UNSIGNED_SHORT;
    break;
  // RT / SC have 32bits
  case gdcm::PixelFormat::INT32:
    this->DataScalarType = VTK_INT;
    break;
  case gdcm::PixelFormat::UINT32:
    this->DataScalarType = VTK_UNSIGNED_INT;
    break;
  // FIXME 12bits should not be that hard...
  case gdcm::PixelFormat::INT12:
    //this->DataScalarType = VTK_SHORT;
    //break;
  case gdcm::PixelFormat::UINT12:
    //this->DataScalarType = VTK_UNSIGNED_SHORT;
    //break;
  default:
    vtkErrorMacro( "Do not support this Pixel Type: " << pixeltype );
    return 0;
    }

  this->NumberOfScalarComponents = pixeltype.GetSamplesPerPixel();

  // Ok let's fill in the 'extra' info:
  FillMedicalImageInformation(reader);

  // Do the IconImage if requested:
  const gdcm::IconImage& icon = image.GetIconImage();
  if( this->LoadIconImage && !icon.IsEmpty() )
    {
    this->IconImageDataExtent[0] = 0;
    this->IconImageDataExtent[1] = icon.GetColumns() - 1;
    this->IconImageDataExtent[2] = 0;
    this->IconImageDataExtent[3] = icon.GetRows() - 1;
    }

//  return this->Superclass::RequestInformation(
//    request, inputVector, outputVector);

  return 1;
}

//----------------------------------------------------------------------------
int vtkGDCMImageReader::LoadSingleFile(const char *filename, char *pointer) //, int *dext, vtkImageData* data, bool filelowerleft)
{
  int *dext = this->GetDataExtent();
  vtkImageData *data = this->GetOutput(0);
  bool filelowerleft = this->FileLowerLeft ? true : false;

  //char * pointer = static_cast<char*>(data->GetScalarPointer());

  gdcm::ImageReader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
	   // cerr << "ImageReader failed" << endl;
    return 0;
    }
  const gdcm::Image &image = reader.GetImage();
  assert( image.GetNumberOfDimensions() == 2 || image.GetNumberOfDimensions() == 3 );
  unsigned long len = image.GetBufferLength();
  //char *tempimage = new char[len];
  //unsigned char *tempimage2 = 0;
  unsigned long overlaylen = 0;
  //image.GetBuffer(tempimage);
  image.GetBuffer(pointer);
  // Do the Icon Image:
  this->NumberOfIconImages = image.GetIconImage().IsEmpty() ? 0 : 1;
  if( this->NumberOfIconImages )
  {
  char * iconpointer = static_cast<char*>(this->GetOutput(IconImagePortNumber)->GetScalarPointer());
  assert( iconpointer );
  image.GetIconImage().GetBuffer( iconpointer );
  }

  // Do the Overlay:
  unsigned int numoverlays = image.GetNumberOfOverlays();
  long overlayoutsize = (dext[1] - dext[0] + 1);
  this->NumberOfOverlays = numoverlays;
  unsigned char * overlaypointer = static_cast<unsigned char*>(this->GetOutput(OverlayPortNumber)->GetScalarPointer());
  if( numoverlays )
    {
    // vtkOpenGLImageMapper::RenderData does not support bit array (since OpenGL does not either)
    // we have to decompress the bit overlay into an unsigned char array to please everybody:
    const gdcm::Overlay& ov1 = image.GetOverlay();
    vtkImageData *image = this->GetOutput(OverlayPortNumber);
    assert( image->GetScalarType() == VTK_UNSIGNED_CHAR );

    assert( image->GetPointData()->GetScalars() != 0 );
    vtkUnsignedCharArray *chararray = vtkUnsignedCharArray::New();
    chararray->SetNumberOfTuples( overlayoutsize * ( dext[3] - dext[2] + 1 ) );
    overlaylen = overlayoutsize * ( dext[3] - dext[2] + 1 );
    assert( ov1.GetRows()*ov1.GetColumns() <= overlaylen );
    const signed short *origin = ov1.GetOrigin();
    if( (unsigned long)ov1.GetRows()*ov1.GetColumns() != overlaylen )
      {
      vtkWarningMacro( "vtkImageData Overlay have an extent that do not match the one of the image" );
      }
    if( origin[0] != 0 || origin[1] != 0 )
      {
      vtkWarningMacro( "Overlay with origin are not supported right now" );
      }
    //tempimage2 = new unsigned char[overlaylen];
    //memset(tempimage2,0,overlaylen);
    memset(overlaypointer,0,overlaylen); // FIXME: can be optimized
    //ov1.GetUnpackBuffer( tempimage2 );
    ov1.GetUnpackBuffer( overlaypointer );
    image->GetPointData()->SetScalars( chararray );
    image->GetPointData()->GetScalars()->SetName( ov1.GetDescription() );
    chararray->Delete();
    }

  const gdcm::PixelFormat &pixeltype = image.GetPixelFormat();
  // Do the LUT
  if ( image.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::PALETTE_COLOR )
    {
    this->ImageFormat = VTK_LOOKUP_TABLE;
    // SOLVED: GetPointer(0) is skrew up, need to replace it with WritePointer(0,4) ...
    const gdcm::LookupTable &lut = image.GetLUT();
    vtkLookupTable *vtklut = vtkLookupTable::New();
    vtklut->SetNumberOfTableValues(256);
    if( !lut.GetBufferAsRGBA( vtklut->WritePointer(0,4) ) )
      {
      vtkWarningMacro( "Could not get values from LUT" );
      return 0;
      }
    vtklut->SetRange(0,255);
    data->GetPointData()->GetScalars()->SetLookupTable( vtklut );
    vtklut->Delete();
    }
  else if ( image.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::MONOCHROME1 )
    {
    this->ImageFormat = VTK_INVERSE_LUMINANCE;
    vtkWindowLevelLookupTable *vtklut = vtkWindowLevelLookupTable::New();
    // Technically we could also use the first of the Window Width / Window Center
    // oh well, if they are missing let's just compute something:
    int64_t min = pixeltype.GetMin();
    int64_t max = pixeltype.GetMax(); 
    vtklut->SetWindow( max - min );
    vtklut->SetLevel( 0.5 * (max + min) );
    //vtklut->SetWindow(1024); // WindowWidth
    //vtklut->SetLevel(550); // WindowCenter
    vtklut->InverseVideoOn();
    data->GetPointData()->GetScalars()->SetLookupTable( vtklut );
    vtklut->Delete();
    }
  else if ( image.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::YBR_FULL_422 )
    {
    assert( image.GetPixelFormat().GetSamplesPerPixel() == 3 );
    this->ImageFormat = VTK_RGB; // FIXME 
    }
  else if ( image.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::YBR_FULL )
    {
    this->ImageFormat = VTK_YBR;
    }
  else if ( image.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::RGB )
    {
    this->ImageFormat = VTK_RGB;
    }
  else if ( image.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::MONOCHROME2 )
    {
    this->ImageFormat = VTK_LUMINANCE;
    }
  assert( this->ImageFormat );

  long outsize = pixeltype.GetPixelSize()*(dext[1] - dext[0] + 1);
  if( numoverlays ) assert( overlayoutsize * ( dext[3] - dext[2] + 1 ) == overlaylen );
  assert( outsize * (dext[3] - dext[2]+1) * (dext[5]-dext[4]+1) == len );

  // If user overrides this flag, he/she wants image upside down
  if (filelowerleft)
    {
    // image
    //memcpy(pointer, tempimage, len);
    // overlay
    if( numoverlays )
      {
      //memcpy(overlaypointer, tempimage2, overlaylen);
      }
    }
  else
    {
	    int maxz = dext[4];
	    // FIXME: poor test
	    // Basically we are syaing if there is only one file, then maybe this is a multi frame volume
	    // in which case I need to invert frame-by-frame each slice:
	    if( this->FileName )
	    {
		    maxz = dext[5];
	    }
	    char *line = new char[outsize];
	    //cerr << "outsize:" << outsize << endl;
		//cerr << dext[4] << "," << dext[5] << endl;
    for(int j = dext[4]; j <= maxz /*dext[5]*/; ++j)
	    {
	    char *start = pointer;
      //int j = 0;
      for(int i = dext[2]; i <= dext[3] / 2; ++i)
        {
        // image:
        //memcpy(pointer,
        //  tempimage+((dext[3] - i)+j*(dext[3]+1))*outsize, outsize);
	char * end = start+(dext[3] - i)*outsize;
	//char * end = start+((dext[3] - i)+j*(dext[3]+1))*outsize;
	memcpy(line,end,outsize); // duplicate
	memcpy(end,pointer,outsize);
	memcpy(pointer,line,outsize);
        pointer += outsize;
        if( numoverlays )
          {
          // overlay
          //memcpy(overlaypointer,
          //  tempimage2+((dext[3] - i)+j*(dext[3]+1))*overlayoutsize, overlayoutsize);
          //overlaypointer += overlayoutsize;
          }
        }
      pointer += (dext[3] - dext[3]/2)*outsize;
      }
      delete[] line;
    }
  //delete[] tempimage;
  //delete[] tempimage2;

  return 1; // success
}

//----------------------------------------------------------------------------
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
int vtkGDCMImageReader::RequestData(vtkInformation *vtkNotUsed(request),
                                vtkInformationVector **vtkNotUsed(inputVector),
                                vtkInformationVector *outputVector)
{
  //this->UpdateProgress(0.2);

  // Make sure the output dimension is OK, and allocate its scalars

  for(int i = 0; i < this->GetNumberOfOutputPorts(); ++i)
  {
  // Copy/paste from vtkImageAlgorithm::AllocateScalars. Cf. "this needs to be fixed -Ken"
    vtkStreamingDemandDrivenPipeline *sddp = 
      vtkStreamingDemandDrivenPipeline::SafeDownCast(this->GetExecutive());
    if (sddp)
      {
      int extent[6];
      sddp->GetOutputInformation(i)->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),extent);
      this->GetOutput(i)->SetExtent(extent);
      }
    this->GetOutput(i)->AllocateScalars();
  }
  int res = RequestDataCompat();
  return res;
}
#endif

//----------------------------------------------------------------------------
int vtkGDCMImageReader::RequestDataCompat()
{
  vtkImageData *output = this->GetOutput(0);
  output->GetPointData()->GetScalars()->SetName("GDCMImage");

  char * pointer = static_cast<char*>(output->GetScalarPointer());
  if( this->FileName )
    {
    const char *filename = this->FileName;
    this->LoadSingleFile( filename, pointer ); //, dext, output, this->FileLowerLeft);
    return 1;
    }
  else
    {
    assert( this->FileNames && this->FileNames->GetNumberOfValues() >= 1 );
    }

  // Load each 2D files
  char *tempimage = 0;
  unsigned long reflen = 0;
  int *dext = this->GetDataExtent();
  for(int j = dext[4]; j <= dext[5]; ++j)
    {
	    //cerr << "j=" << j << endl;
    const char *filename = this->FileNames->GetValue( j );
    int load = this->LoadSingleFile( filename, pointer ); //, dext, output, this->FileLowerLeft);
	    //cerr << "load=" << load << endl;
    gdcm::ImageReader reader;
    reader.SetFileName( filename );
    if( !reader.Read() )
      {
      // TODO need to do some cleanup...
      return 0;
      }

    const gdcm::Image &image = reader.GetImage();
    assert( image.GetNumberOfDimensions() == 2 || image.GetNumberOfDimensions() == 3 );
    unsigned long len = image.GetBufferLength();
    //cerr << "len=" << len << endl;
    pointer += len;
    /*
    if( !tempimage )
      {
      tempimage = new char[len];
      reflen = len;
      }
    else
      {
      assert( reflen == len );
      }
    image.GetBuffer(tempimage);

    assert( image.GetNumberOfDimensions() == 2 );
    gdcm::PixelFormat pixeltype = image.GetPixelFormat();
    long outsize = pixeltype.GetPixelSize()*(dext[1] - dext[0] + 1);

    // If user overrides this flag, he/she wants image upside down
    if (this->FileLowerLeft)
      {
      memcpy(pointer, tempimage, len);
      pointer += len;
      }
    else
      {
      // Copy image upside down, to please VTK
      assert( dext[2] == 0 );
      for(int i = dext[2]; i <= dext[3]; ++i)
        {
        int offset = (dext[3] - i)*outsize;
        assert( offset >= 0 && offset+outsize <= len);
        memcpy(pointer,tempimage+offset, outsize);
        pointer += outsize;
        }
      }
      */
    }
  //delete[] tempimage;

  return 1;
}

#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
vtkAlgorithmOutput* vtkGDCMImageReader::GetOverlayPort(int index)
{
  if( index >= 0 && index < this->NumberOfOverlays)
    return this->GetOutputPort(index+OverlayPortNumber);
  return NULL;
}
vtkAlgorithmOutput* vtkGDCMImageReader::GetIconImagePort()
{
  const int index = 0;
  if( index >= 0 && index < this->NumberOfIconImages)
    return this->GetOutputPort(index+IconImagePortNumber);
  return NULL;
}
#endif

//----------------------------------------------------------------------------
vtkImageData* vtkGDCMImageReader::GetOverlay(int i)
{
  if( i >= 0 && i < this->NumberOfOverlays)
    return this->GetOutput(i+OverlayPortNumber);
  return NULL;
}
//----------------------------------------------------------------------------
vtkImageData* vtkGDCMImageReader::GetIconImage()
{
  const int i = 0;
  if( i >= 0 && i < this->NumberOfIconImages)
    return this->GetOutput(i+IconImagePortNumber);
  return NULL;
}

//----------------------------------------------------------------------------
void vtkGDCMImageReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

