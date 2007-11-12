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

#ifndef __gdcmExplicitDataElement_h
#define __gdcmExplicitDataElement_h

#include "gdcmDataElement.h"

namespace gdcm
{
// Data Element (Explicit)
/**
 * \brief Class to read/write a DataElement as Explicit Data Element
 * \note bla
 */
class GDCM_EXPORT ExplicitDataElement : public DataElement
{
public:
  VL GetLength() const;

  template <typename TSwap>
  IStream &Read(IStream &is);

  template <typename TSwap>
  const OStream &Write(OStream &os) const;
};

} // end namespace gdcm

#include "gdcmExplicitDataElement.txx"

#endif //__gdcmExplicitDataElement_h

