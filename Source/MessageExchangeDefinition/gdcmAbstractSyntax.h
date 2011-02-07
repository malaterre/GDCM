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
#ifndef GDCMABSTRACTSYNTAX_H
#define GDCMABSTRACTSYNTAX_H

#include "gdcmTypes.h"
#include "gdcmUIDs.h"

namespace gdcm
{

namespace network
{

/**
 * \brief AbstractSyntax
 * Table 9-14
 * ABSTRACT SYNTAX SUB-ITEM FIELDS
 */
class AbstractSyntax
{
public:
  AbstractSyntax();
  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;

  void SetName( const char *name ) { UpdateName( name ); }
  const char *GetName() const { return Name.c_str(); }

  // accept a UIDs::TSType also...
  void SetNameFromUID( UIDs::TSName tsname );
  //now that the PresentationContext messes around with UIDs and returns a string
  //use that string as well.
  void SetNameFromUIDString( const std::string& inUIDName );

  size_t Size() const;

  void Print(std::ostream &os) const;
private:
  void UpdateName( const char *name );
  static const uint8_t ItemType;
  static const uint8_t Reserved2;
  uint16_t ItemLength; // len of
  std::string /*AbstractSyntax*/ Name; // UID
};

} // end namespace network
} // end namespace gdcm

#endif //GDCMABSTRACTSYNTAX_H
