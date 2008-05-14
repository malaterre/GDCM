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
/*
 * TODO:
 * Should implement the gdcmiodvfy here
 * I need to implement gdcmoverlay here (print info on overlay / img / LUT ...)
 */
#include "gdcmReader.h"
#include "gdcmMediaStorage.h"
#include "gdcmFile.h"
#include "gdcmDataSet.h"
#include "gdcmUIDs.h"
#include "gdcmGlobal.h"
#include "gdcmModules.h"
#include "gdcmDefs.h"

#include <iostream>

int main(int argc, char *argv[])
{
  const char *filename = argv[1];
  std::cout << "filename: " << filename << std::endl;
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    return 1;
    }
  const gdcm::File &file = reader.GetFile();
  const gdcm::DataSet &ds = file.GetDataSet();
  gdcm::MediaStorage ms;
  ms.SetFromFile(file);

  gdcm::UIDs uid;
  uid.SetFromUID( ms.GetString() );
  std::cout << "MediaStorage is " << ms << " [" << uid.GetName() << "]" << std::endl;

  if( ms == gdcm::MediaStorage::MRImageStorage )
    {
    const gdcm::Global& g = gdcm::Global::GetInstance();
    const gdcm::Defs &defs = g.GetDefs();
    const gdcm::Modules &modules = defs.GetModules();
    const gdcm::Module module = modules.GetModule( "MR Image Module Attributes" );
    //std::cout << module << std::endl;
    gdcm::Module::ConstIterator it = module.Begin();
    for(; it != module.End(); ++it)
      {
      const gdcm::Tag &tag = it->first;
      const gdcm::ModuleEntry &me = it->second;
      if( ds.FindDataElement( tag ) )
        {
        }
      else
        {
        //if( me.GetType() == )
          {
          std::cerr << "DataSet is missing tag: " << tag << std::endl;
          std::cerr << "ModuleEntry specify: " << me << std::endl;
          }
        }
      }
    }

  return 0;
}
