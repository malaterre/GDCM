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
#include "gdcmFilename.h"
#include "gdcmSystem.h"
#include "gdcmTesting.h"

#include <iostream>
#include <cstdlib> // EXIT_FAILURE

/*!
 * \test TestFilename
 * bla coucou
 */
int TestFilename(int argc, char *argv[])
{
  (void)argc;(void)argv;
  std::string path = "/gdcm/is/a/dicom/";
  std::string name = "library.dcm";
  std::string fullpath = path;
  fullpath += '/';
  fullpath += name;
  gdcm::Filename f( fullpath.c_str() );
  std::cout << f.GetPath() << std::endl;
  std::cout << f.GetName() << std::endl;
  std::cout << f.GetExtension() << std::endl;
  std::cout << f << std::endl;

  if( f.GetPath() != path )
    {
    std::cerr << "Wrong path" << std::endl;
    return 1;
    }
  if( f.GetName() != name)
    {
    std::cerr << "Wrong name" << std::endl;
    return 1;
    }
  if( f.GetExtension() != std::string( ".dcm" ) )
    {
    std::cerr << "Wrong extension" << std::endl;
    return 1;
    }
//  if( std::string( "/tmp/debug.dcm" ) != f )
//    {
//    return 1;
//    }
  
  std::string dataroot = gdcm::Testing::GetDataRoot();
  std::string current = dataroot +  "/test.acr";
  if( !gdcm::System::FileExists( current.c_str() ) )
    {
    std::cerr << "File does not exist: " << current << std::endl;
    return 1;
    }
  std::cerr << "Current:" << current << std::endl;
  gdcm::Filename fn(current.c_str());
  std::cerr << fn.GetPath() << std::endl;
  std::string current2 = fn.GetPath();
  current2 += "/./";
  current2 += fn.GetName();
  std::cerr << current2 << std::endl;
  if( current2 == current )
    {
    return 1;
    }
  gdcm::Filename fn2(current2.c_str());
  if( !fn.IsIdentical(fn2))
    {
    return 1;
    }

  {
  const char *curprocfn = gdcm::System::GetCurrentProcessFileName();
  if( curprocfn )
    {
    gdcm::Filename fn( curprocfn );
    std::string str = fn.GetPath();
    std::cout << str << std::endl;
    }
  }

{
#ifdef HAVE_WCHAR_IFSTREAM
  const wchar_t ifn[] = L"UnicodeFileName.dcm"; 
  const wchar_t* fn = gdcm::Testing::GetTempFilenameW(ifn);
  std::ofstream outputFileStream( fn );
  if ( ! outputFileStream.is_open() )
    {
    std::cerr << "Failed to read UTF-16: " << fn << std::endl;
    return EXIT_FAILURE;
    }
  outputFileStream.close();
#else
  //char ifn2[] = "α.dcm"; //MM: I do not think this is legal C++...
  char ifn2[] = "\xCE\xB1.dcm"; // this is the proper way to write it (portable)
  char ifn1[] = {
  (char)0xCE,
  (char)0xB1,
  '.',
  'd',
  'c',
  'm',
  0}; // trailing NULL char
  std::string sfn1 = gdcm::Testing::GetTempFilename(ifn1);
  const char *fn1 = sfn1.c_str();
  std::string sfn2 = gdcm::Testing::GetTempFilename(ifn2);
  const char *fn2 = sfn2.c_str();
  std::ofstream outputFileStream( fn1 );
  if ( ! outputFileStream.is_open() )
    {
    std::cerr << "Failed to create UTF-8 file: " << fn1 << std::endl;
    return EXIT_FAILURE;
    }
  const char secret[]= "My_secret_pass_phrase";
  outputFileStream << secret;
  outputFileStream.close();
  if( !gdcm::System::FileExists(fn1) )
    {
    std::cerr << "File does not exist: " << fn1 << std::endl;
    return EXIT_FAILURE;
    }

  // Now open version 2 (different encoding)
  std::ifstream inputFileStream( fn2 );
  if ( ! inputFileStream.is_open() )
    {
    std::cerr << "Failed to open UTF-8 file: " << fn2 << std::endl;
    return EXIT_FAILURE;
    }
  std::string ssecret;
  inputFileStream >> ssecret;
  inputFileStream.close();
  if( ssecret != secret )
    {
    std::cerr << "Found: " << ssecret << " should have been " << secret << std::endl;
    return EXIT_FAILURE;
    }

  if( !gdcm::System::RemoveFile(fn1) )
    {
    std::cerr << "Could not remvoe #1: " << fn1 << std::endl;
    return EXIT_FAILURE;
    }
  // cannot remove twice the same file:
  if( gdcm::System::RemoveFile(fn2) )
    {
    std::cerr << "Could remvoe #2 a second time...seriously " << fn2 << std::endl;
    return EXIT_FAILURE;
    }
#endif
}

{
  // Apparently there is an issue with long pathanem i nWin32 system:
  // http://msdn.microsoft.com/en-us/library/aa365247(VS.85).aspx#maxpath
  // The only way to work around the 260 byte limitation it appears as if we
  // have to deal with universal naming convention (UNC) path.
  const char subdir[] = 
    "very/long/pathname/foobar/hello_world/toreproduceabugindpkg/pleaseconsider/"
    "very/long/pathname/foobar/hello_world/toreproduceabugindpkg/pleaseconsider/"
    "very/long/pathname/foobar/hello_world/toreproduceabugindpkg/pleaseconsider/"
    "very/long/pathname/foobar/hello_world/toreproduceabugindpkg/pleaseconsider/";
  const char *directory_ = gdcm::Testing::GetTempDirectory(subdir);
#ifdef _WIN32
  gdcm::Filename mydir( directory_ );
  std::string unc = "\\\\?\\";
  unc += mydir.ToWindowsSlashes();
  const char *directory = unc.c_str();
#else
  const char *directory = directory_;
#endif
  if( !gdcm::System::MakeDirectory(directory))
    {
    std::cerr << "Failed to create directory with long path: " << directory << std::endl;
    return EXIT_FAILURE;
    }
std::string sfn = gdcm::Testing::GetTempFilename( "dummy.dcm", subdir );
  std::cerr << "Long path is: " << sfn.size() << std::endl;
  std::cerr << "Long path is: " << sfn << std::endl;
  if( sfn.size() > 260 )
    {
    const char *fn = sfn.c_str();
    // Should demontrate the issue
  std::ofstream outputFileStream( fn );
  if ( ! outputFileStream.is_open() )
    {
    std::cerr << "Failed to create file with long path: " << fn << std::endl;
    return EXIT_FAILURE;
    }
  outputFileStream.close();
  if( !gdcm::System::FileExists(fn) )
    {
    std::cerr << "File does not exist: " << fn << std::endl;
    return EXIT_FAILURE;
    }
  if( !gdcm::System::RemoveFile(fn) )
    {
    std::cerr << "Could not remvoe: " << fn << std::endl;
    return EXIT_FAILURE;
    }

    }
else
{
    std::cerr << "seriously " << fn << std::endl;
    return EXIT_FAILURE;
}
}

  return 0;
}

