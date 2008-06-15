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
#include "vtkGDCMPolyDataReader.h"

#include "vtkObjectFactory.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkPolyData.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkFloatArray.h"
#include "vtkCellArray.h"

#include "gdcmReader.h"
#include "gdcmAttribute.h"
#include "gdcmSequenceOfItems.h"

vtkCxxRevisionMacro(vtkGDCMPolyDataReader, "$Revision: 1.74 $")
vtkStandardNewMacro(vtkGDCMPolyDataReader)

//----------------------------------------------------------------------------
vtkGDCMPolyDataReader::vtkGDCMPolyDataReader()
{
  this->FileName = NULL;
  this->SetNumberOfInputPorts(0);
}

//----------------------------------------------------------------------------
vtkGDCMPolyDataReader::~vtkGDCMPolyDataReader()
{
  this->SetFileName(0);
}

//----------------------------------------------------------------------------
int vtkGDCMPolyDataReader::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *outputVector)
{
  // get the info object
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  // get the ouptut
  vtkPolyData *output = vtkPolyData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));

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
  //std::cout << ms << std::endl;
  if( ms != gdcm::MediaStorage::RTStructureSetStorage )
    {
    return 0;
    }

  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();
  // (3006,0020) SQ (Sequence with explicit length #=4)      # 370, 1 StructureSetROISequence  
  // (3006,0039) SQ (Sequence with explicit length #=4)      # 24216, 1 ROIContourSequence
  gdcm::Tag troicsq(0x3006,0x0039);
  if( !ds.FindDataElement( troicsq ) )
    {
    return 0;
    }

  const gdcm::DataElement &roicsq = ds.GetDataElement( troicsq );
  //std::cout << roicsq << std::endl;
  const gdcm::SequenceOfItems *sqi = roicsq.GetSequenceOfItems();
  if( !sqi || !sqi->GetNumberOfItems() )
    {
    return 0;
    }

  const gdcm::Item & item = sqi->GetItem(1);
  //std::cout << item << std::endl;

  const gdcm::DataSet& nestedds = item.GetNestedDataSet();
  //std::cout << nestedds << std::endl;
  //(3006,0040) SQ (Sequence with explicit length #=8)      # 4326, 1 ContourSequence
  gdcm::Tag tcsq(0x3006,0x0040);
  if( !nestedds.FindDataElement( tcsq ) )
    {
    return 0;
    }
  const gdcm::DataElement& csq = nestedds.GetDataElement( tcsq );
  //std::cout << csq << std::endl;

  const gdcm::SequenceOfItems *sqi2 = csq.GetSequenceOfItems();
  if( !sqi2 || !sqi2->GetNumberOfItems() )
    {
    return 0;
    }
  unsigned int nitems = sqi2->GetNumberOfItems();
  std::cout << nitems << std::endl;
  //this->SetNumberOfOutputPorts(nitems);
  vtkPoints *newPts = vtkPoints::New();
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
    const float* pts = at.GetValues();
    vtkIdType buffer[256];
    for(unsigned int i = 0; i < (at.GetNumberOfValues() / 3) * 3; i+=3)
      {
      float x[3];
      x[0] = pts[i+0];
      x[1] = pts[i+1];
      x[2] = pts[i+2];
      vtkIdType ptId = newPts->InsertNextPoint( x );
      buffer[i / 3] = ptId;
      }
    // Each Contour Data is in fact a Cell:
    polys->InsertNextCell( at.GetNumberOfValues() / 3 , buffer);
    }
  output->SetPoints(newPts);
  newPts->Delete();
  output->SetPolys(polys);
  polys->Delete();

  return 1;
}

//----------------------------------------------------------------------------
int vtkGDCMPolyDataReader::RequestInformation(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *outputVector)
{
  // get the info object
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  outInfo->Set(vtkStreamingDemandDrivenPipeline::MAXIMUM_NUMBER_OF_PIECES(),
               -1);

  return 1;
}


//----------------------------------------------------------------------------
void vtkGDCMPolyDataReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "File Name: "
     << (this->FileName ? this->FileName : "(none)") << "\n";


}
