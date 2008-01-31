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

  const char str1[] = "1\\2";
  unsigned int count1 = gdcm::VM::GetNumberOfElementsFromArray(str1, strlen(str1) );
  if( count1 != 2 ) return 1;

  const char str2[] = "1\\2\\3";
  unsigned int count2 = gdcm::VM::GetNumberOfElementsFromArray(str2, strlen(str2) );
  if( count2 != 3 ) return 1;

  const char str3[] = "1";
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
  if( count8 != 0 ) return 1;

  return 0;
}
