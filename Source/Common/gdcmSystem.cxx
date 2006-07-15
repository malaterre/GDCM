/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmSystem.h"

#include "md5.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

namespace gdcm
{

void process_file(const char *filename, md5_byte_t *digest)
{
  int di;
  size_t file_size, read;
  void *buffer;
  md5_state_t state;
  FILE *file = fopen(filename, "rb");

  /* go to the end */
  /*int*/ fseek(file, 0, SEEK_END);
  file_size = ftell(file);
  /*int*/ fseek(file, 0, SEEK_SET);
  buffer = malloc(file_size);
  read = fread(buffer, 1, file_size, file);
  assert( read == file_size );

  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)buffer, file_size);
  md5_finish(&state, digest);
  /*printf("MD5 (\"%s\") = ", test[i]); */
  for (di = 0; di < 16; ++di)
  {
    printf("%02x", digest[di]);
  }
  printf("\t%s\n", filename);
  free(buffer);
  fclose(file);
}

bool System::CompareMD5(const char *filename1, const char *filename2)
{
  md5_byte_t digest1[16];
  md5_byte_t digest2[16];

  /* Do file1 */
  process_file(filename1, digest1);

  /* Do file2 */
  process_file(filename2, digest2);

  int r = memcmp(digest1, digest2, 16);

  return bool(r);
}

int Mkdir(const char *pathname)
{
  (void)pathname;
  abort();
  return -1;
}

}
