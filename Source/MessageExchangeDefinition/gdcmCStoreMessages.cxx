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

PresentationDataValue CStoreRQ::ConstructPDV(DataSet* inDataSet){
  assert( inDataSet );
  PresentationDataValue thePDV;
  thePDV.SetPresentationContextID(1);

  thePDV.SetCommand(true);
  // FIXME how should I send multiple PDV ...
  //thePDV.SetLastFragment(true);
  //ignore incoming data set, make your own

  DataSet ds;
  {
  DataElement de( Tag(0x0,0x2) );
  de.SetVR( VR::UI );
  const DataElement& msclass = inDataSet->GetDataElement( Tag(0x0008, 0x0016) );
  const char *uidsci = gdcm::UIDs::GetUIDString( gdcm::UIDs::SecondaryCaptureImageStorage );
  const char *uid = msclass.GetByteValue()->GetPointer();
  std::string suid = uid;
  assert( suid == uidsci );
  if( suid.size() % 2 )
    suid.push_back( ' ' ); // no \0 !
  de.SetByteValue( suid.c_str(), suid.size()  );
  ds.Insert( de );
  }

  {
  //const char sopinstane[] = "1.2.826.0.1.3680043.2.1125.7445042278205614490601873384971697089";
  const DataElement& msinst = inDataSet->GetDataElement( Tag(0x0008, 0x0018) );
  const char *uid = msinst.GetByteValue()->GetPointer();
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
  return thePDV;

}

PresentationDataValue  CStoreRSP::ConstructPDV(DataSet* inDataSet){
  PresentationDataValue thePDV;
  return thePDV;
}

}//namespace network
}//namespace gdcm
