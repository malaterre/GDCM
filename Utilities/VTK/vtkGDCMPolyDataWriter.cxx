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

#include "gdcmWriter.h"
#include "gdcmUIDGenerator.h"
#include "gdcmSmartPointer.h"
#include "gdcmAttribute.h"
#include "gdcmSmartPointer.h"
#include "gdcmSequenceOfItems.h"

vtkCxxRevisionMacro(vtkGDCMPolyDataWriter, "$Revision: 1.74 $")
vtkStandardNewMacro(vtkGDCMPolyDataWriter)

//----------------------------------------------------------------------------
vtkGDCMPolyDataWriter::vtkGDCMPolyDataWriter()
{
}

//----------------------------------------------------------------------------
void vtkGDCMPolyDataWriter::WriteData()
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

  if ( this->FileName == NULL)
    {
    vtkErrorMacro(<< "Please specify FileName to write");
    this->SetErrorCode(vtkErrorCode::NoFileNameError);
    return;
    }

  this->WriteRTSTRUCT(pts,polys);

}

//----------------------------------------------------------------------------
void vtkGDCMPolyDataWriter::WriteRTSTRUCT(vtkPoints *pts, vtkCellArray *polys)
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
  using namespace gdcm;
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
  Writer writer;
  writer.SetFileName( this->FileName );
  File &file = writer.GetFile();
  DataSet& ds = file.GetDataSet();
{
  const Tag sisq(0x3006,0x0039);
  DataElement de( sisq );
  de.SetVR( VR::SQ );
  SmartPointer<SequenceOfItems> sqi1;
  sqi1 = new SequenceOfItems;
  de.SetValue( *sqi1 );
  de.SetVLToUndefined();
  ds.Insert( de );

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
  UIDGenerator uid;

    {
    const char *sop = uid.Generate();
    DataElement de( Tag(0x0008,0x0018) );
    VL::Type strlenSOP = (VL::Type) strlen(sop);
    de.SetByteValue( sop, strlenSOP );
    de.SetVR( Attribute<0x0008, 0x0018>::GetVR() );
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

if( !writer.Write() )
{
}

}

//----------------------------------------------------------------------------
vtkGDCMPolyDataWriter::~vtkGDCMPolyDataWriter()
{
}


//----------------------------------------------------------------------------
void vtkGDCMPolyDataWriter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
