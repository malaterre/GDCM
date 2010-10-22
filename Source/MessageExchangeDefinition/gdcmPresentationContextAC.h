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
\see PresentationContext
 */
class GDCM_EXPORT PresentationContextAC
{
public:
  PresentationContextAC();
  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;

  size_t Size() const;

  void SetTransferSyntax( TransferSyntax_ const &ts );
  void SetPresentationContextID( uint8_t id );

  void Print(std::ostream &os) const;

private:
  static const uint8_t ItemType;
  static const uint8_t Reserved2;
  uint16_t ItemLength; // len of last transfer syntax
  uint8_t /*PresentationContext*/ID;
  static const uint8_t Reserved6;
  uint8_t /*Reason*/Result;
  static const uint8_t Reserved8;
  TransferSyntax_ SubItems;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMPRESENTATIONCONTEXTAC_H
