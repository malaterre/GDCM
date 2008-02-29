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
#ifndef __gdcmAnonymizer_h
#define __gdcmAnonymizer_h

#include "gdcmFile.h"

namespace gdcm
{
/**
 * \brief Anonymizer
 */
class GDCM_EXPORT Anonymizer
{
public:
  Anonymizer():F(new File) {}
  ~Anonymizer();

  // Make take t empty (if not found tag will be created)
  void Empty( Tag const &t );

  // remove a tag
  void Remove( Tag const &t );

  // Replace tag with another value, if tag is not found it will be created:
  bool Replace( Tag const &t, const char *value );
  // when the value contains \0, it is a good idea to specify the length
  bool Replace( Tag const &t, const char *value, VL const & vl );

  bool Anonymize();

  void SetFile(const File& f) { F = &f; }
  //const File &GetFile() const { return *F; }
  File &GetFile() { return *F; }

protected:

private:
  // I would prefer to have a smart pointer to DataSet but DataSet does not derive from Object...
  SmartPointer<File> F;
};

} // end namespace gdcm

#endif //__gdcmAnonymizer_h
