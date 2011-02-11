/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmReader.h"
#include "gdcmImage.h"
#include "gdcmImageWriter.h"
#include "gdcmDataElement.h"
#include "gdcmPrivateTag.h"
#include "gdcmUIDGenerator.h"

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  using namespace gdcm;
  const char *filename = argv[1];
  gdcm::Reader reader;
  reader.SetFileName( filename );
  reader.Read();

  gdcm::File &file = reader.GetFile();
  gdcm::DataSet &ds = file.GetDataSet();
  const PrivateTag tseq(0x7fe1,0x1,"GEMS_Ultrasound_MovieGroup_001");

  if( !ds.FindDataElement( tseq ) ) return 1;
  const DataElement& seq = ds.GetDataElement( tseq );

  SmartPointer<SequenceOfItems> sqi = seq.GetValueAsSQ();
  assert( sqi->GetNumberOfItems() == 1 );
  Item &item = sqi->GetItem(1);
  DataSet &subds = item.GetNestedDataSet();

  const PrivateTag tseq1(0x7fe1,0x10,"GEMS_Ultrasound_MovieGroup_001");

  if( !subds.FindDataElement( tseq1 ) ) return 1;
  const DataElement& seq1 = subds.GetDataElement( tseq1 );

  SmartPointer<SequenceOfItems> sqi2 = seq1.GetValueAsSQ();
  int n = sqi2->GetNumberOfItems();
//std::cout << n << std::endl;
int i = 1;
//  for( int i = 1; i <= n; ++i )
    Item &item2 = sqi2->GetItem(i);
    DataSet &subds2 = item2.GetNestedDataSet();

    const PrivateTag tseq2(0x7fe1,0x20,"GEMS_Ultrasound_MovieGroup_001");

    if( !subds2.FindDataElement( tseq2 ) ) return 1;
    const DataElement& seq2 = subds2.GetDataElement( tseq2 );

//    std::cout << seq2 << std::endl;

  SmartPointer<SequenceOfItems> sqi3 = seq2.GetValueAsSQ();
  int ni3= sqi3->GetNumberOfItems();
  assert( sqi3->GetNumberOfItems() >= 1 );
  Item &item3 = sqi3->GetItem(1);
  DataSet &subds3 = item3.GetNestedDataSet();

  const PrivateTag tseq3(0x7fe1,0x36,"GEMS_Ultrasound_MovieGroup_001");

  if( !subds3.FindDataElement( tseq3 ) ) return 1;
  const DataElement& seq3 = subds3.GetDataElement( tseq3 );

    std::cout << seq3 << std::endl;

  SmartPointer<SequenceOfItems> sqi4 = seq3.GetValueAsSQ();
  int ni4= sqi4->GetNumberOfItems();
  assert( sqi4->GetNumberOfItems() >= 1 );
  Item &item4 = sqi4->GetItem(1);
  DataSet &subds4 = item4.GetNestedDataSet();

  const PrivateTag tseq4(0x7fe1,0x43,"GEMS_Ultrasound_MovieGroup_001");
  const PrivateTag tseq5(0x7fe1,0x60,"GEMS_Ultrasound_MovieGroup_001");

  if( !subds4.FindDataElement( tseq4 ) ) return 1;
  const DataElement& seq4 = subds4.GetDataElement( tseq4 );
  if( !subds4.FindDataElement( tseq5 ) ) return 1;
  const DataElement& seq5 = subds4.GetDataElement( tseq5 );

    std::cout << seq4 << std::endl;
    std::cout << seq5 << std::endl;

  const ByteValue *bv4 = seq4.GetByteValue();
{
  std::ofstream out( "/tmp/mo4" );
  out.write( bv4->GetPointer(), bv4->GetLength());
  out.close();
}

  const ByteValue *bv5 = seq5.GetByteValue();
{
  std::ofstream out( "/tmp/mo5" );
  out.write( bv5->GetPointer(), bv5->GetLength());
  out.close();
}

  gdcm::SmartPointer<gdcm::Image> im = new gdcm::Image;
  im->SetNumberOfDimensions( 3 );
  // (7fe1,1086) SL 440\129\0\2                              #  16, 4 Unknown Tag & Data

  im->SetDimension(0, 440 );
  im->SetDimension(0, 923 );
  im->SetDimension(1, 129 );
  im->SetDimension(1, 189 );
  im->SetDimension(2, 800 );
  im->SetDimension(2, 1 );
  im->SetPhotometricInterpretation( gdcm::PhotometricInterpretation::MONOCHROME2 );

//  gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
//  pixeldata.SetByteValue( bv5->GetPointer(), l );
//  im->SetDataElement( pixeldata );
  im->SetDataElement( seq5 );

  gdcm::ImageWriter w;
  w.SetImage( *im );
//  w.SetFile( fd.GetFile() );
  DataSet &dataset = w.GetFile().GetDataSet();

  gdcm::UIDGenerator uid;
  gdcm::DataElement de( Tag(0x8,0x18) ); // SOP Instance UID
  de.SetVR( VR::UI );
  const char *u = uid.Generate();
  de.SetByteValue( u, strlen(u) );
  //ds.Insert( de );
  dataset.Replace( de );

  de.SetTag( Tag(0x8,0x16) ); // SOP Class UID
  de.SetVR( VR::UI );
  gdcm::MediaStorage ms(
    gdcm::MediaStorage::MultiframeGrayscaleByteSecondaryCaptureImageStorage );
  de.SetByteValue( ms.GetString(), strlen(ms.GetString()));
  dataset.Replace( de ); // replace !

  w.SetFileName( "outvid.dcm" );
  if( !w.Write() )
    {
    return 1;
    }

  return 0;
}
