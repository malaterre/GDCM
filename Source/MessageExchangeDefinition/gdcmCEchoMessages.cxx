/*
this file defines the messages for the cecho action
5 oct 2010 mmr
*/

#include "gdcmCEchoMessages.h"
#include "gdcmUIDs.h"
#include "gdcmAttribute.h"
#include "gdcmImplicitDataElement.h"

namespace gdcm{
namespace network{

PresentationDataValue CEchoRQ::ConstructPDV(DataSet* inDataSet){
  PresentationDataValue thePDV;
  thePDV.SetPresentationContextID(1);

  thePDV.SetCommand(true);
  thePDV.SetLastFragment(true);
  //ignore incoming data set, make your own

  DataSet ds;
  DataElement de( Tag(0x0,0x2) );
  de.SetVR( VR::UI );
  const char *uid = gdcm::UIDs::GetUIDString( gdcm::UIDs::VerificationSOPClass );
  std::string suid = uid;
  if( suid.size() % 2 )
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

  thePDV.SetDataSet(ds);
  thePDV.ComputeSize();
  return thePDV;

}

PresentationDataValue  CEchoRSP::ConstructPDV(DataSet* inDataSet){
  PresentationDataValue thePDV;
  return thePDV;
}

}//namespace network
}//namespace gdcm
