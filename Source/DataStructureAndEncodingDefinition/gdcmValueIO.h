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

#ifndef __gdcmValueIO_h
#define __gdcmValueIO_h

// FIXME
#include "gdcmIStream.h"
#include "gdcmOStream.h"

namespace gdcm
{
/**
 * \brief Class to represent the value of a Data Element.
 * \note
 * VALUE: A component of a Value Field. A Value Field may consist of one
 * or more of these components.
 */
template <typename DE, typename TSwap>
class GDCM_EXPORT ValueIO
{
public:
  static IStream &Read(IStream &is, Value& v);

  static const OStream &Write(OStream &os, const Value& v);
};


} // end namespace gdcm

#include "gdcmValueIO.txx"

#endif //__gdcmValue_h

