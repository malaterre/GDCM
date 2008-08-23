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
#ifndef __gdcmImageCSAFilter_h
#define __gdcmImageCSAFilter_h

#include "gdcmFile.h"

namespace gdcm
{

/**
 * \brief ImageCSAFilter class
 * Class to reshuffle byes for a SIEMENS Mosaic image
 *
 * Everything done in this code is for the sole purpose of writing interoperable 
 * software under Sect. 1201 (f) Reverse Engineering exception of the DMCA.
 * If you believe anything in this code violates any law or any of your rights, 
 * please contact us (gdcm-developers@lists.sourceforge.net) so that we can 
 * find a solution. 
 *
 */
class GDCM_EXPORT ImageCSAFilter
{
public:
  ImageCSAFilter();
  ~ImageCSAFilter();

  bool Filter();

protected:

private:
};

} // end namespace gdcm

#endif //__gdcmImageCSAFilter_h

