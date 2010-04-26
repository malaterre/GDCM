/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmIOD.h"

#include "gdcmDataSet.h"
#include "gdcmModule.h"
#include "gdcmModules.h"

namespace gdcm
{

Type IOD::GetTypeFromTag(const Modules &modules, const Tag& tag) const
{
  throw "FIXME";
  Type ret;
  const IOD &iod = *this;

  const unsigned int niods = iod.GetNumberOfIODs();
  // Iterate over each iod entry in order:
  bool found = false;
  for(unsigned int idx = 0; !found && idx < niods; ++idx)
    {
    const IODEntry &iodentry = iod.GetIODEntry(idx);
    const char *ref = iodentry.GetRef();
    //Usage::UsageType ut = iodentry.GetUsageType();

    const Module &module = modules.GetModule( ref );
    //if( module.FindModuleEntry( tag ) )
    //  {
    //  const ModuleEntry &module_entry = module.GetModuleEntry(tag);
    //  ret = module_entry.GetType();
    //  found = true;
    //  }
    }

  return ret;
}

}

