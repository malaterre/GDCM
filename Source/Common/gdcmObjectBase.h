/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmObjectBase_h
#define __gdcmObjectBase_h

#include "gdcmTypes.h"

#include <assert.h>
#include <iostream> // grrrr

//namespace std { class ostream; }
namespace gdcm
{

template<class ObjectBaseType> class SmartPointer;

/**
 * \brief ObjectBase
 *
 * \note main superclass for object that want to use SmartPointer
 * invasive ref counting system
 *
 * \see SmartPointer
 */
class GDCM_EXPORT ObjectBase
{
  template <class ObjectBaseType> friend class SmartPointer;
  friend std::ostream& operator<<(std::ostream &os, const ObjectBase &obj);

public:
  ObjectBase():ReferenceCount(0) {}

  // Implementation note:
  // If I move ~ObjectBase in the protected section I can prevent people
  // from writing:
  // SmartPointer<ObjectBase> p = new ObjectBase;
  // delete p; // due to SmartPointer::operator ObjectBaseType * () const 
  // but on the other hand one could not define an ObjectBase on the stack
  // ObjectBase obj;
  // Furthermore it would not prevent anyone from doing:
  // class MyObjectBase : public ObjectBase {};
  // SmartPointer<MyObjectBase> o = new MyObjectBase;
  // delete o; // grrrrrr
  virtual ~ObjectBase() {
    // If your debugger reach here it means you are doing something silly
    // like using SmartPointer on object allocated on the stack (vs heap)
    assert(ReferenceCount == 0);
    }

  // http://www.parashift.com/c++-faq-lite/freestore-mgmt.html#faq-16.24
  // Set the ref count to 0
  // Do NOT copy the reference count !
  /// Special requirement for copy/cstor, assigment operator
  ObjectBase(const ObjectBase&):ReferenceCount(0){}
  void operator=(const ObjectBase&){}

protected:
  // For the purpose of the invasive SmartPointer implementation
  void Register() {
    ReferenceCount++;
    assert( ReferenceCount > 0 );
  }
  void UnRegister() {
    assert( ReferenceCount > 0 );
    ReferenceCount--;
    if(!ReferenceCount)
      {
      delete this;
      }
    }

public:
  // For dealing with printing of object and polymorphism
  virtual void Print(std::ostream &) const {}

private:
  long ReferenceCount;
};

//----------------------------------------------------------------------------
// function do not carry vtable. Thus define in the base class the operator
// and use the member function ->Print() to call the appropriate function
// NOTE: All subclass of ObjectBase needs to implement the Print function
inline std::ostream& operator<<(std::ostream &os, const ObjectBase &obj)
{
  obj.Print(os);
  return os;
}

} // end namespace gdcm

#endif //__gdcmObjectBase_h

