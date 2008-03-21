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
#ifndef __gdcmSorter_h
#define __gdcmSorter_h

#include "gdcmDirectory.h"

#include <vector>
#include <string>

namespace gdcm
{
/**
 * \brief Sorter
 */
class GDCM_EXPORT Sorter
{
public:
  Sorter();
  ~Sorter();

  // Typically the output of gdcm::Directory::GetFilenames()
  bool Sort(std::vector<std::string> const & filenames);

private:
};


} // end namespace gdcm

#endif //__gdcmSorter_h
