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
#include "vtkGDCMImageWriter.h"

#include "vtkVersion.h"
#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkLookupTable.h"
#include "vtkMatrix4x4.h"
#include "vtkMedicalImageProperties.h"
#include "vtkStringArray.h"
#include "vtkPointData.h"
#include "vtkGDCMImageReader.h"
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
#include "vtkInformationVector.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformation.h"
#endif /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/

#include "gdcmImageWriter.h"
#include "gdcmByteValue.h"
#include "gdcmUIDGenerator.h"
#include "gdcmAttribute.h"

vtkCxxRevisionMacro(vtkGDCMImageWriter, "$Revision: 1.1 $")
vtkStandardNewMacro(vtkGDCMImageWriter)

vtkCxxSetObjectMacro(vtkGDCMImageWriter,LookupTable,vtkLookupTable)
vtkCxxSetObjectMacro(vtkGDCMImageWriter,MedicalImageProperties,vtkMedicalImageProperties)
vtkCxxSetObjectMacro(vtkGDCMImageWriter,FileNames,vtkStringArray)
vtkCxxSetObjectMacro(vtkGDCMImageWriter,DirectionCosines,vtkMatrix4x4)

vtkGDCMImageWriter::vtkGDCMImageWriter()
{
  this->DataUpdateExtent[0] = 0;
  this->DataUpdateExtent[1] = 0;
  this->DataUpdateExtent[2] = 0;
  this->DataUpdateExtent[3] = 0;
  this->DataUpdateExtent[4] = 0;
  this->DataUpdateExtent[5] = 0;

  this->LookupTable = vtkLookupTable::New();
  this->MedicalImageProperties = vtkMedicalImageProperties::New();
  this->FileNames = vtkStringArray::New();
  this->UID = 0;
  this->DirectionCosines = vtkMatrix4x4::New();
  this->DirectionCosines->SetElement(0,0,1);
  this->DirectionCosines->SetElement(1,0,0);
  this->DirectionCosines->SetElement(2,0,0);
  this->DirectionCosines->SetElement(0,1,0);
  this->DirectionCosines->SetElement(1,1,1);
  this->DirectionCosines->SetElement(2,1,0);

  // This is the same root as ITK, but implementation version will be different...
  gdcm::UIDGenerator::SetRoot( "1.2.826.0.1.3680043.2.1125.1" );

  // echo "VTK" | od -b
  gdcm::FileMetaInformation::SetImplementationClassUID( "126.124.113" );
  const std::string project_name = std::string("VTK ") + vtkVersion::GetVTKVersion();
  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle( project_name.c_str() );

  this->ImageFormat = 0; // invalid

}

//----------------------------------------------------------------------------
vtkGDCMImageWriter::~vtkGDCMImageWriter()
{
  this->LookupTable->Delete();
  this->MedicalImageProperties->Delete();
  this->FileNames->Delete();
  this->SetUID(NULL);
  this->DirectionCosines->Delete();
}

//----------------------------------------------------------------------------
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
int vtkGDCMImageWriter::FillInputPortInformation(
  int port, vtkInformation *info)
{
  if (!this->Superclass::FillInputPortInformation(port, info))
    {
    return 0;
    }
  info->Set(vtkAlgorithm::INPUT_IS_REPEATABLE(), 1);
  return 1;
}
//---------------------------------------------------------------------------
int vtkGDCMImageWriter::RequestInformation(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *vtkNotUsed(outputVector))
{
  // Check to make sure that all input information agrees
  int mismatchedInputs = 0;

  double spacing[3];
  double origin[3];
  int extent[6];
  int components = 0;
  int dataType = 0;

  // For each connection on port 0, check against the first connection
  for (int i = 0; i < this->GetNumberOfInputConnections(0); i++)
    {
    vtkInformation *inInfo = inputVector[0]->GetInformationObject(i);
    if (i == 0)
      {
      inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
      inInfo->Get(vtkDataObject::SPACING(), spacing);
      inInfo->Get(vtkDataObject::ORIGIN(), origin);
      components = inInfo->Get(vtkDataObject::FIELD_NUMBER_OF_COMPONENTS());
      dataType = inInfo->Get(vtkDataObject::FIELD_ARRAY_TYPE());
      continue;
      }

    if (memcmp(inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT()),
               extent, sizeof(extent)) ||
        memcmp(inInfo->Get(vtkDataObject::SPACING()), spacing,
               sizeof(spacing)) ||
        memcmp(inInfo->Get(vtkDataObject::ORIGIN()), origin,
               sizeof(origin)) ||
        inInfo->Get(vtkDataObject::FIELD_NUMBER_OF_COMPONENTS())
          != components ||
        inInfo->Get(vtkDataObject::FIELD_ARRAY_TYPE()) != dataType)
      {
      mismatchedInputs = 1;
      return 0;
      }
    }

  return 1;
}

//--------------------------------------------------------------------------
int vtkGDCMImageWriter::RequestUpdateExtent(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *vtkNotUsed(outputVector))
{
  // Set the UpdateExtent from the DataUpdateExtent for the current slice
  int n = inputVector[0]->GetNumberOfInformationObjects();
  for (int i = 0; i < n; i++)
    {
    vtkInformation *inInfo = inputVector[0]->GetInformationObject(i);
    inInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),
                this->DataUpdateExtent, 6);
    }

  return 1;
}

//--------------------------------------------------------------------------
int vtkGDCMImageWriter::RequestData(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector,
  vtkInformationVector* vtkNotUsed(outputVector))
{
  // Go through the inputs and write the data for each
  int numTimeSteps = inputVector[0]->GetNumberOfInformationObjects();

  for (int timeStep = 0; timeStep < numTimeSteps; timeStep++)
    {
    vtkInformation *inInfo =
      inputVector[0]->GetInformationObject(timeStep);
    vtkImageData *input =
      vtkImageData::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));

    // Error checking
    if (input == NULL)
      {
      // Close file, set GDCMFileID to zero
      //this->CloseFile(this->GDCMFileId);
      //this->GDCMFileId = 0;
      vtkErrorMacro(<<"Write: Please specify an input!");
      return 0;
      }
    // Call WriteGDCMData for each input
    if (this->WriteGDCMData(input, timeStep) == 0)
      {
      return 0;
      }
    }

  return 1;
}
#endif /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/

/*const*/ char *vtkGDCMImageWriter::GetFileName()
{
  if( this->FileNames->GetNumberOfValues() )
    {
    const char *filename = this->FileNames->GetValue(0);
    return (char*)filename;
    }
  return this->Superclass::GetFileName();
}

#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
void vtkGDCMImageWriter::Write()
{
  if (this->GetFileName() == 0)
    {
    vtkErrorMacro("Write: You must supply a file name.");
    return;
    }

  // Get the first input and update its information.
  vtkImageData *input = this->GetImageDataInput(0);

  if (input == 0)
    {
    vtkErrorMacro("Write: No input supplied.");
    return;
    }

  input->UpdateInformation();

  // Update the rest.
  this->UpdateInformation();

  // Get the whole extent of the input
  input->GetWholeExtent(this->DataUpdateExtent);

  // For both case (2d file or 3d file) we need a common uid for the Series/Study:
  gdcm::UIDGenerator uidgen;
  const char *uid = uidgen.Generate();
  this->SetUID(uid);

  // Did the user specified dim of output file to be 2 ?
  if( this->FileDimensionality == 2 )
    {
    int dimIndex = 2;
    int firstSlice = this->DataUpdateExtent[2*dimIndex];
    int lastSlice = this->DataUpdateExtent[2*dimIndex+1];
    if( this->FileNames->GetNumberOfValues() )
      {
      if( lastSlice - firstSlice + 1 != this->FileNames->GetNumberOfValues() )
        {
        vtkErrorMacro("Wrong number of filenames: " << this->FileNames->GetNumberOfValues() 
          << " should be " << lastSlice - firstSlice + 1);
        return;
        }
      }

    // Go through data slice-by-slice using file-order slices
    for (int slice = firstSlice; slice <= lastSlice; slice++)
      {
      //std::cerr << "Slice:" << slice << std::endl;
      // Set the DataUpdateExtent to the slice extent we want to write
      this->DataUpdateExtent[2*dimIndex] = slice;
      this->DataUpdateExtent[2*dimIndex+1] = slice;
      this->Modified();

      // Call Update to execute pipeline and write slice to disk.
      this->Update();
      }
    }
  else if( this->FileDimensionality == 3 )
    {
    // Call Update to execute pipeline and write slice to disk.
    this->Update();
    }
  else
    {
    vtkErrorMacro( "Unhandled: " << this->FileDimensionality );
    }

}
#else
//----------------------------------------------------------------------------
// Writes all the data from the input.
void vtkGDCMImageWriter::Write()
{
  // Error checking
  if ( this->GetInput() == NULL )
    {
    vtkErrorMacro(<<"Write:Please specify an input!");
    return;
    }
//  if (!this->WriteToMemory && !this->FileName && !this->FilePattern)
//    {
//    vtkErrorMacro(<<"Write:Please specify either a FileName or a file prefix and pattern");
//    return;
//    }
  
  // For both case (2d file or 3d file) we need a common uid for the Series/Study:
  gdcm::UIDGenerator uidgen;
  const char *uid = uidgen.Generate();
  this->SetUID(uid);

  // Make sure the file name is allocated
  this->InternalFileName =  0;
//    new char[(this->FileName ? strlen(this->FileName) : 1) +
//            (this->FilePrefix ? strlen(this->FilePrefix) : 1) +
//            (this->FilePattern ? strlen(this->FilePattern) : 1) + 10];
  
  // Fill in image information.
  this->GetInput()->UpdateInformation();
  int *wExtent;
  wExtent = this->GetInput()->GetWholeExtent();
  this->FileNumber = this->GetInput()->GetWholeExtent()[4];
  this->UpdateProgress(0.0);
  // loop over the z axis and write the slices
  for (this->FileNumber = wExtent[4]; this->FileNumber <= wExtent[5]; 
       ++this->FileNumber)
    {
    this->GetInput()->SetUpdateExtent(wExtent[0], wExtent[1],
                                      wExtent[2], wExtent[3],
                                      this->FileNumber, 
                                      this->FileNumber);
    // determine the name
/*
    if (this->FileName)
      {
      sprintf(this->InternalFileName,"%s",this->FileName);
      }
    else 
      {
      if (this->FilePrefix)
        {
        sprintf(this->InternalFileName, this->FilePattern, 
                this->FilePrefix, this->FileNumber);
        }
      else
        {
        sprintf(this->InternalFileName, this->FilePattern,this->FileNumber);
        }
      }
*/
    this->GetInput()->UpdateData();
    this->WriteSlice(this->GetInput());
    this->UpdateProgress((this->FileNumber - wExtent[4])/
                         (wExtent[5] - wExtent[4] + 1.0));
    }
  //delete [] this->InternalFileName;
  //this->InternalFileName = NULL;
}

void vtkGDCMImageWriter::WriteSlice(vtkImageData *data)
{
  this->WriteGDCMData(data, 0);
}

#endif

void SetStringValueFromTag(const char *s, const gdcm::Tag& t, gdcm::DataSet& ds)
{
  if( s && *s )
    {
    gdcm::DataElement de( t );
    de.SetByteValue( s, strlen( s ) );
    ds.Insert( de );
    }
}


//----------------------------------------------------------------------------
int vtkGDCMImageWriter::WriteGDCMData(vtkImageData *data, int timeStep)
{
  //std::cerr << "Calling WriteGDCMData" << std::endl;
  assert( timeStep >= 0 );
  int inWholeExt[6];
  data->GetWholeExtent(inWholeExt);
  int inExt[6];
  data->GetUpdateExtent(inExt);
  vtkIdType inInc[3];
  data->GetIncrements(inInc);

  //data->Update();
  //data->Print( std::cout );
  //const char * filename = this->GetFileName();
  //std::cerr << data->GetDataDimension() << std::endl;

  gdcm::ImageWriter writer;
  //writer.SetImage( image );

  gdcm::ImageValue &image = dynamic_cast<gdcm::ImageValue&>(writer.GetImage());
  image.SetNumberOfDimensions( 2 ); // good default
  const int *dims = data->GetDimensions();
  assert( dims[0] >= 0 && dims[1] >= 0 && dims[2] >= 0 );
  image.SetDimension(0, dims[0] );
  image.SetDimension(1, dims[1] );
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 2 )
  const double *spacing = data->GetSpacing();
#else
  const float *spacing = data->GetSpacing();
#endif
  image.SetSpacing(0, spacing[0] );
  image.SetSpacing(1, spacing[1] );
  if( dims[2] > 1 && this->FileDimensionality == 3 )
    {
    // resize num of dim to 3:
    image.SetNumberOfDimensions( 3 );
    image.SetDimension(2, dims[2] );
    }
  image.SetSpacing(2, spacing[2] ); // should always be valid...
  // TODO: need to do Origin / Image Position (Patient)
  // For now FileDimensionality should match File Dimension
  //this->FileDimensionality
  int scalarType = data->GetScalarType();
  gdcm::PixelFormat pixeltype = gdcm::PixelFormat::UNKNOWN;
  switch( scalarType )
    {
  case VTK_CHAR:
    pixeltype = gdcm::PixelFormat::INT8; // FIXME ??
    break;
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
  case VTK_SIGNED_CHAR:
    pixeltype = gdcm::PixelFormat::INT8;
    break;
#endif
  case VTK_UNSIGNED_CHAR:
    pixeltype = gdcm::PixelFormat::UINT8;
    break;
  case VTK_SHORT:
    pixeltype = gdcm::PixelFormat::INT16;
    break;
  case VTK_UNSIGNED_SHORT:
    pixeltype = gdcm::PixelFormat::UINT16;
    break;
  case VTK_INT:
    pixeltype = gdcm::PixelFormat::INT32;
    break;
  case VTK_UNSIGNED_INT:
    pixeltype = gdcm::PixelFormat::UINT32;
    break;
  default:
    vtkErrorMacro( "Do not support this Pixel Type: " << scalarType );
    return 0;
    }

  gdcm::PhotometricInterpretation pi;
  if( this->ImageFormat )
    {
    // We have been passed the proper image format, let's use it !
    switch( this->ImageFormat )
      {
      case VTK_LUMINANCE:
        pi = gdcm::PhotometricInterpretation::MONOCHROME2;
        break;
      case VTK_RGB:
        pi = gdcm::PhotometricInterpretation::RGB;
        break;
      case VTK_INVERSE_LUMINANCE:
        pi = gdcm::PhotometricInterpretation::MONOCHROME1;
        break;
      case VTK_LOOKUP_TABLE:
        pi = gdcm::PhotometricInterpretation::PALETTE_COLOR;
        break;
      case VTK_YBR:
        pi = gdcm::PhotometricInterpretation::YBR_FULL;
        break;
      default:
        vtkErrorMacro( "Unknown ImageFormat:" << this->ImageFormat );
        return 0;
      }
    }
  else
    {
    // Attempt a guess
    if( data->GetNumberOfScalarComponents() == 1 )
      {
      pi = gdcm::PhotometricInterpretation::MONOCHROME2;
      }
    else if( data->GetNumberOfScalarComponents() == 3 )
      {
      pi = gdcm::PhotometricInterpretation::RGB;
      // (0028,0006) US 0                                        #   2, 1 PlanarConfiguration
      }
    else
      {
      return 0;
      }
    }

  pixeltype.SetSamplesPerPixel( data->GetNumberOfScalarComponents() );
  image.SetPhotometricInterpretation( pi );
  image.SetPixelFormat( pixeltype );

  // Setup LUt if any:
  if( pi == gdcm::PhotometricInterpretation::PALETTE_COLOR )
    {
    vtkLookupTable * vtklut = data->GetPointData()->GetScalars()->GetLookupTable();
    assert( vtklut );
    assert( vtklut->GetNumberOfTableValues() == 256 );
    gdcm::SmartPointer<gdcm::LookupTable> lut = new gdcm::LookupTable;
    assert( pixeltype.GetBitsAllocated() == 8 );
    lut->Allocate( pixeltype.GetBitsAllocated() );
    lut->InitializeLUT( gdcm::LookupTable::RED, 256, 0, 16 );
    lut->InitializeLUT( gdcm::LookupTable::GREEN, 256, 0, 16 );
    lut->InitializeLUT( gdcm::LookupTable::BLUE, 256, 0, 16 );
    if( !lut->WriteBufferAsRGBA( vtklut->WritePointer(0,4) ) )
      {
      vtkWarningMacro( "Could not get values from LUT" );
      return 0;
      }

    image.SetLUT( *lut );
    }

  unsigned long len = image.GetBufferLength();

  gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
  gdcm::ByteValue *bv = new gdcm::ByteValue(); // (char*)data->GetScalarPointer(), len );
  bv->SetLength( len ); // allocate !
  
//  std::ofstream of( "/tmp/bla.raw" );
//  of.write( (char*)data->GetScalarPointer(), len);
//  of.close();
  // re shuffle the line within ByteValue:
  //
  char *pointer = (char*)bv->GetPointer();
  //const char *tempimage = (char*)data->GetScalarPointer();
  const char *tempimage = (char*)data->GetScalarPointerForExtent(inExt);
  //std::cerr << "Pointer:" << (unsigned int)tempimage << std::endl;
  int *dext = data->GetExtent();
  long outsize = pixeltype.GetPixelSize()*(dext[1] - dext[0] + 1);
  int j = dext[4];
  //std::cerr << "dext[4]:" << j << std::endl;
  //std::cerr << "inExt[4]:" << inExt[4] << std::endl;
  if( dims[2] > 1 && this->FileDimensionality == 3 )
    {
    for(int j = dext[4]; j <= dext[5]; ++j)
      {
      for(int i = dext[2]; i <= dext[3]; ++i)
        {
        memcpy(pointer,
          tempimage+((dext[3] - i)+j*(dext[3]+1))*outsize, outsize);
        pointer += outsize;
        }
      }
    }
  else
    {
    //for(int j = dext[4]; j <= dext[5]; ++j)
      {
      for(int i = dext[2]; i <= dext[3]; ++i)
        {
        memcpy(pointer,
          tempimage+((dext[3] - i)+j*(dext[3]+1))*outsize, outsize);
        pointer += outsize;
        }
      }
    }

  pixeldata.SetValue( *bv );
  image.SetDataElement( pixeldata );

// DEBUG
  const gdcm::DataElement &pixeldata2 = image.GetDataElement();
  //const gdcm::Value &v = image.GetValue();
  //const gdcm::ByteValue *bv1 = dynamic_cast<const gdcm::ByteValue*>(&v);
  const gdcm::ByteValue *bv1 = pixeldata2.GetByteValue();
  assert( bv1 && bv1 == bv );
  //image.Print( std::cerr );
// END DEBUG


  gdcm::File& file = writer.GetFile();
  gdcm::DataSet& ds = file.GetDataSet();
  // For ex: DICOM (0010,0010) = DOE,JOHN
  SetStringValueFromTag(this->MedicalImageProperties->GetPatientName(), gdcm::Tag(0x0010,0x0010), ds);
  // For ex: DICOM (0010,0020) = 1933197
  SetStringValueFromTag( this->MedicalImageProperties->GetPatientID(), gdcm::Tag(0x0010,0x0020), ds);
  // For ex: DICOM (0010,1010) = 031Y
  SetStringValueFromTag( this->MedicalImageProperties->GetPatientAge(), gdcm::Tag(0x0010,0x1010), ds);
  // For ex: DICOM (0010,0040) = M
  SetStringValueFromTag( this->MedicalImageProperties->GetPatientSex(), gdcm::Tag(0x0010,0x0040), ds);
  // For ex: DICOM (0010,0030) = 19680427
  SetStringValueFromTag( this->MedicalImageProperties->GetPatientBirthDate(), gdcm::Tag(0x0010,0x0030), ds);
#if ( VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 0 )
  // For ex: DICOM (0008,0020) = 20030617
  SetStringValueFromTag( this->MedicalImageProperties->GetStudyDate(), gdcm::Tag(0x0008,0x0020), ds);
#endif
  // For ex: DICOM (0008,0022) = 20030617
  SetStringValueFromTag( this->MedicalImageProperties->GetAcquisitionDate(), gdcm::Tag(0x0008,0x0022), ds);
#if ( VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 0 )
  // For ex: DICOM (0008,0030) = 162552.0705 or 230012, or 0012
  SetStringValueFromTag( this->MedicalImageProperties->GetStudyTime(), gdcm::Tag(0x0008,0x0030), ds);
#endif
  // For ex: DICOM (0008,0032) = 162552.0705 or 230012, or 0012
  SetStringValueFromTag( this->MedicalImageProperties->GetAcquisitionTime(), gdcm::Tag(0x0008,0x0032), ds);
  // For ex: DICOM (0008,0023) = 20030617
  SetStringValueFromTag( this->MedicalImageProperties->GetImageDate(), gdcm::Tag(0x0008,0x0023), ds);
  // For ex: DICOM (0008,0033) = 162552.0705 or 230012, or 0012
  SetStringValueFromTag( this->MedicalImageProperties->GetImageTime(), gdcm::Tag(0x0008,0x0033), ds);
  // For ex: DICOM (0020,0013) = 1
  SetStringValueFromTag( this->MedicalImageProperties->GetImageNumber(), gdcm::Tag(0x0020,0x0013), ds);
  // For ex: DICOM (0020,0011) = 902
  SetStringValueFromTag( this->MedicalImageProperties->GetSeriesNumber(), gdcm::Tag(0x0020,0x0011), ds);
  // For ex: DICOM (0008,103e) = SCOUT
  SetStringValueFromTag( this->MedicalImageProperties->GetSeriesDescription(), gdcm::Tag(0x0008,0x103e), ds);
  // For ex: DICOM (0020,0010) = 37481
  SetStringValueFromTag( this->MedicalImageProperties->GetStudyID(), gdcm::Tag(0x0020,0x0010), ds);
  // For ex: DICOM (0008,1030) = BRAIN/C-SP/FACIAL
  SetStringValueFromTag( this->MedicalImageProperties->GetStudyDescription(), gdcm::Tag(0x0008,0x1030), ds);
  // For ex: DICOM (0008,0060)= CT
  SetStringValueFromTag( this->MedicalImageProperties->GetModality(), gdcm::Tag(0x0008,0x0060), ds);
  // For ex: DICOM (0008,0070) = Siemens
  SetStringValueFromTag( this->MedicalImageProperties->GetManufacturer(), gdcm::Tag(0x0008,0x0070), ds);
  // For ex: DICOM (0008,1090) = LightSpeed QX/i
  SetStringValueFromTag( this->MedicalImageProperties->GetManufacturerModelName(), gdcm::Tag(0x0008,0x1090), ds);
  // For ex: DICOM (0008,1010) = LSPD_OC8
  SetStringValueFromTag( this->MedicalImageProperties->GetStationName(), gdcm::Tag(0x0008,0x1010), ds);
  // For ex: DICOM (0008,0080) = FooCity Medical Center
  SetStringValueFromTag( this->MedicalImageProperties->GetInstitutionName(), gdcm::Tag(0x0008,0x0080), ds);
  // For ex: DICOM (0018,1210) = Bone
  SetStringValueFromTag( this->MedicalImageProperties->GetConvolutionKernel(), gdcm::Tag(0x0018,0x1210), ds);
  // For ex: DICOM (0018,0050) = 0.273438
  SetStringValueFromTag( this->MedicalImageProperties->GetSliceThickness(), gdcm::Tag(0x0018,0x0050), ds);
  // For ex: DICOM (0018,0060) = 120
  SetStringValueFromTag( this->MedicalImageProperties->GetKVP(), gdcm::Tag(0x0018,0x0060), ds);
  // For ex: DICOM (0018,1120) = 15
  SetStringValueFromTag( this->MedicalImageProperties->GetGantryTilt(), gdcm::Tag(0x0018,0x1120), ds);
  // For ex: DICOM (0018,0081) = 105
  SetStringValueFromTag( this->MedicalImageProperties->GetEchoTime(), gdcm::Tag(0x0018,0x0081), ds);
  // For ex: DICOM (0018,0091) = 35
  SetStringValueFromTag( this->MedicalImageProperties->GetEchoTrainLength(), gdcm::Tag(0x0018,0x0091), ds);
  // For ex: DICOM (0018,0080) = 2040
  SetStringValueFromTag( this->MedicalImageProperties->GetRepetitionTime(), gdcm::Tag(0x0018,0x0080), ds);
  // For ex: DICOM (0018,1150) = 5
  SetStringValueFromTag( this->MedicalImageProperties->GetExposureTime(), gdcm::Tag(0x0018,0x1150), ds);
  // For ex: DICOM (0018,1151) = 400
  SetStringValueFromTag( this->MedicalImageProperties->GetXRayTubeCurrent(), gdcm::Tag(0x0018,0x1151), ds);
  // For ex: DICOM (0018,1152) = 114
  SetStringValueFromTag( this->MedicalImageProperties->GetExposure(), gdcm::Tag(0x0018,0x1152), ds);

  // Window Level / Window Center
  int numwl = this->MedicalImageProperties->GetNumberOfWindowLevelPresets();
  if( numwl )
{
  gdcm::VR vr = gdcm::VR::DS;
  gdcm::Element<gdcm::VR::DS,gdcm::VM::VM1_n> elwc;
  elwc.SetLength( numwl * vr.GetSizeof() );
  gdcm::Element<gdcm::VR::DS,gdcm::VM::VM1_n> elww;
  elww.SetLength( numwl * vr.GetSizeof() );
  vr = gdcm::VR::LO;
  gdcm::Element<gdcm::VR::LO,gdcm::VM::VM1_n> elwe;
  elwe.SetLength( numwl * vr.GetSizeof() );
  for(int i = 0; i < numwl; ++i)
    {
    const double *wl = this->MedicalImageProperties->GetNthWindowLevelPreset(i);
    elww.SetValue( wl[0], i );
    elwc.SetValue( wl[1], i );
    const char* we = this->MedicalImageProperties->GetNthWindowLevelPresetComment(i);
    elwe.SetValue( we, i );
    }
{
  gdcm::DataElement de = elwc.GetAsDataElement();
  de.SetTag( gdcm::Tag(0x0028,0x1050) );
  ds.Insert( de );
}
{
  gdcm::DataElement de = elww.GetAsDataElement();
  de.SetTag( gdcm::Tag(0x0028,0x1051) );
  ds.Insert( de );
}
{
  gdcm::DataElement de = elwe.GetAsDataElement();
  de.SetTag( gdcm::Tag(0x0028,0x1055) );
  ds.Insert( de );
}
}


  // Let's try to fake out the SOP Class UID here:
  gdcm::MediaStorage ms = gdcm::MediaStorage::SecondaryCaptureImageStorage;
  ms.GuessFromModality( this->MedicalImageProperties->GetModality(), this->FileDimensionality ); // Will override SC only if something is found...
  if( this->FileDimensionality != 2 && ms == gdcm::MediaStorage::SecondaryCaptureImageStorage )
    {
    vtkErrorMacro( "Cannot handle Multi Frame image in SecondaryCaptureImageStorage" );
    return 0;
    }
  // FIXME: new Secondary object handle multi frames...
  assert( gdcm::MediaStorage::IsImage( ms ) );
{
  gdcm::DataElement de( gdcm::Tag(0x0008, 0x0016) );
  const char* msstr = gdcm::MediaStorage::GetMSString(ms);
  de.SetByteValue( msstr, strlen(msstr) );
  ds.Insert( de );
}

  // Image Type is pretty much always required:
  gdcm::Attribute<0x0008,0x0008> imagetype;
  const gdcm::CSComp values[] = { "DERIVED", "PRIMARY" };
  imagetype.SetValues( values, 2 );
  ds.Insert( imagetype.GetAsDataElement() );

  // I am pretty sure that for all other images it is valid to add an Image Position (Patient)
  // and an Image Orientation (Patient)
  if ( ms != gdcm::MediaStorage::SecondaryCaptureImageStorage )
    {
    // Image Position (Patient)
    gdcm::Attribute<0x0020,0x0032> ipp = {{0,0,0}}; // default value
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 2 )
    const double *origin = data->GetOrigin();
#else
    const float *origin = data->GetOrigin();
#endif
    for(int i = 0; i < 3; ++i)
      ipp.SetValue( origin[i], i );
    ds.Insert( ipp.GetAsDataElement() );

    // Image Orientation (Patient)
    gdcm::Attribute<0x0020,0x0037> iop = {{1,0,0,0,1,0}}; // default value
    const vtkMatrix4x4 *dircos = this->DirectionCosines;
    for(int i = 0; i < 3; ++i)
      iop.SetValue( dircos->GetElement(i,0), i );
    for(int i = 0; i < 3; ++i)
      iop.SetValue( dircos->GetElement(i,1), i+3 );
    ds.Insert( iop.GetAsDataElement() );
    }

  // Here come the important part: generate proper UID for Series/Study so that people knows this is the same Study/Series
  const char *uid = this->UID;
{
  gdcm::DataElement de( gdcm::Tag(0x0020,0x000d) );
  de.SetByteValue( uid, strlen(uid) );
  ds.Insert( de );
}
{
  gdcm::DataElement de( gdcm::Tag(0x0020,0x000e) );
  de.SetByteValue( uid, strlen(uid) );
  ds.Insert( de );
}

  const char *filename = NULL;
  int k = inExt[4];
  if( this->FileNames->GetNumberOfValues() )
  {
    //int n = this->FileNames->GetNumberOfValues();
    filename = this->FileNames->GetValue(k);
  }
  else
  {
    filename = this->GetFileName();
  }
  assert( filename );
  
  // Let's add an Instance Number just for fun:
  std::ostringstream os;
  os << k;
  // Will only be added if none found
  SetStringValueFromTag(os.str().c_str(), gdcm::Tag(0x0020,0x0013), ds);
  writer.SetFileName( filename );
  if( !writer.Write() )
    {
    return 0;
    }

  return 1;
}

//----------------------------------------------------------------------------
void vtkGDCMImageWriter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
