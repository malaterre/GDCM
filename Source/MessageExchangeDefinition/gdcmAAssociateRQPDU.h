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
#ifndef GDCMAASSOCIATERQPDU_H
#define GDCMAASSOCIATERQPDU_H

#include "gdcmTypes.h"
#include "gdcmVR.h" // AEComp
#include "gdcmApplicationContext.h"
#include "gdcmPresentationContext.h"
#include "gdcmUserInformation.h"

namespace gdcm
{

// TODO: MM : does swig handle nested namespace
// I would like to avoid polluting gdcm namespace with such low level details the networ
// primitives:
namespace network
{

/**
Table 9-11 ASSOCIATE-RQ PDU fields
 */
class AAssociateRQPDU
{
public:
  AAssociateRQPDU();
  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;
  size_t Size() const;
  void AddPresentationContext( PresentationContext const &pc );

private:
  // 1 PDU-type 01H
  static const uint8_t ItemType; // PDUType ?
  // 2 Reserved This reserved field shall be sent with a value 00H but not tested to this value when received.
  static const uint8_t Reserved2;
  /* 3-6 PDU-length This PDU-length shall be the number of bytes from the first byte of the
     following field to the last byte of the variable field. It shall be encoded as
     an unsigned binary number
   */
  uint32_t ItemLength; // PDU Length
  /*
  7-8 Protocol-version This two byte field shall use one bit to identify each version of the
  DICOM UL protocol supported by the calling end-system. This is
  Version 1 and shall be identified with bit 0 set. A receiver of this PDU
  implementing only this version of the DICOM UL protocol shall only test
  that bit 0 is set.
   */
  static const uint16_t ProtocolVersion;
  /*
  9-10 Reserved This reserved field shall be sent with a value 0000H but not tested to
  this value when received.
   */
  static const uint16_t Reserved9_10;
  /*
  11-26 Called-AE-title Destination DICOM Application Name. It shall be encoded as 16
  characters as defined by the ISO 646:1990-Basic G0 Set with leading
  and trailing spaces (20H) being non-significant. The value made of 16
  spaces (20H) meaning “no Application Name specified” shall not be
  used. For a complete description of the use of this field, see Section
  7.1.1.4.
   */
  char CalledAETitle[16];
  /*
  27-42 Calling-AE-title Source DICOM Application Name. It shall be encoded as 16
  characters as defined by the ISO 646:1990-Basic G0 Set with leading
  and trailing spaces (20H) being non-significant. The value made of 16
  spaces (20H) meaning “no Application Name specified” shall not be
  used. For a complete description of the use of this field, see Section
  7.1.1.3.
   */
  char CallingAETitle[16];
  /*
  43-74 Reserved This reserved field shall be sent with a value 00H for all bytes but not
  tested to this value when received
   */
  static const uint8_t Reserved43_74[32]; // { 0 }
  /*
  75-xxx Variable items This variable field shall contain the following items: one Application
  Context Item, one or more Presentation Context Items and one User
  Information Item. For a complete description of the use of these items
  see Sections 7.1.1.2, 7.1.1.13, and 7.1.1.6.
   */
  ApplicationContext AppContext;
  std::vector<PresentationContext> PresContext;
  UserInformation UserInfo;
};

} // end namespace network
} // end namespace gdcm

#endif //GDCMAASSOCIATERQPDU_H
