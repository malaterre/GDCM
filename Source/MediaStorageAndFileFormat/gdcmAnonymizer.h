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
 * User has to call Anonymize() function to get anything executed
 * \todo implement the Basic Application Level Confidentiality Profile
 */
class GDCM_EXPORT Anonymizer
{
public:
  Anonymizer():F(new File),RemovePrivateTags(true),BasicApplicationLevelConfidentialityProfile(false) {}
  ~Anonymizer();

  // Make tag t empty (if not found tag will be created)
  bool Empty( Tag const &t );

  // remove a tag (even a SQ can be removed)
  bool Remove( Tag const &t );

  // Replace tag with another value, if tag is not found it will be created:
  // WARNING: this function can only execute if tag is a VRASCII
  bool Replace( Tag const &t, const char *value );

  // when the value contains \0, it is a good idea to specify the length. This function
  // is required when dealing with VRBINARY tag
  bool Replace( Tag const &t, const char *value, VL const & vl );

  // Main function that loop over all elements and execute user specified anonymization
  bool Anonymize();

  void SetFile(const File& f) { F = &f; }
  //const File &GetFile() const { return *F; }
  File &GetFile() { return *F; }

  // Decide whether or not to remove all private tags
  void SetRemovePrivateTags(bool b) { RemovePrivateTags = b; }

  // PS 3.15 
  // E.1.1 De-Identifier
  // An Application may claim conformance to the Basic Application Level Confidentiality Profile as a deidentifier
  // if it protects all Attributes that might be used by unauthorized entities to identify the patient.
  //void SetBasicApplicationLevelConfidentialityProfile(bool b) { BasicApplicationLevelConfidentialityProfile = b; }

protected:

private:
  // I would prefer to have a smart pointer to DataSet but DataSet does not derive from Object...
  SmartPointer<File> F;
  bool RemovePrivateTags;
  bool BasicApplicationLevelConfidentialityProfile;
};

} // end namespace gdcm

#endif //__gdcmAnonymizer_h
