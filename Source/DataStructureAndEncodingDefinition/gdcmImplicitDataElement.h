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

#ifndef __gdcmImplicitDataElement_h
#define __gdcmImplicitDataElement_h

#include "gdcmDataElement.h"
#include "gdcmByteValue.h"
#include "gdcmSmartPointer.h"

namespace gdcm
{
/**
 * \brief Class to represent an *Implicit VR* Data Element
 * \note bla
 */
class Value;
class GDCM_EXPORT ImplicitDataElement : public DataElement
{
  template <typename TSwap> friend class IOSerialize;
public:
  ImplicitDataElement(const Tag& t = Tag(0), uint32_t const &vl = 0) : DataElement(t,vl),ValueField(0) {}
  ~ImplicitDataElement();

  friend std::ostream& operator<<(std::ostream& _os, const ImplicitDataElement &_val);

  Value const & GetValue() const { return *ValueField; }
  void SetValue(Value const & vl) { ValueField = const_cast<Value*>(&vl); }

  VL GetLength() const;

  template <typename TSwap>
    IStream &Read(IStream& is);
  template <typename TSwap>
    const OStream &Write(OStream& os) const;

  ImplicitDataElement(ImplicitDataElement const & val):DataElement(val)
    {
    //assert( val.ValueField );
//    if( ValueField )
//      {
      ValueField = val.ValueField;
//      }
//    else
//      {
//      assert( !val.ValueField );
//      }
    }

//  ImplicitDataElement(ExplicitDataElement const &val);

private:
  typedef SmartPointer<Value> ValuePtr;
  ValuePtr ValueField;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const ImplicitDataElement &val)
{
  const DataElement &de = val;
  os << de;
  if( val.ValueField )
    {
    const Value& v = *(val.ValueField);
    // could not get operator<< to work on references (no dynamic type)
    v.Print(os << "\t");
    }
  return os;
}

} // end namespace gdcm

#include "gdcmImplicitDataElement.txx"

#endif //__gdcmImplicitDataElement_h
