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
#include "gdcmTagPath.h"
#include "gdcmTag.h"

#include <vector>
#include <string.h> // strlen

namespace gdcm
{

TagPath::TagPath():Path()
{
}

TagPath::~TagPath()
{
}

void TagPath::Print(std::ostream &os) const
{
  std::vector<Tag>::const_iterator it = Path.begin();
  for(; it != Path.end(); ++it)
  {
	  os << *it << std::endl;
  }
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
  Path.clear();
  while( pos != len )
  {
  if( path[pos] == '/' )
  {
	  ++pos;
  }
  Tag t;
  t.ReadFromCommaSeparatedString( path+pos );
  pos += 4 + 4 + 1;
  Path.push_back( t );
  }
}

void TagPath::Push(Tag const & t)
{
  Path.push_back( t );
}

void TagPath::Push(unsigned int itemnum)
{
}

}

