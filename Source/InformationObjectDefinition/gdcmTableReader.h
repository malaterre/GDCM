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
#ifndef __gdcmTableReader_h
#define __gdcmTableReader_h

#include "gdcmTypes.h"
#include <string>

namespace gdcm
{
/**
 * \brief Class for representing a TableReader
 * \note bla
 */
class GDCM_EXPORT TableReader
{
public:
  TableReader() {}
  ~TableReader() {}

  // Set/Get filename
  void SetFilename(const char *filename) { Filename = filename; }
  const char *GetFilename() { return Filename.c_str(); }

  int Read();

private:
  std::string Filename;
};

} // end namespace gdcm

#endif //__gdcmTableReader_h
