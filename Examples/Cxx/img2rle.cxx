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
#include <limits>
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

void encode_div_mod(std::vector<char> & output, int value)
{
  assert( value >= 0 );
  // This is an integer that cannot be stored on a char value, thus store
  // it as modulo and remainder
  int v1 = (int)value % 256;
  int v2 = (int)value / 256;
  assert( v1 >= 0 && v1 <= std::numeric_limits<uint16_t>::max() );
  assert( v2 >= 0 && v2 <= std::numeric_limits<uint16_t>::max() );
  output.push_back( 0x5a );
  output.push_back( v1 );
  output.push_back( v2 );
}

void encode_diff_value(std::vector<char> & output, int value)
{
  assert( value <= (int)std::numeric_limits<char>::max() && value >= (int)std::numeric_limits<char>::min() );
  output.push_back( value );
}

void encode_pixel_value(std::vector<char> & output, unsigned short value)
{
  encode_div_mod(output, value);
}

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

  // Do Run Length Encoding now:
  char prev0 = output[0];
  char prev1 = output[1];
  assert( prev0 != 0xa5 - 256 && prev1 != 0xa5 - 256 );
  for(unsigned int i = 2; i < output.size(); ++i)
    {
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
      // HACK: when the next char is 0x5A, and 
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
      output.insert( output.begin()+i-2+2, 1, 'M' );
      output[i-2] = 0xa5;
      output[i-2+1] = 0x01;
      assert( prev0 != 0xa5 - 256 );
      output[i-2+2] = prev0;
      ++i;
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
  if( cmp )
    {
    //std::ofstream out(
    
    }

  // cmp can be <= 0 ...
  return cmp == 0 ? 0 : 1;
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

"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002004",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002005",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002006",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002007",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002008",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002009",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002010",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002011",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002012",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002013",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002014",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002015",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002016",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002017",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002018",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002019",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002020",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002021",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002022",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310085921000002/1.3.12.2.1107.5.2.1.5356.20080310085921000002023",

"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003024",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003025",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003026",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003027",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003028",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003029",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003030",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003031",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003032",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003033",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003034",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003035",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003036",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003037",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003038",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003039",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003040",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003041",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003042",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310090236000003/1.3.12.2.1107.5.2.1.5356.20080310090236000003043",

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

"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005064",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005065",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005066",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005067",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005068",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005069",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005070",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005071",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005072",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005073",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005074",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005075",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005076",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005077",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005078",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005079",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005080",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005081",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005082",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091214000005/1.3.12.2.1107.5.2.1.5356.20080310091214000005083",

"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006084",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006085",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006086",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006087",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006088",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006089",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006090",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006091",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006092",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006093",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006094",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006095",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006096",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006097",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006098",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006099",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006100",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006101",
"/home/mmalaterre/Creatis/gdcmData/study1-original/1.3.12.2.1107.5.2.1.5356.20080310085222000/1.3.12.2.1107.5.2.1.5356.20080310091635000006/1.3.12.2.1107.5.2.1.5356.20080310091635000006102",

  0
};

static const char *rlefilenames[] = {
  "/home/mmalaterre/Creatis/gdcmData/study1/s10/i10",
  "/home/mmalaterre/Creatis/gdcmData/study1/s10/i20",
  "/home/mmalaterre/Creatis/gdcmData/study1/s10/i30",

  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i40",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i50",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i60",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i70",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i80",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i90",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i100",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i110",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i120",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i130",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i140",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i150",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i160",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i170",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i180",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i190",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i200",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i210",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i220",
  "/home/mmalaterre/Creatis/gdcmData/study1/s20/i230",

  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i240",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i250",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i260",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i270",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i280",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i290",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i300",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i310",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i320",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i330",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i340",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i350",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i360",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i370",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i380",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i390",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i400",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i410",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i420",
  "/home/mmalaterre/Creatis/gdcmData/study1/s30/i430",

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

  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i640",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i650",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i660",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i670",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i680",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i690",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i700",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i710",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i720",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i730",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i740",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i750",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i760",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i770",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i780",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i790",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i800",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i810",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i820",
  "/home/mmalaterre/Creatis/gdcmData/study1/s50/i830",

  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i840",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i850",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i860",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i870",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i880",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i890",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i900",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i910",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i920",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i930",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i940",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i950",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i960",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i970",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i980",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i990",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i1000",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i1010",
  "/home/mmalaterre/Creatis/gdcmData/study1/s60/i1020",

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
