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
#ifndef __gdcmXMLDictReader_h
#define __gdcmXMLDictReader_h

#include "gdcmTableReader.h"
#include "gdcmDict.h"
#include "gdcmDictEntry.h"
#include "gdcmTag.h"

namespace gdcm
{
/**
 * \brief Class for representing a XMLDictReader
 * \note bla
 * Will read the DICOMV3.xml file
 */
class GDCM_EXPORT XMLDictReader : public TableReader
{
public:
  XMLDictReader();
  ~XMLDictReader() {}

  void StartElement(const char *name, const char **atts);
  void EndElement(const char *name);
  void CharacterDataHandler(const char *data, int length);

  const Dict & GetDict() { return DICOMDict; }

protected:
  void HandleEntry(const char **atts);
  void HandleDescription(const char **atts);

private:
  Dict DICOMDict;
  Tag CurrentTag;
  DictEntry CurrentDE;
  bool ParsingDescription;
  std::string Description;
};

} // end namespace gdcm

#endif //__gdcmXMLDictReader_h
