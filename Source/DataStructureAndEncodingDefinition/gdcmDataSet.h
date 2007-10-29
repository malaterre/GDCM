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
#ifndef __gdcmDataSet_h
#define __gdcmDataSet_h

#include "gdcmTS.h"
#include "gdcmValue.h"
#include "gdcmDataElement.h"
#include "gdcmStructuredSet.h"

namespace gdcm
{
/**
 * \brief Class to represent a Data Set (which contains Data Elements)
 * A Data Set represents an instance of a real world Information Object
 * \note
 * DATA SET: 
 * Exchanged information consisting of a structured set of Attribute values
 * directly or indirectly related to Information Objects. The value of each
 * Attribute in a Data Set is expressed as a Data Element.
 * A collection of Data Elements ordered by increasing Data Element Tag 
 * number that is an encoding of the values of Attributes of a real world 
 * object.
 * \note
 * Implementation note. If one do:
 * DataSet ds;
 * ds.SetLength(0);
 * ds.Read(is);
 * setting length to 0 actually means try to read is as if it was a root
 * DataSet. Other value are undefined (nested dataset with undefined length)
 * or defined length (different from 0) means nested dataset with defined
 * length.
 */
class ExplicitDataElement;
class GDCM_EXPORT DataSet : public Value
{
  template <typename TSwap> friend class IOSerialize;
public:
  DataSet(TS::NegociatedType type = TS::Explicit);
  ~DataSet();

  // Clear
  void Clear();

  bool IsValid() { return true; }

  // Read
//  template <typename TSwap>
//  IStream &Read(IStream &is);
//
//  // Write
//  template <typename TSwap>
//  OStream const &Write(OStream &os) const;

  VL GetLength() const;
  void SetLength(VL l) { 
    Length = l; 
  }

  void InsertDataElement(ExplicitDataElement const &de);
  const ExplicitDataElement& GetDataElement(const Tag &t) const;
  bool FindDataElement(const Tag &t) const;

  DataSet &operator = (DataSet const &r);
  DataSet(DataSet const &ds);

  void Print(std::ostream &os) const;

  const StructuredSet<ExplicitDataElement> &GetInternal() const { return Internal; }

  // TODO
  // This function should not be in the public API:
  void SetType(TS::NegociatedType type) { NegociatedTS = type; }

private:
  TS::NegociatedType NegociatedTS;
  StructuredSet<ExplicitDataElement> Internal;

  VL Length;
};
//-----------------------------------------------------------------------------

} // end namespace gdcm

#endif //__gdcmDataSet_h

