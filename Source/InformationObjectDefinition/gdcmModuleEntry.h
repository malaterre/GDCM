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
#ifndef __gdcmModuleEntry_h
#define __gdcmModuleEntry_h

#include "gdcmTypes.h"
#include "gdcmType.h"

#include <string>

namespace gdcm
{
/**
 * \brief Class for representing a ModuleEntry
 * \note bla
 * \sea DictEntry
 */
class GDCM_EXPORT ModuleEntry
{
public:
  ModuleEntry(/*const char *name,*/const char *type, const char *description):Description(description) {
	  DataElementType = Type::GetTypeType(type);
  }
  friend std::ostream& operator<<(std::ostream& _os, const ModuleEntry &_val);

  const char *GetName() const { return ""; }

  const Type &GetType() const { return DataElementType; }

  const char *GetDescription() const { return Description.c_str(); }

private:
  // PS 3.3 repeats the name of an attribute, but often contains typos
  // for now we will not use this info, but instead access the DataDict instead
  //std::string Name;

  // An attribute, encoded as a Data Element, may or may not be required in a 
  // Data Set, depending on that Attribute's Data Element Type.
  Type DataElementType;

  // TODO: for now contains the raw description (with enumerated values, defined terms...)
  std::string Description;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const ModuleEntry &_val)
{
  _os << _val.DataElementType << "\t" << _val.Description;
  return _os;
}


} // end namespace gdcm

#endif //__gdcmModuleEntry_h
