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
#ifndef __gdcmObject_h
#define __gdcmObject_h

#include "gdcmTypes.h"
#include <assert.h>
#include <iostream> // grrrr

//namespace std { class ostream; }
namespace gdcm
{
class Object
{
public:
  friend std::ostream& operator<<(std::ostream &os, const Object &obj);

  Object():ReferenceCount(0) {}

  // If I move ~Object in the protected section I can prevent people
  // from writing:
  // SmartPointer<Object> p = new Object;
  // delete p; // due to SmartPointer::operator ObjectType * () const 
  // but on the other hand one could not define an Object on the stack
  // Object obj;
  // Furthermore it would not prevent anyone from doing:
  // class MyObject : public Object {};
  // SmartPointer<MyObject> o = new MyObject;
  // delete o; // grrrrrr
  virtual ~Object()
    {
    // If your debugger reach here it means you are doing something silly
    // like using SmartPointer on object allocated on the stack (vs heap)
    assert(ReferenceCount == 0 );
    }

  // For the purpose of the invasive SmartPointer implementation
  void Register() {
    ReferenceCount++;
  }
  void UnRegister()
    {
    ReferenceCount--;
    if(!ReferenceCount)
      {
      delete this;
      }
    }


//protected:
  // For dealing with printing of object and polymorphism
  virtual void Print(std::ostream &) const {};

private:
  long ReferenceCount;
};

//----------------------------------------------------------------------------
// function do not carry vtable. Thus define in the base class the operator
// and use the member function ->Print() to call the appropriate function
// NOTE: All subclass of Value needs to implement the Print function
inline std::ostream& operator<<(std::ostream &os, const Object &obj)
{
  obj.Print(os);
  return os;
}

} // end namespace gdcm

#endif //__gdcmObject_h

