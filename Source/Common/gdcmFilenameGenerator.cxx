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
#include "gdcmFilenameGenerator.h"

namespace gdcm
{

//-----------------------------------------------------------------------------
unsigned int FilenameGenerator::GetNumberOfFilenames() const
{
  return Filenames.size();
}

//-----------------------------------------------------------------------------
void FilenameGenerator::SetNumberOfFilenames(unsigned int nfiles)
{
  Filenames.resize( nfiles );
}

//-----------------------------------------------------------------------------
const char * FilenameGenerator::GetFilename(unsigned int n) const
{
  assert( n < Filenames.size() );
  return Filenames[n].c_str();
}

//-----------------------------------------------------------------------------
bool FilenameGenerator::Generate()
{
  if( Pattern.empty() )
    {
    return false;
    }
  std::string::size_type len = Pattern.size();
  char *internal = new char[len + 10]; // FIXME: 10 ??
  const unsigned int numfiles = Filenames.size();
  if( numfiles == 0 )
    {
    // I am pretty sure this is an error:
    return false;
    }
  for( unsigned int i = 0; i < numfiles; ++i)
    {
    sprintf( internal, Pattern.c_str(), i );
    Filenames[i] = internal;
    }
  delete[] internal;
  return true;
}

} // namespace gdcm
