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
#ifndef __gdcmPythonFilter_h
#define __gdcmPythonFilter_h

#include "gdcmDataElement.h"
#include "gdcmDicts.h"
#include "gdcmFile.h"

#include <Python.h>

namespace gdcm
{

/**
 * \brief PythonFilter
 * PythonFilter is the class that make gdcm2.x looks more like gdcm1 and transform the binary blob 
 * contained in a DataElement into a string, typically this is a nice feature to have for wrapped language
 */
class GDCM_EXPORT PythonFilter
{
public:
  PythonFilter();
  ~PythonFilter();

  void UseDictAlways(bool use) {}

  // Allow user to pass in there own dicts
  void SetDicts(const Dicts &dicts);

  // Convert to string the ByteValue contained in a DataElement
  PyObject *ToPyObject(const Tag& t) const;

  void SetFile(const File& f) { F = &f; }
  File &GetFile() { return *F; }
  const File &GetFile() const { return *F; }

private:
  SmartPointer<File> F;
};

} // end namespace gdcm

#endif //__gdcmPythonFilter_h
