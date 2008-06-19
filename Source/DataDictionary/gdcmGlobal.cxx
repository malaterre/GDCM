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
    assert( Internals->GlobalDicts.IsEmpty() );
    // Fill in with default values now !
    // at startup time is safer as later call might be from different thread
    // thus initialization of std::map would be all skrew up
    Internals->GlobalDicts.LoadDefaults();
    assert( Internals->GlobalDefs.IsEmpty() );
    // Same goes for GlobalDefs:
    Internals->GlobalDefs.LoadDefaults();
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
  assert( !Internals->GlobalDicts.IsEmpty() );
  return Internals->GlobalDicts;
}

Defs const &Global::GetDefs() const
{
  assert( !Internals->GlobalDefs.IsEmpty() );
  return Internals->GlobalDefs;
}

const Global& Global::GetInstance()
{
  return GlobalInstance;
}

// Purposely not initialized.  ClassInitialize will handle it.
GlobalInternal * Global::Internals;


} // end namespace gdcm

