/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkDoubleArray.h"
#include <vtkXMLImageDataWriter.h>

#include "gdcmReader.h"
#include "gdcmAttribute.h"

int main(int argc, char *argv[])
{
  if( argc < 3 )
    {
    std::cerr << argv[0] << " filename.dcm outfile.vti\n";
    return 1;
    }
  const char * filename = argv[1];
  const char * outfilename = argv[2];

  gdcm::Reader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    return 1;
    }

  gdcm::MediaStorage ms;
  ms.SetFromFile( reader.GetFile() );
  if( ms != gdcm::MediaStorage::RTIonPlanStorage )
    {
    return 1;
    }

/*
(300a,00b0) SQ                                                    # u/l,1 Beam Sequence
  (fffe,e000) na (Item with undefined length)
    (300a,00b2) SH (no value)                                     # 0,1 Treatment Machine Name
    (300a,00c0) IS [1 ]                                           # 2,1 Beam Number
    (300a,00c2) LO [1 ]                                           # 2,1 Beam Name
    (300a,00c4) CS [STATIC]                                       # 6,1 Beam Type
    (300a,00c6) CS [PROTON]                                       # 6,1 Radiation Type
    (300a,00ce) CS [TREATMENT ]                                   # 10,1 Treatment Delivery Type
    (300a,00e0) IS [1 ]                                           # 2,1 Number of Compensators
    (300a,00e3) SQ                                                # u/l,1 Compensator Sequence
      (fffe,e000) na (Item with undefined length)
        (300a,00e1) SH [lucite]                                   # 6,1 Material ID
        (300a,00e4) IS [1 ]                                       # 2,1 Compensator Number
        (300a,00e5) SH [75hdhe5 ]                                 # 8,1 Compensator ID
        (300a,00e7) IS [35]                                       # 2,1 Compensator Rows
        (300a,00e8) IS [37]                                       # 2,1 Compensator Columns
        (300a,00e9) DS [3.679991\4.249288 ]                       # 18,2 Compensator Pixel Spacing
        (300a,00ea) DS [-76.00\62.50]                             # 12,2 Compensator Position
        (300a,00ec) DS [52.13\52.13\52.13\53.18\54.04\54.04\47.11\40.06\40.06\38.79\34.87\33.28\33.28\33.28\33.28\35.43\35.43\34.54\34.54\34.71\36.10\38.62\44.88\44.88\44.88\45.00\45.00\45.00\45.66\45.66\46.42\39.77\39.77\39.77\39.77\39.77\43.52\52.13\52.13\52.13\53.18\53.52\54.0]         # 7618,1-n Compensator Thickness Data
        (300a,02e0) CS [ABSENT]                                   # 6,1 Compensator Divergence
        (300a,02e1) CS [SOURCE_SIDE ]                             # 12,1 Compensator Mounting Position
      (fffe,e00d)
      (fffe,e000) na (Item with undefined length)
      (fffe,e00d)
    (fffe,e0dd)
*/
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();
  gdcm::Tag tbeamsq(0x300a,0x00b0);
  if( !ds.FindDataElement( tbeamsq ) )
    {
    return 1;
    }
  const gdcm::DataElement &beamsq = ds.GetDataElement( tbeamsq );
  //std::cout << beamsq << std::endl;
  gdcm::SmartPointer<gdcm::SequenceOfItems> sqi = beamsq.GetValueAsSQ();
  if( !sqi || !sqi->GetNumberOfItems() )
    {
    return 1;
    }

  //const gdcm::Item & item = sqi->GetItem(1); // Item start at #1
  const gdcm::Item & item = sqi->GetItem(2); // Item start at #1
  const gdcm::DataSet& nestedds = item.GetNestedDataSet();
  //std::cout << nestedds << std::endl;
  gdcm::Tag tcompensatorsq(0x300a,0x00e3);
  if( !nestedds.FindDataElement( tcompensatorsq ) )
    {
    return 1;
    }
  const gdcm::DataElement &compensatorsq = nestedds.GetDataElement( tcompensatorsq );
  //std::cout << compensatorsq << std::endl;
  gdcm::SmartPointer<gdcm::SequenceOfItems> ssqi = compensatorsq.GetValueAsSQ();
  const gdcm::Item & item2 = ssqi->GetItem(1); // Item start at #1
  const gdcm::DataSet& nestedds2 = item2.GetNestedDataSet();
  //std::cout << nestedds2 << std::endl;
  gdcm::Tag tcompensatorthicknessdata(0x300a,0x00ec);
  if( !nestedds2.FindDataElement( tcompensatorthicknessdata ) )
    {
    return 1;
    }
  const gdcm::DataElement &compensatorthicknessdata = nestedds2.GetDataElement( tcompensatorthicknessdata );
  //  std::cout << compensatorthicknessdata << std::endl;
  gdcm::Attribute<0x300a,0x00ec> at;
  at.SetFromDataElement( compensatorthicknessdata );
  const double* pts = at.GetValues();
  //        (300a,00e7) IS [35]                                       # 2,1 Compensator Rows
  gdcm::Attribute<0x300a,0x00e7> at1;
  const gdcm::DataElement &compensatorrows = nestedds2.GetDataElement( at1.GetTag() );
  at1.SetFromDataElement( compensatorrows );
  std::cout << at1.GetValue() << std::endl;
  //        (300a,00e8) IS [37]                                       # 2,1 Compensator Columns
  gdcm::Attribute<0x300a,0x00e8> at2;
  const gdcm::DataElement &compensatorcols = nestedds2.GetDataElement( at2.GetTag() );
  at2.SetFromDataElement( compensatorcols );
  std::cout << at2.GetValue() << std::endl;

  vtkDoubleArray *d = vtkDoubleArray::New();
  d->SetArray( (double*)pts , at1.GetValue() * at2.GetValue() , 0 );

  vtkImageData *img = vtkImageData::New();
  img->Initialize();
  img->SetDimensions( at2.GetValue(), at1.GetValue(), 1 );
  //imgb->SetExtent(1, xdim, 1, ydim, 1, zdim);
  img->SetScalarTypeToDouble();
  img->SetNumberOfScalarComponents(1);
  img->GetPointData()->SetScalars(d);

  vtkXMLImageDataWriter *writeb= vtkXMLImageDataWriter::New();
  writeb->SetInput( img );
  writeb->SetFileName( outfilename );
  writeb->Write( );

  return 0;
}

