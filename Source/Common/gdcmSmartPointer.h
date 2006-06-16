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

  // Overload operator -> 
  ObjectType *operator -> () const
    { return Pointer; }

  // Return pointer to object.
  operator ObjectType * () const 
    { return Pointer; }

  // Overload operator assignment.
  SmartPointer &operator = (const SmartPointer &r)
    { return operator = (r.Pointer); }
  
  // Overload operator assignment.
  SmartPointer &operator = (ObjectType *r)
    {                                                              
    if (Pointer != r)
      {
      ObjectType* tmp = Pointer; //important
      Pointer = r;
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
