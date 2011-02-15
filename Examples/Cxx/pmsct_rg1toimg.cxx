/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
 * This example shows how to rewrite a ELSCINT1/PMSCT_RGB1 compressed
 * image so that it is readable by most 3rd party software (DICOM does
 * not specify this particular encoding).
 * This is required for the sake of interoperability with any standard
 * conforming DICOM system.
 *
 * Everything done in this code is for the sole purpose of writing interoperable
 * software under Sect. 1201 (f) Reverse Engineering exception of the DMCA.
 * If you believe anything in this code violates any law or any of your rights,
 * please contact us (gdcm-developers@lists.sourceforge.net) so that we can
 * find a solution.
 *
 * Everything you do with this code is at your own risk, since decompression
 * algorithm was not written from specification documents.
 *
 * Special thanks to:
 * Jean-Pierre Roux for providing the sample datasets
 */
#include "gdcmReader.h"
#include "gdcmPrivateTag.h"
#include "gdcmAttribute.h"
#include "gdcmImageWriter.h"

void delta_decode(const unsigned char *data_in, size_t data_size,
  std::vector<unsigned char> &new_stream, int w, int h)
{
  size_t outputlen = 3 * w * h;
#if 0
  new_stream.resize( 3 * w * h );
  (void)outputlen;
  signed short val = 0 ;

  for ( size_t ii=0, jj=0; (ii < data_size) && (jj < 3*w*h) ;  )
    {
    unsigned char byte = data_in[ii++];

    switch( byte )
      {
    case 0x81 : // reset value
      val = (signed char) data_in[ii++];
      new_stream[jj++] = val;
      break ;

    case 0x83 : // repetition code
        {
        unsigned char rep  = data_in[ii++];
        for ( int k=0; k < rep; k++ )
          {
          new_stream[jj++] = val;
          new_stream[jj++] = val;
          new_stream[jj++] = val;
          }
        }
      break ;

    case 0x82 : // esc 1 byte (use roll through)
      byte = data_in[ii++] ;

    default :
      // --- negative or positive values ? ---
      int val_pos = byte ;
      int val_neg = 256 - byte ;

      short new_val = 0 ;

      // --- The "middle range" values are found with "byte" as a signed char ---
      // Apparently I need to let the values go slightly negative...
      if ( (val + (signed char) byte >= -64) && (val + (signed char) byte <= 255) )
        {
        // if ( (byte < 0x040) || (byte > 0x0A0) )
        new_val = (signed char) byte ;

        // --- for more "extreme" we use "byte" and "256-byte" ---
        }
      else if ( val - val_neg >= 0 )
        {
        new_val = -val_neg;
        }
      else if ( val + val_pos <= 255 )
        {
        new_val = val_pos;
        }

      val += new_val ;
      new_stream[jj++] = val;
      }
    }
#else

  // RLE pass
  std::vector<unsigned char> temp;
  for(size_t i = 0; i < data_size; ++i)
    {
    if( data_in[i] == 0x83 )
      {
      int repeat = data_in[i+1] + 1;
      const unsigned char *value = data_in+i+2;
      while(repeat)
        {
        temp.push_back( value[0] );
        temp.push_back( value[1] );
        temp.push_back( value[2] );
        --repeat;
        }
      i+=4;
      }
    else
      {
      temp.push_back( data_in[i] );
      }
    }

#if 1
  std::cout <<  " RLE pass: " << temp.size() << std::endl;
  std::cout <<  " RLE pass / 3: " << ((double)temp.size()/3) << std::endl;
//  assert( temp.size() % 3 == 0 );

  // Delta encoding pass
  unsigned char delta = 0;
  for(size_t i = 0; i < temp.size(); ++i)
    {
    unsigned char value = temp[i] + delta;
    new_stream.push_back( value );
    delta = value;
    }
#else
  new_stream.resize( temp.size() );
  std::copy( temp.begin(), temp.end(), new_stream.begin() );
#endif

#endif
  std::cout << data_size << " -> " << new_stream.size() << " (" << outputlen << ")" << std::endl;
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

  // (07a1,1011) CS [PMSCT_RGB1]                                       # 10,1 Tamar Compression Type
  const gdcm::PrivateTag tcompressiontype(0x07a1,0x0011,"ELSCINT1");
  if( !ds.FindDataElement( tcompressiontype ) ) return 1;
  const gdcm::DataElement& compressiontype = ds.GetDataElement( tcompressiontype );
  if ( compressiontype.IsEmpty() ) return 1;
  const gdcm::ByteValue * bv = compressiontype.GetByteValue();
  std::string comprle = "PMSCT_RLE1";
  std::string comprgb = "PMSCT_RGB1";
  bool isrle = false;
  bool isrgb = false;
  if( strncmp( bv->GetPointer(), comprle.c_str(), comprle.size() ) == 0 )
    {
    isrle = true;
    return 1;
    }
  if( strncmp( bv->GetPointer(), comprgb.c_str(), comprgb.size() ) == 0 )
    {
    isrgb = true;
    }
  if( !isrgb && !isrle ) return 1;

  const gdcm::PrivateTag tcompressedpixeldata(0x07a1,0x000a,"ELSCINT1");
  if( !ds.FindDataElement( tcompressedpixeldata) ) return 1;
  const gdcm::DataElement& compressionpixeldata = ds.GetDataElement( tcompressedpixeldata);
  if ( compressionpixeldata.IsEmpty() ) return 1;
  const gdcm::ByteValue * bv2 = compressionpixeldata.GetByteValue();

  gdcm::Attribute<0x0028,0x0010> at1;
  at1.SetFromDataSet( ds );
  gdcm::Attribute<0x0028,0x0011> at2;
  at2.SetFromDataSet( ds );

  std::vector<unsigned char> buffer;
  delta_decode((const unsigned char*)bv2->GetPointer(), bv2->GetLength(), buffer,
    at1.GetValue(), at2.GetValue() );

  gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
  pixeldata.SetVR( gdcm::VR::OW );
  pixeldata.SetByteValue( (char*)&buffer[0], buffer.size() );
  // TODO we should check that decompress byte buffer match the expected size (row*col*...)

  // Add the pixel data element
  reader.GetFile().GetDataSet().Replace( pixeldata );

  reader.GetFile().GetHeader().SetDataSetTransferSyntax(
    gdcm::TransferSyntax::ExplicitVRLittleEndian);
  gdcm::Writer writer;
  writer.SetFile( reader.GetFile() );

  // Cleanup stuff:
  // remove the compressed pixel data:
  // FIXME: should I remove more private tags ? all of them ?
  // oh well this is just an example
  // use gdcm::Anonymizer::RemovePrivateTags if needed...
  writer.GetFile().GetDataSet().Remove( compressionpixeldata.GetTag() );
  std::string outfilename;
  if (argc > 2)
     outfilename = argv[2];
  else
     outfilename = "outrgb.dcm";
  writer.SetFileName( outfilename.c_str() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write" << std::endl;
    return 1;
    }

  std::cout << "success !" << std::endl;

  return 0;
}
