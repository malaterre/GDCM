/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmTable_h
#define __gdcmTable_h

#include "gdcmTableEntry.h"

#include <string>

namespace gdcm
{

/* \brief Table
 */
class Table
{
public:
  Table() {}
  ~Table() {}

  void InsertEntry(TableEntry const &te);

private:
  Tag TagField;
  std::string Attribute;
  Type TypeField;
  std::string Description;
};

} // end namespace gdcm

#endif //__gdcmTable_h
