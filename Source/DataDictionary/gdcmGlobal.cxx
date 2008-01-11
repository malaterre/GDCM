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

namespace gdcm
{

// Must NOT be initialized.  Default initialization to zero is
// necessary.
unsigned int GlobalCount;

class GlobalInternal
{
public:
  GlobalInternal():GlobalDicts() {}
  Dicts GlobalDicts; // Part 6 + Part 4 elements
// TODO need H table for TransferSyntax / MediaStorage / Part 3 ...
};

Global::Global()
{
  if(++GlobalCount == 1)
    {
    assert( Internals == NULL ); // paranoid
    Internals = new GlobalInternal;
    // Fill in with default values:
    Internals->GlobalDicts.Initialize();
    }
}

Global::~Global()
{
  if(--GlobalCount == 0)
    {
    Internals->GlobalDicts.Finalize();
    delete Internals;
    Internals = NULL; // paranoid
    }
}

Dicts const &Global::GetDicts() const
{
  return Internals->GlobalDicts;
}

// Purposely not initialized.  ClassInitialize will handle it.
GlobalInternal * Global::Internals;


} // end namespace gdcm

