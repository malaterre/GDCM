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

#ifndef __gdcmWriter_h
#define __gdcmWriter_h

#include "gdcmOFStream.h"
#include "gdcmDataSet.h"

namespace gdcm
{
/**
 * \brief Writer ala DOM (Document Object Model)
 *
 * Detailled description here
 */
class FileMetaInformation;
class GDCM_EXPORT Writer
{
public:
  Writer():Stream(),Preamble(0),DS(0),Header(0) {}
  virtual ~Writer();

  virtual bool Write(); // Execute()
  void SetFileName(std::string const &filename) {
    Stream.Open(filename.c_str());
  }

  const FileMetaInformation &GetHeader() const {
    return *Header;
  }
  void SetHeader(FileMetaInformation const &fmi) {
    Header = const_cast<FileMetaInformation*>(&fmi);
  }
  const DataSet &GetDataSet() const {
    return *DS;
  }
  void SetDataSet(DataSet const &ds) {
    DS = const_cast<DataSet*>(&ds);
  }

  void SetPreamble(const char *preamble) {
    assert( Preamble == 0 );
    if( !Preamble && preamble)
      {
      Preamble = new char[128+4];
      }
    if( preamble )
      {
      assert( Preamble );
      memcpy(Preamble,preamble, 128+4);
      }
    else
      {
      assert( Preamble == 0 );
      }
  }

protected:
  OFStream Stream;

  bool WritePreamble();
  char *Preamble;

private:
  DataSet *DS;
  FileMetaInformation *Header;
};

} // end namespace gdcm

#endif //__gdcmWriter_h
