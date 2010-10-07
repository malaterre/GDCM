/*
this file defines the messages for the cfind action
5 oct 2010 mmr
*/

#include "gdcmCFindMessages.h"
#include "gdcmUIDs.h"
#include "gdcmAttribute.h"
#include "gdcmImplicitDataElement.h"

namespace gdcm{
namespace network{

std::vector<PresentationDataValue> CFindRQ::ConstructPDV(DataSet* inDataSet){
  std::vector<PresentationDataValue> thePDVs;
{
  PresentationDataValue thePDV;
  thePDV.SetPresentationContextID(2);

  thePDV.SetCommand(true);
  thePDV.SetLastFragment(true);
  //ignore incoming data set, make your own

  DataSet ds;
  DataElement de( Tag(0x0,0x2) );
  de.SetVR( VR::UI );
  const char *uid = gdcm::UIDs::GetUIDString( 
    gdcm::UIDs::PatientRootQueryRetrieveInformationModelFIND );

  std::string suid = uid;
  if( suid.size() % 2 )
    suid.push_back( ' ' ); // no \0 !
  de.SetByteValue( suid.c_str(), suid.size()  );
  ds.Insert( de );
  {
  gdcm::Attribute<0x0,0x100> at = { 32 };
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

  thePDV.SetDataSet(ds);
  thePDV.ComputeSize();
  thePDVs.push_back(thePDV);
}

{
    PresentationDataValue thePDV;
    thePDV.SetPresentationContextID(2); // FIXME
    //thePDV.SetBlob( sub );
    thePDV.SetDataSet(*inDataSet);
      thePDV.SetMessageHeader( 2 );
    thePDVs.push_back(thePDV);

}
  return thePDVs;

}

std::vector<PresentationDataValue>  CFindRSP::ConstructPDV(DataSet* inDataSet){
  std::vector<PresentationDataValue> thePDV;
  return thePDV;
}
std::vector<PresentationDataValue>  CFindCancelRq::ConstructPDV(DataSet* inDataSet){
  std::vector<PresentationDataValue> thePDV;
  return thePDV;
}


}//namespace network
}//namespace gdcm
