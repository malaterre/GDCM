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
#ifndef __gdcmTableReader_h
#define __gdcmTableReader_h

#include "gdcmTypes.h"
#include "gdcmModule.h"
#include "gdcmModules.h"

#include <string>
#include <vector>
#include <map>

namespace gdcm
{
/**
 * \brief Class for representing a TableReader
 * \note This class is an empty shell meant to be derived
 */
class GDCM_EXPORT TableReader
{
public:
  TableReader():ParsingModule(false),ParsingModuleEntry(false),
  ParsingModuleEntryDescription(false),
  Description() {}
  virtual ~TableReader() {}

  // Set/Get filename
  void SetFilename(const char *filename) { Filename = filename; }
  const char *GetFilename() { return Filename.c_str(); }

  int Read();

  

//protected:
  // You need to override those function in your subclasses:
  virtual void StartElement(const char *name, const char **atts);
  virtual void EndElement(const char *name);
  virtual void CharacterDataHandler(const char *data, int length);

void HandleModuleEntry(const char **atts);
void HandleModule(const char **atts);
void HandleModuleEntryDescription(const char **atts);

  const Modules & GetModules() const { return CurrentModules; }

private:
  std::string Filename;
  Modules CurrentModules;
  Module CurrentModule;
  ModuleEntry CurrentModuleEntry;
  std::string CurrentModuleName;
  bool ParsingModule;
  bool ParsingModuleEntry;
  bool ParsingModuleEntryDescription;
  Tag CurrentTag;
  std::string Description;
};

} // end namespace gdcm

#endif //__gdcmTableReader_h
