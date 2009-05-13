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
#include "gdcmPKCS7.h"

#include <stdio.h> // stderr
#include <string.h> // strcmp
#include <assert.h>
#include <time.h> // time()


#ifdef GDCM_USE_SYSTEM_OPENSSL
//namespace openssl // prevent namespace clash such as PKCS7 vs gdcm::PKCS7
//{
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/rand.h>
//#define my_sk_PKCS7_SIGNER_INFO_value(st, i) SKM_sk_value(PKCS7_SIGNER_INFO, (st), (i))
//}
#endif

#include "gdcmX509.h"

namespace gdcm
{


class PKCS7Internals
{
public:
  PKCS7Internals():x509(NULL) {}
  X509 *x509;
};

PKCS7::PKCS7()
{
  Internals = new PKCS7Internals;
}

PKCS7::~PKCS7()
{
  delete Internals;
  //EVP_cleanup();
}


} // end namespace gdcm
