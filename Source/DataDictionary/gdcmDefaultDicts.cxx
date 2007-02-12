/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmDefaultDicts_cxx
#define __gdcmDefaultDicts_cxx

#include "gdcmDicts.h"
#include "gdcmVR.h"
#include "gdcmDict.h"
#include "gdcmDictEntry.h"

namespace gdcm
{

typedef struct
{
  uint16_t group;
  uint16_t element;
  VR::VRType vr;
  VM::VMType vm;
  const char *name;
} DICT_ENTRY;

void FillDataDict(Dict &dict, const DICT_ENTRY * const array)
{
   unsigned int i = 0;
   DICT_ENTRY n = array[i];
   while( n.name != 0 )
   {
      Tag t(n.group, n.element);
      DictEntry e( n.name, n.vr, n.vm );
      dict.AddDictEntry( t, e );
      n = array[++i];
   }
//   Tag t(0, 0);
//   DictEntry e( "", (VR::VRType)0, (VM::VMType)0);
//   dict.AddDictEntry( t, e );
}

@DEFAULT_DICTS@

void Dicts::FillDataDicts()
{
  @DEFAULT_DICTS_COMMAND@
}

} // end namespace gdcm

#endif //__gdcmDefaultDicts_cxx
