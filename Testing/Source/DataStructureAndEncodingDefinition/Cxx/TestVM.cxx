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

int TestVM(int, char *[])
{
  //gdcm::VM::VMType vm = gdcm::LengthToVM<1>::TVM;

  const char str1[] = " 1\\2";
  unsigned int count1 = gdcm::VM::GetNumberOfElementsFromArray(str1, strlen(str1) );
  if( count1 != 2 ) return 1;

  const char str2[] = "  1\\2\\3";
  unsigned int count2 = gdcm::VM::GetNumberOfElementsFromArray(str2, strlen(str2) );
  if( count2 != 3 ) return 1;

  const char str3[] = "   1";
  unsigned int count3 = gdcm::VM::GetNumberOfElementsFromArray(str3, strlen(str3) );
  if( count3 != 1 ) return 1;

  const char str4[] = "";
  unsigned int count4 = gdcm::VM::GetNumberOfElementsFromArray(str4, strlen(str4) );
  if( count4 != 0 ) return 1;

  const char *str5 = 0;
  unsigned int count5 = gdcm::VM::GetNumberOfElementsFromArray(str5, 0);
  if( count5 != 0 ) return 1;

  const char str6[] = "   1";
  unsigned int count6 = gdcm::VM::GetNumberOfElementsFromArray(str6, strlen(str6) );
  if( count6 != 1 ) return 1;

  const char str7[] = "   1 \\   2  ";
  unsigned int count7 = gdcm::VM::GetNumberOfElementsFromArray(str7, strlen(str7) );
  if( count7 != 2 ) return 1;

  const char str8[] = "   ";
  unsigned int count8 = gdcm::VM::GetNumberOfElementsFromArray(str8, strlen(str8) );
  if( count8 != 0 ) 
    {
    std::cerr << "count8 failed" << std::endl;
    return 1;
    }

  const char str9[] = "     \\      ";
  unsigned int count9 = gdcm::VM::GetNumberOfElementsFromArray(str9, strlen(str9) );
  if( count9 != 0 ) return 1;

  const char str10[] = "   3  \\      ";
  unsigned int count10 = gdcm::VM::GetNumberOfElementsFromArray(str10, strlen(str10) );
  if( count10 != 1 ) return 1;

  if( gdcm::VM::VM1 & gdcm::VM::VM2 ) return 1;
  if( gdcm::VM::VM1 & gdcm::VM::VM3 ) return 1;
  if( gdcm::VM::VM1 & gdcm::VM::VM32 ) return 1;

  if( !(gdcm::VM::VM1 & gdcm::VM::VM1_2) ) return 1;
  if( !(gdcm::VM::VM2 & gdcm::VM::VM1_2) ) return 1;

  if( !(gdcm::VM::VM1 & gdcm::VM::VM1_3) ) return 1;
  if( !(gdcm::VM::VM2 & gdcm::VM::VM1_3) ) return 1;
  if( !(gdcm::VM::VM3 & gdcm::VM::VM1_3) ) return 1;

  if( !(gdcm::VM::VM1 & gdcm::VM::VM1_n) ) return 1;

  if( gdcm::VM::VM1 & gdcm::VM::VM2_n ) return 1;
  if( !(gdcm::VM::VM2 & gdcm::VM::VM2_n) ) return 1;

  if( gdcm::VM::VM1 & gdcm::VM::VM3_4 ) return 1;
  if( !(gdcm::VM::VM3 & gdcm::VM::VM3_4) ) return 1;
  if( !(gdcm::VM::VM4 & gdcm::VM::VM3_4) ) return 1;

  if( gdcm::VM::VM1 & gdcm::VM::VM3_3n ) return 1;
  if( !(gdcm::VM::VM3 & gdcm::VM::VM3_3n) ) return 1;
  if( !(gdcm::VM::VM9 & gdcm::VM::VM3_3n) ) return 1;
  if( !(gdcm::VM::VM99 & gdcm::VM::VM3_3n) ) return 1;

  if( gdcm::VM::VM1 & gdcm::VM::VM4_4n ) return 1;
  if( !(gdcm::VM::VM4 & gdcm::VM::VM4_4n) ) return 1;

  const char *vm1 = gdcm::VM::GetVMString( gdcm::VM::VM1 );
  if( strcmp(vm1, "1" ) != 0 )
    {
    std::cerr << "Error:" << vm1 << std::endl;
    return 1;
    }

  const char *vm8 = gdcm::VM::GetVMString( gdcm::VM::VM8 );
  if( strcmp(vm8, "8" ) != 0 )
    {
    std::cerr << "Error:" << vm8 << std::endl;
    return 1;
    }


  return 0;
}

