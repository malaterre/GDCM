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
#ifndef GDCMABSTRACTSYNTAX_H
#define GDCMABSTRACTSYNTAX_H

#include "gdcmTypes.h"

namespace gdcm
{

namespace network
{

/**
Table 9-16
USER INFORMATION ITEM FIELDS

TODO what is the goal of :

Table 9-20
USER INFORMATION ITEM FIELDS
 */
class UserInformation
{
public:
static const uint8_t ItemType = 0x50;
static const uint8_t Reserved2 = 0x00;
uint16_t ItemLength; // len of
std::string /*UserInformation*/ Data; // ??
private:
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMABSTRACTSYNTAX_H
