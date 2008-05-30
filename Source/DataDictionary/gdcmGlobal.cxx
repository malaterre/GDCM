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
#include "gdcmGlobal.h"
#include "gdcmDicts.h"
#include "gdcmDefs.h"

namespace gdcm
{

// Must NOT be initialized.  Default initialization to zero is
// necessary.
unsigned int GlobalCount;

class GlobalInternal
{
public:
  GlobalInternal():GlobalDicts(),GlobalDefs() {}
  Dicts GlobalDicts; // Part 6 + Part 4 elements
// TODO need H table for TransferSyntax / MediaStorage / Part 3 ...
  Defs GlobalDefs;
};

Global::Global()
{
  if(++GlobalCount == 1)
    {
    assert( Internals == NULL ); // paranoid
    Internals = new GlobalInternal;
    }
}

Global::~Global()
{
  if(--GlobalCount == 0)
    {
    //Internals->GlobalDicts.Unload();
    delete Internals;
    Internals = NULL; // paranoid
    }
}

Dicts const &Global::GetDicts() const
{
  if( Internals->GlobalDicts.IsEmpty() )
    {
    // Fill in with default values:
    Internals->GlobalDicts.LoadDefaults();
    }
  return Internals->GlobalDicts;
}

Defs const &Global::GetDefs() const
{
  if( Internals->GlobalDefs.IsEmpty() )
    {
    // Fill in with default values:
    Internals->GlobalDefs.LoadDefaults();
    }
  return Internals->GlobalDefs;
}

const Global& Global::GetInstance()
{
  return GlobalInstance;
}

// Purposely not initialized.  ClassInitialize will handle it.
GlobalInternal * Global::Internals;


} // end namespace gdcm

