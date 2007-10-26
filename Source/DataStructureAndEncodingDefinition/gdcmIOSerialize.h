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

#ifndef __gdcmIOSerialize_h
#define __gdcmIOSerialize_h

#include "gdcmTypes.h"
#include "gdcmIStream.h"
#include "gdcmOStream.h"

namespace gdcm
{
/**
 * \brief Class
 * \note TODO rename IOSerialize into Serialize 
 */

class Tag;
class VL;
class ExplicitDataElement;
class Value;
class ByteValue;
class BasicOffsetTable;
class Fragment;
class SequenceOfFragments;
class DataSet;

template <typename TSwap>
class GDCM_EXPORT IOSerialize
{
public:
  static IStream &Read(IStream &is,DataSet &ds);
  static OStream const &Write(OStream &os,DataSet const &ds);

};

} // end namespace gdcm

#endif //__gdcmIOSerialize_h

