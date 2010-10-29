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
#ifndef GDCMAPPLICATIONCONTEXT_H
#define GDCMAPPLICATIONCONTEXT_H

#include "gdcmTypes.h"

namespace gdcm
{

namespace network
{

/**
 * \brief ApplicationContext
 * Table 9-12
 * APPLICATION CONTEXT ITEM FIELDS
 * \fixme
 * Looks like Application Context can only be 64 bytes at max (see Figure 9-1 / PS 3.8 - 2009 )
 */
class GDCM_EXPORT ApplicationContext
{
public:
  ApplicationContext();
  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;

  void SetName( const char *name ) { UpdateName( name ); }
  const char *GetName() const { return Name.c_str(); }
  size_t Size() const;

  //static const uint8_t GetItemType() { return ItemType; }
  void Print(std::ostream &os) const;

private:
  void UpdateName( const char *name );
  static const uint8_t ItemType;
  static const uint8_t Reserved2;
  uint16_t ItemLength; // len of application context name
  std::string /*ApplicationContext*/ Name; // UID
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMAPPLICATIONCONTEXT_H
