/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
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
#include "gdcmFile.h"

namespace gdcm
{
/**
 * \brief Writer ala DOM (Document Object Model)
 *
 * Detailled description here
 * To avoid GDCM being yet another broken DICOM lib we try to 
 * be user level and avoid writing illegal stuff (odd length,
 * non-zero value for Item start/end length ...)
 * Therefore you cannot (well unless you are really smart) write
 * DICOM with even length tag.
 * All the checks are consider basics:
 * - Correct Meta Information Header (see gdcm::FileMetaInformation)
 * - Zero value for Item Length (0xfffe, 0xe00d/0xe0dd)
 * - Even length for any elements
 * - Alphabetical order for elements (garanteed by design of internals)
 * - 32bits VR will be rewritten with 00
 * - Any Elements with Tags (0001,xxxx), (0003,xxxx),
 *   (0005,xxxx), (0007,xxxx) will NOT be written.
 */
class FileMetaInformation;
class GDCM_EXPORT Writer
{
public:
  Writer():Stream(),F(0) {}
  virtual ~Writer();

  virtual bool Write(); // Execute()
  void SetFileName(const char *filename) {
    Stream.open(filename, std::ios::out | std::ios::binary );
    //std::cerr << Stream.is_open() << std::endl;
  }

  void SetFile( const File& f) { F = &f; }

//  const FileMetaInformation &GetHeader() const {
//    return *Header;
//  }
//  void SetHeader(FileMetaInformation const &fmi) {
//    Header = const_cast<FileMetaInformation*>(&fmi);
//  }
//  const DataSet &GetDataSet() const {
//    return *DS;
//  }
//  void SetDataSet(DataSet const &ds) {
//    DS = const_cast<DataSet*>(&ds);
//  }

//  void SetPreamble(const char *preamble) {
//    assert( Preamble == 0 );
//    if( !Preamble && preamble)
//      {
//      Preamble = new char[128+4];
//      }
//    if( preamble )
//      {
//      assert( Preamble );
//      memcpy(Preamble,preamble, 128+4);
//      }
//    else
//      {
//      assert( Preamble == 0 );
//      }
//  }

protected:
  /*OFStream */ std::ofstream Stream;

  //bool WritePreamble();

private:
  const File *F;
};

} // end namespace gdcm

#endif //__gdcmWriter_h
