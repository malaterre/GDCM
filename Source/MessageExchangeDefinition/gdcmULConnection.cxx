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
  mEcho = NULL;
  mInfo = inConnectInfo;
}


ULConnection::~ULConnection(){
    if (mEcho != NULL){
      delete mEcho;
      mEcho = NULL;
    }
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
  if (mEcho){
    return mEcho;
  }
  //be careful-- the socket doesn't get removed when the protocol is stopped,
  //because then subsequent cstores will break.
  if (mSocket){
    return mSocket;
  }
  return NULL;
}

ARTIMTimer& ULConnection::GetTimer(){
  return mTimer;
}

const ULConnectionInfo &ULConnection::GetConnectionInfo() const{
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


bool ULConnection::InitializeConnection(){
  try{
    echo* p = new echo(protocol::tcp);
    if (GetConnectionInfo().GetCalledIPPort() == 0){
      if (!GetConnectionInfo().GetCalledComputerName().empty())
        (*p)->connect(GetConnectionInfo().GetCalledComputerName().c_str());
      else
        (*p)->connect(GetConnectionInfo().GetCalledIPAddress());
    }
    else {
      if (!GetConnectionInfo().GetCalledComputerName().empty())
        (*p)->connect(GetConnectionInfo().GetCalledComputerName().c_str(),
          GetConnectionInfo().GetCalledIPPort());
    }
    //make sure to convert timeouts to platform appropriate values.
    (*p)->recvtimeout((int)GetTimer().GetTimeout());
    (*p)->sendtimeout((int)GetTimer().GetTimeout());
    if (mEcho != NULL){
      delete mEcho;
      mEcho = NULL;
    }
    if (mSocket != NULL){
      delete mSocket;
      mSocket = NULL;
    }
    mEcho = p;
  } catch (std::exception& ex){//unable to establish connection, so break off.
     gdcmWarningMacro("Unable to open connection with exception " << ex.what() << std::endl);
     return false;
  }
  return true;
}
bool ULConnection::InitializeIncomingConnection(){
  try{
    if (mEcho != NULL){
      delete mEcho;
      mEcho = NULL;
    }
    if (mSocket != NULL){
      delete mSocket;
      mSocket = NULL;
    }
    sockinetbuf sin (sockbuf::sock_stream);
    sin.bind( mInfo.GetCalledIPPort() );
    sin.recvtimeout((int)GetTimer().GetTimeout());
    sin.sendtimeout((int)GetTimer().GetTimeout());
    sin.listen();
    mSocket = new iosockinet(sin.accept());

    SetState(eSta2Open);

    /*
    if (mSocket != NULL){
      delete mSocket;
    }
    mSocket = new protocol();
    sockinetaddr theAddy(GetConnectionInfo().GetCalledComputerName().c_str(),
      GetConnectionInfo().GetCalledIPPort());
    mSocket->rdbuf()->connect(theAddy);
    mSocket->rdbuf()->recvtimeout((int)GetTimer().GetTimeout());
    mSocket->rdbuf()->sendtimeout((int)GetTimer().GetTimeout());
*/
  } catch (std::exception& ex){//unable to establish connection, so break off.
     gdcmWarningMacro("Unable to open connection with exception " << ex.what() << std::endl);
     return false;
  }
  return true;
}

void ULConnection::StopProtocol(){
  if (mEcho != NULL){
    delete mEcho;
    mEcho = NULL;
    SetState(eSta1Idle);
  } else {
    //don't actually kill the connection, just kill the association.
    //this is just for a cstorescp initialized by a cmove
    SetState(eSta2Open);
  }
}
