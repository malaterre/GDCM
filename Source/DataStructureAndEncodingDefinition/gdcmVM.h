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
#ifndef __gdcmVM_h
#define __gdcmVM_h

#include "gdcmTypes.h"
#include <iostream>
/* \brief Value Multiplicity
 * Looking at the DICOMV3 dict only there is very few cases:
 * 1
 * 2
 * 3
 * 4
 * 5
 * 6
 * 8
 * 16
 * 24
 * 1-2
 * 1-3
 * 1-8
 * 1-32
 * 1-99
 * 1-n
 * 2-2n
 * 2-n
 * 3-3n
 * 3-n
 *
 * Some private dict define some more:
 * 4-4n
 * 1-4
 * 1-5
 * 256
 * 11
 * 9
 * 3-4
 */
namespace gdcm
{

class GDCM_EXPORT VM
{
public:
  typedef enum {
    VM0 = 0, // aka the invalid VM
    VM1,
    VM2,
    VM3,
    VM4,
    VM5,
    VM6,
    VM8,
    VM9,
    VM11,
    VM16,
    VM24,
    VM32,
    VM99,
    VM256,
    VM1_2,
    VM1_3,
    VM1_4,
    VM1_5,
    VM1_8,
    VM1_32,
    VM1_99,
    VM1_n,
    VM2_2n,
    VM2_n,
    VM3_4,
    VM3_3n,
    VM3_n,
    VM4_4n,
    VM_END  // Custom tag to count number of entry
  } VMType;

  //friend std::ostream& operator<<(std::ostream& _os, const VRType&_val);

  // Return the string as written in the official DICOM dict from 
  // a custom enum type
  static const char* GetVMString(const VMType &vm);
  static VMType GetVMType(const char *vm);

  // Check if vm1 is valid compare to vm2, i.e vm1 is element of vm2
  // vm1 is typically deduct from counting in a ValueField
  static bool IsValid(const int &vm1, const VMType &vm2);
  //bool IsValid() { return VMField != VM0 && VMField < VM_END; }

  // WARNING: Implementation deficiency
  // The Compatible function is poorly implemented, the reference vm should be coming from
  // the dictionary, while the passed in value is the value guess from the file.
  bool Compatible(VM const &vm) const;

  static VMType GetVMTypeFromLength(unsigned int length, unsigned int size);
  static unsigned int GetNumberOfElementsFromArray(const char *array, unsigned int length);

  VM(VMType type = VM0):VMField(type) {}
  operator VMType () const { return VMField; }
  unsigned int GetLength() const;

  friend std::ostream &operator<<(std::ostream &os, const VM &vm);
private:
  VMType VMField;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const VM &_val)
{
  assert( VM::GetVMString(_val) );
  _os << VM::GetVMString(_val);
  return _os;
}

//template <int TVM> struct LengthToVM;
//template <> struct LengthToVM<1>
//{ enum { TVM = VM::VM1 }; };

template<int T> struct VMToLength;
#define TYPETOLENGTH(type,length) \
  template<> struct VMToLength<VM::type> \
  { enum { Length = length }; };
// TODO: Could be generated from XML file
//TYPETOLENGTH(VM0,1)
TYPETOLENGTH(VM1,1)
TYPETOLENGTH(VM2,2)
TYPETOLENGTH(VM3,3)
TYPETOLENGTH(VM4,4)
TYPETOLENGTH(VM5,5)
TYPETOLENGTH(VM6,6)
TYPETOLENGTH(VM8,8)
TYPETOLENGTH(VM16,16)
TYPETOLENGTH(VM24,24)
//TYPETOLENGTH(VM1_2,2)
//TYPETOLENGTH(VM1_3,3)
//TYPETOLENGTH(VM1_8,8)
//TYPETOLENGTH(VM1_32,32)
//TYPETOLENGTH(VM1_99,99)
//TYPETOLENGTH(VM1_n,
//TYPETOLENGTH(VM2_2n,
//TYPETOLENGTH(VM2_n,
//TYPETOLENGTH(VM3_3n,
//TYPETOLENGTH(VM3_n,

} // end namespace gdcm

#endif //__gdcmVM_h
