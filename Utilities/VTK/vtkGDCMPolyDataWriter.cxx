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
#include "vtkGDCMPolyDataWriter.h"

#include "vtkObjectFactory.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkPolyData.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkFloatArray.h"
#include "vtkCellArray.h"
#include "vtkCellData.h"
#include "vtkErrorCode.h"
#include "vtkMedicalImageProperties.h"
#include "vtkRTStructSetProperties.h"

#include "gdcmWriter.h"
#include "gdcmUIDGenerator.h"
#include "gdcmSmartPointer.h"
#include "gdcmAttribute.h"
#include "gdcmSmartPointer.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmAnonymizer.h"

vtkCxxRevisionMacro(vtkGDCMPolyDataWriter, "$Revision: 1.74 $")
vtkStandardNewMacro(vtkGDCMPolyDataWriter)
vtkCxxSetObjectMacro(vtkGDCMPolyDataWriter,MedicalImageProperties,vtkMedicalImageProperties)
vtkCxxSetObjectMacro(vtkGDCMPolyDataWriter,RTStructSetProperties,vtkRTStructSetProperties)

//----------------------------------------------------------------------------
vtkGDCMPolyDataWriter::vtkGDCMPolyDataWriter()
{
  this->SetNumberOfInputPorts(9);
  this->MedicalImageProperties = vtkMedicalImageProperties::New();
  this->RTStructSetProperties = vtkRTStructSetProperties::New();
}

//----------------------------------------------------------------------------
vtkGDCMPolyDataWriter::~vtkGDCMPolyDataWriter()
{
  this->MedicalImageProperties->Delete();
  this->RTStructSetProperties->Delete();
}

using namespace gdcm;

static void SetStringValueFromTag(const char *s, const gdcm::Tag& t, gdcm::Anonymizer & ano)
{
  if( s && *s )
    {
#if 0
    gdcm::DataElement de( t );
    de.SetByteValue( s, strlen( s ) );
    const gdcm::Global& g = gdcm::Global::GetInstance();
    const gdcm::Dicts &dicts = g.GetDicts();
    // FIXME: we know the tag at compile time we could save some time
    // Using the static dict instead of the run-time one:
    const gdcm::DictEntry &dictentry = dicts.GetDictEntry( t );
    de.SetVR( dictentry.GetVR() );
    ds.Insert( de );
#else
    ano.Replace(t, s);
#endif
    }
}

//----------------------------------------------------------------------------
void vtkGDCMPolyDataWriter::WriteData()
{
  if ( this->FileName == NULL)
    {
    vtkErrorMacro(<< "Please specify FileName to write");
    this->SetErrorCode(vtkErrorCode::NoFileNameError);
    return;
    }
  Writer writer;
  writer.SetFileName( this->FileName );
  File &file = writer.GetFile();

  this->WriteRTSTRUCTInfo(file);

  int numInputs = this->GetNumberOfInputPorts();
  for(int input = 0; input < numInputs; ++input )
    {
    vtkPoints *pts;
    vtkCellArray *polys;
    vtkPolyData *input = this->GetInput();

    polys = input->GetPolys();
    pts = input->GetPoints();
    if (pts == NULL || polys == NULL )
      {
      vtkErrorMacro(<<"No data to write!");
      return;
      }

    this->WriteRTSTRUCTData(file, pts, polys);
    }

  if( !writer.Write() )
    {
    }

}

//----------------------------------------------------------------------------
void vtkGDCMPolyDataWriter::WriteRTSTRUCTInfo(gdcm::File &file)
{
  DataSet& ds = file.GetDataSet();
  const Tag sisq(0x3006,0x0039);
  DataElement de( sisq );
  de.SetVR( VR::SQ );
  SmartPointer<SequenceOfItems> sqi1 = 0;
  sqi1 = new SequenceOfItems;
  de.SetValue( *sqi1 );
  de.SetVLToUndefined();
  ds.Insert( de );

  UIDGenerator uid;

    {
    const char *sop = uid.Generate();
    DataElement de( Tag(0x0008,0x0018) );
    VL::Type strlenSOP = (VL::Type) strlen(sop);
    de.SetByteValue( sop, strlenSOP );
    de.SetVR( Attribute<0x0008, 0x0018>::GetVR() );
    ds.ReplaceEmpty( de );
    }
    {
    const char *study = uid.Generate();
    DataElement de( Tag(0x0020,0x000d) );
    VL::Type strlenStudy= (VL::Type)strlen(study);
    de.SetByteValue( study, strlenStudy );
    de.SetVR( Attribute<0x0020, 0x000d>::GetVR() );
    ds.ReplaceEmpty( de );
    }
    {
    const char *series = uid.Generate();
    DataElement de( Tag(0x0020,0x000e) );
    VL::Type strlenSeries= (VL::Type)strlen(series);
    de.SetByteValue( series, strlenSeries );
    de.SetVR( Attribute<0x0020, 0x000e>::GetVR() );
    ds.ReplaceEmpty( de );
    }

  FileMetaInformation &fmi = file.GetHeader();
  TransferSyntax ts = TransferSyntax::ImplicitVRLittleEndian;
    {
    const char *tsuid = TransferSyntax::GetTSString( ts );
    DataElement de( Tag(0x0002,0x0010) );
    VL::Type strlenTSUID = (VL::Type)strlen(tsuid);
    de.SetByteValue( tsuid, strlenTSUID );
    de.SetVR( Attribute<0x0002, 0x0010>::GetVR() );
    fmi.Replace( de );
    fmi.SetDataSetTransferSyntax(ts);
    }
  MediaStorage ms = MediaStorage::RTStructureSetStorage ;
  const char* msstr = MediaStorage::GetMSString(ms);
    {
    DataElement de( Tag(0x0008, 0x0016 ) );
    VL::Type strlenMsstr = (VL::Type)strlen(msstr);
    de.SetByteValue( msstr, strlenMsstr);
    de.SetVR( Attribute<0x0008, 0x0016>::GetVR() );
    ds.Insert( de );
    }

  int year, month, day;
  gdcm::Anonymizer ano;
    ano.SetFile( file );

    SetStringValueFromTag(this->RTStructSetProperties->GetStructureSetLabel(), gdcm::Tag(0x3006,0x0002), ano);
    SetStringValueFromTag(this->RTStructSetProperties->GetStructureSetName(), gdcm::Tag(0x3006,0x0004), ano);
    SetStringValueFromTag(this->RTStructSetProperties->GetStructureSetDate(), gdcm::Tag(0x3006,0x0008), ano);
    SetStringValueFromTag(this->RTStructSetProperties->GetStructureSetTime(), gdcm::Tag(0x3006,0x0009), ano);

{
  SmartPointer<SequenceOfItems> sqi;
  sqi = new SequenceOfItems;
  vtkIdType n = this->RTStructSetProperties->GetNumberOfReferencedFrameOfReferences();
  for( vtkIdType id = 0; id < n; ++id )
    {
    const char *sopclass = this->RTStructSetProperties->GetReferencedFrameOfReferenceClassUID(id);
    const char *instanceuid = this->RTStructSetProperties->GetReferencedFrameOfReferenceInstanceUID(id);
    Item item;
    item.SetVLToUndefined();
    DataSet &subds = item.GetNestedDataSet();
{
    Attribute<0x0008,0x1150> at;
    at.SetValue( sopclass );
    subds.Insert( at.GetAsDataElement() );
}
{
    Attribute<0x0008,0x1155> at;
    at.SetValue( instanceuid );
    subds.Insert( at.GetAsDataElement() );
}

    sqi->AddItem( item );
    }

  DataElement de1( Tag(0x3006,0x0010) );
  de1.SetVR( VR::SQ );
  SmartPointer<SequenceOfItems> sqi1 = new SequenceOfItems;
  de1.SetValue( *sqi1 );
  de1.SetVLToUndefined();
  ds.Insert( de1 );

  Item item1;
  item1.SetVLToUndefined();
  DataSet &ds2 = item1.GetNestedDataSet();

  DataElement de2( Tag(0x3006,0x0012) );
  de2.SetVR( VR::SQ );
  SmartPointer<SequenceOfItems> sqi2 = new SequenceOfItems;
  de2.SetValue( *sqi2 );
  de2.SetVLToUndefined();
  ds2.Insert( de2 );

  Item item2;
  item2.SetVLToUndefined();
  DataSet &ds3 = item2.GetNestedDataSet();

  DataElement de3( Tag(0x3006,0x0014) );
  de3.SetVR( VR::SQ );
  SmartPointer<SequenceOfItems> sqi3 = new SequenceOfItems;
  de3.SetValue( *sqi3 );
  de3.SetVLToUndefined();
  ds3.Insert( de3 );

  Item item3;
  item3.SetVLToUndefined();
  DataSet &ds4 = item3.GetNestedDataSet();

  DataElement de4( Tag(0x3006,0x0016) );
  de4.SetVR( VR::SQ );
  //SmartPointer<SequenceOfItems> sqi4 = new SequenceOfItems;
  de4.SetValue( *sqi );
  de4.SetVLToUndefined();
  ds4.Insert( de4 );

  //Item item4;
  //item4.SetVLToUndefined();
  //DataSet &ds5 = item4.GetNestedDataSet();

  //sqi4->AddItem( item4 );

  sqi3->AddItem( item3 );

  sqi2->AddItem( item2 );

  sqi1->AddItem( item1 );


}

    // For ex: DICOM (0010,0010) = DOE,JOHN
    SetStringValueFromTag(this->MedicalImageProperties->GetPatientName(), gdcm::Tag(0x0010,0x0010), ano);
    // For ex: DICOM (0010,0020) = 1933197
    SetStringValueFromTag( this->MedicalImageProperties->GetPatientID(), gdcm::Tag(0x0010,0x0020), ano);
    // For ex: DICOM (0010,1010) = 031Y
    SetStringValueFromTag( this->MedicalImageProperties->GetPatientAge(), gdcm::Tag(0x0010,0x1010), ano);
    // For ex: DICOM (0010,0040) = M
    SetStringValueFromTag( this->MedicalImageProperties->GetPatientSex(), gdcm::Tag(0x0010,0x0040), ano);
    // For ex: DICOM (0010,0030) = 19680427
    SetStringValueFromTag( this->MedicalImageProperties->GetPatientBirthDate(), gdcm::Tag(0x0010,0x0030), ano);
#if ( VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 0 )
    // For ex: DICOM (0008,0020) = 20030617
    if( vtkMedicalImageProperties::GetDateAsFields( this->MedicalImageProperties->GetStudyDate(), year, month, day ) )
      SetStringValueFromTag( this->MedicalImageProperties->GetStudyDate(), gdcm::Tag(0x0008,0x0020), ano);
#endif
    // For ex: DICOM (0008,0022) = 20030617
    SetStringValueFromTag( this->MedicalImageProperties->GetAcquisitionDate(), gdcm::Tag(0x0008,0x0022), ano);
#if ( VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 0 )
    // For ex: DICOM (0008,0030) = 162552.0705 or 230012, or 0012
#if ( VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 4 )
    int hour, minute, second;
    if( vtkMedicalImageProperties::GetTimeAsFields( this->MedicalImageProperties->GetStudyTime(), hour, minute, second ) )
#endif
      SetStringValueFromTag( this->MedicalImageProperties->GetStudyTime(), gdcm::Tag(0x0008,0x0030), ano);
#endif
    // For ex: DICOM (0008,0032) = 162552.0705 or 230012, or 0012
    SetStringValueFromTag( this->MedicalImageProperties->GetAcquisitionTime(), gdcm::Tag(0x0008,0x0032), ano);
    // For ex: DICOM (0008,0023) = 20030617
    SetStringValueFromTag( this->MedicalImageProperties->GetImageDate(), gdcm::Tag(0x0008,0x0023), ano);
    // For ex: DICOM (0008,0033) = 162552.0705 or 230012, or 0012
    SetStringValueFromTag( this->MedicalImageProperties->GetImageTime(), gdcm::Tag(0x0008,0x0033), ano);
    // For ex: DICOM (0020,0013) = 1
    SetStringValueFromTag( this->MedicalImageProperties->GetImageNumber(), gdcm::Tag(0x0020,0x0013), ano);
    // For ex: DICOM (0020,0011) = 902
    SetStringValueFromTag( this->MedicalImageProperties->GetSeriesNumber(), gdcm::Tag(0x0020,0x0011), ano);
    // For ex: DICOM (0008,103e) = SCOUT
    SetStringValueFromTag( this->MedicalImageProperties->GetSeriesDescription(), gdcm::Tag(0x0008,0x103e), ano);
    // For ex: DICOM (0020,0010) = 37481
    SetStringValueFromTag( this->MedicalImageProperties->GetStudyID(), gdcm::Tag(0x0020,0x0010), ano);
    // For ex: DICOM (0008,1030) = BRAIN/C-SP/FACIAL
    SetStringValueFromTag( this->MedicalImageProperties->GetStudyDescription(), gdcm::Tag(0x0008,0x1030), ano);
    // For ex: DICOM (0008,0060)= CT
    SetStringValueFromTag( this->MedicalImageProperties->GetModality(), gdcm::Tag(0x0008,0x0060), ano);
    // For ex: DICOM (0008,0070) = Siemens
    SetStringValueFromTag( this->MedicalImageProperties->GetManufacturer(), gdcm::Tag(0x0008,0x0070), ano);
    // For ex: DICOM (0008,1090) = LightSpeed QX/i
    SetStringValueFromTag( this->MedicalImageProperties->GetManufacturerModelName(), gdcm::Tag(0x0008,0x1090), ano);
    // For ex: DICOM (0008,1010) = LSPD_OC8
    SetStringValueFromTag( this->MedicalImageProperties->GetStationName(), gdcm::Tag(0x0008,0x1010), ano);
    // For ex: DICOM (0008,0080) = FooCity Medical Center
    SetStringValueFromTag( this->MedicalImageProperties->GetInstitutionName(), gdcm::Tag(0x0008,0x0080), ano);
    // For ex: DICOM (0018,1210) = Bone
    SetStringValueFromTag( this->MedicalImageProperties->GetConvolutionKernel(), gdcm::Tag(0x0018,0x1210), ano);
    // For ex: DICOM (0018,0050) = 0.273438
    SetStringValueFromTag( this->MedicalImageProperties->GetSliceThickness(), gdcm::Tag(0x0018,0x0050), ano);
    // For ex: DICOM (0018,0060) = 120
    SetStringValueFromTag( this->MedicalImageProperties->GetKVP(), gdcm::Tag(0x0018,0x0060), ano);
    // For ex: DICOM (0018,1120) = 15
    SetStringValueFromTag( this->MedicalImageProperties->GetGantryTilt(), gdcm::Tag(0x0018,0x1120), ano);
    // For ex: DICOM (0018,0081) = 105
    SetStringValueFromTag( this->MedicalImageProperties->GetEchoTime(), gdcm::Tag(0x0018,0x0081), ano);
    // For ex: DICOM (0018,0091) = 35
    SetStringValueFromTag( this->MedicalImageProperties->GetEchoTrainLength(), gdcm::Tag(0x0018,0x0091), ano);
    // For ex: DICOM (0018,0080) = 2040
    SetStringValueFromTag( this->MedicalImageProperties->GetRepetitionTime(), gdcm::Tag(0x0018,0x0080), ano);
    // For ex: DICOM (0018,1150) = 5
    SetStringValueFromTag( this->MedicalImageProperties->GetExposureTime(), gdcm::Tag(0x0018,0x1150), ano);
    // For ex: DICOM (0018,1151) = 400
    SetStringValueFromTag( this->MedicalImageProperties->GetXRayTubeCurrent(), gdcm::Tag(0x0018,0x1151), ano);
    // For ex: DICOM (0018,1152) = 114
    SetStringValueFromTag( this->MedicalImageProperties->GetExposure(), gdcm::Tag(0x0018,0x1152), ano);

}

void vtkGDCMPolyDataWriter::WriteRTSTRUCTData(gdcm::File &file, vtkPoints *pts, vtkCellArray *polys)
{
/*
(3006,0039) ?? (SQ)                                               # u/l,1 ROI Contour Sequence
  (fffe,e000) na (Item with undefined length)
    (3006,002a) ?? (IS) [220\160\120 ]                            # 12,3 ROI Display Color
    (3006,0040) ?? (SQ)                                           # u/l,1 Contour Sequence
      (fffe,e000) na (Item with undefined length)
        (3006,0016) ?? (SQ)                                       # u/l,1 Contour Image Sequence
          (fffe,e000) na (Item with undefined length)
            (0008,1150) ?? (UI) [1.2.840.10008.5.1.4.1.1.2]       # 26,1 Referenced SOP Class UID
            (0008,1155) ?? (UI) [1.3.6.1.4.1.22213.1.1396.148]    # 28,1 Referenced SOP Instance UID
          (fffe,e00d)
        (fffe,e0dd)
        (3006,0042) ?? (CS) [CLOSED_PLANAR ]                      # 14,1 Contour Geometric Type
        (3006,0046) ?? (IS) [139 ]                                # 4,1 Number of Contour Points
        (3006,0050) ?? (DS) [-209.81171875\-392.41171875\...]     # 5004,3-3n Contour Data
      (fffe,e00d)

*/
  SmartPointer<SequenceOfItems> sqi;
  sqi = new SequenceOfItems;

  vtkIdType npts = 0;
  vtkIdType *indx = 0;
  double v[3];
  std::vector<double> cellpoints;
  for (polys->InitTraversal(); polys->GetNextCell(npts,indx); )
    {
    cellpoints.resize(0);
    for(vtkIdType index = 0; index < npts; ++index)
      {
      pts->GetPoint(indx[index],v);
      cellpoints.push_back( v[0] );
      cellpoints.push_back( v[1] );
      cellpoints.push_back( v[2] );
      }
    Item item;
    item.SetVLToUndefined();
    DataSet &subds = item.GetNestedDataSet();
    Attribute<0x3006,0x0050> at;
    at.SetValues( &cellpoints[0], cellpoints.size(), false );
    subds.Insert( at.GetAsDataElement() );

    Attribute<0x3006,0x0046> numcontpoints;
    numcontpoints.SetValue( npts );
    subds.Insert( numcontpoints.GetAsDataElement() );
    Attribute<0x3006,0x0042> contgeotype;
    contgeotype.SetValue( "CLOSED_PLANAR " );
    subds.Insert( contgeotype.GetAsDataElement() );

    sqi->AddItem( item );
    }
  DataSet& ds = file.GetDataSet();
{
  const Tag sisq(0x3006,0x0039);
  SmartPointer<SequenceOfItems> sqi1 = 0;
  sqi1 = ds.GetDataElement( sisq ).GetValueAsSQ();
  assert( sqi1 );

  Item item;
  item.SetVLToUndefined();
  DataSet &subds = item.GetNestedDataSet();

  const Tag sisq2(0x3006,0x0040);
  DataElement de2( sisq2 );
  de2.SetVR( VR::SQ );
  de2.SetValue( *sqi );
  de2.SetVLToUndefined();
  subds.Insert( de2 );

    sqi1->AddItem( item );
}

}


//----------------------------------------------------------------------------
void vtkGDCMPolyDataWriter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
