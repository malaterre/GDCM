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
#include "gdcmDefs.h"
#include "gdcmTableReader.h"
#include "gdcmMediaStorage.h"
#include "gdcmGlobal.h"
#include "gdcmTrace.h"

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
  const Global &g = Global::GetInstance();
  const char *filename = g.Locate( "Part3.xml" );
  
  if( filename )
    {
    tr.SetFilename(filename);
    tr.Read();
    }
  else
    {
    gdcmErrorMacro( "Could not find Part3.xml file. Please report" );
    throw Exception( "Impossible" );
    }
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

