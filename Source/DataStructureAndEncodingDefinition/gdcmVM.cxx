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
#include "gdcmVM.h"
#include <assert.h>

namespace gdcm
{

static const char *VMStrings[] = {
  "INVALID",
  "1",
  "2",
  "3",
  "4",
  "5",
  "6",
  "8",
  "9",
  "11",
  "16",
  "24",
  "256",
  "1-2",
  "1-3",
  "1-4",
  "1-5",
  "1-8",
  "1-32",
  "1-99",
  "1-n",
  "2-2n",
  "2-n",
  "3-3n",
  "3-n",
  "4-4n",
  0
};

unsigned int VM::GetLength() const
{
  unsigned int len;
  switch(VMField)
    {
  case VM::VM2:
    len = VMToLength<VM::VM2>::Length;
    break;
  default:
    len = 0;
    }
  assert( len );
  return len;
}

const char *VM::GetVMString(const VMType &vm)
{
  assert( vm <= VM_END );
  return VMStrings[(int)vm];
}

VM::VMType VM::GetVMType(const char *vm)
{
  if(!vm) return VM::VM_END;
  if(!*vm) return VM::VM0; // ??
  for (int i = 0; VMStrings[i] != NULL; i++)
    {
    //if (strncmp(VMStrings[i],vm,strlen(VMStrings[i])) == 0)
    if (strcmp(VMStrings[i],vm) == 0)
      {
      return (VM::VMType)(i);
      }
    }

  return VM::VM_END;
}

// FIXME IsValid will only work for VM defined in public dict...
bool VM::IsValid(const int &vm1, const VMType &vm2)
{
  bool r = false;
  assert( vm1 >= 0 ); // Still need to check Part 3
  // If you update the VMType, you need to update this code. Hopefully a compiler is
  // able to tell when a case is missing
  switch(vm2)
    {
  case VM1:
    r = vm1 == 1;
    break;
  case VM2:
    r = vm1 == 2;
    break;
  case VM3:
    r = vm1 == 3;
    break;
  case VM4:
    r = vm1 == 4;
    break;
  case VM5:
    r = vm1 == 5;
    break;
  case VM6:
    r = vm1 == 6;
    break;
  case VM8:
    r = vm1 == 8;
    break;
  case VM16:
    r = vm1 == 16;
    break;
  case VM24:
    r = vm1 == 24;
    break;
  case VM1_2:
    r = (vm1 == 1 || vm1 == 2);
    break;
  case VM1_3:
    r = (vm1 >= 1 && vm1 <= 3);
    break;
  case VM1_8:
    r = (vm1 >= 1 && vm1 <= 8);
    break;
  case VM1_32:
    r = (vm1 >= 1 && vm1 <= 32);
    break;
  case VM1_99:
    r = (vm1 >= 1 && vm1 <= 99);
    break;
  case VM1_n:
    r = (vm1 >= 1);
    break;
  case VM2_2n:
    r = (vm1 >= 2 && !(vm1%2) );
    break;
  case VM2_n:
    r = (vm1 >= 2);
    break;
  case VM3_3n:
    r = (vm1 >= 3 && !(vm1%3) );
    break;
  case VM3_n:
    r = (vm1 >= 3);
    break;
  default:
    assert(0); // should not happen
    }
  return r;
}

// TODO write some ugly macro to expand the template
//int VM::GetLength()
//{
//}

// This function should not be used in production code.
// Indeed this only return a 'guess' at the VM (ie. a lower bound)
VM::VMType VM::GetVMTypeFromLength(unsigned int length, unsigned int size)
{
  // Check first of length is a indeed a multiple of size and that length is != 0
  if ( !length || length % size ) return VM::VM0;
  const unsigned int ratio = length / size;
  //std::cerr << "RATIO=" << ratio << std::endl;
  switch( ratio )
    {
  case 1: return VM::VM1;
  case 2: return VM::VM2;
  case 3: return VM::VM3;
  case 4: return VM::VM4;
  case 5: return VM::VM5;
  case 6: return VM::VM6;
  case 8: return VM::VM8;
  case 16: return VM::VM16;
  case 24: return VM::VM24;
  default:
           return VM::VM1_n;
    }
}

} // end namespace gdcm
