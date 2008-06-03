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
#include "gdcmImageReader.h"
#include "gdcmMediaStorage.h"
#include "gdcmFile.h"
#include "gdcmDataSet.h"
#include "gdcmUIDs.h"
#include "gdcmGlobal.h"
#include "gdcmModules.h"
#include "gdcmDefs.h"
#include "gdcmOrientation.h"

#include <iostream>

int main(int argc, char *argv[])
{
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
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

  if( gdcm::MediaStorage::IsImage( ms ) )
    {
    gdcm::ImageReader reader;
    reader.SetFileName( filename );
    if( !reader.Read() )
      {
      return 1;
      }
    const gdcm::File &file = reader.GetFile();
    const gdcm::DataSet &ds = file.GetDataSet();
    const gdcm::Image &image = reader.GetImage();
    const double *dircos = image.GetDirectionCosines();
    gdcm::Orientation::OrientationType type = gdcm::Orientation::GetType(dircos);
    const char *label = gdcm::Orientation::GetLabel( type );
    image.Print( std::cout );
    std::cout << "Orientation Label: " << label << std::endl;

    }

  if( ms == gdcm::MediaStorage::MRImageStorage && false )
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
      const gdcm::Type &type = me.GetType();
      if( ds.FindDataElement( tag ) )
        {
        // element found
        const gdcm::DataElement &de = ds.GetDataElement( tag );
        if ( de.IsEmpty() && (type == gdcm::Type::T1 || type == gdcm::Type::T1C ) )
          {
          std::cerr << "T1 element cannot be empty: " << de << std::endl;
          }
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
