/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

//#include "gdcmCryptographicMessageSyntax.h"
#include "gdcmOpenSSLCryptographicMessageSyntax.h"
#include "gdcmTrace.h"

#include <limits> // numeric_limits

#include <stdio.h> // stderr
#include <string.h> // strcmp
#include <assert.h>
#include <time.h> // time()

#include <openssl/cms.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/rand.h>
//#include <openssl/x509_vfy.h>
//#include <openssl/x509v3.h>
//#include <openssl/crypto.h>

namespace gdcm
{

//class CryptographicMessageSyntaxInternals
//{
//#ifdef GDCM_USE_SYSTEM_OPENSSL
//public:
//  CryptographicMessageSyntaxInternals():recips(NULL),pkey(NULL),CipherType( CryptographicMessageSyntax::AES256_CIPHER ),cipher(NULL),p7(PKCS7_new()){
//    recips = sk_X509_new_null();
//    PKCS7_set_type(p7,NID_pkcs7_enveloped);
//    bio_buffer = BIO_new(BIO_s_mem());
//    Initialized = false;
//  }
//  ~CryptographicMessageSyntaxInternals() {
//    EVP_PKEY_free(pkey);
//    PKCS7_free(p7);
//    p7 = NULL;
//    BIO_free_all(bio_buffer);
//  }
//  unsigned int GetNumberOfRecipients() const {
//    //::STACK_OF(X509) *recips = recips;
//    if(!recips) {
//      return 0;
//    }
//    return ::sk_X509_num(recips);
//    }
//  STACK_OF(X509)* GetRecipients( ) const {
//    return recips;
//  }
//  ::X509* GetRecipient( unsigned int i ) const {
//    //::STACK_OF(X509) *recips = Internals->recips;
//    ::X509 *ret = sk_X509_value(recips, i);
//    return ret;
//  }
//  void SetPrivateKey(::EVP_PKEY* thepkey) {
//    this->pkey = thepkey;
//  }
//  ::EVP_PKEY* GetPrivateKey() const {
//    return pkey;
//  }
//  void SetCipherType(CryptographicMessageSyntax::CipherTypes ciphertype) {
//    CipherType = ciphertype;
//  }
//  bool Initialize()
//    {
//    if(!cipher)
//      {
//      cipher = CreateCipher( GetCipherType() );
//      }
//    if(!cipher) return false;
//    // The following is inspired by PKCS7_encrypt
//    // and openssl/crypto/pkcs7/enc.c
//    if( !PKCS7_set_cipher(p7,cipher) ) return false;
//
//    for(unsigned int i = 0; i < GetNumberOfRecipients(); i++) {
//      ::X509* recip = GetRecipient(i);
//      if (!PKCS7_add_recipient(p7,recip)) return false;
//    }
//    sk_X509_pop_free(recips, X509_free);
//
//    /* Set the content of the signed to 'data' */
//    /* PKCS7_content_new(p7,NID_pkcs7_data); not used in envelope */
//
//    /* could be used, but not in this version :-)
//       if (!nodetach) PKCS7_set_detached(p7,1);
//     */
//
//    return true;
//    }
//
//  bool Encrypt(char *output, size_t &outlen, const char *array, size_t len)
//    {
//    
//    
//    if( !Initialized )
//      {
//      bool b = Initialize();
//      if ( !b )
//        {
//        //gdcmErrorMacro( "Initialize" );
//        return false;
//        }
//      Initialized = true;
//      }
//
//    if( len > (size_t)std::numeric_limits<int>::max() )
//      {
//      //gdcmErrorMacro( "len is too big: " << len );
//      return false;
//      }
//    BIO *data = BIO_new_mem_buf((void*)array, (int)len);
//    if(!data)
//      {
//      //gdcmErrorMacro( "BIO_new_mem_buf" );
//      return false;
//      }
//
//    char buf[256];
//    BIO *p7bio;
//    if ((p7bio=PKCS7_dataInit(p7,NULL)) == NULL) return false;
//    for (;;)
//      {
//      int i = BIO_read(data,buf,sizeof(buf));
//      if (i <= 0) break;
//      BIO_write(p7bio,buf,i);
//      }
//    // BIO_flush() returns 1 for success and 0 or -1 for failure.
//    int bflush = BIO_flush(p7bio);
//    if( bflush != 1 )
//      {
//      //gdcmErrorMacro( "BIO_flush: " << bflush );
//      return false;
//      }
//
//    if (!PKCS7_dataFinal(p7,p7bio))
//      {
//      //gdcmErrorMacro( "PKCS7_dataFinal" );
//      return false;
//      }
//
//    // WARNING:
//    // BIO_reset() normally returns 1 for success and 0 or -1 for failure. File
//    // BIOs are an exception, they return 0 for success and -1 for failure.
//    if( BIO_reset(bio_buffer) != 1 )
//      {
//      //gdcmErrorMacro( "BIO_reset" );
//      return false;
//      }
//
//    i2d_PKCS7_bio(bio_buffer,p7);
//    // (void)BIO_flush(wbio);
//
//    char *binary;
//    long biolen = BIO_get_mem_data(bio_buffer,&binary);
//    //gdcmAssertMacro( biolen >= 0 );
//    if ( outlen < (size_t)biolen )
//      {
//      //gdcmErrorMacro( "Allocation issue: " << outlen << " vs " << biolen << " from " << len );
//      return false;
//      }
//    outlen = biolen;
//    memcpy( output, binary, outlen );
//
//    BIO_free(data);
//    BIO_free_all(p7bio);
//    return true;
//    }
//  CryptographicMessageSyntax::CipherTypes GetCipherType() const {
//    return CipherType;
//  }
//  ::PKCS7 *GetP7() const { return p7; }
//private:
//  STACK_OF(X509) *recips;
//  ::EVP_PKEY *pkey;
//  CryptographicMessageSyntax::CipherTypes CipherType;
//  const EVP_CIPHER *cipher;
//  ::PKCS7 *p7;
//  BIO *bio_buffer;
//  bool Initialized;
//#endif
//};

OpenSSLCMS::OpenSSLCMS():recips(NULL),pkey(NULL),cipher(NULL)
{
  //Internals = new CryptographicMessageSyntaxInternals;
  recips = sk_X509_new_null();
}

OpenSSLCMS::~OpenSSLCMS()
{
  //delete Internals;
  EVP_PKEY_free(pkey);
  //PKCS7_free(p7);
  //p7 = NULL;
  //BIO_free_all(bio_buffer);
  sk_X509_free(recips);
}

void OpenSSLCMS::SetCipherType( CryptographicMessageSyntax::CipherTypes type )
{
  cipher = CreateCipher(type);
  cipherType = type;
}
/*
CryptographicMessageSyntax::CipherTypes OpenSSLCMS::GetCipherType() const
{
  return CipherType;
}*/

bool OpenSSLCMS::Encrypt(char *output, size_t &outlen, const char *array, size_t len) const
{
  BIO *in = NULL, *out = NULL;
  CMS_ContentInfo *cms = NULL;
  int flags = CMS_BINARY;
  bool ret = false;

  // RAND_status() and RAND_event() return 1 if the PRNG has been seeded with
  // enough data, 0 otherwise.
  if( !RAND_status() )
    {
    gdcmErrorMacro( "PRNG was not seeded properly" );
    outlen = 0;
    return false;
    }

  //load randomness ?
  if( len > (size_t)std::numeric_limits<int>::max() )
    {
    gdcmErrorMacro( "len is too big: " << len );
    return false;
    }

  in = BIO_new_mem_buf((void*)array, (int)len);
  if(!in)
    {
    gdcmErrorMacro( "BIO_new_mem_buf" );
    goto err;
    }

  out = BIO_new(BIO_s_mem());
  if (!out)
    {
    goto err;
    }


  cms = CMS_encrypt((::stack_st_X509*)recips, in, cipher, flags);
  if (!cms)
    {
    goto err;
    }

  if (! i2d_CMS_bio(out, cms))
    {
    gdcmErrorMacro( "Error at writing CMS structure to output." );
    return false;
    }

  BUF_MEM *bptr;
  BIO_get_mem_ptr(out, &bptr);
  //BIO_set_close(out, BIO_NOCLOSE); /* So BIO_free() leaves BUF_MEM alone */
  //BIO_free(out);

  if (bptr->length > outlen)
    {
    //TODO: how to treat this ???
    gdcmErrorMacro( "Supplied output buffer too small: " << bptr->length << " bytes needed." );
    goto err;
    }
  memcpy(output, bptr->data, bptr->length);
  outlen = bptr->length;
  //BUF_MEM_free(bptr);
  
  ret = true;

err:
  //unsigned long errcode = ERR_peek_error();
  //cout << ERR_error_string(errcode, NULL) << endl;
  if (!ret)
    {
    outlen = 0;
    fprintf(stderr, "Error Decrypting Data\n");
    ERR_load_crypto_strings();
    ERR_print_errors_fp(stderr);
    }

  if (cms)
    CMS_ContentInfo_free(cms);

  if (in)
    BIO_free(in);
  if (out)
    BIO_free(out);

  return ret;
}

bool OpenSSLCMS::Decrypt(char *output, size_t &outlen, const char *array, size_t len) //const
{
  BIO *in = NULL, *out = NULL;
  CMS_ContentInfo *cms = NULL;
  bool ret = false;
  int flags = CMS_BINARY;

  //if (!rcert || !rkey)
  //  goto err;

  in = BIO_new_mem_buf((void*)array, (int)len);
  if (!in)
    goto err;

  cms = d2i_CMS_bio(in, NULL);
  if (!cms)
    goto err;

  out = BIO_new(BIO_s_mem());
  if (!out)
    goto err;

  if (!CMS_decrypt(cms, pkey, NULL, NULL, out, flags))
    goto err;

  BUF_MEM *bptr;
  BIO_get_mem_ptr(out, &bptr);

  if (bptr->length > outlen)
    {
    //TODO: how to treat this ???
    gdcmErrorMacro( "Supplied output buffer too small: " << bptr->length << " bytes needed." );
    goto err;
    }
  memcpy(output, bptr->data, bptr->length);
  outlen = bptr->length;
  //BUF_MEM_free(bptr);
  //bptr = NULL; //good form ?
  
  ret = true;

err:
  //unsigned long errcode = ERR_peek_error();
  //cout << ERR_error_string(errcode, NULL) << endl;
  if (!ret)
    {
    outlen = 0;
    fprintf(stderr, "Error Decrypting Data\n");
    ERR_load_crypto_strings();
    ERR_print_errors_fp(stderr);
    }

  if (cms)
    CMS_ContentInfo_free(cms);

  if (in)
    BIO_free(in);
  if (out)
    BIO_free(out);

  return ret;

//#ifdef GDCM_USE_SYSTEM_OPENSSL
//  //CryptographicMessageSyntaxInternals *x509 = Internals;
//  ::PKCS7 *p7;
//#undef PKCS7_SIGNER_INFO
//  ::PKCS7_SIGNER_INFO *si;
//  X509_STORE_CTX cert_ctx;
//  X509_STORE *cert_store=NULL;
//  BIO *data,*detached=NULL,*p7bio=NULL;
//  char buf[1024*4];
//  unsigned char *pp;
//  int i;
//  STACK_OF(PKCS7_SIGNER_INFO) *sk;
//  char * ptr = output;
//  outlen = 0;
//
//  OpenSSL_add_all_algorithms();
//  //bio_err=BIO_new_fp(stderr,BIO_NOCLOSE);
//
//  //data=BIO_new(BIO_s_file());
//  pp=NULL;
//
//  //EVP_PKEY *pkey = x509->GetPrivateKey();
//
//  if( len > (size_t)std::numeric_limits<int>::max() )
//    {
//    //gdcmErrorMacro( "len is too big: " << len );
//    return false;
//    }
//  data = BIO_new_mem_buf((void*)array, (int)len);
//  if(!data) goto err;
//
//
//  if (pp == NULL)
//    BIO_set_fp(data,stdin,BIO_NOCLOSE);
//
//
//  /* Load the PKCS7 object from a file */
//  //if ((p7=PEM_read_bio_PKCS7(data,NULL,NULL,NULL)) == NULL) goto err;
//  if ((p7=d2i_PKCS7_bio(data,NULL)) == NULL) goto err;
//
//  if(!PKCS7_type_is_enveloped(p7)) {
//    goto err;
//  }
//
////  if(cert && !X509_check_private_key(cert, pkey)) {
////    PKCS7err(PKCS7_F_PKCS7_DECRYPT,
////        PKCS7_R_PRIVATE_KEY_DOES_NOT_MATCH_CERTIFICATE);
////    return 0;
////  }
//
//
//  /* This stuff is being setup for certificate verification.
//   * When using SSL, it could be replaced with a
//   * cert_stre=SSL_CTX_get_cert_store(ssl_ctx); */
//  cert_store=X509_STORE_new();
//  X509_STORE_set_default_paths(cert_store);
//  X509_STORE_load_locations(cert_store,NULL,"../../certs");
//  //X509_STORE_set_verify_cb_func(cert_store,verify_callback);
//
//  ERR_clear_error();
//
//  /* We need to process the data */
//  /* We cannot support detached encryption */
//  p7bio=PKCS7_dataDecode(p7,pkey,detached,NULL);
//
//  if (p7bio == NULL)
//    {
//    printf("problems decoding\n");
//    goto err;
//    }
//
//  /* We now have to 'read' from p7bio to calculate digests etc. */
//  for (;;)
//    {
//    i=BIO_read(p7bio,buf,sizeof(buf));
//    /* print it? */
//    if (i <= 0) break;
//    //fwrite(buf,1, i, stdout);
//    memcpy(ptr, buf, i);
//    ptr += i;
//    outlen += i;
//    }
//
//  /* We can now verify signatures */
//  sk=PKCS7_get_signer_info(p7);
//  if (sk == NULL)
//    {
//    //fprintf(stderr, "there are no signatures on this data\n");
//    }
//  else
//    {
//    /* Ok, first we need to, for each subject entry,
//     * see if we can verify */
//    ERR_clear_error();
//    for (i=0; i<sk_PKCS7_SIGNER_INFO_num(sk); i++)
//      {
//      //si=my_sk_PKCS7_SIGNER_INFO_value(sk,i);
//          si=sk_PKCS7_SIGNER_INFO_value(sk,i);
//      i=PKCS7_dataVerify(cert_store,&cert_ctx,p7bio,p7,si);
//      if (i <= 0)
//        goto err;
//      else
//        fprintf(stderr,"Signature verified\n");
//      }
//    }
//  X509_STORE_free(cert_store);
//
//  BIO_free_all(p7bio);
//  PKCS7_free(p7); p7 = NULL;
//  BIO_free(data);
//
//  return true;
//err:
//  ERR_load_crypto_strings();
//  ERR_print_errors_fp(stderr);
//  return false;
//#else
//  (void)output;
//  (void)array;
//  (void)len;
//  outlen = 0;
//  gdcmDebugMacro( "GDCM_USE_SYSTEM_OPENSSL is OFF" );
//  return false;
//#endif /* GDCM_USE_SYSTEM_OPENSSL */
}

bool OpenSSLCMS::ParseKeyFile( const char *keyfile)
{
  ::BIO *in;
  ::EVP_PKEY *new_pkey;
  if ((in=::BIO_new_file(keyfile,"r")) == NULL)
    {
    return false;
    }
  //if ((x509=openssl::PEM_read_bio_X509(in,NULL,NULL,NULL)) == NULL) goto err;
  (void)BIO_reset(in);
  if ((new_pkey=PEM_read_bio_PrivateKey(in,NULL,NULL,NULL)) == NULL)
    {
    return false;
    }
  BIO_free(in);

  if (pkey != NULL)
    {
    EVP_PKEY_free(pkey);
    }
  
  this->pkey = new_pkey;
  return true;
}

bool OpenSSLCMS::ParseCertificateFile( const char *keyfile)
{
  //STACK_OF(X509) *recips = Internals->GetRecipients();
  //assert( recips );
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
}

const EVP_CIPHER* OpenSSLCMS::CreateCipher( CryptographicMessageSyntax::CipherTypes ciphertype)
{
  const EVP_CIPHER *cipher = 0;
  switch( ciphertype )
    {
  case CryptographicMessageSyntax::DES_CIPHER:    // DES
    cipher = EVP_des_cbc();
    break;
  case CryptographicMessageSyntax::DES3_CIPHER:   // Triple DES
    cipher = EVP_des_ede3_cbc();
    break;
  case CryptographicMessageSyntax::AES128_CIPHER: // CBC AES
    cipher = EVP_aes_128_cbc();
    break;
  case CryptographicMessageSyntax::AES192_CIPHER: // '   '
    cipher = EVP_aes_192_cbc();
    break;
  case CryptographicMessageSyntax::AES256_CIPHER: // '   '
    cipher = EVP_aes_256_cbc();
    break;
    }
  return cipher;
}

} // end namespace gdcm

