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

/**
 * \brief          Add the message padding, then do an RSA operation
 *
 * \param ctx      RSA context
 * \param mode     RSA_PUBLIC or RSA_PRIVATE
 * \param ilen     contains the plaintext length
 * \param input    buffer holding the data to be encrypted
 * \param output   buffer that will hold the ciphertext
 *
 * \return         0 if successful, or an XYSSL_ERR_RSA_XXX error code
 *
 * \note           The output buffer must be as large as the size
 *                 of ctx->N (eg. 128 bytes if RSA-1024 is used).
 */
int Pkcs1Encrypt( 
                       int mode, int  ilen,
                       unsigned char *input,
                       unsigned char *output );

private:
  RSAInternals *Internals;
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmRSA_h
