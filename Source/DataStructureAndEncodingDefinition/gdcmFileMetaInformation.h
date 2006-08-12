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

#ifndef __gdcmFileMetaInformation_h
#define __gdcmFileMetaInformation_h

#include "gdcmDataSet.h"
#include "gdcmTS.h"

namespace gdcm
{
/**
 * \brief Class to represent a File Meta Information
 * \note
 * In theory this should only be explicit, but just in case we also handle
 * the implicit case (illegal)
 * Warning (TODO):
 * When writing the Meta Header we make sure to have at least:
 * - the Group Length
 * - the File Meta Information Version
 */
class ExplicitDataElement;
class ImplicitDataElement;
class GDCM_EXPORT FileMetaInformation
{
public:
  FileMetaInformation():DS(0),InternalTS(TS::TS_END) {}
  ~FileMetaInformation();

  friend std::ostream &operator<<(std::ostream &_os, const FileMetaInformation &_val);

  void SetTransferSyntaxType(TS const &ts);
  TS GetTransferSyntaxType() const;
  TS::MSType GetMediaStorageType() const;
  bool IsEmpty() const { return DS == 0; };

  // Read
  IStream &Read(IStream &is);

  // Write
  OStream &Write(OStream &os) const;

private:
  bool ReadExplicitDataElement(IStream &is, ExplicitDataElement &de);
  bool ReadImplicitDataElement(IStream &is, ImplicitDataElement &de);

  DataSet *DS;
  TS InternalTS;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const FileMetaInformation &val)
{
  if(val.DS)
    {
    const DataSet &ds = *(val.DS);
    os << ds;
    }
  else
    {
    os << "No File Meta Information Header";
    }
  return os;
}

} // end namespace gdcm

#endif //__gdcmFileMetaInformation_h

