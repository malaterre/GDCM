/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmTableEntry_h
#define __gdcmTableEntry_h

#include "gdcmType.h"

#include <string>

namespace gdcm
{

/* \brief TableEntry
 */
class TableEntry
{
public:
  TableEntry(const char *attribute = 0,
    Type const &type = Type(), const char * des = 0 ) :
    Attribute(attribute),TypeField(type),Description(des) {}
  ~TableEntry() {}

private:
  std::string Attribute;
  Type TypeField;
  std::string Description;
};

} // end namespace gdcm

#endif //__gdcmTableEntry_h
