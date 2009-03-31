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
#include "gdcmRSA.h"
#include "gdcm_polarssl.h"

/*
 */
namespace gdcm
{

class RSAInternals
{
public:
rsa_context ctx;
};

RSA::RSA()
{
  Internals = new RSAInternals;
}

RSA::~RSA()
{
  delete Internals;
}

int RSA::Pkcs1Encrypt( 
                       int mode, int  ilen,
                       const unsigned char *input,
                       unsigned char *output ) const
{
  return 
rsa_pkcs1_encrypt( &Internals->ctx,
                       mode, ilen,
                       const_cast<unsigned char*>(input),
                       output );

}

int RSA::X509ParseKeyfile( const char *path, const char *password )
{
  return x509parse_keyfile( &Internals->ctx, const_cast<char*>(path), const_cast<char*>(password) );
}


} // end namespace gdcm
