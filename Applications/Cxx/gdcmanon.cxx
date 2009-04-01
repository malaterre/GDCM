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
 */

#include "gdcmReader.h"
#include "gdcmWriter.h"
#include "gdcmVersion.h"
#include "gdcmRSA.h"
#include "gdcmSystem.h"
#include "gdcmUIDGenerator.h"
#include "gdcmAnonymizer.h"
#include "gdcmGlobal.h"

#include <getopt.h>

void PrintVersion()
{
  std::cout << "gdcmanon: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
}

bool GetRSAKey(gdcm::RSA &rsa)
{
  // By default on *nix system there should be a id_rsa file in $HOME/.ssh. Let's try parsing it:
  char *home = getenv("HOME");
  if(!home) return false;

  std::string id_rsa_path = home;
  id_rsa_path += "/.ssh/id_rsa";

  if( !gdcm::System::FileExists( id_rsa_path.c_str() ) )
    {
    return false;
    }

  if( rsa.X509ParseKeyfile( id_rsa_path.c_str() ) != 0 ) // success == 0
    {
    return false;
    }
  if( rsa.CheckPubkey() != 0 || rsa.CheckPrivkey() != 0 )
    {
    return false;
    }

  return true;
}

void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcmanon [OPTION]... FILE..." << std::endl;
  std::cout << "Basic Application Level Confidentiality Profile" << std::endl;
  std::cout << "Parameter (required):" << std::endl;
  std::cout << "  -i --input       DICOM filename" << std::endl;
  std::cout << "  -o --output      DICOM filename" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "     --root-uid            Root UID." << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "  -V --verbose   more verbose (warning+error)." << std::endl;
  std::cout << "  -W --warning   print warning info." << std::endl;
  std::cout << "  -D --debug     print debug info." << std::endl;
  std::cout << "  -E --error     print error info." << std::endl;
  std::cout << "  -h --help      print help." << std::endl;
  std::cout << "  -v --version   print version." << std::endl;
  std::cout << "Env var:" << std::endl;
  std::cout << "  GDCM_ROOT_UID Root UID" << std::endl;
  std::cout << "  GDCM_RESOURCES_PATH path pointing to resources files (Part3.xml, ...)" << std::endl;
}

int main(int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  std::string filename;
  std::string outfilename;
  std::string root;
  int rootuid = 0;
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
        {"input", 1, 0, 0},                 // i
        {"output", 1, 0, 0},                // o
        {"root-uid", 1, &rootuid, 1}, // specific Root (not GDCM)

        {"verbose", 0, &verbose, 1},
        {"warning", 0, &warning, 1},
        {"debug", 0, &debug, 1},
        {"error", 0, &error, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},

        {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "i:o:VWDEhv",
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
      //printf ("option o with value '%s'\n", optarg);
      assert( outfilename.empty() );
      outfilename = optarg;
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
    std::vector<std::string> files;
    while (optind < argc)
      {
      //printf ("%s\n", argv[optind++]);
      files.push_back( argv[optind++] );
      }
    //printf ("\n");
    if( files.size() == 2 
      && filename.empty()
      && outfilename.empty() 
    )
      {
      filename = files[0];
      outfilename = files[1];
      }
    else
      {
      PrintHelp();
      return 1;
      }
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

  if( filename.empty() )
    {
    //std::cerr << "Need input file (-i)\n";
    PrintHelp();
    return 1;
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

  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle( "gdcmanon" );
  if( !rootuid )
    {
    // only read the env var is no explicit cmd line option
    // maybe there is an env var defined... let's check
    const char *rootuid_env = getenv("GDCM_ROOT_UID");
    if( rootuid_env )
      {
      rootuid = 1;
      root = rootuid_env;
      }
    }
  if( rootuid )
    {
    // root is set either by the cmd line option or the env var
    if( !gdcm::UIDGenerator::IsValid( root.c_str() ) )
      {
      std::cerr << "specified Root UID is not valid: " << root << std::endl;
      return 1;
      }
    gdcm::UIDGenerator::SetRoot( root.c_str() );
    }

  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  if( !reader.Read() )
    {
    return 1;
    }
  gdcm::File &file = reader.GetFile();

  unsigned char key[32] = {};
  gdcm::AES aes;
  const unsigned int KEY_LEN = 256;
  if( !aes.SetkeyEnc( key, KEY_LEN ) ) return 1;

  gdcm::RSA rsa;
  if( !GetRSAKey(rsa) )
    {
    return 1;
    }
  if( rsa.GetLenkey() != KEY_LEN ) return 1;

  unsigned char rsa_plaintext[KEY_LEN];
  unsigned char rsa_ciphertext[KEY_LEN];
  memcpy( rsa_plaintext, key, KEY_LEN );

  int err = rsa.Pkcs1Encrypt( gdcm::RSA::PUBLIC, KEY_LEN, rsa_plaintext, rsa_ciphertext );
  if( err != 0 )
    {
    std::cerr << "Pkcs1Encrypt failed with: " << err << std::endl;
    //return 1;
    }

  std::cout << rsa_ciphertext << std::endl;

  gdcm::Global& g = gdcm::Global::GetInstance();
  const char *xmlpath = getenv("GDCM_RESOURCES_PATH");
  if( xmlpath )
    {
    // Make sure to look for XML dict in user explicitly specified dir first:
    g.Prepend( xmlpath );
    }
  // All set, then load the XML files:
  if( !g.LoadResourcesFiles() )
    {
    return 1;
    }

  gdcm::Anonymizer anon;
  anon.SetAESKey( aes );
  anon.SetFile( file );
  anon.RemovePrivateTags();
  anon.RemoveRetired();
  if( !anon.BasicApplicationLevelConfidentialityProfile() )
    {
    return 1;
    }

  // FIXME:
  gdcm::FileMetaInformation &fmi = file.GetHeader();
  //fmi.Remove( gdcm::Tag(0x0002,0x0003) ); // will be regenerated
  fmi.Remove( gdcm::Tag(0x0002,0x0012) ); // will be regenerated
  fmi.Remove( gdcm::Tag(0x0002,0x0013) ); //  '   '    '
  fmi.Remove( gdcm::Tag(0x0002,0x0016) ); //  '   '    '

  gdcm::Writer writer;
  writer.SetFileName( outfilename.c_str() );
  writer.SetFile( file );
  if( !writer.Write() )
    {
    return 1;
    }


  return 0;
}

