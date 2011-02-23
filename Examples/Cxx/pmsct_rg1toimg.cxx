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

int CLIP(int min, int val, int max)
{
  if( val < min ) val = min;
  if( val > max ) val = max;
  return val;
}

void delta_decode(const unsigned char *data_in, size_t data_size,
  std::vector<unsigned char> &new_stream, size_t w, size_t h)
{
  size_t outputlen = 3 * w * h;
#if 0
  signed short val = 0 ;
  signed short col[3] = { 0, 0, 0 } ;

  // --- prepare memory for the decoded stream ---
  new_stream.resize( 3 * w * h );

#define  VAL CLIP(0,val,255)
#define  COL CLIP(0,col[jj%3],255)

  // --- We have 2 modes: color or B&W.  In Color mode each color component
  // is treated individually, in B&W all 3 component are the same.
  // code "81" change the color mode. ---
  int mode_color = 0 ;

  // --- for all the element in the input stream ---
  for ( size_t ii=0, jj=0; (ii < data_size) && (jj < 3*w*h) ;  ) {

    // --- fetch the next byte ---
    unsigned char byte = data_in[ii++] ;

    switch( byte ) {

      // ================================================================
      // ===  Code 81:  Color mode and color reset        ===
      // used change the color mode and set the colors         ===
      // ================================================================
      // Note: we only use the code 81 if it fall on a first color    ===
      //       component.  Otherwhise we use the roll through to get  ===
      //       the byte value to the "default" treatment.
      // ================================================================
    case 0x81 :  // reset value & switch color mode

      // --- only valid if first color component ---
      if ( ! (jj % 3) ) {
        mode_color = ! mode_color ;

        // --- special case if next code is 0x82 (just skip it!) ---
        if ( data_in[ii] == 0x082 )
          ii++ ;

        if ( mode_color ) {
          col[0] = data_in[ii++] ;
          col[1] = data_in[ii++] ;
          col[2] = data_in[ii++] ;
          new_stream[jj] = COL ; jj++;
          new_stream[jj] = COL ; jj++;
          new_stream[jj] = COL ; jj++;

        } else {
          col[0] = col[1] = col[2] = val = data_in[ii++] ;
          new_stream[jj++] = VAL ;
          new_stream[jj++] = VAL ;
          new_stream[jj++] = VAL ;
        }

        break ;
      }


      // ================================================================
      // ===  Code 83:  Repetition code            ===
      // used to repeat the current color multiple times        ===
      // ================================================================
      // Note: we only use the code 83 if it fall on a first color    ===
      //       component.  Otherwhise we use the roll through to get  ===
      //       the byte value to the "default" treatment.
      // ================================================================
    case 0x83 :  // repetition code

      // --- only valid if first color component ---
      if ( ! (jj % 3) ) {

        if ( mode_color ) {
          unsigned char rep  = data_in[ii++] ;
          for ( int k=0; k < rep; k++ ) {
            new_stream[jj] = COL ;
            jj++ ;
            new_stream[jj] = COL ;
            jj++ ;
            new_stream[jj] = COL ;
            jj++ ;
          }
        } else {
          unsigned char rep  = data_in[ii++] ;
          for ( int k=0; k < rep; k++ ) {
            new_stream[jj++] = VAL ;
            new_stream[jj++] = VAL ;
            new_stream[jj++] = VAL ;
          }
        }
        break ;
      }

      // ================================================================
      // ===  Code 82:  Esc sequence.            ===
      // Used to treat a byte 81, 82 or 83 as a normal data byte      ===
      // ================================================================
      // Note: we only use the code 83 if it fall on a first color    ===
      //       component.  Otherwhise we use the roll through to get  ===
      //       the byte value to the "default" treatment.
      // ================================================================
    case 0x82 :  // esc 1 byte (use roll through)

      // --- only valid if first color component ---
      if ( ! (jj % 3) ) {
        if ( (data_in[ii] == 0x081) || (data_in[ii] == 0x082) || (data_in[ii] == 0x083) ) {
          byte = data_in[ii++] ;
        }
      }

      // ================================================================
      // ===  Default                ===
      // ================================================================
      // Note: The byte value is added either to the current B&W or   ===
      //       color values.  The value added can be a signed char    ===
      //       (-128 to 127) or a positive value (0 to 255) or a      ===
      //       negative value (-1 to -255).
      // ================================================================
    default :

      // --- negative or positive values ? ---
      int val_pos = byte ;
      int val_neg = 256 - byte ;

      short old_val = 0 ;

      if ( ! mode_color )
        old_val = val ;
      else
        old_val = col[jj%3] ;


      short new_val = 0 ;
      // --- The "middle range" values are found with "byte" as a signed char ---
      if ( (old_val + (signed char) byte >= 0) && (old_val + (signed char) byte <= 255) ) {

        new_val = (signed char) byte ;

        // --- for more "extreme" we use "byte" and "256-byte" ---
      } else if ( old_val - val_neg >= 0 ) {

        new_val = -val_neg ;

      } else if ( old_val + val_pos <= 255 ) {

        new_val = val_pos ;
      }

      if ( ! mode_color ) {
        val += new_val ;
        col[0] = col[1] = col[2] = val ;
        new_stream[jj++] = VAL ;
        new_stream[jj++] = VAL ;
        new_stream[jj++] = VAL ;
      } else {
        col[jj%3] += new_val ;
        new_stream[jj] = COL ;
        jj++ ;
      }

    }
  }

#else

  // RLE pass
  std::vector<unsigned char> temp;
  int count = 0;
  for(size_t i = 0; i < data_size; ++i)
    {
    if( data_in[i] == 0x83 )
      {
      int repeat = data_in[i+1];
      assert( repeat );
      ++count;
#if 0
      const unsigned char *value = data_in+i+2;
      while(repeat)
        {
        temp.push_back( value[0] );
        temp.push_back( value[1] );
        temp.push_back( value[2] );
        --repeat;
        }
      i+=4;
#else
      unsigned char value = data_in[i+2];
      std::cout << count << " " << repeat << " " << (int)value << std::endl;
      while(repeat)
        {
        temp.push_back( value );
        --repeat;
        }
      i+=2;
#endif
      }
    else
      {
      temp.push_back( data_in[i] );
      }
    }

#if 0
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
