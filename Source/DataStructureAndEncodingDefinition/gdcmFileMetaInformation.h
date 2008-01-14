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

#ifndef __gdcmFileMetaInformation_h
#define __gdcmFileMetaInformation_h

#include "gdcmDataSet.h"
#include "gdcmDataElement.h"
#include "gdcmMediaStorage.h"
#include "gdcmTransferSyntax.h"

namespace gdcm
{
/**
 * \brief Class to represent a File Meta Information
 * \note
 * FileMetaInformation is a Explicit Structured Set.
 * Whenever the file contains an ImplicitDataElement DataSet, a conversion
 * will take place.
 * \todo
 * If user adds an element with group != 0x0002 it will be written...
 */
class GDCM_EXPORT FileMetaInformation : public DataSet
{
public:
  FileMetaInformation():DataSetTS(),MetaInformationTS(TransferSyntax::Unknown),DataSetMS(MediaStorage::MS_END) {}
 ~FileMetaInformation() { };

  friend std::ostream &operator<<(std::ostream &_os, const FileMetaInformation &_val);

  bool IsValid() const { return true; }

  TransferSyntax::NegociatedType GetMetaInformationTS() const { return MetaInformationTS; }
  const TransferSyntax &GetDataSetTransferSyntax() const { return DataSetTS; }
  MediaStorage GetMediaStorage() const;

  // Read
  std::istream &Read(std::istream &is);
  std::istream &ReadCompat(std::istream &is);

  // Write
  std::ostream &Write(std::ostream &os) const;

  // Construct a FileMetaInformation from an already existing DataSet:
  void FillFromDataSet(DataSet const &ds);
 
protected:
  void ComputeDataSetTransferSyntax(); // FIXME

  template <typename TSwap>
  std::istream &ReadCompatInternal(std::istream &is);

  void Default();
  void ComputeDataSetMediaStorageSOPClass();

  TransferSyntax DataSetTS;
  TransferSyntax::NegociatedType MetaInformationTS;
  MediaStorage::MSType DataSetMS;

private:
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const FileMetaInformation &val)
{
  val.Print( os );
  return os;
}

} // end namespace gdcm

#endif //__gdcmFileMetaInformation_h

