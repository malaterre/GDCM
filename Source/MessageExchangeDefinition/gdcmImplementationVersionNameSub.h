/*=========================================================================
:w

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMIMPLEMENTATIONVERSIONNAMESUB_H
#define GDCMIMPLEMENTATIONVERSIONNAMESUB_H

#include "gdcmTypes.h"

namespace gdcm
{

namespace network
{

/**
Table D.3-3
IMPLEMENTATION VERSION NAME SUB-ITEM FIELDS (A-ASSOCIATE-RQ)
 */
class ImplementationVersionNameSub
{
public:
  ImplementationVersionNameSub();
  const std::ostream &Write(std::ostream &os) const;
private:
  static const uint8_t ItemType;
  static const uint8_t Reserved2;
  uint16_t ItemLength;
  std::string ImplementationVersionName;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMMAXIMUMLENGTHSUB_H
