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
#ifndef __gdcmCSAElement_h
#define __gdcmCSAElement_h

#include "gdcmTag.h"
#include "gdcmVM.h"
#include "gdcmVR.h"
#include "gdcmByteValue.h"
#include "gdcmSmartPointer.h"

namespace gdcm
{
/**
 * \brief Class to represent a CSA Element
 */

class GDCM_EXPORT CSAElement
{
public:
  CSAElement() {}

  friend std::ostream& operator<<(std::ostream &os, const CSAElement &val);

  // Set/Get Key
  unsigned int GetKey() const { return KeyField; }
  void SetKey(unsigned int key) { KeyField = key; }

  // Set/Get Name
  const char *GetName() const { return NameField.c_str(); }
  void SetName(const char *name) { NameField = name; }

  // Set/Get VM
  const VM& GetVM() const { return ValueMultiplicityField; }
  void SetVM(const VM &vm) { ValueMultiplicityField = vm; }

  // Set/Get VR
  VR const &GetVR() const { return VRField; }
  void SetVR(VR const &vr) { VRField = vr; }

  // Set/Get SyngoDT
  unsigned int GetSyngoDT() const { return SyngoDTField; }
  void SetSyngoDT(unsigned int syngodt) { SyngoDTField = syngodt; }

  // Set/Get NoOfItems
  unsigned int GetNoOfItems() const { return NoOfItemsField; }
  void SetNoOfItems(unsigned int items) { NoOfItemsField = items; }

  // Set/Get Value (bytes array, SQ of items, SQ of fragments):
  Value const &GetValue() const { return *DataField; }
  Value &GetValue() { return *DataField; }
  void SetValue(Value const & vl) {
    //assert( DataField == 0 );
    DataField = &vl;
  }
  bool IsEmpty() const { return DataField == 0; }
  void SetByteValue(const char *array, VL length)
  {
    ByteValue *bv = new ByteValue(array,length);
    SetValue( *bv );
  }
  CSAElement(const CSAElement &_val)
    {
    if( this != &_val)
      {
      *this = _val;
      }
    }

  bool operator<(const CSAElement &de) const
    {
    return GetKey() < de.GetKey();
    }
  CSAElement &operator=(const CSAElement &de)
    {
    KeyField = de.KeyField;
    NameField = de.NameField;
    ValueMultiplicityField = de.ValueMultiplicityField;
    VRField = de.VRField;
    SyngoDTField = de.SyngoDTField;
    //ValueField = de.ValueField; // Pointer copy
    return *this;
    }

  bool operator==(const CSAElement &de) const
    {
    return KeyField == de.KeyField
      && NameField == de.NameField
      && ValueMultiplicityField == de.ValueMultiplicityField
      && VRField == de.VRField
      && SyngoDTField == de.SyngoDTField
      //&& ValueField == de.ValueField;
      ;
    }

protected:
  unsigned int KeyField;
  std::string NameField;
  VM ValueMultiplicityField;
  VR VRField;
  unsigned int SyngoDTField;
  unsigned int NoOfItemsField;
  typedef SmartPointer<Value> DataPtr;
  DataPtr DataField;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const CSAElement &val)
{
  os << val.KeyField;
  os << "\t" << val.VRField;
  //os << "\t" << val.ValueLengthField;
  if( val.DataField )
    {
    val.DataField->Print( os << "\t" );
    }
  return os;
}

} // end namespace gdcm

#endif //__gdcmCSAElement_h

