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
#ifndef GDCMPDATATFPDU_H
#define GDCMPDATATFPDU_H

#include "gdcmTypes.h"
#include "gdcmPresentationDataValue.h"

namespace gdcm
{

// TODO: MM : does swig handle nested namespace
// I would like to avoid polluting gdcm namespace with such low level details the networ
// primitives:
namespace network
{

/**
 */
class PDataTPPDU
{
public:
static const uint8_t ItemType = 0x04; // PDUType ?
static const uint8_t Reserved2 = 0x00;
uint32_t ItemLength; // PDU Length ?
std::vector<PresentationDataValue> V;
private:
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMPDATATFPDU_H
