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
#include "gdcmBasePDU.h"

namespace gdcm
{

// TODO: MM : does swig handle nested namespace
// I would like to avoid polluting gdcm namespace with such low level details the networ
// primitives:
namespace network
{

/**
Table 9-22
P-DATA-TF PDU FIELDS
 */
class GDCM_EXPORT PDataTFPDU : public BasePDU
{
public:
  PDataTFPDU();
  std::istream &Read(std::istream &is);
  std::istream &ReadInto(std::istream &is, std::ostream &os);
  const std::ostream &Write(std::ostream &os) const;

  /// \internal Compute Size
  size_t Size() const;

  void AddPresentationDataValue( PresentationDataValue const &pdv ) {
    V.push_back( pdv );
    ItemLength = Size() - 6;
  }
  PresentationDataValue const &GetPresentationDataValue(unsigned int i) const {
    assert( !V.empty() && i < V.size() );
    return V[i];
  }
  void Print(std::ostream &os) const;

private:
  static const uint8_t ItemType; // PDUType ?
  static const uint8_t Reserved2;
  uint32_t ItemLength; // PDU Length ?
  std::vector<PresentationDataValue> V;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMPDATATFPDU_H
