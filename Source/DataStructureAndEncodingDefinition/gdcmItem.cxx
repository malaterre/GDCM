/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmItem.h"

#include <cassert>
#include "gdcmException.h"

namespace gdcm_ns
{


namespace
{
// One counter per thread: a thread_local keeps independent parses from affecting
// each other without requiring a lock on the hot path.
thread_local unsigned int parse_depth = 0;
unsigned int parse_limit = 1000;
}

ParseDepthGuard::ParseDepthGuard()
{
  if( ++parse_depth > parse_limit )
    {
    --parse_depth;
    throw Exception( "Nesting depth limit exceeded while parsing data set" );
    }
}

ParseDepthGuard::~ParseDepthGuard()
{
  --parse_depth;
}

unsigned int ParseDepthGuard::GetLimit()
{
  return parse_limit;
}

void ParseDepthGuard::SetLimit(unsigned int limit)
{
  parse_limit = limit;
}

} // end namespace gdcm
