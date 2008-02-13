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
#include "gdcmWriter.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmDataSet.h"
#include "gdcmTrace.h"

namespace gdcm
{

Writer::~Writer()
{
}

bool Writer::Write()
{
  if( !Stream.is_open() )
    {
    gdcmErrorMacro( "No Filename" );
    return false;
    }

  //assert( F );
  F->Write( Stream );

  // FIXME : call this function twice...
  Stream.close();

  return true;
}

} // end namespace gdcm

