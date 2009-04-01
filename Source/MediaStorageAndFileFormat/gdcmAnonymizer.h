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
#ifndef __gdcmAnonymizer_h
#define __gdcmAnonymizer_h

#include "gdcmFile.h"
#include "gdcmAES.h"

namespace gdcm
{
/**
 * \brief Anonymizer
 * This is a dumb anonymizer implementation. All it allows user is simple operation such as:
 * Tag based functions:
 * - complete removal of DICOM attribute (Remove)
 * - make a take empty, ie make it's length 0 (Empty)
 * - replace with another string-based value (Replace)
 * 
 * DataSet function:
 * - Remove all group length attribute from a DICOM dataset (Group Length element are deprecated, DICOM 2008)
 * - Remove all private attributes
 *
 * All function calls actually execute the user specified request. Previous implementation were calling 
 * a general Anonymize function but traversing a std::set is O(n) operation, while a simple user specified
 * request is O(log(n)) operation. So 'm' user interaction is O(m*log(n)) which is < O(n) complexity.
 *
 * \todo implement the Basic Application Level Confidentiality Profile
 */
class GDCM_EXPORT Anonymizer
{
public:
  Anonymizer():F(new File),AESKey() {}
  ~Anonymizer();

  /// Make Tag t empty (if not found tag will be created)
  /// Warning: does not handle SQ element
  bool Empty( Tag const &t );

  /// remove a tag (even a SQ can be removed)
  bool Remove( Tag const &t );

  /// Replace tag with another value, if tag is not found it will be created:
  /// WARNING: this function can only execute if tag is a VRASCII
  bool Replace( Tag const &t, const char *value );

  /// when the value contains \0, it is a good idea to specify the length. This function
  /// is required when dealing with VRBINARY tag
  bool Replace( Tag const &t, const char *value, VL const & vl );

  /// Main function that loop over all elements and remove private tags
  bool RemovePrivateTags();

  /// Main function that loop over all elements and remove group length
  bool RemoveGroupLength();

  /// Main function that loop over all elements and remove retired element
  bool RemoveRetired();

  // TODO:
  // bool Remove( PRIVATE_TAGS | GROUP_LENGTH | RETIRED );

  /// Set/Get File
  void SetFile(const File& f) { F = f; }
  //const File &GetFile() const { return *F; }
  File &GetFile() { return *F; }

  /// PS 3.15 
  /// E.1.1 De-Identifier
  /// An Application may claim conformance to the Basic Application Level Confidentiality Profile as a deidentifier
  /// if it protects all Attributes that might be used by unauthorized entities to identify the patient.
  bool BasicApplicationLevelConfidentialityProfile();

  void SetAESKey(AES const &aes);
  const AES &GetAESKey() const;

protected:
  bool BALCPProtect(Tag const & tag);

private:
  // I would prefer to have a smart pointer to DataSet but DataSet does not derive from Object...
  SmartPointer<File> F;
  AES AESKey;
};

/**
 * \example ManipulateFile.cs
 * This is a C# example on how to use gdcm::Anonymizer
 */

} // end namespace gdcm

#endif //__gdcmAnonymizer_h
