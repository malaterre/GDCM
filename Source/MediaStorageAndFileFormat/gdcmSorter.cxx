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
#include "gdcmSorter.h"
#include "gdcmElement.h"

#include <map>

namespace gdcm
{

Sorter::Sorter()
{
}


Sorter::~Sorter()
{
}


bool Sorter::Sort(std::vector<std::string> const & filenames)
{
  (void)filenames;
  Filenames.clear();
  return false;
}

bool Sorter::AddSelect( Tag const &tag, const char *value )
{
  Selection.insert( SelectionMap::value_type(tag,value) );
  return true;
}


void Sorter::Print( std::ostream &os)
{
  std::vector<std::string>::const_iterator it = Filenames.begin();
  for( ; it != Filenames.end(); ++it)
    {
    os << *it <<std::endl;
    }
}

} // end namespace gdcm
