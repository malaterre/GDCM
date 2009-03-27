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
/* 
 * The following is a simple proof of concept to show we are capable of implementing
 * C.12.1.1.4 Encrypted Attribute Descriptions (PS 3.3-2008)
 * 
 * for now we only encrypt two attribute: Patient Name & Patient ID
 *
 * Usage:
 *  AnonymizeAES gdcmData/012345.002.050.dcm out.dcm
 */

#include "gdcmAES.h"
#include "gdcmReader.h"
#include "gdcmImage.h"
#include "gdcmWriter.h"
#include "gdcmAttribute.h"
#include "gdcmImageWriter.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmAnonymizer.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmSwapper.h"
#include "gdcmUIDGenerator.h"
#include "gdcmFileExplicitFilter.h"

#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
  if( argc < 3 )
    {
    std::cerr << argv[0] << " input.dcm output.dcm" << std::endl;
    return 1;
    }
  const char *filename = argv[1];
  const char *outfilename = argv[2];

  gdcm::Reader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    std::cerr << "Could not read: " << filename << std::endl;
    return 1;
    }

  // The output of gdcm::Reader is a gdcm::File
  gdcm::File &file = reader.GetFile();

  // the dataset is the the set of element we are interested in:
  gdcm::DataSet &ds = file.GetDataSet();

  // Let's do only Patient Name / Patient ID
  gdcm::Tag tag1(0x10,0x10);
  gdcm::Tag tag2(0x10,0x20);

  // Create an instance of the Encrypted Attributes DataSet
  gdcm::DataSet encryptedds;
  encryptedds.Insert( ds.GetDataElement( tag1 ) );
  encryptedds.Insert( ds.GetDataElement( tag2 ) );
  std::ostringstream os;
  encryptedds.Write<gdcm::ExplicitDataElement,gdcm::SwapperNoOp>(os);

  std::string encrypted_str = os.str();
  std::cout << "Size:" <<  encrypted_str.size() << std::endl;
  size_t encrypted_len = encrypted_str.size();

/*
Note: 1. Content encryption may require that the content (the DICOM Data Set) be padded to a
multiple of some block size. This shall be performed according to the Content-encryption
Process defined in RFC-2630.
*/
  if( encrypted_len % 16 != 0 )
    {
    encrypted_len = ((encrypted_len / 16) + 1) * 16;
    }
  unsigned char *buf = new unsigned char[ encrypted_len ];
  memset( buf, 0, encrypted_len );
  memcpy( buf, encrypted_str.c_str(), encrypted_str.size() );

  unsigned char key[32] = {};
  gdcm::AES aes;
  if( !aes.SetkeyEnc( key, 128 ) ) return 1;
  unsigned char iv[16] = {};
  aes.CryptCbc( gdcm::AES::ENCRYPT, encrypted_len, iv, buf, buf );

  // Create a Sequence
  gdcm::SmartPointer<gdcm::SequenceOfItems> sq = new gdcm::SequenceOfItems();
  sq->SetLengthToUndefined();

  //gdcm::DataElement copy = de;
  //copy.SetByteValue( (char*)buf, bv->GetLength() );

  gdcm::TransferSyntax encrypted_ts = gdcm::TransferSyntax::ExplicitVRLittleEndian;
  // <entry group="0400" element="0510" vr="UI" vm="1" name="Encrypted Content Transfer Syntax UID"/>
  gdcm::DataElement encrypted_ts_de( gdcm::Tag(0x400,0x510) );
  encrypted_ts_de.SetByteValue( encrypted_ts.GetString(), strlen(encrypted_ts.GetString()) );
  // <entry group="0400" element="0520" vr="OB" vm="1" name="Encrypted Content"/>
  gdcm::DataElement encrypted_de( gdcm::Tag(0x400,0x520) );
  encrypted_de.SetByteValue( (char*)buf, encrypted_len );
  delete[] buf;

    // Create an item
    gdcm::Item it;
    it.SetVLToUndefined();
    gdcm::DataSet &nds = it.GetNestedDataSet();
    nds.Insert(encrypted_ts_de);
    nds.Insert(encrypted_de);

    sq->AddItem(it);


  // Insert sequence into data set
  gdcm::DataElement des( gdcm::Tag(0x0400,0x0500) );
  des.SetVR(gdcm::VR::SQ);
  des.SetValue(*sq);
  des.SetVLToUndefined();
  
  ds.Insert(des);

  // We still need to create a Modified Attributes Sequence,
  // in order to list all attributes that were removed/dummyfied
{
  // Create a Sequence
  gdcm::SmartPointer<gdcm::SequenceOfItems> sq = new gdcm::SequenceOfItems();
  sq->SetLengthToUndefined();

    // Create an item
    gdcm::Item it;
    it.SetVLToUndefined();
    gdcm::DataSet &nds = it.GetNestedDataSet();
    nds.Insert( gdcm::DataElement( tag1 ) );
    nds.Insert( gdcm::DataElement( tag2 ) );

    sq->AddItem(it);

  gdcm::DataElement des( gdcm::Tag(0x0400,0x0550) );
  des.SetVR(gdcm::VR::SQ);
  des.SetValue(*sq);
  des.SetVLToUndefined();
  
  ds.Insert(des);
}


  gdcm::Anonymizer ano;
  ano.SetFile( reader.GetFile() );
  ano.Empty( tag1 ); // Patient Name is 1C
  ano.Empty( tag2 ); // Patient ID is 1C
  ano.RemoveGroupLength();
  ano.RemovePrivateTags();

  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle( "AnonymizeAES" );
    gdcm::FileMetaInformation &fmi = file.GetHeader();
    //fmi.Remove( gdcm::Tag(0x0002,0x0003) ); // will be regenerated
    fmi.Remove( gdcm::Tag(0x0002,0x0012) ); // will be regenerated
    fmi.Remove( gdcm::Tag(0x0002,0x0013) ); //  '   '    '

// Since the de-identified SOP Instance is a significantly altered version of the original Data Set, it is
// a new SOP Instance, with a SOP Instance UID that differs from the original Data Set.
{
//        ds.Remove( gdcm::Tag(0x008,0x0018) );
        gdcm::DataElement de( gdcm::Tag(0x008,0x0018) ); // Instance
  gdcm::UIDGenerator uid;
  std::string instance_uid = uid.Generate();
        de.SetByteValue( instance_uid.c_str(), instance_uid.size() );
        de.SetVR( gdcm::Attribute<0x008, 0x0018>::GetVR() );
        ds.Replace( de );

}
      gdcm::FileExplicitFilter fef;
      fef.SetFile( reader.GetFile() );
      if(!fef.Change())
        {
        std::cerr << "Failed to change: " << filename << std::endl;
        return 1;
        }

  gdcm::Writer writer;
  writer.SetFile( reader.GetFile() );
  writer.SetFileName( outfilename );
  if( !writer.Write() )
    {
    return 1;
    }

  return 0;
}

