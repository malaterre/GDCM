/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmIODEntry_h
#define __gdcmIODEntry_h

#include "gdcmTypes.h"
#include "gdcmType.h"

#include <string>

namespace gdcm
{
/**
 * \brief Class for representing a IODEntry
 * \note bla
 * \sa DictEntry
 */
class GDCM_EXPORT IODEntry
{
public:
  IODEntry(const char *name = "", const char *ref = "", const char *usage = ""):Name(name),Ref(ref),Usage(usage) {
  }
  friend std::ostream& operator<<(std::ostream& _os, const IODEntry &_val);

  void SetIE(const char *ie) { IE = ie; }
  const char *GetIE() const { return IE.c_str(); }

  void SetName(const char *name) { Name = name; }
  const char *GetName() const { return Name.c_str(); }

  void SetRef(const char *ref) { Ref = ref; }
  const char *GetRef() const { return Ref.c_str(); }

  void SetUsage(const char *usage) { Usage = usage; }
  const char *GetUsage() const { return Usage.c_str(); }

private:
  std::string IE;

  std::string Name;

  std::string Ref;

  std::string Usage;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const IODEntry &_val)
{
  _os << _val.IE << "\t" << _val.Name << "\t" << _val.Ref << "\t" << _val.Usage;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmIODEntry_h
