/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMPRESENTATIONDATAVALUE_H
#define GDCMPRESENTATIONDATAVALUE_H

#include "gdcmTypes.h"
#include "gdcmDataSet.h"

namespace gdcm
{
class File;

namespace network
{

/**
 Table 9-23
PRESENTATION-DATA-VALUE ITEM FIELDS
 */
class GDCM_EXPORT PresentationDataValue
{
public:
  PresentationDataValue();
  std::istream &Read(std::istream &is);
  std::istream &ReadInto(std::istream &is, std::ostream &os);

  const std::ostream &Write(std::ostream &os) const;

  /// \internal Compute Size
  size_t Size() const;

  /// Get DataSet
  void SetDataSet(const DataSet & ds);
  DataSet const &GetDataSet() const { return DS; }

  void MyInit(File const &file);
  void MyInit2(File const &file);
  void MyInit3();

  uint8_t GetPresentationContextID() const { return PresentationContextID; }
  void SetPresentationContextID(uint8_t id) {
    PresentationContextID = id;
  }
  uint8_t GetMessageHeader() const {
    return MessageHeader;
  }
  void SetMessageHeader(uint8_t messageheader) {
    MessageHeader = messageheader;
  }
  void Print(std::ostream &os) const;

private:
  uint32_t ItemLength;
  uint8_t PresentationContextID;
  DataSet DS;

  uint8_t MessageHeader;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMPRESENTATIONDATAVALUE_H
