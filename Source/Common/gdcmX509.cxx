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
namespace openssl // prevent namespace clash such as openssl::PKCS7 vs gdcm::PKCS7
{
#include <openssl/pem.h>
#include <openssl/x509.h>
#define my_sk_X509_value(st, i) SKM_sk_value(openssl::X509, (st), (i))
}
#endif

//#include <stdlib>


/*
 */
namespace gdcm
{

class X509Internals
{
public:
  X509Internals():pkey(NULL) {
    recips = openssl::sk_X509_new_null();
  }
  ~X509Internals() {
    openssl::sk_X509_pop_free(recips, openssl::X509_free);
    EVP_PKEY_free(pkey);
    }
  openssl::STACK_OF(X509) *recips;
  openssl::EVP_PKEY *pkey;
};

void foobar() {}
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
  openssl::BIO *in;
  openssl::EVP_PKEY *pkey;
  if ((in=openssl::BIO_new_file(keyfile,"r")) == NULL)
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
}

bool X509::ParseCertificateFile( const char *keyfile)
{
  openssl::STACK_OF(X509) *recips = Internals->recips;
  assert( recips );
  openssl::X509 *x509 = NULL;

  ::openssl::BIO *in;
  if (!(in=openssl::BIO_new_file(keyfile,"r")))
    {
    return false;
    }
  // -> LEAK reported by valgrind...
  if (!(x509=openssl::PEM_read_bio_X509(in,NULL,NULL,NULL)))
    {
    return false;
    }
  openssl::BIO_free(in); in = NULL;
  openssl::sk_X509_push(recips, x509);
  return true;
}

unsigned int X509::GetNumberOfRecipients() const
{
  openssl::STACK_OF(X509) *recips = Internals->recips;
  if(!recips) {
    return 0;
  }
  return openssl::sk_X509_num(recips);
}

openssl::X509* X509::GetRecipient( unsigned int i ) const
{
  openssl::STACK_OF(X509) *recips = Internals->recips;
  return my_sk_X509_value(recips, i);
}

openssl::EVP_PKEY* X509::GetPrivateKey() const
{
  return Internals->pkey;
}

} // end namespace gdcm
