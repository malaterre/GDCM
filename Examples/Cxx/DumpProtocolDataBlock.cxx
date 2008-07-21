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
 * In some GE MEDICAL SYSTEMS image one can find a Data Element: 0025,xx10,GEMS_SERS_01
 * which is documented as Protocol Data Block (compressed).
 * in fact this is a simple text format compressed using the gzip algorithm
 *
 * Typically one could do:
 *
 *   $ gdcmraw -i input.dcm -o output.raw -t 0025,101b 
 *
 * Skip the binary length (little endian encoding):
 *
 *   $ dd bs=4 skip=1 if=output.raw of=foo 
 *
 * Check file type:
 *
 *   $ file foo
 *   foo: gzip compressed data, was "Ex421Ser8Scan1", from Unix
 *
 * Gunzip !
 *   $ gzip -dc < foo > bar
 *   $ cat bar
 *
 * THANKS to: John Reiser (BitWagon.com) for hints
 */
#include "gdcmReader.h"
#include "gdcmTag.h"
#include "gdcmDataSet.h"
#include "gdcmPrivateTag.h"

#include "gdcmDeflateStream.h"

int readprotocoldatablock(const char *input, size_t inputlen)
{
  // First 4 bytes are the length (again)
  uint32_t len = *(uint32_t*)input;
  std::cout << len << "," << inputlen << std::endl;
  if( len + 4 == inputlen + 1 )
    {
    std::cout << "gzip stream was padded with an extra \0 \n";
    }
  else if( len + 4 == inputlen )
    {
    std::cout << "gzip stream was not padded with an extra \0 \n";
    }
  else
    {
    return 1;
    }
  // Alright we need to check if the binary blob was padded, if padded we need to 
  // discard the trailing \0 to please gzip:
  std::string str( input + 4, input + len );
  std::istringstream is( str );

  zlib_stream::zip_istream gzis( is );

//  if (gzis.is_gzip())
//    {
//    std::cout<<"crc check: "<<( gzis.check_crc() ? "ok" : "failed");
//    std::cout << std::endl;
//    }

  std::string out;
  //while( gzis >> out )
  while( std::getline(gzis , out ) )
    {
    std::cout << out << std::endl;
    }
  //std::cout << out.size();

  return 0;
}

int main(int argc, char *argv [])
{
  if( argc < 2 ) return 1;
  const char *filename = argv[1];
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();

  const gdcm::PrivateTag tprotocoldatablock(0x0025,0x1b,"GEMS_SERS_01");
  if( !ds.FindDataElement( tprotocoldatablock) ) return 1;
  const gdcm::DataElement& protocoldatablock= ds.GetDataElement( tprotocoldatablock);
  if ( protocoldatablock.IsEmpty() ) return 1;
  const gdcm::ByteValue * bv = protocoldatablock.GetByteValue();

  std::cout << "Dumping: " << tprotocoldatablock << std::endl;
  int ret = readprotocoldatablock( bv->GetPointer(), bv->GetLength() );

  return ret;
}
