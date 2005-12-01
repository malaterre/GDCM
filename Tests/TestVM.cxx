#include "gdcmVM.h"
#include <iostream>
#include <string>

int TestVM(int , char *[])
{
  int n = (int)gdcm::VM::VM_END;
  gdcm::VM::VMType vm;
  for(int i=0; i<n; ++i)
    {
    vm = (gdcm::VM::VMType)i;
    std::cout << vm << "\t->\t" << gdcm::VM::GetVMString(vm) << std::endl;
    }
  //    VM1,
  vm = gdcm::VM::VM1;
  if( !gdcm::VM::IsValid(1, vm) )
    return 1;
  if( gdcm::VM::IsValid(2, vm) )
    return 1;
  //    VM2,
  vm = gdcm::VM::VM2;
  if( !gdcm::VM::IsValid(2, vm) )
    return 1;
  if( gdcm::VM::IsValid(1, vm) )
    return 1;
  //    VM3,
  vm = gdcm::VM::VM3;
  if( !gdcm::VM::IsValid(3, vm) )
    return 1;
  if( gdcm::VM::IsValid(1, vm) )
    return 1;
  //    VM4,
  vm = gdcm::VM::VM4;
  if( !gdcm::VM::IsValid(4, vm) )
    return 1;
  if( gdcm::VM::IsValid(1, vm) )
    return 1;
  //    VM5,
  vm = gdcm::VM::VM5;
  if( !gdcm::VM::IsValid(5, vm) )
    return 1;
  if( gdcm::VM::IsValid(1, vm) )
    return 1;
  //    VM6,
  vm = gdcm::VM::VM6;
  if( !gdcm::VM::IsValid(6, vm) )
    return 1;
  if( gdcm::VM::IsValid(1, vm) )
    return 1;
  //    VM8,
  vm = gdcm::VM::VM8;
  if( !gdcm::VM::IsValid(8, vm) )
    return 1;
  if( gdcm::VM::IsValid(1, vm) )
    return 1;
  //    VM16,
  vm = gdcm::VM::VM16;
  if( !gdcm::VM::IsValid(16, vm) )
    return 1;
  if( gdcm::VM::IsValid(1, vm) )
    return 1;
  //    VM24,
  vm = gdcm::VM::VM24;
  if( !gdcm::VM::IsValid(24, vm) )
    return 1;
  if( gdcm::VM::IsValid(1, vm) )
    return 1;
  //    VM1_2,
  vm = gdcm::VM::VM1_2;
  if( !gdcm::VM::IsValid(1, vm) )
    return 1;
  if( !gdcm::VM::IsValid(2, vm) )
    return 1;
  if( gdcm::VM::IsValid(3, vm) )
    return 1;
  //    VM1_3,
  vm = gdcm::VM::VM1_3;
  if( !gdcm::VM::IsValid(1, vm) )
    return 1;
  if( !gdcm::VM::IsValid(3, vm) )
    return 1;
  if( gdcm::VM::IsValid(4, vm) )
    return 1;
  //    VM1_8,
  vm = gdcm::VM::VM1_8;
  if( !gdcm::VM::IsValid(1, vm) )
    return 1;
  if( !gdcm::VM::IsValid(8, vm) )
    return 1;
  if( gdcm::VM::IsValid(9, vm) )
    return 1;
  //    VM1_32,
  vm = gdcm::VM::VM1_32;
  if( !gdcm::VM::IsValid(1, vm) )
    return 1;
  if( !gdcm::VM::IsValid(32, vm) )
    return 1;
  if( gdcm::VM::IsValid(33, vm) )
    return 1;
  //    VM1_99,
  vm = gdcm::VM::VM1_99;
  if( !gdcm::VM::IsValid(1, vm) )
    return 1;
  if( !gdcm::VM::IsValid(99, vm) )
    return 1;
  if( gdcm::VM::IsValid(100, vm) )
    return 1;
  //    VM1_n,
  vm = gdcm::VM::VM1_n;
  if( !gdcm::VM::IsValid(1, vm) )
    return 1;
  if( !gdcm::VM::IsValid(99, vm) )
    return 1;
  //    VM2_2n,
  vm = gdcm::VM::VM2_2n;
  if( !gdcm::VM::IsValid(2, vm) )
    return 1;
  if( !gdcm::VM::IsValid(20, vm) )
    return 1;
  if( gdcm::VM::IsValid(1, vm) )
    return 1;
  //    VM2_n,
  vm = gdcm::VM::VM2_n;
  if( !gdcm::VM::IsValid(2, vm) )
    return 1;
  if( !gdcm::VM::IsValid(21, vm) )
    return 1;
  if( gdcm::VM::IsValid(1, vm) )
    return 1;
  //    VM3_3n,
  vm = gdcm::VM::VM3_3n;
  if( !gdcm::VM::IsValid(3, vm) )
    return 1;
  if( !gdcm::VM::IsValid(30, vm) )
    return 1;
  if( gdcm::VM::IsValid(31, vm) )
    return 1;
  if( gdcm::VM::IsValid(32, vm) )
    return 1;
  //    VM3_n,
  vm = gdcm::VM::VM3_n;
  if( !gdcm::VM::IsValid(3, vm) )
    return 1;
  if( !gdcm::VM::IsValid(30, vm) )
    return 1;
  if( !gdcm::VM::IsValid(31, vm) )
    return 1;
  if( !gdcm::VM::IsValid(32, vm) )
    return 1;

  // From const char * back and forth
  std::string s = "2-2n";
  vm = gdcm::VM::GetVMType( s.c_str() );
  if( s != gdcm::VM::GetVMString(vm) )
    return 1;
  s = "2-3n";  // invalid
  vm = gdcm::VM::GetVMType( s.c_str() );
  if( vm != gdcm::VM::VM_END )
    return 1;
  if( gdcm::VM::GetVMString(vm) != 0 )
    return 1;

  vm = gdcm::VM::GetVMType("1-8");
  if( vm == gdcm::VM::VM1 )
    return 1;

  return 0;
}
