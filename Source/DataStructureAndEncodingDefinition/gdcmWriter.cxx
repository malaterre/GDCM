/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
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

/// \precondition we are at the beginning of file
bool Writer::WritePreamble()
{
  if( Preamble )
    {
    Stream.Write( Preamble, 128+4);
    }
#if 0
  char dicm[128];
  memset( dicm, 0, 128 );
  Stream.Write( dicm, 128);
  Stream.Write( "DICM", 4);
#endif

  return true;
}

bool Writer::Write()
{
  if( !Stream.IsOpen() )
    {
    gdcmErrorMacro( "No File" );
    return false;
    }
  if ( !WritePreamble() )
    {
    return false;
    }
  if( !Header )
    {
    Header = new FileMetaInformation;
    }
  Header->Write(Stream);
  if( !DS )
    {
    DS = new DataSet;
    }
  DS->Write(Stream);

  Stream.Close();

  return true;
}

} // end namespace gdcm
