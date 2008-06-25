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
#include "gdcmDefs.h"
#include "gdcmTableReader.h"
#include "gdcmSystem.h"

namespace gdcm
{

Defs::Defs()
{
}

Defs::~Defs()
{
}

void Defs::LoadDefaults()
{
  gdcm::TableReader tr(*this);
  // FIXME: hardcoded path:
  const char filename1[] = GDCM_SOURCE_DIR "/Source/InformationObjectDefinition/Part3.xml";
  const char filename2[] = GDCM_CMAKE_INSTALL_PREFIX "/" GDCM_INSTALL_INCLUDE_DIR "/XML/Part3.xml";
//    std::cerr << filename2 << std::endl;
//    std::cerr << filename1 << std::endl;
//    std::cout << System::GetCWD() << std::endl;
//   std::cout << "Argv0:" << System::GetArgv0() << std::endl;
  if( System::FileExists(filename2) )
    {
    tr.SetFilename(filename2);
    }
  else if( System::FileExists(filename1) )
    {
    tr.SetFilename(filename1);
    }
  else
    {
    throw Exception( "Impossible" );
    }
  tr.Read();
}


} // end namespace gdcm

