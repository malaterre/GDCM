/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmDefs.h"
#include "gdcmTableReader.h"
#include "gdcmMediaStorage.h"
//#include "gdcmGlobal.h"
#include "gdcmTrace.h"
#include "gdcmFile.h"

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
//  TableReader tr(*this);
//  const Global &g = Global::GetInstance();
//  const char *filename = g.Locate( "Part3.xml" );
//  
//  if( filename )
//    {
//    tr.SetFilename(filename);
//    tr.Read();
//    }
//  else
//    {
//    gdcmErrorMacro( "Could not find Part3.xml file. Please report" );
//    throw Exception( "Impossible" );
//    }
}

void Defs::LoadFromFile(const char *filename)
{
  assert( filename );
  TableReader tr(*this);
  tr.SetFilename(filename);
  tr.Read();
}

const char *Defs::GetIODNameFromMediaStorage(MediaStorage const &ms)
{
  const char *iodname;
  switch(ms)
    {
    case MediaStorage::MediaStorageDirectoryStorage:
      iodname = "Basic Directory IOD Modules";
      break;
    case MediaStorage::MRImageStorage:
      iodname = "MR Image IOD Modules";
      break;
    case MediaStorage::EnhancedMRImageStorage:
      iodname = "Enhanced MR Image IOD Modules";
      break;
    case MediaStorage::CTImageStorage:
      iodname = "CT Image IOD Modules";
      break;
    case MediaStorage::EnhancedCTImageStorage:
      iodname = "Enhanced CT Image IOD Modules";
      break;
    case MediaStorage::ComputedRadiographyImageStorage:
      iodname = "CR Image IOD Modules";
      break;
    case MediaStorage::XRayAngiographicImageStorage:
      iodname = "X Ray Angiographic Image IOD Modules";
      break;
    case MediaStorage::UltrasoundImageStorageRetired:
    case MediaStorage::UltrasoundImageStorage:
      iodname = "US Image IOD Modules";
      break;
    case MediaStorage::UltrasoundMultiFrameImageStorageRetired:
    case MediaStorage::UltrasoundMultiFrameImageStorage:
      iodname ="US Multi Frame Image IOD Modules";
      break;
    case MediaStorage::SecondaryCaptureImageStorage:
      iodname = "SC Image IOD Modules";
      break;
    case MediaStorage::DigitalXRayImageStorageForPresentation:
      iodname = "Digital X Ray Image IOD Modules";
      break;
    case MediaStorage::XRayRadiofluoroscopingImageStorage:
      iodname = "XRF Image IOD Modules";
      break;
    case MediaStorage::MRSpectroscopyStorage:
      iodname = "MR Spectroscopy IOD Modules";
      break;
    case MediaStorage::NuclearMedicineImageStorageRetired:
    case MediaStorage::NuclearMedicineImageStorage:
      iodname = "NM Image IOD Modules";
      break;
    case MediaStorage::MultiframeSingleBitSecondaryCaptureImageStorage:
      iodname = "Multi Frame Single Bit SC Image IOD Modules";
      break;
    case MediaStorage::MultiframeGrayscaleByteSecondaryCaptureImageStorage:
      iodname = "Multi Frame Grayscale Byte SC Image IOD Modules";
      break;
    case MediaStorage::MultiframeGrayscaleWordSecondaryCaptureImageStorage:
      iodname = "Multi Frame Grayscale Word SC Image IOD Modules";
      break;
    case MediaStorage::MultiframeTrueColorSecondaryCaptureImageStorage:
      iodname = "Multi Frame True Color SC Image IOD Modules";
      break;
    case MediaStorage::EncapsulatedPDFStorage:
      iodname = "Encapsulated PDF IOD Modules";
      break;
    case MediaStorage::DigitalMammographyImageStorageForPresentation:
    case MediaStorage::DigitalMammographyImageStorageForProcessing:
      iodname = "Digital Mammography X Ray Image IOD Modules";
      break;
    case MediaStorage::RawDataStorage:
      iodname = "Raw Data IOD Modules";
      break;
    default:
      iodname = 0;
    }
  return iodname;
}

Type Defs::GetTypeFromTag(const File& file, const Tag& tag) const
{
  Type ret;
  MediaStorage ms;
  ms.SetFromFile(file); // SetFromDataSet does not handle DICOMDIR

  const IODs &iods = GetIODs();
  const Modules &modules = GetModules();
  const char *iodname = GetIODNameFromMediaStorage( ms );
  if( !iodname )
    {
    gdcmErrorMacro( "Not implemented: " << ms );
    return ret;
    }
  const IOD &iod = iods.GetIOD( iodname );

  unsigned int niods = iod.GetNumberOfIODs();
  // Iterate over each iod entry in order:
  for(unsigned int idx = 0; idx < niods; ++idx)
    {
    const IODEntry &iodentry = iod.GetIODEntry(idx);
    const char *ref = iodentry.GetRef();
    //Usage::UsageType ut = iodentry.GetUsageType();

    const Module &module = modules.GetModule( ref );
    if( module.FindModuleEntry( tag ) )
      {
      const ModuleEntry &module_entry = module.GetModuleEntry(tag);
      ret = module_entry.GetType();
      }
    }

  return ret;
}

bool Defs::Verify(const File& file) const
{
  MediaStorage ms;
  ms.SetFromFile(file);

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
    Usage::UsageType ut = iodentry.GetUsageType();

    const Module &module = modules.GetModule( ref );
    //std::cout << module << std::endl;
    v = v && module.Verify( file.GetDataSet(), ut );
    }

  return v;

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
    Usage::UsageType ut = iodentry.GetUsageType();

    const Module &module = modules.GetModule( ref );
    //std::cout << module << std::endl;
    v = v && module.Verify( ds, ut );
    }

  return v;

}


} // end namespace gdcm

