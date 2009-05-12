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
#ifndef __gdcmX509_h
#define __gdcmX509_h

#include "gdcmTypes.h"

//namespace openssl { 
#ifdef GDCM_USE_SYSTEM_OPENSSL
#include <openssl/x509.h>
#else
class X509;
class EVP_PKEY;
#endif
// }
namespace gdcm
{
/**
 * \brief Class for x509 
 *
 */
//-----------------------------------------------------------------------------
class X509Internals;
class GDCM_EXPORT X509
{
public :
  X509();
  ~X509();

  // 0 is a reserved value do not use
  typedef enum {
/*#define POLARSSL_*/ ERR_X509_KEY_PASSWORD_REQUIRED           = 1,
/*#define POLARSSL_*/ ERR_X509_KEY_PASSWORD_MISMATCH           
  } X509ErrorType;

unsigned int GetNumberOfRecipients() const;
bool ParseCertificateFile( const char *filename );
bool ParseKeyFile( const char *filename );

protected:
	friend class PKCS7;
	::X509* GetRecipient( unsigned int i ) const;
	::EVP_PKEY* GetPrivateKey() const;

private:
  X509Internals *Internals;
private:
  X509(const X509&);  // Not implemented.
  void operator=(const X509&);  // Not implemented.
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmX509_h
