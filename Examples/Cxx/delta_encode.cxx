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

void encode_a5(std::vector<char> & output, int value)
{
  assert( value == 0xa5 - 256 );
  output.push_back( 0xa5 );
  output.push_back( 0x0 );
  output.push_back( 0xa5 );
}

void encode_5a(std::vector<char> & output, int value)
{
  assert( value == 0x5a );
  output.push_back( 0xa5 );
  output.push_back( 0x01 );
  output.push_back( 0x5a );
}

void encode_value(std::vector<char> & output, int value)
{
  if( value == 0xa5 - 256 )
    {
    encode_a5(output, value);
    }
  else if( value == 0x5a )
    {
    encode_5a(output, value);
    }
  else if( value <= 0x7f && value >= -0x80 )
    {
    assert( value != 0xa5 - 256 && value != 0x5a );
    output.push_back( value );
    }
  else
    {
    assert( value >= 0 );
    // This is an integer that cannot be stored on a char value, thus store
    // it as modulo and remainder
    int v1 = (int)value % 256;
    int v2 = (int)value / 256;
    assert( v1 >= 0 && v1 <= std::numeric_limits<uint16_t>::max() );
    assert( v2 >= 0 && v2 <= std::numeric_limits<uint16_t>::max() );
    output.push_back( 0x5a );
    //assert( v1 != 0xa5 - 256 && v1 != 0xa5 );
    output.push_back( v1 );
    output.push_back( v2 );
    }
}

void encode_diff(std::vector<char> & output, unsigned short current, unsigned short prev)
{
}

void delta_encode(unsigned short *inbuffer, size_t length)
{
  std::vector<char> output;
  unsigned short prev = 0;

  // Do delta encoding:
  for(unsigned int i = 0; i < length; ++i)
    {
    int diff = (int)inbuffer[i] - prev;
    if( diff <= std::numeric_limits<char>::max() && diff >= std::numeric_limits<char>::min() )
      {
      encode_value( output, diff );
      }
    else
      {
      encode_value( output, inbuffer[i] );
      }
    prev = inbuffer[i];
    }

  // Do Run Length now:
  char prev0 = output[0];
  char prev1 = output[1];
  for(unsigned int i = 2; i < output.size(); ++i)
    {
    if( output[i] == prev1 && prev1 == prev0 ) 
      {
      unsigned int j = 0; // nb repetition
      while( (i+j) < output.size() && output[i+j] == prev0 )
        {
        ++j;
        }
      ++j; // count cprev too
      // in place:
      //assert( i == 2 || output[i-3] != 0xa5 - 256 );
      output[i-2] = 0xa5;
      assert( j != 0 && j != 1 );
      output[i-2+1] = j;
      assert( prev0 != 0xa5 - 256 );
      output[i-2+2] = prev0;
      output.erase( output.begin() + i, output.begin() + i - 2 + j);
      }
    else if( output[i] == 0x5a && prev1 == prev0 
    //else if( (output[i] == 0x5a || (output[i] == 0xa5 - 256)) && prev1 == prev0 
    //       && (output[i-3] != 0xa5 - 256)
    //       && (output[i-3] != 0x5a)
    ) 
      {
      /*
       * Why would you want to replace 0E 0E with A5 01 0E ???
       * oh well ...
       */
      //assert( output[i-3] != 0xa5 - 256 );
      //assert( output[i-3] != 0x5a );
      output.insert( output.begin()+i-2+2, 1, 'M' );
      output[i-2] = 0xa5;
      output[i-2+1] = 0x01;
      assert( prev0 != 0xa5 - 256 );
      output[i-2+2] = prev0;
      ++i; // I might need to update prev0/prev1 ...
      assert( output[i] == 0x5a || output[i] == 0xa5 - 256 );
      prev1 = output[i-1]; // is it really needed ?
      }
    prev0 = prev1;
    prev1 = output[i];
    }

  // DICOM need % 2
  if( output.size() % 2 )
    {
    output.push_back( 0x0 );
    }
  std::cout << output.size() << std::endl;
  std::ofstream out("comp.rle");
  out.write( &output[0], output.size() );
  out.close();
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
  delta_encode((unsigned short*)ref, size / 2);

  return 0;
}

