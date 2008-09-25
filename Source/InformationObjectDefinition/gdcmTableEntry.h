/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
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

/**
 * \brief TableEntry
 */
class TableEntry
{
public:
  TableEntry(const char *attribute = 0,
    Type const &type = Type(), const char * des = 0 ) :
    Attribute(""),TypeField(type),Description("") {}
  ~TableEntry() {}

private:
  std::string Attribute;
  Type TypeField;
  std::string Description;
};

} // end namespace gdcm

#endif //__gdcmTableEntry_h
