/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmRessourceManager.h"
#include "gdcmSystem.h"
#include "gdcmFilename.h"

#include <stdlib.h>

namespace gdcm
{

const char *RessourceManager::Locate(const char *resfile)
{
  // FIXME: hardcoded path:
  const char filename1[] = GDCM_SOURCE_DIR "/Source/InformationObjectDefinition/Part3.xml";
  const char filename2[] = GDCM_CMAKE_INSTALL_PREFIX "/" GDCM_INSTALL_DATA_DIR "/XML/Part3.xml";
  const char *datadir = System::GetCurrentDataDirectory();
  std::string filename3;
  if ( datadir )
    {
    filename3 = datadir;
    filename3 += "/XML/Part3.xml";
    }
  //std::cerr << filename3 << std::endl;
  //std::cerr << "where: " << myenv << std::endl;
  //std::cerr << "python: " << fn.GetName() << std::endl;
  // python2.4
  // python2.5
  // Python.exe 
  // ...
  // let's do a simple comparison:
  const char python[] = "python";
  std::string filename4;
  gdcm::Filename fn( System::GetCurrentProcessFileName() );
  if( System::StrNCaseCmp( python, fn.GetName(), strlen(python) ) == 0 )
    {
    const char *myenv = getenv("GDCM_WHEREAMI");
    const char *myenv2 = getenv("GDCM_WHEREAMI2");
    if(myenv)
      {
      filename4 = myenv;
      filename4 += "/../../../" GDCM_INSTALL_DATA_DIR "/XML/Part3.xml";
      }
    else if(myenv2)
      {
      filename4 = myenv2;
      filename4 += "/Part3.xml";
      }
    }
//    std::cerr << filename4 << std::endl;
//    std::cerr << filename2 << std::endl;
//    std::cerr << filename1 << std::endl;
//    std::cout << System::GetCWD() << std::endl;
//   std::cout << "Argv0:" << System::GetArgv0() << std::endl;
/* Order is:
 * 1. Check installation directory (static)
 * 2. If not found: check relative to current process execution dir (dynamic)
 * 3. If process is python, check env var to get directory path (dynamic)
 * 4. Hum, alright let's check in the source tree (+warning) (static)
 */
  if( System::FileExists(filename2) )
    {
    tr.SetFilename(filename2);
    }
  else if( System::FileExists(filename3.c_str()) )
    {
    tr.SetFilename(filename3.c_str());
    }
  else if( System::FileExists(filename4.c_str()) )
    {
    tr.SetFilename(filename4.c_str());
    }
  // This one should at least print a warning that source cannot be deleted
  else if( System::FileExists(filename1) )
    {
    gdcmDebugMacro( "Using file from the source directory: " << filename1 );
    tr.SetFilename(filename1);
    }
  else
    {
    gdcmErrorMacro( "Something went wrong in your installation of GDCM. Please report" );
    throw Exception( "Impossible" );
    return;
    }

}

} // end namespace gdcm
