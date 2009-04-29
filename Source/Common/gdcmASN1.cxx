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
#include "gdcmASN1.h"

/*
 */
namespace gdcm
{

class ASN1Internals
{
public:
};

ASN1::ASN1()
{
  Internals = new ASN1Internals;
}

ASN1::~ASN1()
{
  delete Internals;
}

// int ASN1_parse_dump(BIO *bp,const unsigned char *pp,long len,int indent,int dump);
#define FORMAT_ASN1     1

bool ASN1::ParseDumpFile(const char *filename)
{
	ENGINE *e = NULL;
	char *passargin = NULL, *passin = NULL;
	EVP_PKEY *pkey = NULL;
	RSA *rsa = NULL;
	char *keyfile = NULL;
	int keyform = FORMAT_ASN1;
BIO *bio_err=NULL;
	BIO *in = NULL, *out = NULL;
	int keysize;
	int rsa_inlen, rsa_outlen = 0;
	unsigned char *rsa_in = NULL, *rsa_out = NULL, pad;
	char *infile = NULL, *outfile = NULL;
	pad = RSA_PKCS1_PADDING;

	if(!bio_err) bio_err = BIO_new_fp(stderr, BIO_NOCLOSE);
		//pkey = load_key(bio_err, keyfile, keyform, 0,
		//	passin, e, "Private Key");
	BIO *key=NULL;
	key=BIO_new(BIO_s_file());
  keyfile = (char*)filename;
int v =		BIO_read_filename(key,keyfile);
			ERR_print_errors(bio_err);
	if (key != NULL) BIO_free(key);

		pkey=d2i_PrivateKey_bio(key, NULL);

	rsa = EVP_PKEY_get1_RSA(pkey);
	EVP_PKEY_free(pkey);

		in = BIO_new_file(infile, "rb");
		out = BIO_new_fp(stdout, BIO_NOCLOSE);

	keysize = RSA_size(rsa);
	rsa_in = (unsigned char*)OPENSSL_malloc(keysize * 2);
	rsa_out = (unsigned char*)OPENSSL_malloc(keysize);

	rsa_inlen = BIO_read(in, rsa_in, keysize * 2);
	assert(rsa_inlen > 0);
			rsa_outlen  = RSA_public_decrypt(rsa_inlen, rsa_in, rsa_out, rsa, pad);

		if(!ASN1_parse_dump(out, rsa_out, rsa_outlen, 1, -1)) {
			ERR_print_errors(bio_err);
		}

  return true;
}

} // end namespace gdcm
