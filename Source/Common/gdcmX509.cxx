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


X509::X509()
{
  Internals = new X509Internals;
}

X509::~X509()
{
  delete Internals;
}





} // end namespace gdcm
