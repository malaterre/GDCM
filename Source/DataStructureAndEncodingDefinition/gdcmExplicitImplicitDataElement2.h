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
#ifndef __gdcmExplicitImplicitDataElement2_h
#define __gdcmExplicitImplicitDataElement2_h

#include "gdcmDataElement.h"

namespace gdcm
{
// Data Element (ExplicitImplicit2)
/**
 * \brief Class to read/write a DataElement as ExplicitImplicit Data Element
 * \note This only happen for some Philips images
 * Should I derive from ExplicitDataElement instead ?
 */
class GDCM_EXPORT ExplicitImplicitDataElement2 : public DataElement
{
public:
  VL GetLength() const;

  template <typename TSwap>
  std::istream &Read(std::istream &is);

  // PURPOSELY do not provide an implementation for writing !
  //template <typename TSwap>
  //const std::ostream &Write(std::ostream &os) const;
};

} // end namespace gdcm

#include "gdcmExplicitImplicitDataElement2.txx"

#endif //__gdcmExplicitImplicitDataElement2_h

