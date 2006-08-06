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
  unsigned int Length[3]; // In DICOM the length is specified on a short
  // but 65536 is expressed as 0 ... 
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
  else if ( bitsample == 16 )
    {
    Internal->RGB.resize( 65536 * 3 );
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
  assert( subscript == 0 );
  assert( bitsize == 8 || bitsize == 16 );
  if( length == 0 )
    {
    Internal->Length[type] = 65536;
    }
  else
    {
    Internal->Length[type] = length;
    }
  Internal->Subscript[type] = subscript;
  Internal->BitSize[type] = bitsize;
}

void LookupTable::SetLUT(LookupTableType type, unsigned char *array,
  unsigned int length)
{
  // dummy assert need some work:
  assert( Internal->RGB.size() == 3*Internal->Length[type] );
  const unsigned int mult = Internal->BitSize[type]/8;
  assert( Internal->Length[type]*mult == length );
  for( unsigned int i = 0; i < Internal->Length[type]; ++i)
    {
    assert( i*mult+1 < length );
    assert( 3*i+type < Internal->RGB.size() );
    Internal->RGB[3*i+type] = array[i*mult+1];
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

void LookupTable::SetRedLUT(unsigned char *red, unsigned int length)
{
  SetLUT(RED, red, length);
}

void LookupTable::SetGreenLUT(unsigned char *green, unsigned int length)
{
  SetLUT(GREEN, green, length);
}

void LookupTable::SetBlueLUT(unsigned char *blue, unsigned int length)
{
  SetLUT(BLUE, blue, length);
}

void LookupTable::Decode(IStream &is, OStream &os)
{
  char c;
  if ( Internal->BitSize[RED] == 16 )
    {
    unsigned char idx;
    unsigned char rgb[3];
    while( !is.Eof() )
      {
      //is.Get(c);
      is.Read( (char*)(&idx), 1);
      // FIXME
      if( is.Eof() ) break;
      rgb[RED]   = Internal->RGB[3*idx+RED];
      rgb[GREEN] = Internal->RGB[3*idx+GREEN];
      rgb[BLUE]  = Internal->RGB[3*idx+BLUE];
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
      rgb[RED]   = Internal->RGB[3*idx+RED];
      rgb[GREEN] = Internal->RGB[3*idx+GREEN];
      rgb[BLUE]  = Internal->RGB[3*idx+BLUE];
      os.Write((char*)rgb, 3);
      }
    }
}

} // end namespace gdcm
