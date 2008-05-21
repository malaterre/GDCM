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

#include "gdcmReader.h"
#include "gdcmPrivateTag.h"
#include "gdcmImageWriter.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <string.h>
#include <stdlib.h>


int GetPixelData(const char *filename, std::vector<char> &output)
{
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();
  gdcm::Tag tpixeldata(0x7fe0,0x0010);

  const gdcm::DataElement& pixeldata = ds.GetDataElement( tpixeldata);
  const gdcm::ByteValue * bv = pixeldata.GetByteValue();

  output.resize( bv->GetLength() );
  memcpy( &output[0], bv->GetPointer(), bv->GetLength() );
  return 0;
}


void encode_a5(std::vector<char> & output, int v1, int v2)
{
  (void)v1; (void)v2;
  output.push_back( 0xa5 );
  output.push_back( 0x00 );
  output.push_back( 0xa5 );
}

void encode_5a(std::vector<char> & output, int v1, int v2)
{
  assert( v2 != 0xa5 && v2 != 0x5a ); (void)v1;

  output.push_back( 0xa5 );
  output.push_back( 0x01 );
  output.push_back( 0x5a );
  output.push_back( v2 );
}

void encode_v1_v2(std::vector<char> & output, int v1, int v2)
{
  assert( v1 != 0xa5 && v1 != 0x5a );
  assert( v2 != 0xa5 && v2 != 0x5a );

  output.push_back( 0x5a );
  output.push_back( v1 );
  output.push_back( v2 );
}

void delta_encode(unsigned short *inbuffer, size_t length, std::vector<char> &output)
{
  //std::vector<char> output;
  unsigned short prev = 0;

  // Do delta encoding:
  for(unsigned int i = 0; i < length; ++i)
    {
    int diff = inbuffer[i] - prev;
    char cdiff = (char)diff;

    int v1 = inbuffer[i] % 256;
    int v2 = inbuffer[i] / 256;
    assert( v1 != 0xa5 - 256 );
    assert( v2 != 0xa5 - 256 );
    assert( v2 != 0x5a );
    if( diff <= 0x7f && diff >= -0x80 )
      {
      if( cdiff == 0xa5 - 256 )
        {
        encode_a5(output, v1, v2);
        }
      else if( cdiff == 0x5a  )
        {
        if ( v1 == 0xa5 )
          {
          encode_a5(output, v1, v2);
          }
        else if ( v1 == 0x5a )
          {
          encode_5a(output, v1, v2);
          }
        else
          {
          encode_v1_v2(output, v1, v2);
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
        assert( v2 != 0xa5 && v2 != 0x5a );
        output.push_back( 0x5a );

        encode_a5(output, v1, v2);

        output.push_back( v2 );
        }
      else if( v1 == 0x5a )
        {
        encode_5a(output, v1, v2);
        }
      else
        {
        encode_v1_v2(output, v1, v2);
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
       * oh well ...
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
  //std::ofstream out("comp.rle");
  //out.write( &output[0], output.size() );
  //out.close();
}

int CompareRLE(std::vector<char> const & rlepixeldata, const char *filename)
{
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();

  // (07a1,1011) CS [PMSCT_RLE1]                                       # 10,1 Tamar Compression Type
  const gdcm::PrivateTag tcompressiontype(0x07a1,0x0011,"ELSCINT1");
  if( !ds.FindDataElement( tcompressiontype ) ) return 1;
  const gdcm::DataElement& compressiontype = ds.GetDataElement( tcompressiontype );
  if ( compressiontype.IsEmpty() ) return 1;
  const gdcm::ByteValue * bv = compressiontype.GetByteValue();
  std::string comp = "PMSCT_RLE1";
  if( strncmp( bv->GetPointer(), comp.c_str(), comp.size() ) != 0 ) return 1;
  
  const gdcm::PrivateTag tcompressedpixeldata(0x07a1,0x000a,"ELSCINT1");
  if( !ds.FindDataElement( tcompressedpixeldata) ) return 1;
  const gdcm::DataElement& compressionpixeldata = ds.GetDataElement( tcompressedpixeldata);
  if ( compressionpixeldata.IsEmpty() ) return 1;
  const gdcm::ByteValue * bv2 = compressionpixeldata.GetByteValue();

  if ( bv2->GetLength() != rlepixeldata.size() )
    {
    std::cerr << "Length failed: " << bv2->GetLength() << " >< " << rlepixeldata.size() << std::endl;
    return 1;
    }

  int cmp = memcmp(&rlepixeldata[0], bv2->GetPointer(), bv2->GetLength() );

  return cmp;
}

int check_files(const char *rawfile, const char *rlefile)
{
  std::vector<char> rawpixeldata;
  GetPixelData(rawfile, rawpixeldata);
  std::vector<char> rlepixeldata;
  delta_encode( (unsigned short*)&rawpixeldata[0], rawpixeldata.size() / 2, rlepixeldata);

  int ret = CompareRLE(rlepixeldata, rlefile);
  
  //std::cerr << "ret=" << ret  << std::endl;

  return ret;
}

// (0009,1015) LO [034SA2MR032008031113364683]             #  26, 1 SPIImageUID

static const char *rawfilenames[] = {
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085718000001/1.3.12.2.1107.5.2.1.5356.20080310085718000001001",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085718000001/1.3.12.2.1107.5.2.1.5356.20080310085718000001002",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085718000001/1.3.12.2.1107.5.2.1.5356.20080310085718000001003",

"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004044",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004045",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004046",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004047",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004048",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004049",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004050",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004051",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004052",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004053",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004054",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004055",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004056",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004057",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004058",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004059",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004060",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004061",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004062",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090725000004/1.3.12.2.1107.5.2.1.5356.20080310090726000004063",

  0
};

static const char *rlefilenames[] = {
  "/home/mmalaterre/Creatis/gdcmData/study1/s10/i10",
  "/home/mmalaterre/Creatis/gdcmData/study1/s10/i20",
  "/home/mmalaterre/Creatis/gdcmData/study1/s10/i30",

  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i440",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i450",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i460",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i470",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i480",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i490",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i500",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i510",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i520",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i530",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i540",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i550",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i560",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i570",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i580",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i590",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i600",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i610",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i620",
  "/home/mmalaterre/Creatis/gdcmData/study1/s40/i630",

  0
};

int main(int argc, char *argv[])
{
  const unsigned int rawsize = sizeof(rawfilenames) / sizeof(*rawfilenames) - 1;
  const unsigned int rlesize = sizeof(rlefilenames) / sizeof(*rlefilenames) - 1;
  if( rlesize != rawsize ) return 1;

  int ret = 0;
  for(unsigned int i = 0; i < rlesize; ++i)
    {
    int val = check_files( rawfilenames[i], rlefilenames[i] );
    if( val ) std::cerr << "Incompatible: " << rawfilenames[i] << " and " << rlefilenames[i] << std::endl;
    ret += val;
    }

  std::cerr << "Number of check failed: " << ret << std::endl;

  return ret;
}
