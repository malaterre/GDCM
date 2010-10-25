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
#include "gdcmULConnection.h"
#include <socket++/echo.h>

using namespace gdcm::network;


ULConnection::ULConnection(const ULConnectionInfo& inConnectInfo){
  mCurrentState = eSta1Idle;
  mSocket = NULL;
  mInfo = inConnectInfo;
}


ULConnection::~ULConnection(){
  if (mSocket != NULL){
    delete mSocket;
    mSocket = NULL;
  }
}



EStateID ULConnection::GetState() const{
  return mCurrentState;
}
void ULConnection::SetState(const EStateID& inState){
  mCurrentState = inState;
}

//echo* ULConnection::GetProtocol(){
std::iostream* ULConnection::GetProtocol(){
  return mSocket;
}

void ULConnection::SetProtocol(echo* inProtocol){
  if (mSocket != NULL){
    delete mSocket;
    mSocket = NULL;
  }
  mSocket = inProtocol;
}

ARTIMTimer& ULConnection::GetTimer(){
  return mTimer;
}


ULConnectionInfo ULConnection::GetConnectionInfo() const{
  return mInfo;
}


void ULConnection::SetMaxPDUSize(const uint32_t& inSize){
  mMaxPDUSize = inSize;
}
uint32_t ULConnection::GetMaxPDUSize() const{
  return mMaxPDUSize;
}

std::vector<PresentationContext> ULConnection::GetPresentationContexts() const{
  return mPresentationContexts;
}
void ULConnection::SetPresentationContexts(const std::vector<PresentationContext>& inContexts){
  mPresentationContexts = inContexts;
}
//given a particular data element, presumably the SOP class,
//find the presentation context for that SOP
//NOT YET IMPLEMENTED
PresentationContext ULConnection::FindContext(const gdcm::DataElement& de) const{
  PresentationContext empty;
  return empty;
}
