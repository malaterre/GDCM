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
#ifndef GDCMPRESENTATIONCONTEXTAC_H
#define GDCMPRESENTATIONCONTEXTAC_H

#include "gdcmTypes.h"
#include "gdcmTransferSyntax_.h"

namespace gdcm
{

namespace network
{

/**
 Table 9-18
PRESENTATION CONTEXT ITEM FIELDS
 */
class PresentationContextAC
{
public:
static const uint8_t ItemType = 0x21;
static const uint8_t Reserved2 = 0x00;
uint16_t ItemLength; // len of last transfer syntax
uint8_t /*PresentationContext*/ID;
static const uint8_t Reserved6 = 0x00;
uint8_t /*Reason*/Result;
static const uint8_t Reserved8 = 0x00;
TransferSyntax_ SubItems;
private:
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMPRESENTATIONCONTEXTAC_H
