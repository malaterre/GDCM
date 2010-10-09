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

namespace gdcm
{
class DataSet;
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

  /// Set DataSet. Write DataSet in implicit. 
  /// \warning size of dataset should be below maxpdusize
  void SetDataSet(const DataSet & ds);
  void SetBlob(const std::string & partialblob);
  std::string GetBlob() const;

  uint8_t GetPresentationContextID() const { return PresentationContextID; }
  void SetPresentationContextID(uint8_t id) {
    PresentationContextID = id;
  }
  uint8_t GetMessageHeader() const {
    assert( MessageHeader <= 0x3 );
    return MessageHeader;
  }
  // E.2 MESSAGE CONTROL HEADER ENCODING
  // Only the first two bits are considered
  void SetMessageHeader(uint8_t messageheader) {
    MessageHeader = messageheader;
  }
  //flip the least significant bit of the message header to 1 
  //if this is a command, else set it to 0.
  void SetCommand(const bool& inCommand);
  void SetLastFragment(const bool& inLast);//set to true if this is the last PDV of a set

  bool GetIsCommand() const;
  bool GetIsLastFragment() const;

  void Print(std::ostream &os) const;

  //NOTE that the PDVs have to be given in the order in which they were received!
  //also note that a dataset may be across multiple PDVs, or that a single PDV could have
  //many datasets.  
  static std::vector<DataSet> ConcatenatePDVBlobs(const std::vector<PresentationDataValue>& inPDVs);

private:
  uint32_t ItemLength;
  uint8_t PresentationContextID;

  // FIXME this should change if the DataSet cannot fit in memory.
  //DataSet DS;
  std::string Blob; // std::vector<char> ??

  uint8_t MessageHeader;
};
} // end namespace network

} // end namespace gdcm

#endif //GDCMPRESENTATIONDATAVALUE_H
