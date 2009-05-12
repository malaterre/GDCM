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
#include <iostream>

#ifdef GDCM_USE_SYSTEM_OPENSSL
//namespace openssl // prevent namespace clash such as openssl::PKCS7 vs gdcm::PKCS7
//{
#include <openssl/pem.h>
#include <openssl/x509.h>
#define my_sk_X509_value(st, i) SKM_sk_value(::X509, (st), (i))
//}
#endif

//#include <stdlib>


/*
 */
namespace gdcm
{

class X509Internals
{
#ifdef GDCM_USE_SYSTEM_OPENSSL
public:
  X509Internals():pkey(NULL) {
    recips = sk_X509_new_null();
  }
  ~X509Internals() {
    sk_X509_pop_free(recips, X509_free);
    EVP_PKEY_free(pkey);
    }
  ::STACK_OF(X509) *recips;
  ::EVP_PKEY *pkey;
#endif
};

X509::X509()
{
  Internals = new X509Internals;
}

X509::~X509()
{
  delete Internals;
}

bool X509::ParseKeyFile( const char *keyfile)
{
#ifdef GDCM_USE_SYSTEM_OPENSSL
  ::BIO *in;
  ::EVP_PKEY *pkey;
  if ((in=::BIO_new_file(keyfile,"r")) == NULL)
    {
    return false;
    }
  //if ((x509=openssl::PEM_read_bio_X509(in,NULL,NULL,NULL)) == NULL) goto err;
  (void)BIO_reset(in);
  if ((pkey=PEM_read_bio_PrivateKey(in,NULL,NULL,NULL)) == NULL)
    {
    return false;
    }
  BIO_free(in);
  Internals->pkey = pkey;
  return true;
#else
  return false;
#endif
}

bool X509::ParseCertificateFile( const char *keyfile)
{
#ifdef GDCM_USE_SYSTEM_OPENSSL
  ::STACK_OF(X509) *recips = Internals->recips;
  assert( recips );
  ::X509 *x509 = NULL;

  ::BIO *in;
  if (!(in=::BIO_new_file(keyfile,"r")))
    {
    return false;
    }
  // -> LEAK reported by valgrind...
  if (!(x509=::PEM_read_bio_X509(in,NULL,NULL,NULL)))
    {
    return false;
    }
  ::BIO_free(in); in = NULL;
  ::sk_X509_push(recips, x509);
  return true;
#else
  return false;
#endif
}

unsigned int X509::GetNumberOfRecipients() const
{
#ifdef GDCM_USE_SYSTEM_OPENSSL
  ::STACK_OF(X509) *recips = Internals->recips;
  if(!recips) {
    return 0;
  }
  return ::sk_X509_num(recips);
#else
  return 0;
#endif
}

::X509* X509::GetRecipient( unsigned int i ) const
{
#ifdef GDCM_USE_SYSTEM_OPENSSL
  ::STACK_OF(X509) *recips = Internals->recips;
  ::X509 *ret = my_sk_X509_value(recips, i);
  return ret;
#else
  return NULL;
#endif
}

::EVP_PKEY* X509::GetPrivateKey() const
{
#ifdef GDCM_USE_SYSTEM_OPENSSL
  return Internals->pkey;
#else
  return NULL;
#endif
}

} // end namespace gdcm
