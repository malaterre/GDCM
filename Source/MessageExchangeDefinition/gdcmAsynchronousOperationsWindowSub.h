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

#ifndef GDCMASYNCHRONOUSOPERATIONSWINDOWSUB_H
#define GDCMASYNCHRONOUSOPERATIONSWINDOWSUB_H

#include "gdcmTypes.h"

namespace gdcm
{

namespace network
{

/**
PS 3.7
Table D.3-7
ASYNCHRONOUS OPERATIONS WINDOW SUB-ITEM FIELDS
(A-ASSOCIATE-RQ)
 */
class GDCM_EXPORT AsynchronousOperationsWindowSub
{
public:
  AsynchronousOperationsWindowSub();
  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;

  size_t Size() const;

private:
  static const uint8_t ItemType;
  static const uint8_t Reserved2;
  uint16_t ItemLength;
  uint16_t MaximumNumberOperationsInvoked;
  uint16_t MaximumNumberOperationsPerformed;
};

} // end namespace network

} // end namespace gdcm

#endif // GDCMASYNCHRONOUSOPERATIONSWINDOWSUB_H
