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
#ifndef GDCMUSERINFORMATION_H
#define GDCMUSERINFORMATION_H

#include "gdcmTypes.h"
#include "gdcmMaximumLengthSub.h"
#include "gdcmImplementationVersionNameSub.h"
#include "gdcmImplementationClassUIDSub.h"

namespace gdcm
{

namespace network
{

class AsynchronousOperationsWindowSub;
/**
 * \brief UserInformation
 * Table 9-16
 * USER INFORMATION ITEM FIELDS
 *
 * TODO what is the goal of :
 *
 * Table 9-20
 * USER INFORMATION ITEM FIELDS
 */
class GDCM_EXPORT UserInformation
{
public:
  UserInformation();
  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;
  size_t Size() const;

  void Print(std::ostream &os) const;

private:
  static const uint8_t ItemType;
  static const uint8_t Reserved2;
  uint16_t ItemLength; // len of
  MaximumLengthSub MLS;
  //std::string /*UserInformation*/ Data; // ??
  ImplementationClassUIDSub ICUID;
  AsynchronousOperationsWindowSub *AOWS;
  ImplementationVersionNameSub IVNS;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMUSERINFORMATION_H
