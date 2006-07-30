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
  assert( type >= RED && type <= BLUE );
  assert( length != 0 );
  assert( subscript == 0 );
  assert( bitsize == 8 || bitsize == 16 );
  Internal->Length[type] = length;
  Internal->Subscript[type] = subscript;
  Internal->BitSize[type] = bitsize;
  }

void LookupTable::SetLUT(LookupTableType type, unsigned char *array)
{
 // dummy assert need some work:
  assert( Internal->RGB.size() > Internal->Length[type] );
  for( int i = 0; i < Internal->Length[type]; ++i)
  {
  Internal->RGB[3*i+type] = array[i];
  }
}

void LookupTable::InitializeRedLUT(unsigned short length,
unsigned short subscript,
unsigned short bitsize)
  {
  InitializeLUT(RED, length, subscript, bitsize);
  }
void LookupTable::InitializeGreenLUT(unsigned short length,
unsigned short subscript,
unsigned short bitsize)
  {
  InitializeLUT(GREEN, length, subscript, bitsize);
  }
void LookupTable::InitializeBlueLUT(unsigned short length,
unsigned short subscript,
unsigned short bitsize)
  {
  InitializeLUT(BLUE, length, subscript, bitsize);
  }

void LookupTable::SetRedLUT(unsigned char *red)
{
  SetLUT(RED, red);
}

void LookupTable::SetGreenLUT(unsigned char *green)
{
  SetLUT(GREEN, green);
}

void LookupTable::SetBlueLUT(unsigned char *blue)
{
  SetLUT(BLUE, blue);
}

void LookupTable::Decode(IStream &is, OStream &os)
{
  char c;
  if ( Internal->BitSize[RED] == 16 )
    {
  unsigned char rgb[3];
  while( !is.Eof() )
    {
    is.Get(c);
    // FIXME
    if( is.Eof() ) break;
    unsigned char idx(c);
    rgb[RED]   = Internal->RGB[2*idx+1+RED];
    rgb[GREEN] = Internal->RGB[2*idx+1+GREEN];
    rgb[BLUE]  = Internal->RGB[2*idx+1+BLUE];
    os.Write((char*)rgb, 3 );
    }
    }
    else
    {
  while( !is.Eof() )
    {
  unsigned char rgb[3];
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
}

} // end namespace gdcm
