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
#include "gdcmX509.h"
#include "gdcm_polarssl.h"

/*
 */
namespace gdcm
{

class X509Internals
{
public:
rsa_context ctx;
};

X509::X509()
{
  Internals = new X509Internals;
}

X509::~X509()
{
  delete Internals;
}

int X509::Pkcs1Encrypt( 
                       int mode, int  ilen,
                       const unsigned char *input,
                       unsigned char *output )
{
  return 
rsa_pkcs1_encrypt( &Internals->ctx,
                       mode, ilen,
                       input,
                       output );

}

} // end namespace gdcm
