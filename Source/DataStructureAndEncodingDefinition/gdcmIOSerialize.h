/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
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
class Item;
class SequenceOfItems;
class DataSet;

template <typename TSwap>
class GDCM_EXPORT IOSerialize
{
public:
  static IStream &Read(IStream &is,Tag &t);
  static const OStream &Write(OStream &os,Tag const &t);

  static IStream &Read(IStream &is,VL & vl);
  static IStream &Read16(IStream &is,VL & vl);
  static const OStream &Write(OStream &os, VL const &vl);
  static const OStream &Write16(OStream &os, VL const &vl);

  static IStream &Read(IStream &is,ExplicitDataElement &xde);
  static const OStream &Write(OStream &os, ExplicitDataElement const &xde);

  static IStream &Read(IStream &is,ImplicitDataElement &ide);
  static const OStream &Write(OStream &os, ImplicitDataElement const &ide);

  static IStream &Read(IStream &is,Value &v);
  static const OStream &Write(OStream &os,Value const &v);

  static IStream &Read(IStream &is,ByteValue &bv);
  static OStream const &Write(OStream &os,ByteValue const &bv);

  static IStream &Read(IStream &is,BasicOffsetTable &bot);
  static OStream &Write(OStream &os,BasicOffsetTable const &bot);

  static IStream &Read(IStream &is,Fragment &frag);
  static OStream &Write(OStream &os, Fragment const &frag);

  static IStream& Read(IStream &is, SequenceOfFragments &sf);
  static OStream const &Write(OStream &os, SequenceOfFragments const &sf);

  static IStream &Read(IStream &is, Item &item);
  static const OStream &Write(OStream &os, Item const & item);

  static IStream &Read(IStream &is, SequenceOfItems &si);
  static OStream const &Write(OStream &os,SequenceOfItems const &si);

  static IStream &Read(IStream &is,DataSet &ds);
  static OStream const &Write(OStream &os,DataSet const &ds);

  template <typename DEType>
  static IStream &Read(IStream &is,StructuredSet<DEType> &ss);
  template <typename DEType>
  static IStream &ReadWithLength(IStream &is, StructuredSet<DEType> &ss, VL &length);
  template <typename DEType>
  static IStream &ReadNested(IStream &is, StructuredSet<DEType> &ss);
  template <typename DEType>
  static OStream const &Write(OStream &os,StructuredSet<DEType> const &ss);
};

} // end namespace gdcm

#endif //__gdcmIOSerialize_h

