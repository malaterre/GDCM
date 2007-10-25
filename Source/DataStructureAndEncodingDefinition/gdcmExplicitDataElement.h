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
#include "gdcmVR.h"
#include "gdcmSwapCode.h"
#include "gdcmByteValue.h"
#include "gdcmSmartPointer.h"

namespace gdcm
{
// Data Element (Explicit)
/**
 * \brief Class to represent an *Explicit VR* Data Element
 * \note bla
 */
//class Value; // FIXME
class ImplicitDataElement;
class GDCM_EXPORT ExplicitDataElement : public DataElement
{
  template <typename TSwap> friend class IOSerialize;
  friend class ImplicitDataElement;
public:
  ExplicitDataElement(const Tag &t = Tag(0), uint32_t const &vl = 0,
                      const VR &vr = VR::INVALID ) :
    DataElement(t,vl),VRField(vr),ValueField(0) { }
  ~ExplicitDataElement();

  friend std::ostream& operator<<(std::ostream &_os, const ExplicitDataElement &_val);

  VR const &GetVR() const { return VRField; }
  void SetVR(VR const &vr) { VRField = vr; }

  Value const &GetValue() const { return *ValueField; }
  void SetValue(Value const & vl) {
    //assert( ValueField == 0 );
    ValueField = &vl;
  }
  void SetByteValue(const char *array, VL length)
  {
  ByteValue *bv = new ByteValue(array,length);
  SetVL( length );
  SetValue( *bv );
   }

  VL GetLength() const;

//  template <typename TSwap>
//  IStream &Read(IStream &is);
//
//  template <typename TSwap>
//  const OStream &Write(OStream &_os) const;

  ExplicitDataElement(ExplicitDataElement const &val):DataElement(val)
    {
    //assert( val.ValueField );
    VRField    = val.VRField;
    ValueField = val.ValueField;
    }

  ExplicitDataElement(ImplicitDataElement const &val);

private:
  // Value Representation
  VR VRField;
  //typedef std::tr1::shared_ptr<gdcm::Value> ValuePtr;
  typedef SmartPointer<Value> ValuePtr;
  ValuePtr ValueField;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const ExplicitDataElement &val)
{
  os << "Tag: " << val.TagField;
  os << "\tVR=" << val.VRField;
  os << "\tVL: " << val.ValueLengthField;
  if( val.ValueField )
    {
    val.ValueField->Print( os << "\t" );
    }
  return os;
}

} // end namespace gdcm

#endif //__gdcmExplicitDataElement_h

