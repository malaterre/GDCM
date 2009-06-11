/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmFileDerivation_h
#define __gdcmFileDerivation_h

#include "gdcmFile.h"

namespace gdcm
{

class FileDerivationInternals;
/**
 * \brief FileDerivation class
 */
class GDCM_EXPORT FileDerivation
{
public:
  FileDerivation();
  ~FileDerivation();

  bool AddReference(const char *referencedsopclassuid, const char *referencedsopinstanceuid);

  void SetDerivationCodeSequenceCodeValue(unsigned int codevalue);

  /// Change
  bool Derive();

  /// Set/Get File
  void SetFile(const File& f) { F = f; }
  File &GetFile() { return *F; }


protected:
  bool AddDerivationDescription();
  bool AddSourceImageSequence();

private:
  SmartPointer<File> F;
  FileDerivationInternals *Internals;
};


} // end namespace gdcm

#endif //__gdcmFileDerivation_h

