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
/*
this file defines the messages for the cstore action
6 oct 2010 mm
*/

#include "gdcmCStoreMessages.h"
#include "gdcmUIDs.h"
#include "gdcmAttribute.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmPresentationContext.h"
#include "gdcmCommandDataSet.h"
#include <limits>

namespace gdcm{
namespace network{

std::vector<PresentationDataValue> CStoreRQ::ConstructPDV(DataSet* inDataSet){
  std::vector<PresentationDataValue> thePDVs;
{
  assert( inDataSet );
  PresentationDataValue thePDV;
  std::string UIDString;
  thePDV.SetPresentationContextID(
    PresentationContext::AssignPresentationContextID(*inDataSet, UIDString));

  thePDV.SetCommand(true);
  thePDV.SetLastFragment(true);
  //ignore incoming data set, make your own

  CommandDataSet ds;
  {
  DataElement de( Tag(0x0,0x2) );
  de.SetVR( VR::UI );
  const DataElement& msclass = inDataSet->GetDataElement( Tag(0x0008, 0x0016) );
  const char *uid = msclass.GetByteValue()->GetPointer();
  assert( uid );
  std::string suid = uid;
  if( suid.size() % 2 )
    suid.push_back( ' ' ); // no \0 !
  assert(suid.size() < std::numeric_limits<uint32_t>::max());
  de.SetByteValue( suid.c_str(), (uint32_t)suid.size()  );
  ds.Insert( de );
  }

  {
  const DataElement& msinst = inDataSet->GetDataElement( Tag(0x0008, 0x0018) );
  const char *uid = msinst.GetByteValue()->GetPointer();
  assert( uid );
  DataElement de( Tag(0x0,0x1000) );
  de.SetVR( VR::UI );
  std::string suid = uid;
  if( suid.size() % 2 )
    suid.push_back( ' ' ); // no \0 !
  assert(suid.size() < std::numeric_limits<uint32_t>::max());
  de.SetByteValue( suid.c_str(), (uint32_t)suid.size()  );
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

  //ItemLength = Size() - 4;
  //assert (ItemLength + 4 == Size() );

  //ds.Print( std::cout );

//  std::ofstream b( "/tmp/debug1" );
//  ds.Write<ImplicitDataElement,SwapperNoOp>( b );
//  b.close();

  thePDV.SetDataSet(ds);

  //!!!Mathieu, I assume you'll want to fix this
  thePDVs.push_back(thePDV);
}

  // now let's chunk'ate the dataset:
{
  //thePDV.SetCommand(true);
  std::stringstream ss;
  inDataSet->Write<ImplicitDataElement,SwapperNoOp>( ss );
  std::string ds_copy = ss.str();
  // E: 0006:0308 DUL Illegal PDU Length 16390.  Max expected 16384
  //const size_t maxpdu = 16384;
  const size_t maxpdu = 16378;
  size_t len = ds_copy.size();
  const char *begin = ds_copy.c_str();
  const char *end = begin + len;
  const char *cur = begin;
  while( cur < end )
    {
    size_t remaining = std::min( maxpdu , (size_t)(end - cur) );
    std::string sub( cur, remaining );

    PresentationDataValue thePDV;
    std::string UIDString;
    thePDV.SetPresentationContextID(
      PresentationContext::AssignPresentationContextID(*inDataSet, UIDString));

    thePDV.SetBlob( sub );
    //thePDV.SetDataSet(*inDataSet);
    if( remaining == maxpdu )
      thePDV.SetMessageHeader( 0 );
    else
      thePDV.SetMessageHeader( 2 );
    thePDVs.push_back(thePDV);

    cur += remaining;
    }
}

  return thePDVs;

}
///should be passed the received dataset, ie, the cstorerq, so that
///the cstorersp contains the appropriate SOP instance UIDs.
std::vector<PresentationDataValue>  CStoreRSP::ConstructPDV(DataSet* inDataSet){
  std::vector<PresentationDataValue> thePDVs;
  CommandDataSet ds;

  const gdcm::DataElement &de1 = inDataSet->GetDataElement( gdcm::Tag( 0x0000,0x0002 ) );
  const gdcm::DataElement &de2 = inDataSet->GetDataElement( gdcm::Tag( 0x0000,0x1000 ) );
  //pass back the instance UIDs in the response
  ds.Insert(de1);
  ds.Insert(de2);

  //code is from the presentationdatavalue::myinit2
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

  PresentationDataValue pdv;

  // FIXME
  // how do we retrieve the actual PresID from the AAssociate?
  pdv.SetPresentationContextID( 67 );
  // FIXME

  pdv.SetDataSet(ds);

  pdv.SetMessageHeader(3);
  thePDVs.push_back(pdv);

  return thePDVs;
}

}//namespace network
}//namespace gdcm
