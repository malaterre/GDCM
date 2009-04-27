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

#include <string.h> // strcmp

#ifdef GDCM_USE_SYSTEM_OPENSSL
namespace openssl // prevent namespace clash such as openssl::PKCS7 vs gdcm::PKCS7
{
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#define my_sk_X509_value(st, i) SKM_sk_value(openssl::X509, (st), (i))
}
#endif


/*
 * openssl genrsa -out CA_key.pem 2048 
 *
 * openssl req -new -key CA_key.pem -x509 -days 365 -out CA_cert.cer
 */
namespace gdcm
{


class PKCS7Internals
{
public:
};

PKCS7::PKCS7()
{
  Internals = new PKCS7Internals;
}

PKCS7::~PKCS7()
{
  delete Internals;
}

void        PKCS7::SetCipherType( CipherTypes type)
{
}

PKCS7::CipherTypes PKCS7::GetCipherType() const
{
  return AES256_CIPHER;
}

/*
openssl smime -encrypt -aes256 -in inputfile.txt -out outputfile.txt -outform DER /tmp/server.pem 
*/
bool PKCS7::Encrypt(char *output, size_t &outlen, const char *array, size_t len) const
{
#ifdef GDCM_USE_SYSTEM_OPENSSL
  int argc;
  char *myargv[3];
  myargv[0] = "coucou";
  myargv[1] = "-k";
  myargv[2] = "/tmp/server.pem";
  myargv[3] = 0;
  argc = 3;
  char **argv;
  argv = myargv;
  openssl::X509 *x509;
  openssl::PKCS7 *p7;
  openssl::BIO *in;
  openssl::BIO *data,*p7bio;
  char buf[1024*4];
  int i;
  int nodetach=1;
  char *keyfile = NULL;
  const openssl::EVP_CIPHER *cipher=NULL;
  openssl::STACK_OF(X509) *recips=NULL;
  openssl::BIO*  wbio = NULL;
  time_t t;

  t = time(NULL);
  openssl::RAND_seed(&t,sizeof(t));
#ifdef _WIN32
  openssl::RAND_screen(); /* Loading video display memory into random state */
#endif

  //openssl::OpenSSL_add_all_algorithms();

  //data=openssl::BIO_new(openssl::BIO_s_file());
  while(argc > 1)
    {
    if (strcmp(argv[1],"-nd") == 0)
      {
      nodetach=1;
      argv++; argc--;
      }
    else if ((strcmp(argv[1],"-c") == 0) && (argc >= 2)) {
      if(!(cipher = openssl::EVP_get_cipherbyname(argv[2]))) {
        fprintf(stderr, "Unknown cipher %s\n", argv[2]);
        goto err;
      }
      argc-=2;
      argv+=2;
    } else if ((strcmp(argv[1],"-k") == 0) && (argc >= 2)) {
      keyfile = argv[2];
      argc-=2;
      argv+=2;
      if (!(in=openssl::BIO_new_file(keyfile,"r"))) goto err;
      if (!(x509=openssl::PEM_read_bio_X509(in,NULL,NULL,NULL)))
        goto err;
      if(!recips) recips = openssl::sk_X509_new_null();
      openssl::sk_X509_push(recips, x509);
      openssl::BIO_free(in);
    } else break;
  }

  if(!recips) {
    fprintf(stderr, "No recipients\n");
    goto err;
  }

  //if (!openssl::BIO_read_filename(data,argv[1])) goto err;
  data = openssl::BIO_new_mem_buf((void*)array, len);

  if(!cipher)  {
#ifndef OPENSSL_NO_DES
    //cipher = openssl::EVP_des_ede3_cbc();
    cipher = openssl::EVP_aes_256_cbc();
#else
    fprintf(stderr, "No cipher selected\n");
    goto err;
#endif
  }

  // The following is inspired by PKCS7_encrypt
  // and openssl/crypto/pkcs7/enc.c
  p7=openssl::PKCS7_new();
  openssl::PKCS7_set_type(p7,NID_pkcs7_enveloped);
  //openssl::PKCS7_set_type(p7,NID_pkcs7_encrypted);


  if (!openssl::PKCS7_set_cipher(p7,cipher)) goto err;
  for(i = 0; i < openssl::sk_X509_num(recips); i++) {
    openssl::X509* recip = my_sk_X509_value(recips, i);
    if (!PKCS7_add_recipient(p7,recip)) goto err;
  }
  openssl::sk_X509_pop_free(recips, openssl::X509_free);

  if ((p7bio=PKCS7_dataInit(p7,NULL)) == NULL) goto err;

  for (;;)
    {
    i=BIO_read(data,buf,sizeof(buf));
    if (i <= 0) break;
    BIO_write(p7bio,buf,i);
    }
  (void)BIO_flush(p7bio);

  if (!PKCS7_dataFinal(p7,p7bio)) goto err;
  BIO_free(p7bio);

  if (!(wbio = openssl::BIO_new(openssl::BIO_s_mem()))) goto err;
  i2d_PKCS7_bio(wbio,p7);
  (void)BIO_flush(wbio);
  PKCS7_free(p7);
  p7 = NULL;

  char *binary;
  outlen = BIO_get_mem_data(wbio,&binary);
  memcpy( output, binary, outlen );

  openssl::BIO_free_all(wbio);  /* also frees b64 */

  t = time(NULL);
  openssl::RAND_seed(&t,sizeof(t));

  return true;
err:
  openssl::ERR_load_crypto_strings();
  openssl::ERR_print_errors_fp(stderr);
  return false;
#else
  outlen = 0;
  return false;
#endif /* GDCM_USE_SYSTEM_OPENSSL */
}

/*
 $ openssl smime -decrypt -in /tmp/debug.der -inform DER -recip /tmp/server.pem -inkey CA_key.pem   
*/
bool PKCS7::Decrypt(char *output, size_t &outlen, const char *array, size_t len) const
{
  return false;
}


} // end namespace gdcm
