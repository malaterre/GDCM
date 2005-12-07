#ifndef __gdcmDICOMType_h
#define __gdcmDICOMType_h

#include "gdcmType.h"
#include "gdcmVR.h"
#include "gdcmVM.h"
#include <string>
#include <vector>
#include <sstream>

namespace gdcm
{

template<int T> struct TypeEnumToType;
template<> struct TypeEnumToType<VR::FL>
{ typedef float Type; };
template<> struct TypeEnumToType<VR::FD>
{ typedef double Type; };
template<> struct TypeEnumToType<VR::SL>
{ typedef int32_t Type; };
template<> struct TypeEnumToType<VR::SS>
{ typedef int16_t Type; };
template<> struct TypeEnumToType<VR::UL>
{ typedef uint32_t Type; };
template<> struct TypeEnumToType<VR::US>
{ typedef uint16_t Type; };

template<int T> struct ValueEnumToLength;
template<> struct ValueEnumToLength<VM::VM1>
{ enum { Len = 1 }; };
template<> struct ValueEnumToLength<VM::VM2>
{ enum { Len = 2 }; };
template<> struct ValueEnumToLength<VM::VM3>
{ enum { Len = 3 }; };
template<> struct ValueEnumToLength<VM::VM4>
{ enum { Len = 4 }; };
template<> struct ValueEnumToLength<VM::VM5>
{ enum { Len = 5 }; };
template<> struct ValueEnumToLength<VM::VM6>
{ enum { Len = 6 }; };
template<> struct ValueEnumToLength<VM::VM8>
{ enum { Len = 8 }; };
template<> struct ValueEnumToLength<VM::VM16>
{ enum { Len = 16 }; };
template<> struct ValueEnumToLength<VM::VM24>
{ enum { Len = 24 }; };
template<> struct ValueEnumToLength<VM::VM1_32>
{ enum { Len = 32 }; };
template<> struct ValueEnumToLength<VM::VM1_99>
{ enum { Len = 99 }; };
//template<> struct ValueEnumToLength<VM::VM1_n>
//{ enum { Len = 3 }; };
//FIXME TODO: 2-2n and 3-3n...

template<int TVR, int TVM>
class GDCM_EXPORT DICOMType
{
public:
  typename TypeEnumToType<TVR>::Type Internal[ValueEnumToLength<TVM>::Len];

  void Print(std::ostream &_os) const {
    _os << Internal[0]; // VM is at least garantee to be one
    for(int i=1; i<ValueEnumToLength<TVM>::Len; ++i)
      _os << "," << Internal[i];
    _os << std::endl;
    }

  void Read(std::istream &_is) {
    _is >> Internal[0];
    for(int i=1; i<ValueEnumToLength<TVM>::Len; ++i)
      {
      assert( _is );
      _is.get();
      _is >> Internal[i];
      }
    }

  void Write(std::ostream &os) const {
    os << Internal[0];
    for(int i=1; i<ValueEnumToLength<TVM>::Len; ++i)
      {
      os << "\\" << Internal[i];
      }
    }
};

/*
template<int TVR, VM::VM1_n>
class GDCM_EXPORT DICOMType
{
public:
  typename TypeEnumToType<TVR>::Type *Internal;
  DICOMType(TypeEnumToType<TVR>::Type *p)
    {
    Internal = new TypeEnumToType<TVR>::Type[]
    for(int i=1; i<ValueEnumToLength<TVM>::Len; ++i)
    }

  void Print(std::ostream &_os)
    {
    _os << Internal[0]; // VM is at least garantee to be one
    for(int i=1; i<ValueEnumToLength<TVM>::Len; ++i)
      _os << "," << Internal[i];
    _os << std::endl;
    }

  const std::string GetAsDICOM() const {
    std::ostringstream os;
    os << Internal[0];
    for(int i=1; i<ValueEnumToLength<TVM>::Len; ++i)
      {
      os << "\\" << Internal[i];
      }
    return os.str().c_str(); }
};
*/

}

#endif //__gdcmDICOMType_h
