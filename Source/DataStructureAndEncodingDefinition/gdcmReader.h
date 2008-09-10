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

#ifndef __gdcmReader_h
#define __gdcmReader_h

#include "gdcmFile.h"

#include <fstream>

namespace gdcm
{
/**
 * \brief Reader ala DOM (Document Object Model)
 * \details This class is a non-validating reader, it will only performs well-
 * formedness check only, and to some extent catch known error (non
 * well-formed document).
 *
 * Detailled description here
 *
 * A DataSet DOES NOT contains group 0x0002
 *
 * This is really a DataSet reader. This will not make sure the dataset
 * conform to any IOD at all. This is a completely different step. The
 * reasoning was that user could control the IOD there lib would handle
 * and thus we would not be able to read a DataSet if the IOD was not found
 * Instead we separate the reading from the validation.
 *
 * NOTE:
 * From GDCM1.x. Users will realize that one feature is missing
 * from this DOM implementation. In GDCM 1.x user used to be able to
 * control the size of the Value to be read. By default it was 0xfff.
 * The main author of GDCM2 thought this was too dangerous and harmful and
 * therefore this feature did not make it into GDCM2
 *
 * WARNING:
 * GDCM will not produce warning for unorder (non-alphabetical order).
 * See gdcm::Writer for more info
 *
 */
class GDCM_EXPORT Reader
{
public:
  Reader():F(new File){
	  Stream = NULL;
	  Ifstream = NULL;
  }
  virtual ~Reader();

  virtual bool Read(); // Execute()
  void SetFileName(const char *filename) {
	  Ifstream = new std::ifstream();
	  Ifstream->open(filename, std::ios::binary);
	  Stream = Ifstream;
  }
  void SetStream(std::istream &input_stream) {
	  Stream = &input_stream;
  }

  const File &GetFile() const { return *F; }
  File &GetFile() { return *F; }
  void SetFile(File& file) { F = &file; }

  // Will read only up to Tag 'tag'
  bool ReadUpToTag(const Tag & tag, std::set<Tag> const & skiptags);

protected:
  bool ReadPreamble();
  bool ReadMetaInformation();
  bool ReadDataSet();

  SmartPointer<File> F;

private:
  TransferSyntax GuessTransferSyntax();
  std::istream *Stream;
  std::ifstream *Ifstream;
};

/**
 * \example TestReader.cxx
 * \example TestReader.py
 * This is a C++ example on how to use gdcm::Reader
 */

} // end namespace gdcm


#endif //__gdcmReader_h
