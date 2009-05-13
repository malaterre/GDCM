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
#include "gdcmMD5.h"
#include "gdcmTesting.h"
#include "gdcmSystem.h"

#ifdef GDCM_USE_SYSTEM_OPENSSL
#include <openssl/md5.h>
#endif

#include <string.h>//memcmp
#include <stdlib.h> // malloc

/*
 */
namespace gdcm
{

class MD5Internals
{
public:
};

MD5::MD5()
{
  Internals = new MD5Internals;
}

MD5::~MD5()
{
  delete Internals;
}

bool MD5::Compute(const char *buffer, unsigned long buf_len, char digest[33])
{
  return Testing::ComputeMD5(buffer, buf_len, digest);
}

inline bool process_file(const char *filename, unsigned char *digest)
{
  if( !filename || !digest ) return false;

  FILE *file = fopen(filename, "rb");
  if(!file) 
    {
    return false;
    }

  size_t file_size = System::FileSize(filename);
  void *buffer = malloc(file_size);
  if(!buffer) 
    {
    fclose(file);
    return false;
    }
  size_t read = fread(buffer, 1, file_size, file);
  if( read != file_size ) return false;

  MD5_CTX ctx;
  MD5_Init(&ctx);
  MD5_Update(&ctx, buffer, file_size);
  MD5_Final(digest, &ctx);

  /*printf("MD5 (\"%s\") = ", test[i]); */
  /*for (int di = 0; di < 16; ++di)
  {
    printf("%02x", digest[di]);
  }*/
  //printf("\t%s\n", filename);
  free(buffer);
  fclose(file);
  return true;
}

bool MD5::ComputeFile(const char *filename, char digest_str[33])
{
  // If not file exist
  // return false;
  unsigned char digest[16];

  /* Do the file */
  if( !process_file(filename, digest) )
    {
    return false;
    }

  for (int di = 0; di < 16; ++di)
    {
    sprintf(digest_str+2*di, "%02x", digest[di]);
    }
  digest_str[2*16] = '\0';

  char output2[33];
  Testing::ComputeFileMD5(filename, output2);
  assert( strcmp( digest_str, output2 ) == 0 );

  return true;

}


} // end namespace gdcm
