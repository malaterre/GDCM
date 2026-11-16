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

#include <atomic>
#include <cassert>

namespace gdcm_ns
{


namespace
{
// The depth is counted per thread so independent parses do not affect each other.
// The limit is shared by all threads, so it is atomic: SetLimit() may run while
// another thread is parsing.
thread_local unsigned int parse_depth = 0;
std::atomic<unsigned int> parse_limit{128};
}

ParseDepthGuard::ParseDepthGuard()
{
  if( ++parse_depth > parse_limit.load(std::memory_order_relaxed) )
    {
    --parse_depth;
    throw NestingDepthException();
    }
}

ParseDepthGuard::~ParseDepthGuard()
{
  --parse_depth;
}

unsigned int ParseDepthGuard::GetLimit()
{
  return parse_limit.load(std::memory_order_relaxed);
}

bool ParseDepthGuard::SetLimit(unsigned int limit)
{
  if( limit == 0 )
    {
    return false;
    }
  parse_limit.store(limit, std::memory_order_relaxed);
  return true;
}

} // end namespace gdcm
