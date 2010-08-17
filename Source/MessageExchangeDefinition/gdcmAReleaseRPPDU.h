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
#ifndef GDCMARELEASERPPDU_H
#define GDCMARELEASERPPDU_H

#include "gdcmTypes.h"

namespace gdcm
{

// TODO: MM : does swig handle nested namespace
// I would like to avoid polluting gdcm namespace with such low level details the networ
// primitives:
namespace network
{

/**
Table 9-25
A-RELEASE-RP PDU fields
 */
class AReleaseRPPDU
{
public:
  AReleaseRPPDU();
  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;
private:
  static const uint8_t ItemType; // PDUType ?
  static const uint8_t Reserved2;
  uint32_t ItemLength; // PDU Length
  static const uint32_t Reserved7_10;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMARELEASERPPDU_H
