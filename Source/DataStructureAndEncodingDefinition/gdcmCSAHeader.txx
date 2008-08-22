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
#ifndef __gdcmCSAHeader_txx
#define __gdcmCSAHeader_txx

#include "gdcmByteValue.h"

namespace gdcm
{

  template <typename TDE, typename TSwap>
  std::istream &CSAHeader::Read(std::istream &is) {
    return is;
  }


  template <typename TDE, typename TSwap>
  std::ostream const &CSAHeader::Write(std::ostream &os) const {
    return os;
  }
} // end namespace gdcm

#endif // __gdcmCSAHeader_txx

