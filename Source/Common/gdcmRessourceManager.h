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
#ifndef __gdcmRessourceManager_h
#define __gdcmRessourceManager_h

#include "gdcmTypes.h"

namespace gdcm
{

/**
 * \brief Class to handle external ressource
 * typically the DICOM dict, Part 3, 6 and 7 as XML
 */
class GDCM_EXPORT RessourceManager
{
public:
  /// Locate a GDCM ressource file (eg. Part3.xml)
  /// return NULL in case of error (input file contains slash, or cannot be found)
  static const char *Locate(const char *resfile);

  void Print(std::ostream &os);

protected:

private:
};

} // end namespace gdcm

#endif //__gdcmRessourceManager_h
