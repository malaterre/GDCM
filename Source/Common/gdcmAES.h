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
#ifndef __gdcmAES_h
#define __gdcmAES_h

#include "gdcmTypes.h"

namespace gdcm
{
/**
 * \brief Class for AES encryption
 *
 */
//-----------------------------------------------------------------------------
class AESInternals;
class GDCM_EXPORT AES
{
public :
  AES();
  ~AES();

  typedef enum {
/* #define */ ENCRYPT = 1,
/* #define */ DECRYPT = 0
  } AESModeType;


/**
 * \brief          AES key schedule (encryption)
 *
 * \param key      encryption key
 * \param keysize  must be 128, 192 or 256
 */
void SetkeyEnc(unsigned char *key, int keysize );

/**
 * \brief          AES key schedule (decryption)
 *
 * \param key      decryption key
 * \param keysize  must be 128, 192 or 256
 */
void SetkeyDec(unsigned char *key, int keysize );

/**
 * \brief          AES-ECB block encryption/decryption
 *
 * \param mode     ENCRYPT or DECRYPT
 * \param input    16-byte input block
 * \param output   16-byte output block
 */
void CryptEcb(
                    int mode,
                    unsigned char input[16],
                    unsigned char output[16] );

/**
 * \brief          AES-CBC buffer encryption/decryption
 *
 * \param mode     ENCRYPT or DECRYPT
 * \param length   length of the input data
 * \param iv       initialization vector (updated after use)
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 */
void CryptCbc(
                    int mode,
                    int length,
                    unsigned char iv[16],
                    unsigned char *input,
                    unsigned char *output );

/**
 * \brief          AES-CFB128 buffer encryption/decryption
 *
 * \param mode     ENCRYPT or DECRYPT
 * \param length   length of the input data
 * \param iv_off   offset in IV (updated after use)
 * \param iv       initialization vector (updated after use)
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 */
void CryptCfb128(
                       int mode,
                       int length,
                       int *iv_off,
                       unsigned char iv[16],
                       unsigned char *input,
                       unsigned char *output );

protected:
/**
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 */
int SelfTest( int verbose );
private:
AESInternals *Internals;
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmAES_h
