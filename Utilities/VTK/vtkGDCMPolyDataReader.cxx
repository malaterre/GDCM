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
#include "vtkCellData.h"

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

// This is done in RequestInformation
//  gdcm::MediaStorage ms;
//  ms.SetFromFile( reader.GetFile() );
//  //std::cout << ms << std::endl;
//  if( ms != gdcm::MediaStorage::RTStructureSetStorage )
//    {
//    return 0;
//    }

  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();
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

  const gdcm::DataElement &roicsq = ds.GetDataElement( troicsq );
  //std::cout << roicsq << std::endl;
  const gdcm::SequenceOfItems *sqi = roicsq.GetSequenceOfItems();
  if( !sqi || !sqi->GetNumberOfItems() )
    {
    return 0;
    }
  const gdcm::DataElement &ssroisq = ds.GetDataElement( tssroisq );
  const gdcm::SequenceOfItems *ssqi = ssroisq.GetSequenceOfItems();
  if( !ssqi || !ssqi->GetNumberOfItems() )
    {
    return 0;
    }

  // For each Item in the DataSet create a vtkPolyData
  for(unsigned int pd = 0; pd < sqi->GetNumberOfItems(); ++pd)
    {
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
      return 0;
      }
    const gdcm::DataElement &sde = snestedds.GetDataElement( stcsq );


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
    //std::cout << nitems << std::endl;
    //this->SetNumberOfOutputPorts(nitems);
    vtkFloatArray *scalars = vtkFloatArray::New();
    scalars->SetNumberOfComponents(3);

    vtkPoints *newPts = vtkPoints::New();
    std::string s(sde.GetByteValue()->GetPointer(), sde.GetByteValue()->GetLength());
    //std::cout << s << std::endl;
    //newPts->GetData()->SetName( s.c_str() );
    // In VTK there is no API to specify the name of a vtkPolyData, you can only specify Name
    // for the scalars (pointdata or celldata), so let's do that...
    scalars->SetName(s.c_str());
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
  //std::cout << ms << std::endl;
  if( ms != gdcm::MediaStorage::RTStructureSetStorage )
    {
    return 0;
    }

  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();
  // (3006,0020) SQ (Sequence with explicit length #=4)      # 370, 1 StructureSetROISequence  
  gdcm::Tag tssroisq(0x3006,0x0020);
  if( !ds.FindDataElement( tssroisq ) )
    {
    return 0;
    }

  const gdcm::DataElement &ssroisq = ds.GetDataElement( tssroisq );
  const gdcm::SequenceOfItems *sqi = ssroisq.GetSequenceOfItems();
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


//----------------------------------------------------------------------------
void vtkGDCMPolyDataReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "File Name: "
     << (this->FileName ? this->FileName : "(none)") << "\n";


}
