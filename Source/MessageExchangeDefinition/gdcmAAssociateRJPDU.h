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
#ifndef GDCMAASSOCIATERJPDU_H
#define GDCMAASSOCIATERJPDU_H

#include "gdcmTypes.h"

namespace gdcm
{

// TODO: MM : does swig handle nested namespace
// I would like to avoid polluting gdcm namespace with such low level details the networ
// primitives:
namespace network
{

/**
Table 9-21
ASSOCIATE-RJ PDU FIELDS
 */
class AAssociateRJPDU
{
public:
static const uint8_t ItemType = 0x03; // PDUType ?
static const uint8_t Reserved2 = 0x00;
uint32_t ItemLength; // PDU Length ?
static const uint8_t Reserved8 = 0x00;
uint8_t Result;
uint8_t Source;
uint8_t Reason; // diag ?

private:
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMAASSOCIATERJPDU_H
