/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmSmartPointer_h
#define __gdcmSmartPointer_h

#include "gdcmObject.h"

namespace gdcm
{
/*
 * \brief Class for Smart Pointer
 * Will only work for subclass of gdcm::Object
 * See tr1/shared_ptr for a more general approach (not invasive)
 * #include <tr1/memory>
 * {
 *   shared_ptr<Bla> b(new Bla);
 * }
 * Class partly based on post by Bill Hubauer:
 * http://groups.google.com/group/comp.lang.c++/msg/173ddc38a827a930
 */

template<class ObjectType>
class SmartPointer
{
public:
  SmartPointer():Pointer(0) {}
  SmartPointer(const SmartPointer<ObjectType>& p):Pointer(p.Pointer)
    { Register(); }
  SmartPointer(ObjectType* p):Pointer(p)
    { Register(); }
  ~SmartPointer() {
    UnRegister();
    Pointer = 0;
  }

  /// Overload operator -> 
  ObjectType *operator -> () const
    { return Pointer; }

  /// Return pointer to object.
  operator ObjectType * () const 
    { return Pointer; }

  /// Overload operator assignment.
  SmartPointer &operator = (SmartPointer const &r)
    { return operator = (r.Pointer); }
  
  /// Overload operator assignment.
  SmartPointer &operator = (ObjectType const *r)
    {                                                              
    if (Pointer != r)
      {
      ObjectType* tmp = Pointer; //important
      Pointer = const_cast<ObjectType*>(r);
      Register();
      if ( tmp ) { tmp->UnRegister(); }
      }
    return *this;
    }

private:
  void Register()
    {
    if(Pointer) { Pointer->Register(); }
    }

  void UnRegister()
    {
    if(Pointer) { Pointer->UnRegister(); }
    }

  ObjectType* Pointer;
};

} // end namespace gdcm

#endif //__gdcmSmartPointer_h

