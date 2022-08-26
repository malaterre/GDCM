/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMMEC_MR3_H
#define GDCMMEC_MR3_H

#include "gdcmTypes.h"

namespace gdcm
{
/**
 * \brief Class for MEC_MR3
 *
 */
class GDCM_EXPORT MEC_MR3
{
public:
  static void Print(const char *src, size_t srclen);
};

} // end namespace gdcm

#endif // GDCMMEC_MR3_H
