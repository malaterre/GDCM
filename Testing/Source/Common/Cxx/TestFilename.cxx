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
#include "gdcmFilename.h"
#include "gdcmSystem.h"
#include "gdcmTesting.h"

#include <iostream>

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
    return 1;
    }
  if( f.GetName() != name)
    {
    return 1;
    }
  if( f.GetExtension() != std::string( ".dcm" ) )
    {
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

  return 0;
}

