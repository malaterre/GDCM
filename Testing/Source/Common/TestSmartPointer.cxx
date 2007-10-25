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
#include "gdcmSmartPointer.h"
#include "gdcmObject.h"

#include <iostream>

using gdcm::Object;
using gdcm::SmartPointer;

class Foo : public Object {
  public:
   void foo() { // Does exist in Object as far as I know :)
     std::cout << "foo" << std::endl;
   }
};

class Containter {
public:
  Containter():Instance(0) {}
  SmartPointer<Object> Instance;
};

void Fill(SmartPointer<Foo> &p)
{
  SmartPointer<Foo> in = new Foo;
  // p = in;
  Foo & rp = *in;
  p = &rp;
}

int TestSmartPointer(int, char *[])
{
  SmartPointer<Object> p = new Object;
  SmartPointer<Foo> p2 = new Foo;
  p2->foo();
  SmartPointer<Object> p3 = new Foo;
  //p3->foo(); // should not compile

  //std::cout << p << std::endl;
  //std::cout << p2 << std::endl;
  //std::cout << p3 << std::endl;
  
  if( p == p2
   || p == p3
   || p2 == p3 )
    {
    return 1;
    }

  // SmartPointer
  SmartPointer<Foo> p4 = p2;
  SmartPointer<Object> p5 = p3;

  // Pointer:
  SmartPointer<Foo> p6 = &(*p2);
  
  SmartPointer<Foo> p7;
  Fill(p7);
  Foo &foo = *p7;
  foo.foo();

  Containter c1;
  Containter c2;
  c2 = c1;

  // TODO:
  //SmartPointer<Object> s = new Foo;
  //delete s;

  return 0;
}
