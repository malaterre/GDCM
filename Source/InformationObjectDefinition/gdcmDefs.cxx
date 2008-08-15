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
#include "gdcmMediaStorage.h"
#include "gdcmTrace.h"
#include "gdcmFilename.h"

#include <stdlib.h>

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
  TableReader tr(*this);
  // FIXME: hardcoded path:
  const char filename1[] = GDCM_SOURCE_DIR "/Source/InformationObjectDefinition/Part3.xml";
  const char filename2[] = GDCM_CMAKE_INSTALL_PREFIX "/" GDCM_INSTALL_DATA_DIR "/XML/Part3.xml";
  gdcm::Filename fn( System::GetCurrentProcessFileName() );
  std::string filename3 = fn.GetPath();
  filename3 += "/../" GDCM_INSTALL_DATA_DIR "/XML/Part3.xml";
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
  tr.Read();
}

const char *Defs::GetIODNameFromMediaStorage(MediaStorage &ms) const
{
  const char *iodname;
  switch(ms)
    {
    case MediaStorage::MRImageStorage:
      iodname = "MR Image IOD Modules";
      break;
    case MediaStorage::CTImageStorage:
      iodname = "CT Image IOD Modules";
      break;
    default:
      iodname = 0;
    }
  return iodname;
}

bool Defs::Verify(const DataSet& ds) const
{
  MediaStorage ms;
  ms.SetFromDataSet(ds);

  const IODs &iods = GetIODs();
  const Modules &modules = GetModules();
  const char *iodname = GetIODNameFromMediaStorage( ms );
  if( !iodname )
    {
    gdcmErrorMacro( "Not implemented" );
    return false;
    }
  const IOD &iod = iods.GetIOD( iodname );

  //std::cout << iod << std::endl;
  //std::cout << iod.GetIODEntry(14) << std::endl;
  unsigned int niods = iod.GetNumberOfIODs();
  bool v = true;
  // Iterate over each iod entry in order:
  for(unsigned int idx = 0; idx < niods; ++idx)
    {
    const IODEntry &iodentry = iod.GetIODEntry(idx);
    const char *ref = iodentry.GetRef();
    IODEntry::UsageType ut = iodentry.GetUsageType();

    const Module &module = modules.GetModule( ref );
    //std::cout << module << std::endl;
    v = v && module.Verify( ds );
    }

  return v;

}


} // end namespace gdcm

