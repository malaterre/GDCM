/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmHAVEGE_h
#define __gdcmHAVEGE_h

#include "gdcmTypes.h"
#error

namespace gdcm
{
/**
 * \brief Class for HAVEGE 
 * [ HArdware Volatile Entropy Gathering and Expansion ]
 * http://www.irisa.fr/caps/projects/hipsor/publi.php
 *
 */
//-----------------------------------------------------------------------------
class HAVEGEInternals;
class GDCM_EXPORT HAVEGE
{
public :
  HAVEGE();
  ~HAVEGE();

/**
 * \brief          HAVEGE rand function
 *
 * \return         A random int
 */
int Rand( );

private:
  HAVEGEInternals *Internals;

private:
  HAVEGE(const HAVEGE&);  // Not implemented.
  void operator=(const HAVEGE&);  // Not implemented.
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmHAVEGE_h
