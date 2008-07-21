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
 * Typically:
 *
 *
 * THANKS to: John Reiser for hints
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
  // Alright we need to check if the binary blob was padded, if padded we need to 
  // discard the trailing \0 to please gzip:
  std::string str( input + 4, input + len );
  std::istringstream is( str );

  zlib_stream::zip_istream gzis( is );
  //std::cout << gzis << std::endl;

//  if (gzis.is_gzip())
//    {
//    std::cout << "gzip" << std::endl;
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

  int ret = readprotocoldatablock( bv->GetPointer(), bv->GetLength() );

  return 0;
}
