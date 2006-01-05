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

#ifndef __gdcmfstream_
#define __gdcmfstream_

#include <fstream>
#include <list>

namespace gdcm {

class ifstream : public std::ifstream
{
// First the position of the fragment, then the fragment lenght
typedef std::pair<std::streampos, std::streamsize> fragment;

public:
  explicit ifstream(const char* filename,
    std::ios_base::openmode mode = std::ios_base::in);

  std::istream&  read (char* s, std::streamsize n );
  inline void add_fragment(fragment f) { fragments.push_back(f); }

private:
  std::list<fragment> fragments;
};

} //end namespace gdcm

#endif
