/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMFILECHANGETRANSFERSYNTAX_H
#define GDCMFILECHANGETRANSFERSYNTAX_H

#include "gdcmSubject.h"
#include "gdcmSmartPointer.h"

namespace gdcm
{
class FileChangeTransferSyntaxInternals;
class ImageCodec;
class TransferSyntax;

/**
 * \brief FileChangeTransferSyntax
 */
class GDCM_EXPORT FileChangeTransferSyntax : public Subject
{
public:
  FileChangeTransferSyntax();
  ~FileChangeTransferSyntax();

  /// Set input filename
  void SetInputFileName(const char *filename_native);

  /// Set output filename
  void SetOutputFileName(const char *filename_native);

  /// Change
  bool Change();

  /// Specify the Target Transfer Syntax
  void SetTransferSyntax( TransferSyntax const & ts );

  /// Retrieve the actual codec (valid after calling SetTransferSyntax)
  ImageCodec * GetCodec();

  /// for wrapped language: instantiate a reference counted object
  static SmartPointer<FileChangeTransferSyntax> New() { return new FileChangeTransferSyntax; }

private:
  bool InitializeCopy();
  FileChangeTransferSyntaxInternals *Internals;
};

} // end namespace gdcm

#endif //GDCMFILEANONYMIZER_H
