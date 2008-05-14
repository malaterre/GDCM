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
  const char filename[] = GDCM_SOURCE_DIR "/Source/InformationObjectDefinition/Part3.xml";
  tr.SetFilename(filename);
  tr.Read();
}


} // end namespace gdcm

