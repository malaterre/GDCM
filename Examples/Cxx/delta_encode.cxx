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
/*
 */

#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "gdcmTypes.h"

void encode_a5(std::vector<char> & output, int value)
{
  assert( value == 0xa5 - 256 );
  output.push_back( 0xa5 );
  //output.push_back( 0x0 );
  //output.push_back( 0xa5 );
}

void encode_5a(std::vector<char> & output, int value)
{
  assert( value == 0x5a );
  output.push_back( 0xa5 );
  output.push_back( 0x01 );
  output.push_back( 0x5a );
}

void encode_div_mod(std::vector<char> & output, int value)
{
  assert( value >= 0 );
  // This is an integer that cannot be stored on a char value, thus store
  // it as modulo and remainder
  int v1 = (int)value % 256;
  int v2 = (int)value / 256;
  assert( v1 >= 0 && v1 <= std::numeric_limits<uint16_t>::max() );
  assert( v2 >= 0 && v2 <= std::numeric_limits<uint16_t>::max() );
//  if( v1 == 0x5a)
//    {
//    output.push_back( 0xa5 );
//    output.push_back( 0x01 );
//    output.push_back( 0x5a );
//    output.push_back( v2 );
//    }
//  else if( v1 == 0xa5 )
//    {
//    // 5A  A5 00 A5 00
//    output.push_back( 0x5a );
//    output.push_back( 0xa5 );
//    output.push_back( 0x00 );
//    output.push_back( 0xa5 );
//    output.push_back( v2 );
//    }
//  else
    {
    output.push_back( 0x5a );
    output.push_back( v1 );
    output.push_back( v2 );
    }
}

void encode_diff_value(std::vector<char> & output, int value)
{
  if( value == 0xa5 - 256 )
    {
    encode_a5(output, value);
    }
  else if( value == 0x5a )
    {
    // happen ?
   // output.push_back( 'M' );
   // output.push_back( 'O' );
   // output.push_back( 'M' );
  output.push_back( 0x5a );
    }
  else if( value <= (int)std::numeric_limits<char>::max() && value >= (int)std::numeric_limits<char>::min() )
    {
    assert( value != 0xa5 - 256 && value != 0x5a && value != 0xa5 );
    //assert( value != 0x3c );
    output.push_back( value );
    //assert( output.size() != 0x3C67 );
    }
  else
    {
    abort();
    }
}

void encode_pixel_value(std::vector<char> & output, unsigned short value)
{
  encode_div_mod(output, value);
}

void foodebug() {}
void delta_encode(unsigned short *inbuffer, size_t length, std::vector<char>& output)
{
  unsigned short prev = 0;

  // Do delta encoding:
  for(unsigned int i = 0; i < length; ++i)
    {
    int diff = (int)inbuffer[i] - prev;
    if( diff <= (int)std::numeric_limits<char>::max() 
      && diff >= (int)std::numeric_limits<char>::min() 
      && diff != 0x5a
    )
      {
      encode_diff_value( output, diff );
      }
    else
      {
      encode_pixel_value( output, inbuffer[i] );
      }
    prev = inbuffer[i];
    }

  // Do Run Length now:
  char prev0 = output[0];
  char prev1 = output[1];
  assert( prev0 != 0xa5 - 256 && prev1 != 0xa5 - 256 );
  for(unsigned int i = 2; i < output.size(); ++i)
    {
if( i == 0xbc0A )
{
foodebug();
}
    if( output[i] == 0xa5 - 256 )
      {
      unsigned int j = 0; // nb repetition
      while( (i+j) < output.size() && output[i+j] == 0xa5 - 256 )
        {
        ++j;
        }
      // insert a5 00 before:
      output.insert( output.begin()+i, 2, 0xa5 );
      output[i+1] = j - 1;
      // remove duplicates
      output.erase( output.begin() + i + 1 + 1, output.begin() + i + 1 + j);
      i+=2;
      }
    else if( output[i] == 0x5a && output[i-1] == 0x5a )
      {
      assert( output[i-1] != 0xc8 - 256 );
      unsigned int j = 0; // nb repetition
      while( (i+j) < output.size() && output[i+j] == 0x5a )
        {
        ++j;
        }
      ++j;
      // insert a5 00 before:
      output.insert( output.begin()+i-1, 2, 0xa5 );
      output[i] = j - 1;
      // remove duplicates
      output.erase( output.begin() + i + 1, output.begin() + i + j);
      i+=2;
      }
    else if( output[i] == output[i-1] && output[i-1] == output[i-2] && output[i-2] != 0xa5 - 256 ) 
      {
      assert( prev0 != 0x5a && prev0 != 0xa5 - 256 );
      unsigned int j = 0; // nb repetition
      while( (i+j) < output.size() && output[i+j] == prev0 )
        {
        ++j;
        }
      ++j; // count cprev too
      // in place:
      //assert( i == 2 || output[i-3] != 0xa5 - 256 );
      //if ( i > 3 ) assert( output[i-3] != 0xa5 - 256 );
      output[i-2] = 0xa5;
      assert( j != 0 && j != 1 );
      output[i-2+1] = j;
      assert( prev0 != 0xa5 - 256 );
      output[i-2+2] = prev0;
      //assert( output[i-2+1] != output[i-2+2] );
      output.erase( output.begin() + i, output.begin() + i - 2 + j);
      // HACK: when the next char is 05A, and 
      // output[i-2+1] == output[i-2+2] 
      // we enter a degenerate case where yet anothre rle is done...
      if( i+1 < output.size() && output[i+1] == 0x5a )
        {
        i+=1;
        }
      }
    else if( output[i] == 0x5a && output[i-1] == output[i-2] ) 
      {
      /*
       * Why would you want to replace 0E 0E with A5 01 0E ???
       * oh well ...
       */
      //assert( output[i-3] != 0xa5 - 256 );
      //assert( output[i-3] != 0x5a );
      //if( output[i-3] == 0xa5 - 256 )
      //  {
      //  //assert( prev0 == 0 );
      //  //output[i-2] = 0x3E;
      //  output[i-2+1] = prev0;
      //  output[i-2+2] = 0x5a;
      //  }
      //else
        {
        output.insert( output.begin()+i-2+2, 1, 'M' );
        output[i-2] = 0xa5;
        output[i-2+1] = 0x01;
        assert( prev0 != 0xa5 - 256 );
        output[i-2+2] = prev0;
        ++i;
        }
      //assert( output[i] == 0x5a || output[i] == 0xa5 - 256 );
      }
    prev0 = output[i-1];
    prev1 = output[i];
    //assert( prev0 != prev1 );
    }

  // DICOM need % 2
  if( output.size() % 2 )
    {
    output.push_back( 0x0 );
    }
  std::cout << output.size() << std::endl;
}

int main(int argc, char *argv [])
{
  if( argc < 2 ) return 1;
  const char *filename = argv[1];

  std::ifstream i( filename );
  const unsigned int size = 131072;
  char *ref = new char [size];
  memset(ref,0,size);
  i.read( ref, size);
  i.close();
  std::vector<char> output;

  delta_encode((unsigned short*)ref, size / 2, output);

  std::ofstream out("comp.rle");
  out.write( &output[0], output.size() );
  out.close();

  return 0;
}

