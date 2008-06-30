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
#include "gdcmTagPath.h"
#include "gdcmTag.h"

#include <vector>

namespace gdcm
{

TagPath::TagPath()
{
}

TagPath::~TagPath()
{
}

void TagPath::Print(std::ostream &os) const
{
}

bool TagPath::IsValid(const char *path)
{
  return false;
}

void TagPath::ConstructFromTagList(Tag const *l, unsigned int n)
{
  Path = std::vector<Tag>(l,l+n);
}

void TagPath::ConstructFromString(const char *path)
{
  size_t pos = 0;
  const size_t len = strlen(path);
  while( pos != len )
  {
  if( path[pos] == '/' )
  {
	  ++pos;
  }
  Tag t;
  t.ReadFromCommaSeparatedString( path+pos );
  }
}

}

