/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmFilenameGenerator.h"
#include "gdcmTrace.h"

#include <stdio.h> // snprintf
#ifdef _WIN32
#define snprintf _snprintf
#endif

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
  std::string::size_type pat_len = Pattern.size();
  const unsigned int padding = 10; // FIXME is this large enough for all cases ?
  const unsigned int internal_len = pat_len + padding;
  const unsigned int numfiles = Filenames.size();
  if( numfiles == 0 )
    {
    gdcmDebugMacro( "Need to specify the number of files" );
    // I am pretty sure this is an error:
    return false;
    }
  bool success = true;
  char *internal = new char[internal_len];
  for( unsigned int i = 0; i < numfiles && success; ++i)
    {
    int res = snprintf( internal, internal_len, Pattern.c_str(), i );
    assert( res >= 0 );
    success = (unsigned int)res < internal_len;
    Filenames[i] = internal;
    //assert( Filenames[i].size() == res ); // upon success only
    }
  delete[] internal;
  if( !success )
    {
    Filenames.clear();
    // invalidate size too ??
    }
  return success;
}

} // namespace gdcm
