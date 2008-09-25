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
#ifndef __gdcmFile_h
#define __gdcmFile_h

#include "gdcmObject.h"
#include "gdcmDataSet.h"
#include "gdcmFileMetaInformation.h"

namespace gdcm
{

class FileInternal;
/**
 * \brief a DICOM File
 * See PS 3.10
 * File: A File is an ordered string of zero or more bytes, where the first byte is 
 * at the beginning of the file and the last byte at the end of the File. Files are 
 * identified by a unique File ID and may by written, read and/or deleted.
 */
class GDCM_EXPORT File : public Object
{
public:
  File() {};
  ~File() {};

  friend std::ostream &operator<<(std::ostream &os, const File &val);

  // Read
  std::istream &Read(std::istream &is);

  // Write
  std::ostream const &Write(std::ostream &os) const;

  const FileMetaInformation &GetHeader() const { return Header; }
  FileMetaInformation &GetHeader() { return Header; }
  void SetHeader( const FileMetaInformation &fmi ) { Header = fmi; }
  const DataSet &GetDataSet() const { return DS; }
  DataSet &GetDataSet() { return DS; }
  void SetDataSet( const DataSet &ds) { DS = ds; }

private:
  FileMetaInformation Header;
  DataSet DS;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const File &val)
{
  os << val.GetHeader() << std::endl;
  //os << val.GetDataSet() << std::endl; // FIXME
  abort();
  return os;
}

} // end namespace gdcm

#endif //__gdcmFile_h

