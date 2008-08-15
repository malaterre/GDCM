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
#include "gdcmPDBHeader.h"
#include "gdcmPrivateTag.h"
#include "gdcmDataElement.h"
#include "gdcmDataSet.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmSwapper.h"
#include "gdcmDeflateStream.h"

namespace gdcm
{

/*
 * In some GE MEDICAL SYSTEMS image one can find a Data Element: 0025,xx1b,GEMS_SERS_01
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
 *
 * For sample see:
 * GE_MR_0025xx1bProtocolDataBlock.dcm
 * ( <=> http://server.oersted.dtu.dk/personal/jw/jwpublic/courses/31540/mri/second_set/dicom/t2/b17.dcm)
 */

int PDBHeader::readprotocoldatablock(const char *input, size_t inputlen, bool verbose)
{
  // First 4 bytes are the length (again)
  uint32_t len = *(uint32_t*)input;
  //if( verbose )
  //  std::cout << len << "," << inputlen << std::endl;
  if( len + 4 + 1 == inputlen )
    {
    //if( verbose )
    //  std::cout << "gzip stream was padded with an extra 0 \n";
    }
  else if( len + 4 == inputlen )
    {
    //if( verbose )
    //  std::cout << "gzip stream was not padded with an extra 0 \n";
    }
  else
    {
    //std::cerr << "Found the Protocol Data Block but could not read length..." << std::endl;
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
    PDBElement pdbel;
    //std::cout << out << std::endl;
    std::istringstream is2( out );
    std::string name, value;
    is2 >> name;
    std::getline(is2, value);
    pdbel.SetName( name.c_str() );
    std::string value2( value.begin()+2, value.end()-1);
    pdbel.SetValue( value2.c_str() );
   InternalPDBDataSet.push_back( pdbel );
    
    }
  //std::cout << out.size();

  return 0;
}

/*
int DumpProtocolDataBlock(const std::string & filename, bool verbose)
{
  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();

  const gdcm::PrivateTag tprotocoldatablock(0x0025,0x1b,"GEMS_SERS_01");
  if( !ds.FindDataElement( tprotocoldatablock) ) 
    {
    std::cerr << "Could not find tag: " << tprotocoldatablock << std::endl;
    return 1;
    }
  const gdcm::DataElement& protocoldatablock= ds.GetDataElement( tprotocoldatablock);
  if ( protocoldatablock.IsEmpty() ) return 1;
  const gdcm::ByteValue * bv = protocoldatablock.GetByteValue();

  std::cout << "Dumping: " << tprotocoldatablock << std::endl;
  int ret = readprotocoldatablock( bv->GetPointer(), bv->GetLength(), verbose );

  return ret;
}
*/

bool PDBHeader::LoadFromDataElement(DataElement const &protocoldatablock)
{
   InternalPDBDataSet.clear();
  if ( protocoldatablock.IsEmpty() ) return false;
  const gdcm::ByteValue * bv = protocoldatablock.GetByteValue();

  //std::cout << "Dumping: " << tprotocoldatablock << std::endl;
  int ret = readprotocoldatablock( bv->GetPointer(), bv->GetLength(), false);

  if(ret) return false;
  return true;
}

void PDBHeader::Print(std::ostream &os) const
{
  std::vector<PDBElement>::const_iterator it = InternalPDBDataSet.begin();

  for(; it != InternalPDBDataSet.end(); ++it)
    {
    std::cout << *it << std::endl;
    }
}

const PDBElement &PDBHeader::GetPDBElementByName(const char *name)
{
  std::vector<PDBElement>::const_iterator it = InternalPDBDataSet.begin();
  for(; it != InternalPDBDataSet.end(); ++it)
    {
    const char *itname = it->GetName();
    if( strcmp(name, itname) == 0 )
      {
      return *it;
      }
    }
  return Dummy;
}

static const char pdbheader[] = "GEMS_SERS_01";
static const gdcm::PrivateTag t1(0x0025,0x001b,pdbheader);

const PrivateTag & PDBHeader::GetPDBInfoTag()
{
  return t1;
}

} // end namespace gdcm

