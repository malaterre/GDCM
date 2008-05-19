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
#include <stdlib.h>


void delta_decode(char *inbuffer, size_t length, unsigned short * ref)
{
  std::vector<unsigned short> output;
  unsigned short delta = 0;
  for(size_t i = 0; i < length; ++i)
    {
    if( (unsigned char)inbuffer[i] == 0xa5 )
      {
      char repeat = inbuffer[i+1] + 1;
      char value  = inbuffer[i+2];
      if( (unsigned char)value == 0x5a )
        {
        assert( repeat == 2 );
        //std::cout << "5a v=" << std::hex << value << " " << (int)repeat << " " << 
        //  (int)value << " " << (int)inbuffer[i+3] << " " << std::dec << i <<  std::endl;
        unsigned char v1 = (unsigned char)inbuffer[i+1];
        unsigned char v2 = (unsigned char)inbuffer[i+2];
        int value = v1 * 256 + v2;
        if( inbuffer[i+3] == 1 )
          {
          std::cerr << value << " != " << 0x15A << std::endl;
          assert( 0x015A == value );
          }
        if ( v2 == 0x5a )
          {
          int value = ref[ output.size() ];
          output.push_back( value );
          assert( output[ output.size() - 1] == ref[ output.size() - 1 ] );
          delta = value;
          i+=3;
          }
        else
          {
          output.push_back( value );
          assert( output[ output.size() - 1] == ref[ output.size() - 1 ] );
          delta = value;
          i+=3; // 3 values treated at once
          }
        }
      else
        {
        i+=2; // 2 values treated at once
        for( int r = 0; r < repeat; ++r )
          {
          int ivalue = (int)delta + (int)value;
          output.push_back( ivalue );
          assert( output[ output.size() - 1] == ref[ output.size() - 1 ] );
          delta = ivalue;
          }
        }
      }
    else if( inbuffer[i] == 0x5a )
      {
      unsigned char v1 = (unsigned char)inbuffer[i+1];
      unsigned char v2 = (unsigned char)inbuffer[i+2];
      i+=2; // 2 values treated at once
      if( v1 == 0xa5 )
        {
        //assert( v2 == 0 );
        if( (unsigned char)inbuffer[i+1] == 0xa5 )
          {
          //abort();
          //assert( output[ output.size() - 1] == ref[ output.size() - 1 ] );
          //delta = value;
          int value = 421;
          output.push_back( value );
          assert( output[ output.size() - 1] == ref[ output.size() - 1 ] );
          delta = value;
          i+=2;
          }
        else
          {
          int value = (v2 + 1) * 256 + v1;
          output.push_back( value );
          assert( output[ output.size() - 1] == ref[ output.size() - 1 ] );
          delta = value;
          }
        }
      else
        {
        int value = v2 * 256 + v1;
        output.push_back( value );
        assert( output[ output.size() - 1] == ref[ output.size() - 1 ] );
        delta = value;
        }
      }
    else
      {
      //std::cout << delta << "," << (int)inbuffer[i] << std::endl;
      int value = (int)delta + (int)inbuffer[i];
      //std::cout << "value:" << value << std::endl;
      //assert( value <= 0xFFFF && value >= 0 );
      output.push_back( value );
      assert( output[ output.size() - 1] == ref[ output.size() - 1 ] );
      //assert( output.size() != 0x8890 / 2);
      delta = value;
      }
    std::cout << output.size() << " from : " << std::hex << (int)inbuffer[i] << "(" << std::dec << i << ")" << std::endl;
    }

  if ( output.size() % 2 )
    {
    output.resize( output.size() - 1 );
    }
  std::cout << length << " -> " << output.size() << std::endl;
  std::ofstream out("decomp.raw");
  out.write( (char*)&output[0], output.size() * 2 );
  out.close();
}

int main(int argc, char *argv [])
{
  if( argc < 2 ) return 1;
  const char *filename = argv[1];
  const char *reffilename = argv[2];

  std::ifstream ref( reffilename );
  ref.seekg( 0, std::ios::end);
  size_t refgcount = ref.tellg();
  ref.seekg( 0, std::ios::beg);
  std::vector<char> uncompressed;
  uncompressed.resize( refgcount );
  ref.read( (char*)&uncompressed[0], refgcount);
  ref.close();

  std::ifstream i( filename );
  i.seekg( 0, std::ios::end);
  size_t gcount = i.tellg();
  i.seekg( 0, std::ios::beg);
  std::vector<char> compressed;
  compressed.resize( gcount );
  i.read( (char*)&compressed[0], gcount);
  i.close();

  delta_decode(&compressed[0], compressed.size(), (unsigned short*)&uncompressed[0]);

  return 0;
}

