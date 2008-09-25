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
#ifndef __gdcmDefs_h
#define __gdcmDefs_h

#include "gdcmModules.h"
//#include "gdcmMacros.h"
#include "gdcmIODs.h"

#include <string>

namespace gdcm
{
class DataSet;
class MediaStorage;
/**
 * \brief FIXME I do not like the name 'Defs'
 * \note bla
 */
class GDCM_EXPORT Defs
{
public:
  Defs();
  ~Defs();

  const Modules &GetModules() const { return Part3Modules; }
  Modules &GetModules() { return Part3Modules; }

  const Macros &GetMacros() const { return Part3Macros; }
  Macros &GetMacros() { return Part3Macros; }

  const IODs & GetIODs() const { return Part3IODs; }
  IODs & GetIODs() { return Part3IODs; }

  bool IsEmpty() const { return GetModules().IsEmpty(); }

  bool Verify(const DataSet& ds) const;

protected:
  friend class Global;
  void LoadDefaults();
  void LoadFromFile(const char *filename);

  const char *GetIODNameFromMediaStorage(MediaStorage &ms) const;

private:
  // Part 3 stuff:
  Macros Part3Macros;
  Modules Part3Modules;
  IODs Part3IODs;

  Defs &operator=(const Defs &val); // purposely not implemented
  Defs(const Defs &val); // purposely not implemented
};


} // end namespace gdcm

#endif //__gdcmDefs_h

