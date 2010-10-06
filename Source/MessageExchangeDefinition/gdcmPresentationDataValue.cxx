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
#include "gdcmPresentationDataValue.h"
#include "gdcmSwapper.h"
//#include "gdcmDataSet.h" //already in header
//#include "gdcmImplicitDataElement.h"
//#include "gdcmUIDs.h"
//#include "gdcmAttribute.h"
#include "gdcmFile.h"

namespace gdcm
{
namespace network
{

PresentationDataValue::PresentationDataValue()
{
  MessageHeader = 0;
  PresentationContextID = 0; //MUST BE SET BY THE CALLER!
/*  
//this code will create a cecho-rq message, rather than just a pure
//pdv.  PDVs need to be made to accomodate the information contained within them,
//and so should be made directly by the calling composite message.
//note that the message may be split into many different PDVs,
//in which case the PDV will still have to be made when the split occurs.
PresentationContextID = 1;

  DataSet &ds = DS;
  DataElement de( Tag(0x0,0x2) );
  de.SetVR( VR::UI );
  const char *uid = gdcm::UIDs::GetUIDString( gdcm::UIDs::VerificationSOPClass );
  std::string suid = uid;
  suid.push_back( ' ' ); // no \0 !
  de.SetByteValue( suid.c_str(), suid.size()  );
  ds.Insert( de );
    {
    gdcm::Attribute<0x0,0x100> at = { 48 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x110> at = { 1 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x800> at = { 257 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x0> at = { 0 };
    unsigned int glen = ds.GetLength<ImplicitDataElement>();
    assert( (glen % 2) == 0 );
    at.SetValue( glen );
    ds.Insert( at.GetAsDataElement() );
    }

  MessageHeader = 3;
  ItemLength = Size() - 4;
  assert (ItemLength + 4 == Size() );

  */

  // postcondition
  ItemLength = Size() - 4;
  assert (ItemLength + 4 == Size() );
}

std::istream &PresentationDataValue::Read(std::istream &is)
{
  uint32_t itemlength = ItemLength;
  is.read( (char*)&itemlength, sizeof(ItemLength) );
  SwapperDoOp::SwapArray(&itemlength,1);
  ItemLength = itemlength;
  is.read( (char*)&PresentationContextID, sizeof(PresentationContextID) );
  
  uint8_t mh;
  is.read( (char*)&mh, 1 );
  //assert( mh == 0 ); // bitwise stuff...
  MessageHeader = mh;

  DS.Clear();
  //not sure the logic in this next one...
  if( GetIsLastFragment() && GetIsCommand() )
    {
    DataSet &ds = DS;
    VL vl = ItemLength - 2;
    ds.ReadWithLength<ImplicitDataElement,SwapperNoOp>( is, vl );

    //ds.Print( std::cout );

    VL debug = DS.GetLength<ImplicitDataElement>();
    assert( debug == vl );
    }
  else if (GetIsLastFragment() && !GetIsCommand()  )
    {
    char *buf = new char[ ItemLength - 2 ];
    is.read( buf, ItemLength - 2 );

    std::ofstream bug( "/tmp/bug1" );
    bug.write( buf, ItemLength - 2 );
    bug.close();

    delete buf;

    }
  else if ( !GetIsLastFragment() && !GetIsCommand()  )
    {
    //assert( 0 );
    char *buf = new char[ ItemLength - 2 ];
    is.read( buf, ItemLength - 2 );

    std::ofstream bug( "/tmp/msg0-1" );
    bug.write( buf, ItemLength - 2 );
    bug.close();

    delete buf;
    }
  else
    {
    assert( 0 );
    }

  assert (ItemLength + 4 == Size() );  
  return is;

}

std::istream &PresentationDataValue::ReadInto(std::istream &is, std::ostream &os)
{
  uint32_t itemlength = ItemLength;
  is.read( (char*)&itemlength, sizeof(ItemLength) );
  SwapperDoOp::SwapArray(&itemlength,1);
  ItemLength = itemlength;
  is.read( (char*)&PresentationContextID, sizeof(PresentationContextID) );
  
  uint8_t mh;
  is.read( (char*)&mh, 1 );
  //assert( mh == 0 ); // bitwise stuff...
  MessageHeader = mh;

  DS.Clear();
//  if( MessageHeader ==  3 )
//    {
//    DataSet &ds = DS;
//    VL vl = ItemLength - 2;
//    ds.ReadWithLength<ImplicitDataElement,SwapperNoOp>( is, vl );
//
//    //ds.Print( std::cout );
//
//    VL debug = DS.GetLength<ImplicitDataElement>();
//    assert( debug == vl );
//    }
//  else if ( MessageHeader == 2 )
//    {
//    char *buf = new char[ ItemLength - 2 ];
//    is.read( buf, ItemLength - 2 );
//
//    std::ofstream bug( "/tmp/bug1" );
//    bug.write( buf, ItemLength - 2 );
//    bug.close();
//
//    delete buf;
//    }
//  else if ( MessageHeader == 0 )
    {
    char *buf = new char[ ItemLength - 2 ];
    is.read( buf, ItemLength - 2 );
    os.write( buf, ItemLength - 2 );

    delete buf;
    }
//  else
//    {
//    assert( 0 );
//    }

  assert (ItemLength + 4 == Size() );  
  return is;

}

const std::ostream &PresentationDataValue::Write(std::ostream &os) const
{
  uint32_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );
  os.write( (char*)&PresentationContextID, sizeof(PresentationContextID) );

  uint8_t t = MessageHeader;
  //t = 3; // E.2 MESSAGE CONTROL HEADER ENCODING
  os.write( (char*)&t, 1 );

  //std::ofstream b("/tmp/debug");
  //DS.Write<ImplicitDataElement,SwapperNoOp>( b );
  //b.close();

  // FIXME we cannot decide at this point to write in implicit...
  DS.Write<ImplicitDataElement,SwapperNoOp>( os );
  VL debug = DS.GetLength<ImplicitDataElement>();

  assert( debug == ItemLength - 2 );

//  std::cout << "BEFORE" << std::endl;
//  DS.Print( std::cout );
//  std::cout << "AFTER" << std::endl;

  assert (ItemLength + 4 == Size() );
  
  return os;

}

size_t PresentationDataValue::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemLength);
  ret += sizeof(PresentationContextID);
  ret += sizeof(MessageHeader); // MESSAGE CONTROL HEADER ENCODING

//  if( GetIsLastFragment())//not sure the logic here...
    {
    VL vl = DS.GetLength<ImplicitDataElement>();
    ret += vl;
    }
//  else
//    {
//    ret += ItemLength - 2;
//    }

  return ret;
}

void PresentationDataValue::ComputeSize() {
  assert( ItemLength == Size() - 4);
  ItemLength = Size() - 4;
}

void PresentationDataValue::SetDataSet(const DataSet & ds)
{
  DS.Clear();
  DS = ds;
  ItemLength = Size() - 4;
  //MessageHeader = 0;
  assert (ItemLength + 4 == Size() );
}
/*
void PresentationDataValue::MyInit(File const &file)
{
  const FileMetaInformation &fmi = file.GetHeader();
  
//D: # Dicom-Data-Set
//D: # Used TransferSyntax: Little Endian Implicit
//D: (0000,0002) UI =SecondaryCaptureImageStorage            #  26, 1 AffectedSOPClassUID
//D: (0000,0100) US 1                                        #   2, 1 CommandField
//D: (0000,0110) US 1                                        #   2, 1 MessageID
//D: (0000,0700) US 2                                        #   2, 1 Priority
//D: (0000,0800) US 1                                        #   2, 1 DataSetType
//D: (0000,1000) UI [1.2.826.0.1.3680043.2.1125.4986931123241056575784008796031983649] #  64, 1 AffectedSOPInstanceUID
//D: 

  DS.Clear();
  DataSet &ds = DS;
  {
  DataElement de( Tag(0x0,0x2) );
  de.SetVR( VR::UI );
  const char *uid = gdcm::UIDs::GetUIDString( gdcm::UIDs::SecondaryCaptureImageStorage );
  std::string suid = uid;
  if( suid.size() % 2 )
    suid.push_back( ' ' ); // no \0 !
  de.SetByteValue( suid.c_str(), suid.size()  );
  ds.Insert( de );
  }

  {
  const char a[] = "1.2.826.0.1.3680043.2.1125.7445042278205614490601873384971697089";
  DataElement de( Tag(0x0,0x1000) );
  de.SetVR( VR::UI );
  std::string suid = a;
  if( suid.size() % 2 )
    suid.push_back( ' ' ); // no \0 !
  de.SetByteValue( suid.c_str(), suid.size()  );
  ds.Insert( de );
  }

    {
    gdcm::Attribute<0x0,0x100> at = { 1 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x110> at = { 1 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x700> at = { 2 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x800> at = { 1 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x0> at = { 0 };
    unsigned int glen = ds.GetLength<ImplicitDataElement>();
    assert( (glen % 2) == 0 );
    at.SetValue( glen );
    ds.Insert( at.GetAsDataElement() );
    }

  ItemLength = Size() - 4;
  assert (ItemLength + 4 == Size() );

  ds.Print( std::cout );

  std::ofstream b( "/tmp/debug1" );
  ds.Write<ImplicitDataElement,SwapperNoOp>( b );
  b.close();
}

void PresentationDataValue::MyInit2(File const &file)
{
  DS.Clear();
  DataSet &ds = DS;
  {
  DataElement de( Tag(0x0,0x2) );
  de.SetVR( VR::UI );
  const char *uid = gdcm::UIDs::GetUIDString( gdcm::UIDs::SecondaryCaptureImageStorage );
  std::string suid = uid;
  if( suid.size() % 2 )
    suid.push_back( ' ' ); // no \0 !
  de.SetByteValue( suid.c_str(), suid.size()  );
  ds.Insert( de );
  }

  {
  const char a[] = "1.2.826.0.1.3680043.2.1125.7445042278205614490601873384971697089";
  DataElement de( Tag(0x0,0x1000) );
  de.SetVR( VR::UI );
  std::string suid = a;
  if( suid.size() % 2 )
    suid.push_back( ' ' ); // no \0 !
  de.SetByteValue( suid.c_str(), suid.size()  );
  ds.Insert( de );
  }

    {
    gdcm::Attribute<0x0,0x100> at = { 32769 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x120> at = { 1 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x800> at = { 257 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x900> at = { 0 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x0> at = { 0 };
    unsigned int glen = ds.GetLength<ImplicitDataElement>();
    assert( (glen % 2) == 0 );
    at.SetValue( glen );
    ds.Insert( at.GetAsDataElement() );
    }

  ItemLength = Size() - 4;
  assert (ItemLength + 4 == Size() );

  ds.Print( std::cout );

  std::ofstream b( "/tmp/debug1" );
  ds.Write<ImplicitDataElement,SwapperNoOp>( b );
  b.close();
}

void PresentationDataValue::MyInit3()
{
  DS.Clear();
  DataSet &ds = DS;
  DataElement de( Tag(0x0,0x2) );
  de.SetVR( VR::UI );
  const char *uid = gdcm::UIDs::GetUIDString( gdcm::UIDs::VerificationSOPClass );
  std::string suid = uid;
  suid.push_back( ' ' ); // no \0 !
  de.SetByteValue( suid.c_str(), suid.size()  );
  ds.Insert( de );
    {
    gdcm::Attribute<0x0,0x100> at = { 32816 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x120> at = { 1 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x800> at = { 257 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x900> at = { 0 };
    ds.Insert( at.GetAsDataElement() );
    }
    {
    gdcm::Attribute<0x0,0x0> at = { 0 };
    unsigned int glen = ds.GetLength<ImplicitDataElement>();
    assert( (glen % 2) == 0 );
    at.SetValue( glen );
    ds.Insert( at.GetAsDataElement() );
    }

  MessageHeader = 3;
  ItemLength = Size() - 4;
  assert (ItemLength + 4 == Size() );
}
*/
void PresentationDataValue::Print(std::ostream &os) const
{
  os << "ItemLength: " << ItemLength << std::endl;
  os << "PresentationContextID: " << (int)PresentationContextID << std::endl;
//  os << "DataSet:" << std::endl;
//  DS.Print( os );
  os << "MessageHeader: " << (int)MessageHeader << std::endl;
}

void PresentationDataValue::SetCommand(const bool& inCommand){
  if (inCommand){
    MessageHeader |= 1;
  } else {
    MessageHeader &= ~1;
  }
}
void PresentationDataValue::SetLastFragment(const bool& inLast){

  if (inLast){
    MessageHeader |= 2;
  } else {
    MessageHeader &= ~2;//set the second field to zero
  }
}

bool PresentationDataValue::GetIsCommand() const{
  return ((MessageHeader & 1) == 1);
}
bool PresentationDataValue::GetIsLastFragment() const{
  return ((MessageHeader & 2) == 2);
}

} // end namespace network
} // end namespace gdcm
