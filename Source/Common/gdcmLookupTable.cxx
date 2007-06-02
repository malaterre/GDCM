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
  IncompleteLUT = false;
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
    Internal->RGB.resize( 65536 * 2 * 3 );
    }
  else
    {
    abort();
    }
  BitSample = bitsample;
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
    if( length != 256 )
      {
      IncompleteLUT = true;
      }
    Internal->Length[type] = length;
    }
  Internal->Subscript[type] = subscript;
  Internal->BitSize[type] = bitsize;
}

void LookupTable::SetLUT(LookupTableType type, const unsigned char *array,
  unsigned int length)
{
  if( !IncompleteLUT )
    {
    assert( Internal->RGB.size() == 3*Internal->Length[type]*(BitSample/8) );
    }
  if( BitSample == 8 )
    {
    const unsigned int mult = Internal->BitSize[type]/8;
    assert( Internal->Length[type]*mult == length );
    for( unsigned int i = 0; i < Internal->Length[type]; ++i)
      {
      assert( i*mult+1 < length );
      assert( 3*i+type < Internal->RGB.size() );
      Internal->RGB[3*i+type] = array[i*mult+1];
      }
    }
  else
    {
    assert( Internal->Length[type]*(BitSample/8) == length );
    uint16_t *uchar16 = (uint16_t*)&Internal->RGB[0];
    const uint16_t *array16 = (uint16_t*)array;
    for( unsigned int i = 0; i < Internal->Length[type]; ++i)
      {
      assert( 2*i < length );
      assert( 2*(3*i+type) < Internal->RGB.size() );
      uchar16[3*i+type] = array16[i];
      }
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

void LookupTable::SetRedLUT(const unsigned char *red, unsigned int length)
{
  SetLUT(RED, red, length);
}

void LookupTable::SetGreenLUT(const unsigned char *green, unsigned int length)
{
  SetLUT(GREEN, green, length);
}

void LookupTable::SetBlueLUT(const unsigned char *blue, unsigned int length)
{
  SetLUT(BLUE, blue, length);
}

void LookupTable::Decode(IStream &is, OStream &os)
{
  if ( BitSample == 8 )
    {
    unsigned char idx;
    unsigned char rgb[3];
    while( !is.eof() )
      {
      //is.Get(c);
      is.read( (char*)(&idx), 1);
      // FIXME
      if( is.eof() ) break;
      if( IncompleteLUT )
        {
        assert( idx < Internal->Length[RED] );
        assert( idx < Internal->Length[GREEN] );
        assert( idx < Internal->Length[BLUE] );
        }
      rgb[RED]   = Internal->RGB[3*idx+RED];
      rgb[GREEN] = Internal->RGB[3*idx+GREEN];
      rgb[BLUE]  = Internal->RGB[3*idx+BLUE];
      os.write((char*)rgb, 3 );
      }
    }
  else
    {
    const uint16_t *rgb16 = (uint16_t*)&Internal->RGB[0];
    while( !is.eof() )
      {
      unsigned short idx;
      unsigned short rgb[3];
      is.read( (char*)(&idx), 2);
      //is.Get(c);
      // FIXME
      if( is.eof() ) break;
      if( IncompleteLUT )
        {
        assert( idx < Internal->Length[RED] );
        assert( idx < Internal->Length[GREEN] );
        assert( idx < Internal->Length[BLUE] );
        }
      rgb[RED]   = rgb16[3*idx+RED];
      rgb[GREEN] = rgb16[3*idx+GREEN];
      rgb[BLUE]  = rgb16[3*idx+BLUE];
      os.write((char*)rgb, 3*2);
      }
    }
}

} // end namespace gdcm
