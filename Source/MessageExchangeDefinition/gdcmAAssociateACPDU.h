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
#ifndef GDCMAASSOCIATEACPDU_H
#define GDCMAASSOCIATEACPDU_H

#include "gdcmTypes.h"
#include "gdcmApplicationContext.h"
#include "gdcmPresentationContextAC.h"
#include "gdcmUserInformation.h"

namespace gdcm
{

// TODO: MM : does swig handle nested namespace
// I would like to avoid polluting gdcm namespace with such low level details the networ
// primitives:
namespace network
{

/**
Table 9-17
ASSOCIATE-AC PDU fields
 */
class AAssociateACPDU
{
public:
static const uint8_t ItemType = 0x02; // PDUType ?
static const uint8_t Reserved2 = 0x00;
uint16_t PDULength; // len of 
static const uint16_t ProtocolVersion = 0x01;
static const uint16_t Reserved9_10 = 0x0000;
static const uint8_t Reserved11_26[16]; // = { 0x0 };
static const uint8_t Reserved27_42[16]; // = { 0x0 };
static const uint8_t Reserved43_74[32]; // = { 0x0 };
/*
75-xxx Variable items This variable field shall contain the following items: one Application
Context Item, one or more Presentation Context Item(s) and one User
Information Item. For a complete description of these items see Sections
7.1.1.2, 7.1.1.14, and 7.1.1.6.
*/
ApplicationContext AppContext;
std::vector<PresentationContextAC>	PresContextAC;
UserInformation UserInfo;
private:
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMAASSOCIATEACPDU_H
