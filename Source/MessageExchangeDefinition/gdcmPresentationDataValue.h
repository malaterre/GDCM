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

// TODO: MM : does swig handle nested namespace
// I would like to avoid polluting gdcm namespace with such low level details the networ
// primitives:
namespace network
{

/**
 Table 9-23
PRESENTATION-DATA-VALUE ITEM FIELDS
 */
class PresentationDataValue
{
public:
  PresentationDataValue();
  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;
  size_t Size() const;

private:
  uint32_t ItemLength;
  uint8_t PresentationContextID;
  //std::string PresDataValue;
  DataSet DS;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMPRESENTATIONDATAVALUE_H
