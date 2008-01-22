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
#ifndef __gdcmElement_h
#define __gdcmElement_h

#include "gdcmTypes.h"
#include "gdcmVR.h"
#include "gdcmTag.h"
#include "gdcmVM.h"
#include "gdcmByteValue.h"

#include <string>
#include <vector>
#include <sstream>

namespace gdcm
{

// Declaration, also serve as forward declaration
template<int T> class EncodingImplementation;

template<int TVR, int TVM>
class Element
{
public:
  typename VRToType<TVR>::Type Internal[VMToLength<TVM>::Length];

  unsigned long GetLength() const {
    return VMToLength<TVM>::Length;
  }
  // Implementation of Print is common to all Mode (ASCII/Binary)
  // TODO: Can we print a \ when in ASCII...well I don't think so
  // it would mean we used a bad VM then, right ?
  void Print(std::ostream &_os) const {
    _os << Internal[0]; // VM is at least garantee to be one
    for(int i=1; i<VMToLength<TVM>::Length; ++i)
      _os << "," << Internal[i];
    }

  typename VRToType<TVR>::Type GetValue(unsigned int idx = 0) const {
    assert( idx < VMToLength<TVM>::Length );
    return Internal[idx];
  }
  typename VRToType<TVR>::Type operator[] (unsigned int idx) const {
    return GetValue(idx);
  }
  void SetValue(typename VRToType<TVR>::Type v, unsigned int idx = 0) {
    assert( idx < VMToLength<TVM>::Length );
    Internal[idx] = v;
  }
  void Set(Value const &v) {
    const ByteValue *bv = dynamic_cast<const ByteValue*>(&v);
    assert( bv ); // That would be bad...
    //memcpy(Internal, bv->GetPointer(), bv->GetLength());
    std::stringstream ss;
    std::string s = std::string( bv->GetPointer(), bv->GetLength() );
    ss.str( s );
    EncodingImplementation<VRToEncoding<TVR>::Mode>::Read(Internal, 
      GetLength(),ss);
  }

  void Read(std::istream &_is) {
    return EncodingImplementation<VRToEncoding<TVR>::Mode>::Read(Internal, 
      GetLength(),_is);
    }
  void Write(std::ostream &_os) const {
    return EncodingImplementation<VRToEncoding<TVR>::Mode>::Write(Internal, 
      GetLength(),_os);
    }
};


// Implementation to perform formatted read and write
template<> class EncodingImplementation<VR::ASCII> {
public:
  template<typename T> // FIXME this should be VRToType<TVR>::Type
  static inline void Read(T* data, unsigned long length,
                          std::istream &_is) {
    assert( data );
    assert( length ); // != 0
    assert( _is );
    _is >> data[0];
    char sep;
    //std::cout << "GetLength: " << af->GetLength() << std::endl;
    for(unsigned long i=1; i<length;++i) {
      assert( _is );
      // Get the separator in between the values
      _is.get(sep);
      assert( sep == '\\' ); // FIXME: Bad use of assert
      _is >> data[i];
      }
    }

  template<typename T>
  static inline void Write(const T* data, unsigned long length,
                           std::ostream &_os)  {
    assert( data );
    assert( length );
    assert( _os );
    _os << data[0];
    for(unsigned long i=1; i<length; ++i) {
      assert( _os );
      _os << "\\" << data[i];
      }
    }
};


// Implementation to perform binary read and write
// TODO rewrite operation so that either:
// #1. dummy implementation use a pointer to Internal and do ++p (faster)
// #2. Actually do some meta programming to unroll the loop 
// (no notion of order in VM ...)
template<> class EncodingImplementation<VR::BINARY> {
public:
  template<typename T>
  static inline void Read(T* data, unsigned long length,
    std::istream &_is) {
    const unsigned int type_size = sizeof(T);
    assert( data ); // Can we read from pointer ?
    assert( length );
    assert( _is ); // Is stream valid ?
    _is.read( reinterpret_cast<char*>(data+0), type_size);
    for(unsigned long i=1; i<length; ++i) {
      assert( _is );
      _is.read( reinterpret_cast<char*>(data+i), type_size );
    }
    //ByteSwap<T>::SwapRangeFromSwapCodeIntoSystem(data,
    //  _is.GetSwapCode(), length);
  }
  template<typename T>
  static inline void Write(const T* data, unsigned long length,
    std::ostream &_os) { 
    const unsigned int type_size = sizeof(T);
    assert( data ); // Can we write into pointer ?
    assert( length );
    assert( _os ); // Is stream valid ?
    //ByteSwap<T>::SwapRangeFromSwapCodeIntoSystem((T*)data,
    //  _os.GetSwapCode(), length);
    _os.write( reinterpret_cast<const char*>(&(data[0])), type_size);
    for(unsigned long i=1; i<length;++i) {
      assert( _os );
      _os.write( reinterpret_cast<const char*>(&(data[i])), type_size );
    }
    //ByteSwap<T>::SwapRangeFromSwapCodeIntoSystem((T*)data,
    //  _os.GetSwapCode(), length);
  }
};

// For particular case for ASCII string
// WARNING: This template explicitely instanciates a particular 
// EncodingImplementation THEREFORE it is required to be declared after the
// EncodingImplementation is needs (doh!)
#if 0
template<int TVM>
class Element<TVM>
{
public:
  Element(const char array[])
    {
    unsigned int i = 0;
    const char sep = '\\';
    std::string sarray = array;
    std::string::size_type pos1 = 0;
    std::string::size_type pos2 = sarray.find(sep, pos1+1);
    while(pos2 != std::string::npos)
      {
      Internal[i++] = sarray.substr(pos1, pos2-pos1);
      pos1 = pos2+1;
      pos2 = sarray.find(sep, pos1+1);
      } 
    Internal[i] = sarray.substr(pos1, pos2-pos1);
    // Shouldn't we do the contrary, since we know how many separators
    // (and default behavior is to discard anything after the VM declared
    assert( GetLength()-1 == i );
    }

  unsigned long GetLength() const {
    return VMToLength<TVM>::Length;
  }
  // Implementation of Print is common to all Mode (ASCII/Binary)
  void Print(std::ostream &_os) const {
    _os << Internal[0]; // VM is at least garantee to be one
    for(int i=1; i<VMToLength<TVM>::Length; ++i)
      _os << "," << Internal[i];
    }

  void Read(std::istream &_is) {
    EncodingImplementation<VR::ASCII>::Read(Internal, GetLength(),_is);
    }
  void Write(std::ostream &_os) const {
    EncodingImplementation<VR::ASCII>::Write(Internal, GetLength(),_os);
    }
private:
  typename String Internal[VMToLength<TVM>::Length];
};

template< int TVM>
class Element<VR::PN, TVM> : public StringElement<TVM>
{
};
#endif

// Implementation for the undefined length (dynamically allocated array) 
template<int TVR>
class Element<TVR, VM::VM1_n>
{
public:
  // This the way to prevent default initialization
  explicit Element() { Internal=0; Length=0; Save = false; }
  ~Element() {
    if( Save ) {
      delete[] Internal;
    }
    Internal = 0;
  }

  // Length manipulation
  // SetLength should really be protected anyway...all operation
  // should go through SetArray
  unsigned long GetLength() const { return Length; }
  typedef typename VRToType<TVR>::Type ArrayType;
  void SetLength(unsigned long len) {
    const unsigned int size = sizeof(ArrayType);
    if( len ) {
      if( len > Length ) {
        // perform realloc
        assert( (len / size) * size == len );
        ArrayType *internal = new ArrayType[len / size];
        if( Internal )
          {
          memcpy(internal, Internal, len);
          delete[] Internal;
          }
        Internal = internal;
        }
      }
    Length = len / size;
  }

  // If save is set to zero user should not delete the pointer
  //void SetArray(const typename VRToType<TVR>::Type *array, int len, bool save = false) 
  void SetArray(const ArrayType *array, unsigned long len,
    bool save = false) {
    if( save ) {
      SetLength(len); // realloc
      memcpy(Internal, array, len/*/sizeof(ArrayType)*/);
      }
    else {
      // TODO rewrite this stupid code:
      assert( Length == 0 );
      assert( Internal == 0 );
      Length = len / sizeof(ArrayType);
      Internal = const_cast<ArrayType*>(array);
      //abort();
      }
      Save = save;
  }
  void SetValue(typename VRToType<TVR>::Type v, unsigned int idx = 0) {
    assert( idx < Length );
    Internal[idx] = v;
  }
  typename VRToType<TVR>::Type GetValue(unsigned int idx = 0) const {
    assert( idx < Length );
    return Internal[idx];
  }
  typename VRToType<TVR>::Type operator[] (unsigned int idx) const {
    return GetValue(idx);
  }
  void Set(Value const &v) {
    const ByteValue *bv = dynamic_cast<const ByteValue*>(&v);
    assert( bv ); // That would be bad...
    const ArrayType* array = (ArrayType*)bv->GetPointer();
    assert( array ); // That would be bad...
    assert( Internal == 0 );
    //assert( VR::IsBinary( VR(TVR) ) );
    SetArray(array, bv->GetLength() );
  }

  // Need to be placed after definition of EncodingImplementation<VR::ASCII>
  void WriteASCII(std::ostream &os) const {
    return EncodingImplementation<VR::ASCII>::Write(Internal, GetLength(), os);
    }

  // Implementation of Print is common to all Mode (ASCII/Binary)
  void Print(std::ostream &_os) const {
    assert( Length );
    assert( Internal );
    _os << Internal[0]; // VM is at least garantee to be one
    const unsigned long length = GetLength() < 25 ? GetLength() : 25;
    for(unsigned long i=1; i<length; ++i)
      _os << "," << Internal[i];
    }
  void Read(std::istream &_is) {
    assert( Internal ); // FIXME
    EncodingImplementation<VRToEncoding<TVR>::Mode>::Read(Internal, 
      GetLength(),_is);
    }
  void Write(std::ostream &_os) const {
    EncodingImplementation<VRToEncoding<TVR>::Mode>::Write(Internal, 
      GetLength(),_os);
    }

  Element(const Element&_val) {
    if( this != &_val) {
      *this = _val;
      }
    }

  Element &operator=(const Element &_val) {
    Length = 0; // SYITF
    Internal = 0;
    SetArray(_val.Internal, _val.Length, true);
    return *this;
    }

private:
  typename VRToType<TVR>::Type *Internal;
  unsigned long Length; // unsigned int ??
  bool Save;
};

//template <int TVM = VM::VM1_n>
//class Element<VR::OB, TVM > : public Element<VR::OB, VM::VM1_n> {};

// Partial specialization for derivatives of 1-n : 2-n, 3-n ...
template<int TVR>
class Element<TVR, VM::VM2_n> : public Element<TVR, VM::VM1_n>
{
public:
  typedef Element<TVR, VM::VM1_n> Parent;
  void SetLength(int len) {
    if( len <= 1 ) return;
    Parent::SetLength(len);
  }
};
template<int TVR>
class Element<TVR, VM::VM2_2n> : public Element<TVR, VM::VM2_n>
{
public:
  typedef Element<TVR, VM::VM2_n> Parent;
  void SetLength(int len) {
    if( len % 2 ) return;
    Parent::SetLength(len);
  }
};
template<int TVR>
class Element<TVR, VM::VM3_n> : public Element<TVR, VM::VM1_n>
{
public:
  typedef Element<TVR, VM::VM1_n> Parent;
  void SetLength(int len) {
    if( len <= 2 ) return;
    Parent::SetLength(len);
  }
};
template<int TVR>
class Element<TVR, VM::VM3_3n> : public Element<TVR, VM::VM3_n>
{
public:
  typedef Element<TVR, VM::VM3_n> Parent;
  void SetLength(int len) {
    if( len % 3 ) return;
    Parent::SetLength(len);
  }
};


//template<int T> struct VRToLength;
//template <> struct VRToLength<VR::AS>
//{ enum { Length  = VM::VM1 }; }
//template<>
//class Element<VR::AS> : public Element<VR::AS, VRToLength<VR::AS>::Length >

// only 0010 1010 AS 1 Patient’s Age
template<>
class Element<VR::AS, VM::VM5>
{
public:
  char Internal[VMToLength<VM::VM5>::Length];
  void Print(std::ostream &_os) const {
    _os << Internal;
    }
  unsigned long GetLength() const {
    return VMToLength<VM::VM5>::Length;
  }
};

template <>
class Element<VR::OB, VM::VM1> : public Element<VR::OB, VM::VM1_n> {};
// Make it impossible to compile any other cases:
template <int TVM> class Element<VR::OB, TVM>;

// Same for OW:
template <>
class Element<VR::OW, VM::VM1> : public Element<VR::OW, VM::VM1_n> {};
// Make it impossible to compile any other cases:
template <int TVM> class Element<VR::OW, TVM>;

} // namespace gdcm

#endif //__gdcmElement_h
