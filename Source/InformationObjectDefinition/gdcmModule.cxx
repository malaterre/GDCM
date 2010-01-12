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
#include "gdcmModule.h"
#include "gdcmDataSet.h"
#include "gdcmUsage.h"

namespace gdcm
{

bool Module::Verify(const DataSet& ds, Usage const & usage) const
{
  bool success = true;
  if( usage == Usage::UserOption ) return success;
  Module::MapModuleEntry::const_iterator it = ModuleInternal.begin();
  for(;it != ModuleInternal.end(); ++it)
    {
    const Tag &tag = it->first;
    const ModuleEntry &me = it->second;
    const gdcm::Type &type = me.GetType();
    if( ds.FindDataElement( tag ) )
      {
      // element found
      const DataElement &de = ds.GetDataElement( tag );
      if ( de.IsEmpty() && (type == Type::T1 || type == Type::T1C ) )
        {
        gdcmWarningMacro( "T1 element cannot be empty: " << de );
        success = false;
        }
      }
    else
      {
      if( type == Type::T1 || type == Type::T1C )
        {
        gdcmWarningMacro( "DataSet is missing tag: " << tag );
        gdcmWarningMacro( "ModuleEntry specify: " << me );
        gdcmWarningMacro( "Usage is: " << usage );
        success = false;
        }
      }
    }

  return success;
}

}
