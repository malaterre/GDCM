/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "gdcmReader.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmDataSet.h"
#include "gdcmPrinter.h"
#include "gdcmDictPrinter.h"
#include "gdcmValidate.h"
#include "gdcmWriter.h"
#include "gdcmDumper.h"
#include "gdcmSystem.h"
#include "gdcmDirectory.h"
#include "gdcmOverlay.h"
#include "gdcmAttribute.h"

#include <string>
#include <iostream>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string.h>

void UpdateOverlay(gdcm::Overlay & ov, gdcm::DataElement const & de)
{
/*
  8.1.2 Overlay data encoding of related data elements
    Encoded Overlay Planes always have a bit depth of 1, and are encoded separately from the Pixel Data in Overlay Data (60xx,3000). The following two Data Elements shall define the Overlay Plane structure:
    ¿ Overlay Bits Allocated (60xx,0100)
    ¿ Overlay Bit Position (60xx,0102)
    Notes: 1. There is no Data Element analogous to Bits Stored (0028,0101) since Overlay Planes always have a bit depth of 1.
    2. Restrictions on the allowed values for these Data Elements are defined in PS 3.3. Formerly overlay data stored in unused bits of Pixel Data (7FE0,0010) was described, and these attributes had meaningful values but this usage has been retired. See PS 3.5 2004. For overlays encoded in Overlay Data Element (60xx,3000), Overlay Bits Allocated (60xx,0100) is always 1 and Overlay Bit Position (60xx,0102) is always 0.
*/

  assert( de.GetTag().IsPublic() );
  const gdcm::ByteValue* bv = de.GetByteValue();
  assert( bv );
  std::string s( bv->GetPointer(), bv->GetLength() );
  // What if a \0 can be found before the end of string...
  //assert( strlen( s.c_str() ) == s.size() );

  //std::cerr << "Tag: " << de.GetTag() << std::endl;
  if( de.GetTag().GetElement() == 0x0000 ) // OverlayGroupLength
    {
    // ??
    }
  else if( de.GetTag().GetElement() == 0x0010 ) // OverlayRows
    {
    gdcm::Attribute<0x6000,0x0010> at;
    at.Set( de.GetValue() );
    ov.SetRows( at.GetValue() );
    }
  else if( de.GetTag().GetElement() == 0x0011 ) // OverlayColumns
    {
    gdcm::Attribute<0x6000,0x0011> at;
    at.Set( de.GetValue() );
    ov.SetColumns( at.GetValue() );
    }
  else if( de.GetTag().GetElement() == 0x0015 ) // NumberOfFramesInOverlay
    {
    gdcm::Attribute<0x6000,0x0015> at;
    at.Set( de.GetValue() );
    ov.SetNumberOfFrames( at.GetValue() );
    }
  else if( de.GetTag().GetElement() == 0x0022 ) // OverlayDescription
    {
    ov.SetDescription( s.c_str() );
    }
  else if( de.GetTag().GetElement() == 0x0040 ) // OverlayType
    {
    ov.SetType( s.c_str() );
    }
  else if( de.GetTag().GetElement() == 0x0050 ) // OverlayOrigin
    {
    gdcm::Attribute<0x6000,0x0050> at;
    at.Set( de.GetValue() );
    ov.SetOrigin( at.GetBytes() );
    }
  else if( de.GetTag().GetElement() == 0x0051 ) // ImageFrameOrigin
    {
    gdcm::Attribute<0x6000,0x0051> at;
    at.Set( de.GetValue() );
    ov.SetFrameOrigin( at.GetValue() );
    }
  else if( de.GetTag().GetElement() == 0x0100 ) // OverlayBitsAllocated
    {
    gdcm::Attribute<0x6000,0x0100> at;
    at.Set( de.GetValue() );
    assert( at.GetValue() == 1 );
    ov.SetBitsAllocated( at.GetValue() );
    }
  else if( de.GetTag().GetElement() == 0x0102 ) // OverlayBitPosition
    {
    gdcm::Attribute<0x6000,0x0102> at;
    at.Set( de.GetValue() );
    //assert( at.GetValue() == 0 ); // For old ACR when using unused bits...
    ov.SetBitPosition( at.GetValue() );
    }
  else if( de.GetTag().GetElement() == 0x3000 ) // OverlayData
    {
    ov.SetOverlay(bv->GetPointer(), bv->GetLength());
    }
  else
    {
    abort();
    }
}

template <typename TPrinter>
int DoOperation(const std::string & filename)
{
  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  try
    {
    if( !reader.Read() )
      {
      std::cerr << "Failed to read: " << filename << std::endl;
      return 1;
      }
    }
  catch( ... )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  gdcm::Tag overlay(0x6000,0x0000);
  const gdcm::DataSet &ds = reader.GetFile().GetDataSet();
  bool finished = false;
  unsigned int numoverlays = 0;
  while( !finished )
    {
    const gdcm::DataElement &de = ds.GetNextDataElement( overlay );
    if( de.GetTag().GetGroup() > 0x60FF ) // last possible curve
      {
      finished = true;
      }
    else
      {
      // Yeah this is an overlay element
      ++numoverlays;
      gdcm::Overlay ov;
      overlay = de.GetTag();
      uint16_t currentoverlay = overlay.GetGroup();
      assert( !(currentoverlay % 2) ); // 0x6001 is not an overlay...
      // Store the current datalement
      //UpdateOverlay(ov, de);
      gdcm::DataElement de2 = de;
      while( de2.GetTag().GetGroup() == currentoverlay )
        {
        UpdateOverlay(ov, de2);
        overlay.SetElement( de2.GetTag().GetElement() + 1 );
        de2 = ds.GetNextDataElement( overlay );
        // Next element:
        //overlay.SetElement( overlay.GetElement() + 1 );
        }
      // If we exit the loop we have pass the current overlay and potentially point to the next one:
      //overlay.SetElement( overlay.GetElement() + 1 );
      ov.Print( std::cout );

      // Let's decode it:
      std::ostringstream unpack;
      ov.Decompress( unpack );
      std::string s = unpack.str();
      size_t l = s.size();
      // The following line will fail with images like XA_GE_JPEG_02_with_Overlays.dcm
      // since the overlays are stored in the unused bit of the PixelData
      if( !ov.IsEmpty() )
        {
        assert( unpack.str().size() == ov.GetRows() * ov.GetColumns() );
        }
      else
        {
        std::cerr << "This image does not contains Overlay in the 0x60xx tags. "
                  << "Instead the overlay is stored in the unused bit of the Pixel Data. "
                  << "This is not supported right now"
                  << std::endl;
        }
      }
    }
  std::cout << "Num of Overlays: " << numoverlays << std::endl;

  return 0;
}



int main (int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  std::string filename;
  bool printdict = false;
  bool verbose = false;
  while (1) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"input", 1, 0, 0},
        {"output", 1, 0, 0},
        {"dict", 1, 0, 0},
        {"verbose", 1, 0, 0},
        {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "i:o:dv",
      long_options, &option_index);
    if (c == -1)
      {
      break;
      }

    switch (c)
      {
    case 0:
        {
        const char *s = long_options[option_index].name;
        printf ("option %s", s);
        if (optarg)
          {
          if( option_index == 0 ) /* input */
            {
            assert( strcmp(s, "input") == 0 );
            assert( filename.empty() );
            filename = optarg;
            }
          printf (" with arg %s", optarg);
          }
        printf ("\n");
        }
      break;

    case 'i':
      //printf ("option i with value '%s'\n", optarg);
      assert( filename.empty() );
      filename = optarg;
      break;

    case 'o':
      printf ("option o with value '%s'\n", optarg);
      break;

    case 'd':
      //printf ("option d with value '%s'\n", optarg);
      printdict = true;
      break;

    case 'v':
      //printf ("option d with value '%s'\n", optarg);
      verbose = true;
      break;

    case '?':
      break;

    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
      }
  }

  if (optind < argc)
    {
    printf ("non-option ARGV-elements: ");
    while (optind < argc)
      {
      printf ("%s ", argv[optind++]);
      }
    printf ("\n");
    }

  if( filename.empty() )
    {
    std::cerr << "Need input file (-i)\n";
    return 1;
    }
  // else
  int res = 0;
  if( gdcm::System::FileIsDirectory( filename.c_str() ) )
    {
    gdcm::Directory d;
    d.Load(filename);
    gdcm::Directory::FilenamesType const &filenames = d.GetFilenames();
    for( gdcm::Directory::FilenamesType::const_iterator it = filenames.begin(); it != filenames.end(); ++it )
      {
      if( printdict )
        {
        res += DoOperation<gdcm::DictPrinter>(*it);
        }
      else
        {
        res += DoOperation<gdcm::Dumper>(*it);
        }
      if( verbose ) std::cerr << *it << std::endl;
      }
    if( verbose ) std::cerr << "Total: " << filenames.size() << " files were processed" << std::endl;
    }
  else
    {
    assert( gdcm::System::FileExists(filename.c_str()) );
    if( printdict )
      {
      res += DoOperation<gdcm::DictPrinter>(filename);
      }
    else
      {
      res += DoOperation<gdcm::Dumper>(filename);
      }
    // ...
    if ( verbose )
      std::cerr << "Filename: " << filename << std::endl;
    }

  return res;
}

