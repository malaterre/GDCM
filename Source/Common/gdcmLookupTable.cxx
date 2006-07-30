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
#include "gdcmLookupTable.h"
#include "gdcmIStream.h"
#include "gdcmOStream.h"

#include <vector>

namespace gdcm
{

class LookupTableInternal
{
public:
  LookupTableInternal():RGB()
  {
    Length[0] = Length[1] = Length[2] = 0;
    Subscript[0] = Subscript[1] = Subscript[2] = 0;
    BitSize[0] = BitSize[1] = BitSize[2] = 0;
  }
  unsigned short Length[3];
  unsigned short Subscript[3];
  unsigned short BitSize[3];
  std::vector<unsigned char> RGB;
};

LookupTable::LookupTable()
{
  Internal = new LookupTableInternal;
}

LookupTable::~LookupTable()
{
  delete Internal;
}

void LookupTable::Allocate( int bitsample )
{
if( bitsample == 8 )
  {
  Internal->RGB.resize( 256 * 3 );
  }
  else 
  {
  abort();
  }
}

void LookupTable::InitializeLUT(LookupTableType type, unsigned short length,
    unsigned short subscript, unsigned short bitsize)
  {
switch(type)
{
case RED:
InitializeRedLUT(length, subscript, bitsize);
break;
case GREEN:
InitializeGreenLUT(length, subscript, bitsize);
break;
case BLUE:
InitializeBlueLUT(length, subscript, bitsize);
break;
default:
abort();
}

  }

void LookupTable::SetLUT(LookupTableType type, unsigned char *array)
{
switch(type)
{
case RED:
SetRedLUT(array);
break;
case GREEN:
SetGreenLUT(array);
break;
case BLUE:
SetBlueLUT(array);
break;
default:
abort();
}
}

void LookupTable::InitializeRedLUT(unsigned short length,
unsigned short subscript,
unsigned short bitsize)
  {
  Internal->Length[RED] = length;
  Internal->Subscript[RED] = subscript;
  Internal->BitSize[RED] = bitsize;
  }
void LookupTable::InitializeGreenLUT(unsigned short length,
unsigned short subscript,
unsigned short bitsize)
  {
  Internal->Length[GREEN] = length;
  Internal->Subscript[GREEN] = subscript;
  Internal->BitSize[GREEN] = bitsize;
  }
void LookupTable::InitializeBlueLUT(unsigned short length,
unsigned short subscript,
unsigned short bitsize)
  {
  Internal->Length[BLUE] = length;
  Internal->Subscript[BLUE] = subscript;
  Internal->BitSize[BLUE] = bitsize;
  }

void LookupTable::SetRedLUT(unsigned char *red)
{
  assert( Internal->RGB.size() > Internal->Length[RED] );
  for( int i = 0; i < Internal->Length[RED]; ++i)
  {
  Internal->RGB[3*i+RED] = red[i];
  }
}

void LookupTable::SetGreenLUT(unsigned char *green)
{
  assert( Internal->RGB.size() > Internal->Length[GREEN] );
  for( int i = 0; i < Internal->Length[GREEN]; ++i)
  {
  Internal->RGB[3*i+GREEN] = green[i];
  }
}

void LookupTable::SetBlueLUT(unsigned char *blue)
{
  assert( Internal->RGB.size() > Internal->Length[BLUE] );
  for( int i = 0; i < Internal->Length[BLUE]; ++i)
  {
  Internal->RGB[3*i+BLUE] = blue[i];
  }
}

void LookupTable::Decode(IStream &is, OStream &os)
{
  unsigned char rgb[3];
  char c;
  while( !is.Eof() )
    {
    is.Get(c);
    // FIXME
    if( is.Eof() ) break;
    unsigned char idx(c);
    rgb[RED]   = Internal->RGB[idx+RED];
    rgb[GREEN] = Internal->RGB[idx+GREEN];
    rgb[BLUE]  = Internal->RGB[idx+BLUE];
    os.Write((char*)rgb, 3);
    }
}

} // end namespace gdcm
