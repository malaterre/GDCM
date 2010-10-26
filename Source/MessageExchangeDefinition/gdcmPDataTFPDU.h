/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef GDCMPDATATFPDU_H
#define GDCMPDATATFPDU_H

#include "gdcmTypes.h"
#include "gdcmPresentationDataValue.h"
#include "gdcmBasePDU.h"
#include <algorithm>
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
    assert(Size() < std::numeric_limits<uint32_t>::max());
    ItemLength = (uint32_t)Size() - 6;
  }
  PresentationDataValue const &GetPresentationDataValue(unsigned int i) const {
    assert( !V.empty() && i < V.size() );
    return V[i];
  }

  size_t GetNumPDVs() const {
    return V.size();
  }

  void Print(std::ostream &os) const;
  bool IsLastFragment() const;

private:
  static const uint8_t ItemType; // PDUType ?
  static const uint8_t Reserved2;
  uint32_t ItemLength; // PDU Length ?
  std::vector<PresentationDataValue> V;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMPDATATFPDU_H
