#ifndef __gdcmAttributeFactory_h
#define __gdcmAttributeFactory_h

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
//template<> struct TypeEnumToType<VR::AS>
//{ typedef char Type[4]; };

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
class GDCM_EXPORT AttributeFactory
{
public:
  typename TypeEnumToType<TVR>::Type Internal[ValueEnumToLength<TVM>::Len];

  int GetLength() const {
    return ValueEnumToLength<TVM>::Len;
  }
  void Print(std::ostream &_os) const {
    _os << Internal[0]; // VM is at least garantee to be one
    for(int i=1; i<ValueEnumToLength<TVM>::Len; ++i)
      _os << "," << Internal[i];
    //_os << std::endl;
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

template<int TVR>
class GDCM_EXPORT AttributeFactory<TVR, VM::VM1_n>
{
public:
  typename TypeEnumToType<TVR>::Type *Internal;
  int Length;
  // FIXME is this the way to prevent default initialization
  explicit AttributeFactory() { Internal=0; Length=0; }

  int GetLength() const { return Length; }
  void SetLength(int len) { 
    if (len<0) return;
    if( len ) {
      if( len > Length ) {
        // perform realloc
        typename TypeEnumToType<TVR>::Type *internal = 
          new typename TypeEnumToType<TVR>::Type[len];
        memcpy(internal, Internal, Length);
        delete[] Internal;
        Internal = internal;
        }
      }
    Length = len;
  }

  // If save is set to zero user should not delete the pointer
  //void SetArray(const typename TypeEnumToType<TVR>::Type *array, int len, bool save = false) {
  void SetArray(typename TypeEnumToType<TVR>::Type *array, int len, bool save = false) {
    if( save ) {
      SetLength(len); // realloc
      memcpy(Internal, array, len);
      }
    else {
      Length = len;
      Internal = array;
      }
  }

  void Print(std::ostream &_os) const {
    if( !Internal ) return;
    _os << Internal[0]; // VM is at least garantee to be one
    for(int i=1; i<Length; ++i)
      _os << "," << Internal[i];
    //_os << std::endl;
    }

  void Read(std::istream &_is) {
    if( !Internal ) return;
    _is >> Internal[0];
    for(int i=1; i<Length; ++i) {
      assert( _is );
      _is.get();
      _is >> Internal[i];
      }
    }

  void Write(std::ostream &_os) const {
    if( !Internal ) return;
    _os << Internal[0]; // VM is at least garantee to be one
    for(int i=1; i<Length; ++i)
      _os << "\\" << Internal[i];
    }

  AttributeFactory(const AttributeFactory&_val) {
    if( this != &_val) {
      *this = _val;
      }
    }

  AttributeFactory &operator=(const AttributeFactory &_val) {
    Length = 0; // SYITF
    Internal = 0;
    SetArray(_val.Internal, _val.Length, true);
    return *this;
    }
};

template <>
class GDCM_EXPORT AttributeFactory<VR::UL, VM::VM1_n>
{
public:
  TypeEnumToType<VR::UL>::Type *Internal;
  int Length;
  // FIXME is this the way to prevent default initialization
  explicit AttributeFactory() { Internal=0; Length=0; }

  int GetLength() const { return Length; }
  void SetLength(int len) { 
    if (len<0) return;
    if( len ) {
      if( len > Length ) {
        // perform realloc
        TypeEnumToType<VR::UL>::Type *internal = 
          new TypeEnumToType<VR::UL>::Type[len];
        memcpy(internal, Internal, Length);
        delete[] Internal;
        Internal = internal;
        }
      }
    Length = len;
  }

  // If save is set to zero user should not delete the pointer
  //void SetArray(const typename TypeEnumToType<TVR>::Type *array, int len, bool save = false) {
  void SetArray(TypeEnumToType<VR::UL>::Type *array, int len, bool save = false) {
    if( save ) {
      SetLength(len); // realloc
      memcpy(Internal, array, len);
      }
    else {
      Length = len;
      Internal = array;
      }
  }

  void Print(std::ostream &_os) const {
    if( !Internal ) return;
    _os << Internal[0]; // VM is at least garantee to be one
    for(int i=1; i<Length; ++i)
      _os << "," << Internal[i];
    //_os << std::endl;
    }

  void Read(std::istream &_is) {
    if( !Internal ) return;
    _is.read( reinterpret_cast<char*>(&Internal[0]), 4 );
    for(int i=1; i<Length/4; ++i) {
      assert( _is );
      _is.get();
      _is.read( reinterpret_cast<char*>(&Internal[i]), 4 );
      }
    }

  void Write(std::ostream &_os) const {
    if( !Internal ) return;
    _os << Internal[0]; // VM is at least garantee to be one
    for(int i=1; i<Length; ++i)
      _os << "\\" << Internal[i];
    }

  AttributeFactory(const AttributeFactory&_val) {
    if( this != &_val) {
      *this = _val;
      }
    }

  AttributeFactory &operator=(const AttributeFactory &_val) {
    Length = 0; // SYITF
    Internal = 0;
    SetArray(_val.Internal, _val.Length, true);
    return *this;
    }
//public:
//  void SetLength(int len) { abort(); }
//  void Read(std::istream &_is)
//    {
//    abort();
//    }
//  void Print(std::ostream &_os) const { }
};

template<int TVR>
class GDCM_EXPORT AttributeFactory<TVR, VM::VM2_n> : public AttributeFactory<TVR, VM::VM1_n>
{
public:
  typedef AttributeFactory<TVR, VM::VM1_n> Superclass;
  void SetLength(int len) {
    if( len <= 1 ) return;
    Superclass::SetLength(len);
  }
};
template<int TVR>
class GDCM_EXPORT AttributeFactory<TVR, VM::VM2_2n> : public AttributeFactory<TVR, VM::VM2_n>
{
public:
  typedef AttributeFactory<TVR, VM::VM2_n> Superclass;
  void SetLength(int len) {
    if( len % 2 ) return;
    Superclass::SetLength(len);
  }
};
template<int TVR>
class GDCM_EXPORT AttributeFactory<TVR, VM::VM3_n> : public AttributeFactory<TVR, VM::VM1_n>
{
public:
  typedef AttributeFactory<TVR, VM::VM1_n> Superclass;
  void SetLength(int len) {
    if( len <= 2 ) return;
    Superclass::SetLength(len);
  }
};
template<int TVR>
class GDCM_EXPORT AttributeFactory<TVR, VM::VM3_3n> : public AttributeFactory<TVR, VM::VM3_n>
{
public:
  typedef AttributeFactory<TVR, VM::VM3_n> Superclass;
  void SetLength(int len) {
    if( len % 3 ) return;
    Superclass::SetLength(len);
  }
};

//template<int TVM>
//class GDCM_EXPORT AttributeFactoryChar
//{
//public:
//  //char *Internal[ValueEnumToLength<TVM>::Len];
//  char Internal[5];
//};
//
//template<int TVM>
//class GDCM_EXPORT AttributeFactory<VR::AS, TVM> : public AttributeFactoryChar<TVM>
//{
//};

}

#endif //__gdcmAttributeFactory_h
