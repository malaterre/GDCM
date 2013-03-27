/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmServiceClassApplicationInformation.h"

namespace gdcm
{
namespace network
{

ServiceClassApplicationInformation::ServiceClassApplicationInformation()
{
  InternalArray[0] = 3; // Level of Support
  InternalArray[1] = 0; // Reserved
  InternalArray[2] = 0; // Level of Digital Signature support
  InternalArray[3] = 0; // Reserved
  InternalArray[4] = 2; // Element coercion
  InternalArray[5] = 0; // Reserved
}

std::istream &ServiceClassApplicationInformation::Read(std::istream &is)
{
  is.read( InternalArray, sizeof(InternalArray) );
  return is;
}

const std::ostream &ServiceClassApplicationInformation::Write(std::ostream &os) const
{
  os.write( InternalArray, sizeof(InternalArray) );
  return os;
}

size_t ServiceClassApplicationInformation::Size() const
{
  return 6;
}

void ServiceClassApplicationInformation::Print(std::ostream &os) const
{
  os << "ServiceClassApplicationInformation: " << std::endl;
  os << " Level of Support: " << (int)InternalArray[0] << std::endl;
  os << " Level of Digital Signature support: " << (int)InternalArray[2] << std::endl;
  os << " Element coercion: " << (int)InternalArray[4] << std::endl;
}

void ServiceClassApplicationInformation::SetTuple(uint8_t levelofsupport, uint8_t levelofdigitalsig, uint8_t elementcoercion)
{
  InternalArray[0] = levelofsupport;
  InternalArray[2] = levelofdigitalsig;
  InternalArray[4] = elementcoercion;
}

} // end namespace network
} // end namespace gdcm
