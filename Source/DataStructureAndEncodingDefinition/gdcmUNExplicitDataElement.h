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
#ifndef __gdcmUNExplicitDataElement_h
#define __gdcmUNExplicitDataElement_h

#include "gdcmDataElement.h"

namespace gdcm
{
// Data Element (UNExplicit)
/**
 * \brief Class to read/write a DataElement as UNExplicit Data Element
 * \note bla
 */
class GDCM_EXPORT UNExplicitDataElement : public DataElement
{
public:
  VL GetLength() const;

  template <typename TSwap>
  std::istream &Read(std::istream &is);

  template <typename TSwap>
  const std::ostream &Write(std::ostream &os) const;
};

} // end namespace gdcm

#include "gdcmUNExplicitDataElement.txx"

#endif //__gdcmUNExplicitDataElement_h

