/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmEquipmentManufacturer.h"

#include "gdcmAttribute.h"

namespace gdcm
{

struct Mapping
{
  EquipmentManufacturer::Type type;
  size_t nstrings;
  const char* const *strings;
};

static const char* const gems[] = {"GE MEDICAL SYSTEMS"} ;
static const char* const pms[] = { "Philips Medical Systems", "Philips Healthcare", "Philips Medical Systems, Inc." };
static const char* const siemens[] = { "SIEMENS" };
static const char* const marconi[] = { "Marconi Medical Systems, Inc." };
static const char* const toshiba[] = { "TOSHIBA_MEC" };

#define ARRAY_SIZE( X ) \
  sizeof(X) / sizeof(*X)

#define MAPPING(X, Y) \
  { X, ARRAY_SIZE(Y), Y }

static const Mapping mappings[] = {
  MAPPING( EquipmentManufacturer::GEMS, gems ),
  MAPPING( EquipmentManufacturer::PMS, pms ),
  MAPPING( EquipmentManufacturer::SIEMENS, siemens ),
  MAPPING( EquipmentManufacturer::MARCONI, marconi ),
  MAPPING( EquipmentManufacturer::TOSHIBA, toshiba )
};

EquipmentManufacturer::Type EquipmentManufacturer::Compute( DataSet const & ds )
{
  // proper anonymizer should not touch Manufacturer attribute value:
  // http://dicom.nema.org/medical/dicom/current/output/chtml/part15/chapter_E.html#table_E.1-1
  gdcm::Attribute<0x0008,0x0070> manu = { "" }; // Manufacturer
  manu.SetFromDataSet( ds );
  const std::string manufacturer = manu.GetValue().Trim();
  for( const Mapping * mapping = mappings; mapping != mappings + ARRAY_SIZE(mappings); ++mapping )
  {
    for( size_t i = 0; i < mapping->nstrings; ++i )
    {
      if( strcmp( mapping->strings[i], manufacturer.c_str() ) == 0 )
        return mapping->type;
    }
  }

  return UNKNOWN;
}

} // end namespace gdcm
