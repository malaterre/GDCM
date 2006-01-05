/*=========================================================================
  
  Program:   gdcm
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$
  
  Copyright (c) CREATIS (Centre de Recherche et d'Applications en Traitement de
  l'Image). All rights reserved. See Doc/License.txt or
  http://www.creatis.insa-lyon.fr/Public/Gdcm/License.html for details.
  
     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.
  
=========================================================================*/

#include "gdcmfstream.h"
#include <iostream>
#include <assert.h>

namespace gdcm {


ifstream::ifstream(const char* filename,openmode mode)
   :std::ifstream(filename,mode)
{
  fragments.clear();
  currentpos = 0; // initial state
}

std::istream& ifstream::read(char* s, std::streamsize n )
{
  //std::cerr << "my read" << std::endl;
  int numfrags = fragments.size();
  assert( currentpos <= numfrags );
  int i = 0;
  std::streamsize fsize = fragments[i].second; //fragment size
  if( n < fsize )
    {
    // If fragment size is bigger than requested num of bytes:
    return this->std::ifstream::read(s,n);
    }
  else
    {
    this->std::ifstream::read(s,fsize);
    ++i;
    // recusive call
    if( i == numfrags )
      {
      // gcount = fsize;
      }
    return this->read(s+fsize,n-fsize);
    }
}

std::streamsize ifstream::filesize()
{
  std::streamsize size = 0;
  for( listfragments::const_iterator it = fragments.begin();
      it != fragments.end();
      ++it)
    {
    size += it->second;
    }
  return size;
}

std::streamsize ifstream::gcount ( ) const
{
  //FIXME
  abort();
}

} //end namespace gdcm

