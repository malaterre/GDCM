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
#include "gdcmBasePDU.h"

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
class GDCM_EXPORT AAssociateACPDU : public BasePDU
{
public:
  AAssociateACPDU();
  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;

  void AddPresentationContextAC( PresentationContextAC const &pcac );

  const PresentationContextAC &GetPresentationContextAC( unsigned int i ) {
    assert( !PresContextAC.empty() && i < PresContextAC.size() );
    return PresContextAC[i];
  }
  typedef std::vector<PresentationContextAC>::size_type SizeType;
  SizeType GetNumberOfPresentationContextAC() const {
    return PresContextAC.size();
  }

  size_t Size() const;

  void Print(std::ostream &os) const;
  bool IsLastFragment() const { return true; }

private:
  static const uint8_t ItemType; // PDUType ?
  static const uint8_t Reserved2;
  uint32_t PDULength; // len of 
  static const uint16_t ProtocolVersion;
  static const uint16_t Reserved9_10;
  static const uint8_t Reserved11_26[16];
  static const uint8_t Reserved27_42[16];
  static const uint8_t Reserved43_74[32];
  /*
  75-xxx Variable items This variable field shall contain the following items: one Application
  Context Item, one or more Presentation Context Item(s) and one User
  Information Item. For a complete description of these items see Sections
  7.1.1.2, 7.1.1.14, and 7.1.1.6.
   */
  ApplicationContext AppContext;
  std::vector<PresentationContextAC>	PresContextAC;
  UserInformation UserInfo;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMAASSOCIATEACPDU_H
