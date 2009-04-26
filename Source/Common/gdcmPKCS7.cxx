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

#include <string.h>

#include <openssl/crypto.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/x509_vfy.h>
#include <openssl/x509v3.h>
#include <openssl/rand.h>


/*
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



bool PKCS7::Encrypt(char *output, const char *array, size_t len) const
{

}


} // end namespace gdcm
