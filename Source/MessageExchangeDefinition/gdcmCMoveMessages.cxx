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
#include "gdcmCMoveMessages.h"
#include "gdcmUIDs.h"
#include "gdcmAttribute.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmCommandDataSet.h"
#include "gdcmStudyRootQuery.h"
#include "gdcmPresentationContext.h"
#include "gdcmULConnection.h"

namespace gdcm{
namespace network{

std::vector<PresentationDataValue> CMoveRQ::ConstructPDV(
  const ULConnection &inConnection,
  BaseRootQuery* inRootQuery)
{
  std::vector<PresentationDataValue> thePDVs;
  PresentationDataValue thePDV;
  int contextID = ePatientRootQueryRetrieveInformationModelMOVE;
  const char *uid = gdcm::UIDs::GetUIDString(
    gdcm::UIDs::PatientRootQueryRetrieveInformationModelMOVE );
  std::string suid = uid;
  if (dynamic_cast<StudyRootQuery*>(inRootQuery)!=NULL){
    contextID = eStudyRootQueryRetrieveInformationModelMOVE;
    const char *uid2 = gdcm::UIDs::GetUIDString(
      gdcm::UIDs::StudyRootQueryRetrieveInformationModelMOVE );
    suid = uid2;
  }
  thePDV.SetPresentationContextID(contextID);//could it be 5, if the server does study?
  thePDV.SetCommand(true);
  thePDV.SetLastFragment(true);
  //ignore incoming data set, make your own

  CommandDataSet ds;
  DataElement de( Tag(0x0,0x2) );
  de.SetVR( VR::UI );
  if( suid.size() % 2 )
    suid.push_back( ' ' ); // no \0 !
  de.SetByteValue( suid.c_str(), (uint32_t)suid.size()  );
  ds.Insert( de );
  {
  gdcm::Attribute<0x0,0x100> at = { 33 };//0021H, as per the spec
  ds.Insert( at.GetAsDataElement() );
  }
  {
  gdcm::Attribute<0x0,0x110> at = { 1 };
  ds.Insert( at.GetAsDataElement() );
  }
  {
  // FIXME !!!!
  gdcm::Attribute<0x0,0x600> at = { "SILVERSTREAK" };
  const char *calling = inConnection.GetConnectionInfo().GetCallingAETitle();
  at.SetValue( calling );
  ds.Insert( at.GetAsDataElement() );
  }
  {
  gdcm::Attribute<0x0,0x700> at = { 0 };
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
  thePDVs.push_back(thePDV);
  {
    PresentationDataValue thePDV;
    thePDV.SetPresentationContextID(contextID);
    //thePDV.SetBlob( sub );
    thePDV.SetDataSet(inRootQuery->GetQueryDataSet());
    thePDV.SetMessageHeader( 2 );
    thePDVs.push_back(thePDV);
  }
  return thePDVs;

}

//this is a private function, should not be callable
//but if you manage to do call it, return a blank dataset.
std::vector<PresentationDataValue> CMoveRQ::ConstructPDV(DataSet* inDataSet){
  std::vector<PresentationDataValue> thePDVs;
  return thePDVs;

}

std::vector<PresentationDataValue>  CMoveRSP::ConstructPDV(DataSet* inDataSet){
  std::vector<PresentationDataValue> thePDV;
  return thePDV;
}
std::vector<PresentationDataValue>  CMoveCancelRq::ConstructPDV(DataSet* inDataSet){
  std::vector<PresentationDataValue> thePDV;
  return thePDV;
}


}//namespace network
}//namespace gdcm
