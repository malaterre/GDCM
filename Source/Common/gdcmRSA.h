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
#ifndef __gdcmRSA_h
#define __gdcmRSA_h

#include "gdcmTypes.h"

namespace gdcm
{
/**
 * \brief Class for RSA encryption
 *
http://polarssl.org//?page=forum_view_topic&topic_id=12
 */
//-----------------------------------------------------------------------------
class RSAInternals;
class GDCM_EXPORT RSA
{
public :
  RSA();
  ~RSA();

private:
  RSAInternals *Internals;
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmRSA_h
