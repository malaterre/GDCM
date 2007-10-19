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
 * FileMetaInformation is a Explicit Structured Set.
 * Whenever the file contains an ImplicitDataElement StructuredSet, a conversion
 * will take place.
 * \todo
 * If user adds an element with group != 0x0002 it will be written...
 */
class GDCM_EXPORT FileMetaInformation : public StructuredSet<ExplicitDataElement>
{
public:
  FileMetaInformation():DataSetTS(),MetaInformationTS(TS::Unknown),DataSetMS(TS::MS_END) {}
 ~FileMetaInformation() { };

  friend std::ostream &operator<<(std::ostream &_os, const FileMetaInformation &_val);

  bool IsValid() const { return true; }

  TS::NegociatedType GetMetaInformationTS() const { return MetaInformationTS; }
  const TS &GetDataSetTransferSyntax() const { return DataSetTS; }
  TS::MSType GetMediaStorageType() const;

  // Read
  IStream &Read(IStream &is);
  IStream &ReadCompat(IStream &is);

  // Write
  OStream &Write(OStream &os) const;

  // Construct a FileMetaInformation from an already existing DataSet:
  void FillFromDataSet(DataSet const &ds);
 
  void ComputeDataSetTransferSyntax(); // FIXME
protected:
  void Default();
  void ComputeDataSetMediaStorageSOPClass();

  TS DataSetTS;
  TS::NegociatedType MetaInformationTS;
  TS::MSType DataSetMS;

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

