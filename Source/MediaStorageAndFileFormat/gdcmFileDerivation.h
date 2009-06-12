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
class DataSet;
/**
 * \brief FileDerivation class
 * See PS 3.16 - 2008 For the list of Code Value that can be used for in Derivation Code Sequence
 *
 * URL: medical.nema.org/medical/dicom/2008/08_16pu.pdf
 * DICOM Part 16 has two Context Groups CID 7202 and CID 7203 which contain a set of codes defining
 * reason for a source image reference (ie. reason code for referenced image sequence) and a coded 
 * description of the deriation applied to the new image data from the original. Both these context 
 * groups are extensible.
 */
class GDCM_EXPORT FileDerivation
{
public:
  FileDerivation();
  ~FileDerivation();

  bool AddReference(const char *referencedsopclassuid, const char *referencedsopinstanceuid);

  void SetDerivationCodeSequenceCodeValue(unsigned int codevalue);
  void SetPurposeOfReferenceCodeSequenceCodeValue(unsigned int codevalue);
  void SetDerivationDescription( const char *dd );

  /// Change
  bool Derive();

  /// Set/Get File
  void SetFile(const File& f) { F = f; }
  File &GetFile() { return *F; }
  const File &GetFile() const { return *F; }

protected:
  bool AddDerivationDescription();
  bool AddSourceImageSequence();
  bool AddPurposeOfReferenceCodeSequence(DataSet &ds);

private:
  SmartPointer<File> F;
  FileDerivationInternals *Internals;
};

/**
 * \example GenFakeImage.cxx
 * \example ReformatFile.cs
 * This is a C++ example on how to use gdcm::FileDerivation
 */


} // end namespace gdcm

#endif //__gdcmFileDerivation_h

