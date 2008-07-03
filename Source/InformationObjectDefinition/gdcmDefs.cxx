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

const char *Defs::GetIODNameFromMediaStorage(MediaStorage &ms) const
{
  const char *iodname;
  switch(ms)
    {
    case MediaStorage::MRImageStorage:
      iodname = "MR Image IOD Modules";
      break;
    default:
      iodname = 0;
    }
  return iodname;
}

bool Defs::Verify(const DataSet& ds) const
{
  gdcm::MediaStorage ms;
  ms.SetFromDataSet(ds);

  const gdcm::IODs &iods = GetIODs();
  const char *iodname = GetIODNameFromMediaStorage( ms );
  const gdcm::IOD &iod = iods.GetIOD( iodname );

  //std::cout << iod << std::endl;
  //std::cout << iod.GetIODEntry(14) << std::endl;
  const char *ref = iod.GetIODEntry(14).GetRef();

  const Modules &modules = GetModules();
  const Module module = modules.GetModule( ref );
  //std::cout << module << std::endl;
  bool v = module.Verify( ds );

  return v;

}


} // end namespace gdcm

