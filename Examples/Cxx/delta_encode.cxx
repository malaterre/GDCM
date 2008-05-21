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
#include <assert.h>
#include <string.h>
#include <stdlib.h>


void delta_encode(unsigned short *inbuffer, size_t length)
{
  std::vector<char> output;
  unsigned short prev = 0;
  //length = 100;
  // Do delta encoding:
  for(unsigned int i = 0; i < length; ++i)
    {
    //assert( output.size() == i );
    int diff = inbuffer[i] - prev;
    char cdiff = (char)diff;
    //std::cout << std::hex << i << ":" << std::dec << diff << " - > " << std::hex << std::setfill( '0' ) << /*std::left <<*/ std::setw(2) << (short)cdiff << std::endl;
    //if( diff == (int)cdiff )
    int v1 = inbuffer[i] % 256;
    int v2 = inbuffer[i] / 256;
    assert( v1 != 0xa5 - 256 );
    assert( v2 != 0xa5 - 256 );
    assert( v2 != 0x5a );
    if( diff <= 0x7f && diff >= -0x80 )
      {
      if( cdiff == 0xa5 - 256 )
        {
        //output.push_back( 'M' );
        output.push_back( 0xa5 );
        output.push_back( 0x0 );
        output.push_back( 0xa5 );
        }
      else if( cdiff == 0x5a  )
        {
        //output.push_back( 'N' );
        if ( v1 == 0xa5 )
          {
          output.push_back( 'M' );
          output.push_back( 'A' );
          output.push_back( 'T' );
          }
        else if ( v1 == 0x5a )
          {
          output.push_back( 0xa5 );
          output.push_back( 0x01 );
          output.push_back( 0x5a );
          output.push_back( v2 );
          }
        else
          {
          output.push_back( 0x5a );
          assert( v1 != 0xa5 && v1 != 0x5a );
          assert( v2 != 0xa5 && v2 != 0x5a );
          output.push_back( v1 );
          output.push_back( v2 );
          }
        }
      else
        {
        output.push_back( cdiff );
        }
      }
    else
      {
      if( v1 == 0xa5 )
        {
        output.push_back( 0x5a );
        output.push_back( 0xa5 );
        output.push_back( 0x00 );
        output.push_back( 0xa5 );
        assert( v2 != 0xa5 && v2 != 0x5a );
        output.push_back( v2 );
        //output.push_back( 'M' );
        //output.push_back( 'A' );
        //output.push_back( 'T' );
        //output.push_back( 'H' );
        }
      else if( v1 == 0x5a )
        {
        output.push_back( 0xa5 );
        //output.push_back( 'I' );
        //output.push_back( 'E' );
        //output.push_back( 'U' );
        output.push_back( 0x01 );
        output.push_back( 0x5a );
        assert( v2 != 0xa5 && v2 != 0x5a );
        output.push_back( v2 );
        }
      else
        {
        output.push_back( 0x5a );
        output.push_back( (unsigned char)v1 );
        assert( v1 != 0xa5 && v1 != 0x5a );
        assert( v2 != 0xa5 && v2 != 0x5a );
        output.push_back( (unsigned char)v2 );
        }
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
      //std::cout << "I:     " <<   i << std::endl;
      output[i-2] = 0xa5;
      assert( j != 0 && j != 1 );
      output[i-2+1] = j;
      assert( prev0 != 0xa5 - 256 );
      output[i-2+2] = prev0;
      output.erase( output.begin() + i, output.begin() + i - 2 + j);
      }
    else if( output[i] == 0x5a && prev1 == prev0 ) 
      {
      /*
       * Why would you want to replace 0E 0E with A5 01 0E ???
       */
      output.insert( output.begin()+i-2+2, 1, 'M' );
      output[i-2] = 0xa5;
      output[i-2+1] = 0x01;
      output[i-2+2] = prev0;
      ++i; // I might need to update prev0/prev1 ...
      assert( output[i] == 0x5a );
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

