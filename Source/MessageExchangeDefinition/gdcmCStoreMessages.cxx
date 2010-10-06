/*
this file defines the messages for the cstore action
6 oct 2010 mm
*/

#include "gdcmCStoreMessages.h"
#include "gdcmUIDs.h"
#include "gdcmAttribute.h"
#include "gdcmImplicitDataElement.h"

namespace gdcm{
namespace network{

std::vector<PresentationDataValue> CStoreRQ::ConstructPDV(DataSet* inDataSet){
  std::vector<PresentationDataValue> thePDVs;
{
  assert( inDataSet );
  PresentationDataValue thePDV;
  thePDV.SetPresentationContextID(1); // FIXME

  thePDV.SetCommand(true);
  thePDV.SetLastFragment(true);
  //ignore incoming data set, make your own

  DataSet ds;
  {
  DataElement de( Tag(0x0,0x2) );
  de.SetVR( VR::UI );
  const DataElement& msclass = inDataSet->GetDataElement( Tag(0x0008, 0x0016) );
  const char *uid = msclass.GetByteValue()->GetPointer();
  assert( uid );
  std::string suid = uid;
  if( suid.size() % 2 )
    suid.push_back( ' ' ); // no \0 !
  de.SetByteValue( suid.c_str(), suid.size()  );
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

  //ItemLength = Size() - 4;
  //assert (ItemLength + 4 == Size() );

  //ds.Print( std::cout );

//  std::ofstream b( "/tmp/debug1" );
//  ds.Write<ImplicitDataElement,SwapperNoOp>( b );
//  b.close();

  thePDV.SetDataSet(ds);
  thePDV.ComputeSize();

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
    thePDV.SetPresentationContextID(1); // FIXME
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

std::vector<PresentationDataValue>  CStoreRSP::ConstructPDV(DataSet* inDataSet){
  std::vector<PresentationDataValue> thePDV;
  return thePDV;
}

}//namespace network
}//namespace gdcm
