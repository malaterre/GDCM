/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "gdcmPresentationDataValue.h"
#include "gdcmSwapper.h"
#include "gdcmFile.h"
#include "gdcmAttribute.h"
#include "gdcmCommandDataSet.h"
#include "gdcmPrinter.h"
#include <limits>

namespace gdcm
{
namespace network
{

PresentationDataValue::PresentationDataValue()
{
  MessageHeader = 0;
  PresentationContextID = 0; //MUST BE SET BY THE CALLER!

  // postcondition
  assert(Size() < std::numeric_limits<uint32_t>::max());
  ItemLength = (uint32_t)Size() - 4;
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
  MessageHeader = mh;
  if ( MessageHeader > 3 )
    {
    gdcmDebugMacro( "Bizarre MessageHeader: " << MessageHeader );
    }

  assert( ItemLength > 2 );
  VL vl = ItemLength - 2;
  Blob.resize( vl ); // reserve ??
  assert( vl );
  //std::cerr << "Reading Blob: " << vl << std::endl;
  is.read( &Blob[0], vl );

  assert(Blob.size() < std::numeric_limits<uint32_t>::max());
  VL debug = (uint32_t)Blob.size();
  assert( debug == vl );

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

  VL vl = ItemLength - 2;
  Blob.resize( vl ); // reserve ??
  is.read( &Blob[0], ItemLength - 2 );
  os.write( &Blob[0], ItemLength - 2 );

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
  os.write( (char*)&t, 1 );

  os.write( Blob.c_str(), Blob.size() );
  assert(Blob.size() < std::numeric_limits<uint32_t>::max());
  VL debug = (uint32_t)Blob.size();

  assert( debug == ItemLength - 2 );

  assert (ItemLength + 4 == Size() );

  return os;
}

size_t PresentationDataValue::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemLength);
  ret += sizeof(PresentationContextID);
  ret += sizeof(MessageHeader); // MESSAGE CONTROL HEADER ENCODING
  ret += Blob.size();

  return ret;
}

void PresentationDataValue::SetBlob(const std::string & partialblob)
{
  Blob = partialblob;
  assert(Size() < std::numeric_limits<uint32_t>::max());
  ItemLength = (uint32_t)Size() - 4;
}

void PresentationDataValue::SetDataSet(const DataSet & ds)
{
  std::stringstream ss;
  //!!FIXME-- have to make sure that the transfer syntax is known and accounted for!
  ds.Write<ImplicitDataElement,SwapperNoOp>( ss );
  Blob = ss.str();
  assert(Size() < std::numeric_limits<uint32_t>::max());
  ItemLength = (uint32_t)Size() - 4;
  assert (ItemLength + 4 == Size() );
}

const std::string &PresentationDataValue::GetBlob() const{
  return Blob;
}

//should only be one data set per chunk of pdvs.  So, only return one; the
//loop that gets the results from the scp will be clever and only enter this function
//when the pdu has its 'last bit' set to true (ie, when all the pdvs can be sent in at once,
//but the are all part of the same data set)
DataSet PresentationDataValue::ConcatenatePDVBlobs(const std::vector<PresentationDataValue>& inPDVs){

  //size_t s = inPDVs.size();

  std::string theEntireBuffer;//could do it as streams.  but apparently, std isn't letting me
  std::vector<PresentationDataValue>::const_iterator itor;
  for (itor = inPDVs.begin(); itor < inPDVs.end(); itor++){
    std::string theBlobString = itor->GetBlob();
    theEntireBuffer.insert(theEntireBuffer.end(), theBlobString.begin(), theBlobString.end());
  }

  DataSet outDataSet;

  std::stringstream ss;
  ss.str( theEntireBuffer );

#if 0
  std::ofstream d( "/tmp/debug" );
  d.write( theEntireBuffer.c_str(), theEntireBuffer.size() );
  d.close();
  std::ifstream i( "/tmp/debug" );
  outDataSet.Read<ImplicitDataElement,SwapperNoOp>( i );
#endif

  outDataSet.Read<ImplicitDataElement,SwapperNoOp>( ss );


  return outDataSet;
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
*/

void PresentationDataValue::MyInit2(const char *uid1, const char *uid2)
{
  CommandDataSet ds;
  {
  DataElement de( Tag(0x0,0x2) );
  de.SetVR( VR::UI );
  const char *uid = uid1;
  std::string suid = uid;
  if( suid.size() % 2 )
    suid.push_back( ' ' ); // no \0 !
  assert(suid.size() < std::numeric_limits<uint32_t>::max());
  de.SetByteValue( suid.c_str(), (uint32_t)suid.size()  );
  ds.Insert( de );
  }

  {
  DataElement de( Tag(0x0,0x1000) );
  de.SetVR( VR::UI );
  std::string suid = uid2;
  if( suid.size() % 2 )
    suid.push_back( ' ' ); // no \0 !
  assert(suid.size() < std::numeric_limits<uint32_t>::max());
  de.SetByteValue( suid.c_str(), (uint32_t)suid.size()  );
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

  assert(Size() < std::numeric_limits<uint32_t>::max());
  ItemLength = (uint32_t)Size() - 4;
  assert (ItemLength + 4 == Size() );

  //ds.Print( std::cout );
  SetDataSet(ds);

  MessageHeader = 3;
}

/*
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
  os << "MessageHeader: " << (int)MessageHeader << std::endl;
  std::vector<PresentationDataValue> thePDVs;
  thePDVs.push_back(*this);
  DataSet ds = ConcatenatePDVBlobs(thePDVs);
  gdcm::Printer thePrinter;
  thePrinter.PrintDataSet(ds, os);
  //os << "Data: " << ds <<std::endl;

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
