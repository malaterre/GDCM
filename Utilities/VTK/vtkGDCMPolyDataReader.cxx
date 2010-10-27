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
#include "vtkGDCMPolyDataReader.h"

#include "vtkObjectFactory.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkPolyData.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkFloatArray.h"
#include "vtkCellArray.h"
#include "vtkCellData.h"
#include "vtkMedicalImageProperties.h"
#include "vtkRTStructSetProperties.h"

#include "gdcmReader.h"
#include "gdcmSmartPointer.h"
#include "gdcmAttribute.h"
#include "gdcmSequenceOfItems.h"

vtkCxxRevisionMacro(vtkGDCMPolyDataReader, "$Revision: 1.74 $")
vtkStandardNewMacro(vtkGDCMPolyDataReader)

//----------------------------------------------------------------------------
vtkGDCMPolyDataReader::vtkGDCMPolyDataReader()
{
  this->FileName = NULL;
  this->SetNumberOfInputPorts(0);
  this->MedicalImageProperties = vtkMedicalImageProperties::New();
  this->RTStructSetProperties = vtkRTStructSetProperties::New();
}

//----------------------------------------------------------------------------
vtkGDCMPolyDataReader::~vtkGDCMPolyDataReader()
{
  this->SetFileName(0);
  this->MedicalImageProperties->Delete();
  this->RTStructSetProperties->Delete();
}

//----------------------------------------------------------------------------
// inline keyword is needed since GetStringValueFromTag was copy/paste from vtkGDCMImageReader
// FIXME: need to restructure code to avoid copy/paste
inline const char *GetStringValueFromTag(const gdcm::Tag& t, const gdcm::DataSet& ds)
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
void vtkGDCMPolyDataReader::FillMedicalImageInformation(const gdcm::Reader &reader)
{
  const gdcm::File &file = reader.GetFile();
  const gdcm::DataSet &ds = file.GetDataSet();

  this->RTStructSetProperties->SetStructureSetLabel( GetStringValueFromTag( gdcm::Tag(0x3006,0x0002), ds) );
  this->RTStructSetProperties->SetStructureSetName( GetStringValueFromTag( gdcm::Tag(0x3006,0x0004), ds) );
  this->RTStructSetProperties->SetStructureSetDate( GetStringValueFromTag( gdcm::Tag(0x3006,0x0008), ds) );
  this->RTStructSetProperties->SetStructureSetTime( GetStringValueFromTag( gdcm::Tag(0x3006,0x0009), ds) );

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
      unsigned int count = gdcm::VM::GetNumberOfElementsFromArray(swe.c_str(), swe.size()); (void)count;
      // I found a case with only one W/L but two comments: WINDOW1\WINDOW2
      // SIEMENS-IncompletePixelData.dcm
      //assert( count >= (unsigned int)n );
      elwe.SetLength( /*count*/ n * vr.GetSizeof() );
      ss.str( swe );
      elwe.Read( ss );
      for(int i = 0; i < n; ++i)
        {
        this->MedicalImageProperties->SetNthWindowLevelPresetComment(i, elwe.GetValue(i).c_str() );
        }
      }
    }

#if 0
  // gdcmData/JDDICOM_Sample4.dcm
  // -> (0008,0060) CS [DM  Digital microscopy]                 #  24, 1 Modality
  gdcm::MediaStorage ms1 = gdcm::MediaStorage::SecondaryCaptureImageStorage;
  ms1.GuessFromModality( this->MedicalImageProperties->GetModality(), this->FileDimensionality );
  gdcm::MediaStorage ms2;
  ms2.SetFromFile( reader.GetFile() );
  if( ms2 != ms1 && ms2 != gdcm::MediaStorage::SecondaryCaptureImageStorage )
    {
    vtkWarningMacro( "SHOULD NOT HAPPEN. Unrecognized Modality: " << this->MedicalImageProperties->GetModality()
      << " Will be set instead to the known one: " << ms2.GetModality() )
    this->MedicalImageProperties->SetModality( ms2.GetModality() );
    }
#endif

  // Add more info:

}

//(3006,0022) ?? (IS) [2 ]                                      # 2,1 ROI Number
//(3006,0024) ?? (UI) [2.16.840.1.114362.1.759508.1251415878280.193]         # 44,1 Referenced Frame of Reference UID
//(3006,0026) ?? (LO) [Bladder ]                                # 8,1 ROI Name
//(3006,0036) ?? (CS) [MANUAL]                                  # 6,1 ROI Generation Algorithm

struct StructureSetROI
{
  int ROINumber;
  std::string RefFrameRefUID;
  std::string ROIName;
  std::string ROIGenerationAlgorithm;
};

int vtkGDCMPolyDataReader::RequestData_RTStructureSetStorage(gdcm::Reader const &reader,
  vtkInformationVector *outputVector)
{
// This is done in RequestInformation
//  gdcm::MediaStorage ms;
//  ms.SetFromFile( reader.GetFile() );
//  //std::cout << ms << std::endl;
//  if( ms != gdcm::MediaStorage::RTStructureSetStorage )
//    {
//    return 0;
//    }

  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();
  // (3006,0010) SQ (Sequence with undefined length #=1)     # u/l, 1 ReferencedFrameOfReferenceSequence
  // (3006,0020) SQ (Sequence with explicit length #=4)      # 370, 1 StructureSetROISequence
  // (3006,0039) SQ (Sequence with explicit length #=4)      # 24216, 1 ROIContourSequence
  gdcm::Tag troicsq(0x3006,0x0039);
  if( !ds.FindDataElement( troicsq ) )
    {
    return 0;
    }
  gdcm::Tag tssroisq(0x3006,0x0020);
  if( !ds.FindDataElement( tssroisq ) )
    {
    return 0;
    }
  gdcm::Tag trefframerefsq(0x3006,0x0010);
  if( !ds.FindDataElement( trefframerefsq ) )
    {
    return 0;
    }
  const gdcm::DataElement &refframerefsq = ds.GetDataElement( trefframerefsq );
  gdcm::SmartPointer<gdcm::SequenceOfItems> sqi0 = refframerefsq.GetValueAsSQ();
  if( !sqi0 || !sqi0->GetNumberOfItems() )
    {
    return 0;
    }
    assert( sqi0->GetNumberOfItems() == 1 );
  for(unsigned int pd = 0; pd < sqi0->GetNumberOfItems(); ++pd)
    {
    const gdcm::Item & item = sqi0->GetItem(pd+1); // Item start at #1
    const gdcm::DataSet& nestedds = item.GetNestedDataSet();
    // (3006,0012) SQ (Sequence with undefined length #=1)     # u/l, 1 RTReferencedStudySequence
    gdcm::Tag trtrefstudysq(0x3006,0x0012);
    if( !nestedds.FindDataElement( trtrefstudysq) )
      {
      return 0;
      }
    const gdcm::DataElement &rtrefstudysq = nestedds.GetDataElement( trtrefstudysq );
    gdcm::SmartPointer<gdcm::SequenceOfItems> sqi00 = rtrefstudysq.GetValueAsSQ();
    if( !sqi00 || !sqi00->GetNumberOfItems() )
      {
      return 0;
      }
    assert( sqi00->GetNumberOfItems() == 1 );
    for(unsigned int pd0 = 0; pd0 < sqi00->GetNumberOfItems(); ++pd0)
      {
      const gdcm::Item & item = sqi00->GetItem(pd0+1); // Item start at #1
      const gdcm::DataSet& nestedds = item.GetNestedDataSet();

        // (3006,0014) SQ (Sequence with undefined length #=1)     # u/l, 1 RTReferencedSeriesSequence
    gdcm::Tag trtrefseriessq(0x3006,0x0014);
    if( !nestedds.FindDataElement( trtrefseriessq) )
      {
      return 0;
      }
    const gdcm::DataElement &rtrefseriessq = nestedds.GetDataElement( trtrefseriessq);
    gdcm::SmartPointer<gdcm::SequenceOfItems> sqi000 = rtrefseriessq.GetValueAsSQ();
    if( !sqi000 || !sqi000->GetNumberOfItems() )
      {
      return 0;
      }
    assert( sqi000->GetNumberOfItems() == 1 );
    for(unsigned int pd00 = 0; pd00 < sqi000->GetNumberOfItems(); ++pd00)
      {
      const gdcm::Item & item = sqi000->GetItem(pd00+1); // Item start at #1
      const gdcm::DataSet& nestedds = item.GetNestedDataSet();
            // (3006,0016) SQ (Sequence with undefined length #=162)   # u/l, 1 ContourImageSequence
    gdcm::Tag tcontourimageseq(0x3006,0x0016);
    if( !nestedds.FindDataElement( tcontourimageseq) )
      {
      return 0;
      }
    const gdcm::DataElement &contourimageseq = nestedds.GetDataElement( tcontourimageseq );
    gdcm::SmartPointer<gdcm::SequenceOfItems> sqi0000 = contourimageseq.GetValueAsSQ();
    if( !sqi0000 || !sqi0000->GetNumberOfItems() )
      {
      return 0;
      }

    assert( sqi0000->GetNumberOfItems() != 1 );
    for(unsigned int pd000 = 0; pd000 < sqi0000->GetNumberOfItems(); ++pd000)
      {
      const gdcm::Item & item = sqi0000->GetItem(pd000+1); // Item start at #1
      const gdcm::DataSet& nestedds = item.GetNestedDataSet();
      gdcm::Attribute<0x0008,0x1150> refsopclassuid;
      refsopclassuid.SetFromDataSet( nestedds );
      gdcm::Attribute<0x0008,0x1155> refinstanceuid;
      refinstanceuid.SetFromDataSet( nestedds );
  this->RTStructSetProperties->AddReferencedFrameOfReference( refsopclassuid.GetValue().c_str(),
refinstanceuid.GetValue().c_str() );
      }

      }

      }
    }

  const gdcm::DataElement &roicsq = ds.GetDataElement( troicsq );
  //std::cout << roicsq << std::endl;
  //const gdcm::SequenceOfItems *sqi_debug = roicsq.GetSequenceOfItems();
  gdcm::SmartPointer<gdcm::SequenceOfItems> sqi = roicsq.GetValueAsSQ();
  if( !sqi || !sqi->GetNumberOfItems() )
    {
    return 0;
    }
  const gdcm::DataElement &ssroisq = ds.GetDataElement( tssroisq );
  //const gdcm::SequenceOfItems *ssqi = ssroisq.GetSequenceOfItems();
  gdcm::SmartPointer<gdcm::SequenceOfItems> ssqi = ssroisq.GetValueAsSQ();
  if( !ssqi || !ssqi->GetNumberOfItems() )
    {
    return 0;
    }

  // For each Item in the DataSet create a vtkPolyData
  std::vector<StructureSetROI> structuresetrois;
  for(unsigned int pd = 0; pd < sqi->GetNumberOfItems(); ++pd)
    {
    StructureSetROI structuresetroi;
    // get the info object
    vtkInformation *outInfo1 = outputVector->GetInformationObject(pd);

    // get the ouptut
    vtkPolyData *output = vtkPolyData::SafeDownCast(
      outInfo1->Get(vtkDataObject::DATA_OBJECT()));


    const gdcm::Item & item = sqi->GetItem(pd+1); // Item start at #1
    //std::cout << item << std::endl;
    const gdcm::Item & sitem = ssqi->GetItem(pd+1); // Item start at #1
    const gdcm::DataSet& snestedds = sitem.GetNestedDataSet();
    // (3006,0026) ?? (LO) [date]                                    # 4,1 ROI Name
    gdcm::Tag stcsq(0x3006,0x0026);
    if( !snestedds.FindDataElement( stcsq ) )
      {
      continue;
      }
    const gdcm::DataElement &sde = snestedds.GetDataElement( stcsq );
    std::string s(sde.GetByteValue()->GetPointer(), sde.GetByteValue()->GetLength());
    structuresetroi.ROIName = s;
    gdcm::Attribute<0x3006,0x0022> roinumber;
    roinumber.SetFromDataSet( snestedds );
    structuresetroi.ROINumber = roinumber.GetValue();
    gdcm::Attribute<0x3006,0x0024> refframeuid;
    refframeuid.SetFromDataSet( snestedds );
    structuresetroi.RefFrameRefUID = refframeuid.GetValue();
    gdcm::Attribute<0x3006,0x0026> roiname;
    roiname.SetFromDataSet( snestedds );
    assert( s == roiname.GetValue() );
    gdcm::Attribute<0x3006,0x0036> roigenalg;
    roigenalg.SetFromDataSet( snestedds );
    structuresetroi.ROIGenerationAlgorithm = roigenalg.GetValue();
    structuresetrois.push_back( structuresetroi );

    const gdcm::DataSet& nestedds = item.GetNestedDataSet();
    //std::cout << nestedds << std::endl;
    //(3006,002a) IS [255\192\96]                              # 10,3 ROI Display Color
    gdcm::Tag troidc(0x3006,0x002a);
    gdcm::Attribute<0x3006,0x002a> color = {};
    if( nestedds.FindDataElement( troidc) )
      {
      const gdcm::DataElement &decolor = nestedds.GetDataElement( troidc );
      color.SetFromDataElement( decolor );
      //std::cout << "color:" << color[0] << "," << color[1] << "," << color[2] << std::endl;
      }
    //(3006,0040) SQ (Sequence with explicit length #=8)      # 4326, 1 ContourSequence
    gdcm::Tag tcsq(0x3006,0x0040);
    if( !nestedds.FindDataElement( tcsq ) )
      {
      continue;
      }
    const gdcm::DataElement& csq = nestedds.GetDataElement( tcsq );
    //std::cout << csq << std::endl;

    //const gdcm::SequenceOfItems *sqi2 = csq.GetSequenceOfItems();
    gdcm::SmartPointer<gdcm::SequenceOfItems> sqi2 = csq.GetValueAsSQ();
    if( !sqi2 || !sqi2->GetNumberOfItems() )
      {
      continue;
      }
    unsigned int nitems = sqi2->GetNumberOfItems();
    //std::cout << nitems << std::endl;
    //this->SetNumberOfOutputPorts(nitems);
    vtkFloatArray *scalars = vtkFloatArray::New();
    scalars->SetNumberOfComponents(3);

    vtkPoints *newPts = vtkPoints::New();
    //std::string s(sde.GetByteValue()->GetPointer(), sde.GetByteValue()->GetLength());
    //std::cout << s << std::endl;
    //newPts->GetData()->SetName( s.c_str() );
    // In VTK there is no API to specify the name of a vtkPolyData, you can only specify Name
    // for the scalars (pointdata or celldata), so let's do that...
    scalars->SetName( structuresetroi.ROIName.c_str() );
    vtkCellArray *polys = vtkCellArray::New();
    for(unsigned int i = 0; i < nitems; ++i)
      {
      const gdcm::Item & item2 = sqi2->GetItem(i+1); // Item start at #1

      const gdcm::DataSet& nestedds2 = item2.GetNestedDataSet();
      //std::cout << nestedds2 << std::endl;
      // (3006,0050) DS [43.57636\65.52504\-10.0\46.043102\62.564945\-10.0\49.126537\60.714... # 398,48 ContourData
      gdcm::Tag tcontourdata(0x3006,0x0050);
      const gdcm::DataElement & contourdata = nestedds2.GetDataElement( tcontourdata );
      //std::cout << contourdata << std::endl;

      //const gdcm::ByteValue *bv = contourdata.GetByteValue();
      gdcm::Attribute<0x3006,0x0050> at;
      at.SetFromDataElement( contourdata );

      //newPts->SetNumberOfPoints( at.GetNumberOfValues() / 3 );
      //assert( at.GetNumberOfValues() % 3 == 0); // FIXME
      const double* pts = at.GetValues();
      vtkIdType buffer[256];
      vtkIdType *ptIds;
      unsigned int npts = at.GetNumberOfValues() / 3;
      if(npts>256)
        {
        ptIds = new vtkIdType[npts];
        }
      else
        {
        ptIds = buffer;
        }
      for(unsigned int i = 0; i < npts * 3; i+=3)
        {
        float x[3];
        x[0] = pts[i+0];
        x[1] = pts[i+1];
        x[2] = pts[i+2];
        vtkIdType ptId = newPts->InsertNextPoint( x );
        ptIds[i / 3] = ptId;
        }
      // Each Contour Data is in fact a Cell:
      vtkIdType cellId = polys->InsertNextCell( npts , ptIds);
      scalars->InsertTuple3(cellId, (double)color[0]/255.0, (double)color[1]/255.0, (double)color[2]/255.0);
      if(npts>256)
        {
        delete[] ptIds;
        }
      }
    output->SetPoints(newPts);
    newPts->Delete();
    output->SetPolys(polys);
    polys->Delete();
    output->GetCellData()->SetScalars(scalars);
    scalars->Delete();
    }

  return 1;
}

int vtkGDCMPolyDataReader::RequestData_HemodynamicWaveformStorage(gdcm::Reader const &reader,
  vtkInformationVector *outputVector)
{
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();
  // (5400,0100) SQ (Sequence with undefined length #=1)     # u/l, 1 WaveformSequence
  gdcm::Tag twsq(0x5400,0x0100);
  if( !ds.FindDataElement( twsq) )
    {
    return 0;
    }
  const gdcm::DataElement &wsq = ds.GetDataElement( twsq );
  //std::cout << wsq << std::endl;
  //const gdcm::SequenceOfItems *sqi = wsq.GetSequenceOfItems();
  gdcm::SmartPointer<gdcm::SequenceOfItems> sqi = wsq.GetValueAsSQ();
  if( !sqi || !sqi->GetNumberOfItems() )
    {
    return 0;
    }

  const gdcm::Item & item = sqi->GetItem(1); // Item start at #1
  const gdcm::DataSet& nestedds = item.GetNestedDataSet();

  // (5400,1004) US 16                                       #   2, 1 WaveformBitsAllocated
  gdcm::Tag twba(0x5400,0x1004);
  if( !nestedds.FindDataElement( twba ) )
    {
    return 0;
    }
  const gdcm::DataElement &wba= nestedds.GetDataElement( twba );

  //std::cout << wba << std::endl;
  //  (5400,1006) CS [SS]                                     #   2, 1 WaveformSampleInterpretation
  // (5400,1010) OW 00ba\0030\ff76\ff8b\00a2\ffd3\ffae\ff50\0062\00c4\011e\00c2\00ba... # 57600, 1 WaveformData
  gdcm::Tag twd(0x5400,0x1010);
  if( !nestedds.FindDataElement( twd ) )
    {
    return 0;
    }
  const gdcm::DataElement &wd = nestedds.GetDataElement( twd );
  const gdcm::ByteValue *bv = wd.GetByteValue();
  size_t len = bv->GetLength();
  int16_t *p = (int16_t*)bv;

  // get the info object
  int pd = 0;
  vtkInformation *outInfo1 = outputVector->GetInformationObject(pd);

  // get the ouptut
  vtkPolyData *output = vtkPolyData::SafeDownCast(
    outInfo1->Get(vtkDataObject::DATA_OBJECT()));

  vtkPoints *newPts = vtkPoints::New();
  size_t npts = len / 2;
  //npts = 10; // DEBUG !
  for(size_t i = 0; i < npts; ++i )
    {
    float x[3];
    x[0] = (float)p[i] / 8800;
    //std::cout << p[i] << std::endl;
    x[1] = i;
    x[2] = 0;
    vtkIdType ptId = newPts->InsertNextPoint( x );
    }
  output->SetPoints(newPts);
  newPts->Delete();

  vtkCellArray* lines = vtkCellArray::New();
  for ( int i = 0; i < newPts->GetNumberOfPoints() - 1; ++i )
    {
    vtkIdType topol[2];
    topol[0] = i;
    topol[1] = i+1;
    lines->InsertNextCell( 2, topol );
    }

  output->SetLines(lines);
  lines->Delete();
  output->BuildCells();
  //output->GetCellData()->SetScalars(scalars);
  //scalars->Delete();

  return 1;
}

//----------------------------------------------------------------------------
int vtkGDCMPolyDataReader::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *outputVector)
{
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  //vtkPoints *newPts, *mergedPts;
  //vtkCellArray *newPolys, *mergedPolys;
  //vtkFloatArray *newScalars=0, *mergedScalars=0;

  // All of the data in the first piece.
  if (outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_PIECE_NUMBER()) > 0)
    {
    return 0;
    }

  if ( !this->FileName || !*this->FileName )
    {
    vtkErrorMacro(<<"A FileName must be specified.");
    return 0;
    }

  gdcm::Reader reader;
  reader.SetFileName( this->FileName );
  if( !reader.Read() )
    {
    return 0;
    }

  gdcm::MediaStorage ms;
  ms.SetFromFile( reader.GetFile() );

  int ret;
  if( ms == gdcm::MediaStorage::RTStructureSetStorage )
    {
    ret = this->RequestData_RTStructureSetStorage(reader, outputVector);
    }
  else if( ms == gdcm::MediaStorage::HemodynamicWaveformStorage)
    {
    ret = this->RequestData_HemodynamicWaveformStorage(reader, outputVector);
    }
  else
    {
    // not handled assume error
    ret = 0;
    }

  return ret;
}

int vtkGDCMPolyDataReader::RequestInformation_RTStructureSetStorage(gdcm::Reader const & reader)
{
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();
  // (3006,0020) SQ (Sequence with explicit length #=4)      # 370, 1 StructureSetROISequence
  gdcm::Tag tssroisq(0x3006,0x0020);
  if( !ds.FindDataElement( tssroisq ) )
    {
    return 0;
    }

  const gdcm::DataElement &ssroisq = ds.GetDataElement( tssroisq );
  //const gdcm::SequenceOfItems *sqi = ssroisq.GetSequenceOfItems();
  gdcm::SmartPointer<gdcm::SequenceOfItems> sqi = ssroisq.GetValueAsSQ();
  if( !sqi || !sqi->GetNumberOfItems() )
    {
    return 0;
    }
  unsigned int npds = sqi->GetNumberOfItems();

  //std::cout << "Nb pd:" << npds << std::endl;
  this->SetNumberOfOutputPorts( npds );

  // Allocate
  for(unsigned int i = 1; i < npds; ++i) // first output is allocated for us
    {
    vtkPolyData *output2 = vtkPolyData::New();
    this->GetExecutive()->SetOutputData(i, output2);
    output2->Delete();
    }
  return 1;
}

int vtkGDCMPolyDataReader::RequestInformation_HemodynamicWaveformStorage(gdcm::Reader const & reader)
{
  return 1;
}

//----------------------------------------------------------------------------
int vtkGDCMPolyDataReader::RequestInformation(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *outputVector)
{
  // get the info object
//  vtkInformation *outInfo = outputVector->GetInformationObject(0);
//
//  outInfo->Set(vtkStreamingDemandDrivenPipeline::MAXIMUM_NUMBER_OF_PIECES(),
//               -1);
  gdcm::Reader reader;
  reader.SetFileName( this->FileName );
  if( !reader.Read() )
    {
    return 0;
    }

  gdcm::MediaStorage ms;
  ms.SetFromFile( reader.GetFile() );

  int ret;
  if( ms == gdcm::MediaStorage::RTStructureSetStorage )
    {
    ret = this->RequestInformation_RTStructureSetStorage(reader);
    }
  else if( ms == gdcm::MediaStorage::HemodynamicWaveformStorage)
    {
    ret = this->RequestInformation_HemodynamicWaveformStorage(reader);
    }
  else
    {
    // not handled assume error
    ret = 0;
    }

  if( ret )
    {
    // Ok let's fill in the 'extra' info:
    this->FillMedicalImageInformation(reader);
    }

  return ret;
}


//----------------------------------------------------------------------------
void vtkGDCMPolyDataReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "File Name: "
     << (this->FileName ? this->FileName : "(none)") << "\n";


}
