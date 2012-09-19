/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmReader.h"
#include "gdcmTag.h"
#include "gdcmDataElement.h"

#include <fstream>

/*
 * A very simple example to anonymize in place.
 * Let's assume you cannot afford the memory consumption required
 * by gdcmanon --dumb, you could use this example to 'empty' some
 * tags.
 */
int main(int argc, char *argv[])
{
  if( argc < 3 )
    {
    std::cerr << argv[0] << " input.dcm output.dcm" << std::endl;
    return 1;
    }
  using namespace gdcm;

  // Step 1. Get the offset
  const char *filename = argv[1];
  const char *outfilename = argv[2];

  std::ifstream is( filename, std::ios::binary );

  gdcm::Tag t1(0x0018,0x0022);
  gdcm::Tag t2(0x0028,0x0002);
  //gdcm::Tag t(0x0025,0x100a);
  const gdcm::Tag &t = t2;
  std::set<gdcm::Tag> removeme;
  removeme.insert( t1 );

  gdcm::Reader reader;
  reader.SetStream( is );
  if( !reader.ReadSelectedTags( removeme ) )
    {
    // not DICOM ?
    return 1;
    }
  std::streampos pos0 = is.tellg();

  const File & f = reader.GetFile();
  const DataSet &ds = f.GetDataSet();

#if 0
  if( ds.FindDataElement( t1 ) )
    {
    const DataElement &de = ds.GetDataElement( t1 );
    // skip value:
    if( de.GetVL().IsUndefined() )
      {
      // TODO
      assert( 0 );
      }
    else
      {
      is.seekg( de.GetVL(), std::ios::cur );
      }
    }
#endif
  removeme.clear();
  removeme.insert( t2 );

  std::streampos pos1 = is.tellg();

  if( !reader.ReadSelectedTags( removeme ) )
    {
    // not DICOM ?
    return 1;
    }
  std::streampos pos = is.tellg();
  is.close();

  // Step 2. Copy & skip proper portion
  std::ofstream of( outfilename, std::ios::binary );
  std::ifstream is2( filename, std::ios::binary );
  if( ds.FindDataElement( t ) )
    {
    const DataElement &de = ds.GetDataElement( t );
    int vrlen = de.GetVR().GetLength();

    if( de.GetVL().IsUndefined() )
      {
      // TODO
      assert( 0 );
      }
    else
      {
      std::streampos end = pos;
      // seek back:
      end -= de.GetVL();
      end -= vrlen;

      // FIXME: most efficient way to copy chunk of file in c++ ?
      for( int i = 0; i < end; ++ i)
        {
        of.put( is2.get() );
        }
      for( int i = 0; i < vrlen; ++ i)
        {
        of.put( 0 );
        }
      is2.seekg( de.GetVL() + vrlen, std::ios::cur );
      }
    }

  of << is2.rdbuf();
  of.close();
  is2.close();

  return 0;
}
