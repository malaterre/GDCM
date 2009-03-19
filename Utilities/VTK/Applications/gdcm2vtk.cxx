/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
 * TODO: This app should be a suclass of gdcmimg application to avoid code duplication
 */
#include "vtkGDCMImageReader.h"
#include "vtkGDCMImageWriter.h"

#include "vtkVersion.h"
#include "vtkImageReader2Factory.h"
#include "vtkImageReader2.h"
#include "vtkImageData.h"
#if VTK_MAJOR_VERSION >= 5 && VTK_MINOR_VERSION > 0
#include "vtkMINCImageReader.h"
#include "vtkMINCImageAttributes.h"
#include "vtk_tiff.h" // ORIENTATION_BOTLEFT
#endif
#include "vtkMedicalImageProperties.h"
#include "vtkTIFFReader.h"
#include "vtkGESignaReader.h"
#include "vtkImageExtractComponents.h"
#include "vtkImageRGBToYBR.h"
#include "vtkBMPReader.h"
#include "vtkLookupTable.h"
#include "vtkPointData.h"
#include "vtkStructuredPointsReader.h"
#include "vtkStructuredPoints.h"

#include "gdcmFilename.h"
#include "gdcmTrace.h"
#include "gdcmVersion.h"
#include "gdcmImageHelper.h"

#include <getopt.h>

void PrintVersion()
{
  std::cout << "gdcm2vtk: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
  //std::cout << "             VTK " << vtkVersion::GetVTKVersion() << std::endl;
  std::cout << "          " << vtkVersion::GetVTKSourceVersion() << std::endl;
}

void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcm2vtk [OPTION] input output" << std::endl;
  std::cout << "Convert a vtk-supported file into DICOM.\n";
  std::cout << "Options:" << std::endl;
  std::cout << "     --force-rescale    force rescale." << std::endl;
  std::cout << "     --force-spacing    force spacing." << std::endl;
  std::cout << "     --palette-color    when supported generated a PALETTE COLOR file." << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "  -V --verbose    more verbose (warning+error)." << std::endl;
  std::cout << "  -W --warning    print warning info." << std::endl;
  std::cout << "  -D --debug      print debug info." << std::endl;
  std::cout << "  -E --error      print error info." << std::endl;
  std::cout << "  -h --help       print help." << std::endl;
  std::cout << "  -v --version    print version." << std::endl;
}

int main(int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  std::vector<std::string> filenames;
  int forcerescale = 0;
  int forcespacing = 0;
  int palettecolor = 0;

  int verbose = 0;
  int warning = 0;
  int debug = 0;
  int error = 0;
  int help = 0;
  int version = 0;

  while (1) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"force-rescale", 0, &forcerescale, 1},
        {"force-spacing", 0, &forcespacing, 1},
        {"palette-color", 0, &palettecolor, 1},

// General options !
        {"verbose", 0, &verbose, 1},
        {"warning", 0, &warning, 1},
        {"debug", 0, &debug, 1},
        {"error", 0, &error, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},

        {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "VWDEhv",
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
        //printf ("option %s", s);
        if (optarg)
          {
          if( option_index == 0 ) /* input */
            {
            assert( strcmp(s, "input") == 0 );
            //assert( filename.empty() );
            //filename = optarg;
            }
          printf (" with arg %s", optarg);
          }
        //printf ("\n");
        }
      break;

    case 'V':
      verbose = 1;
      break;

    case 'W':
      warning = 1;
      break;

    case 'D':
      debug = 1;
      break;

    case 'E':
      error = 1;
      break;

    case 'h':
      help = 1;
      break;

    case 'v':
      version = 1;
      break;

    case '?':
      break;

    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
      }
  }

  if (optind < argc)
    {
    //printf ("non-option ARGV-elements: ");
    while (optind < argc)
      {
      //printf ("%s ", argv[optind]);
      filenames.push_back( argv[optind++] );
      }
    //printf ("\n");
    }

  if( version )
    {
    //std::cout << "version" << std::endl;
    PrintVersion();
    return 0;
    }

  if( help )
    {
    //std::cout << "help" << std::endl;
    PrintHelp();
    return 0;
    }

  // Debug is a little too verbose
  gdcm::Trace::SetDebug( debug );
  gdcm::Trace::SetWarning( warning );
  gdcm::Trace::SetError( error );
  // when verbose is true, make sure warning+error are turned on:
  if( verbose )
    {
    gdcm::Trace::SetWarning( verbose );
    gdcm::Trace::SetError( verbose);
    }

  if( filenames.size() != 2 )
    {
    PrintHelp();
    return 1;
    }
  const char *filename = filenames[0].c_str();
  const char *outfilename = filenames[1].c_str();


  gdcm::ImageHelper::SetForceRescaleInterceptSlope(forcerescale);
  gdcm::ImageHelper::SetForcePixelSpacing(forcespacing);

  vtkGDCMImageReader *reader = vtkGDCMImageReader::New();

  vtkImageReader2Factory* imgfactory = vtkImageReader2Factory::New();
  imgfactory->RegisterReader( reader );
  vtkImageReader2* imgreader =
    imgfactory->CreateImageReader2(filename);
  vtkStructuredPointsReader *datareader = vtkStructuredPointsReader::New();
  datareader->SetFileName( filename );
  int res = 0;
  if( !imgreader )
    {
    res = datareader->IsFileStructuredPoints();
    if( !res )
      {
      std::cerr << "could not find no reader to handle file: " << filename << std::endl;
      return 1;
      }
    }
  imgfactory->Delete(); 

  vtkImageData *imgdata;
  if( imgreader )
    {
    imgreader->SetFileName(filename);
    imgreader->Update();
    imgdata = imgreader->GetOutput();
    std::cout << imgreader->GetClassName() << std::endl;
    }
  else if( res )
    {
    datareader->Update();
    imgdata = datareader->GetOutput();
    }

  vtkGDCMImageWriter * writer = vtkGDCMImageWriter::New();
  writer->SetFileName( outfilename );

  if( imgreader && imgreader->GetOutput()->GetNumberOfScalarComponents() == 4 )
    {
    std::cerr << "alpha channel will be lost" << std::endl;
    vtkImageExtractComponents *extract = vtkImageExtractComponents::New();
    extract->SetInput( imgreader->GetOutput() );
    extract->SetComponents( 0,1,2 );
    writer->SetInput( extract->GetOutput() );
    extract->Delete();
    }
  else
    {
    //writer->SetInput( imgreader->GetOutput() );
    writer->SetInput( imgdata );

#if 0
    vtkImageRGBToYBR * rgb2ybr = vtkImageRGBToYBR::New();
    rgb2ybr->SetInput( imgreader->GetOutput() );
    writer->SetInput( rgb2ybr->GetOutput() );
    writer->SetImageFormat( VTK_YBR );
#endif
    }

  // If input is 3D, let's write output as 3D if possible:
  if( imgdata->GetDimensions()[2] != 1 )
    {
    writer->SetFileDimensionality( 3 );
    }

  if( imgreader )
    {
    if( vtkGDCMImageReader * reader = vtkGDCMImageReader::SafeDownCast(imgreader) )
      {
      writer->SetMedicalImageProperties( reader->GetMedicalImageProperties() );
      writer->SetDirectionCosines( reader->GetDirectionCosines() );
      writer->SetShift( reader->GetShift() );
      writer->SetScale( reader->GetScale() );
      writer->SetImageFormat( reader->GetImageFormat() );
      reader->GetMedicalImageProperties()->Print( std::cout );
      }
    else if( vtkBMPReader * reader = vtkBMPReader::SafeDownCast(imgreader) )
      {
      if( palettecolor )
        reader->Allow8BitBMPOn( );
      reader->Update( );
      //reader->GetLookupTable()->Print( std::cout );
      if( palettecolor )
        {
        reader->GetOutput()->GetPointData()->GetScalars()->SetLookupTable( reader->GetLookupTable() );
        writer->SetImageFormat( VTK_LOOKUP_TABLE );
        }
      }
    else if( vtkGESignaReader * reader = vtkGESignaReader::SafeDownCast(imgreader) )
      {
      writer->SetMedicalImageProperties( reader->GetMedicalImageProperties() );
      reader->GetMedicalImageProperties()->Print( std::cout );
      }
#if VTK_MAJOR_VERSION >= 5 && VTK_MINOR_VERSION > 0
    else if( vtkMINCImageReader *reader = vtkMINCImageReader::SafeDownCast( imgreader ) )
      {
      writer->SetDirectionCosines( reader->GetDirectionCosines() );
      //writer->GetMedicalImageProperties()->SetModality( "MR" );
      // the following does not work with VTKData/Data/t3_grid_0.mnc
      //writer->SetScale( reader->GetRescaleSlope() );
      //writer->SetShift( reader->GetRescaleIntercept() );
      reader->GetImageAttributes()->PrintFileHeader();
      }
#endif
    else if( vtkTIFFReader *reader = vtkTIFFReader::SafeDownCast( imgreader ) )
      {
      // TIFF has resolution (spacing), and VTK make sure to set set in mm
      // For some reason vtkTIFFReader is all skrew up and will load the image in whatever orientation
      // as stored on file, thus this is up to the user to set it properly...
      // If anyone has any clue why...
#if VTK_MAJOR_VERSION >= 5 && VTK_MINOR_VERSION > 0
      reader->SetOrientationType( ORIENTATION_BOTLEFT );
#endif
      }
    }
  // nothing special need to be done for vtkStructuredPointsReader 

  writer->Write();

  writer->GetInput()->Print( std::cout );

  writer->Delete();
  if( imgreader ) imgreader->Delete();
  datareader->Delete();
  reader->Delete();

  return 0;
}

