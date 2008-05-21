/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "puff.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int checkmagick(unsigned char *input)
{
  if( input[128+0] == 'D' 
   && input[128+1] == 'I' 
   && input[128+2] == 'C' 
   && input[128+3] == 'M' )
    {
    return 1;
    }
  return 0;
}

int main(int argc, char *argv[])
{
  int ret;
  unsigned char *source;
  unsigned long len, sourcelen, destlen;

  unsigned long size;
  unsigned char *buf;
  FILE *in;
  struct stat s;

  if (argc < 2) return 2;
  const char *name = argv[1];

  len = 0;
  if (stat(name, &s)) return 1;
  if ((s.st_mode & S_IFMT) != S_IFREG) return 1;
  size = (unsigned long)(s.st_size);
  if (size == 0 || (off_t)size != s.st_size) return 1;
  in = fopen(name, "r");
  if (in == NULL) return 1;
  buf = malloc(size);
  if (buf != NULL && fread(buf, 1, size, in) != size) {
    free(buf);
    buf = NULL;
  }
  fclose(in);
  len = size;
  source = buf;
  if( source == NULL ) return 1;
  sourcelen = len;

  if( !checkmagick(source) )
    {
    fprintf( stderr, "checkmagick failed\n" );
    return 1;
    }
  // magick succeed so skip header:
  source += 128 + 4;
  sourcelen -= 128 + 4;

  union { uint32_t tag; uint16_t tags[2]; char bytes[4]; } tag;
  memcpy(&tag, source, sizeof(tag) );
  printf( "tag: %d, %d\n", tag.tags[0], tag.tags[1] );
  source += sizeof(tag);
  sourcelen -= sizeof(tag);

  char vr[3];
  vr[2] = 0;
  memcpy(vr, source, 2);
  printf( "vr: %s\n", vr);

  source += 2;
  sourcelen -= 2;

  uint16_t vl;
  memcpy(&vl, source, sizeof(vl));
  printf( "vl: %d\n", vl);

  source += sizeof(vl);
  sourcelen -= sizeof(vl);

  uint32_t value;
  memcpy(&value, source, sizeof(value));
  printf( "value: %d\n", value);

  source += sizeof(value);
  sourcelen -= sizeof(value);

  source += value;
  sourcelen -= value;

  len = sourcelen;
  if( len % 2 )
    {
    printf( "len of bit stream is odd: %d. Continuing anyway\n", len );
    }
  else
    {
    printf( "deflate stream has proper length: %d\n", len );
    }

  ret = puff(NULL, &destlen, source, &sourcelen);

  if (ret)
    printf("puff() failed with return code %d\n", ret);
  else {
    printf("puff() succeeded uncompressing %lu bytes\n", destlen);
    if (sourcelen < len) printf("%lu compressed bytes unused\n",
      len - sourcelen);
  }
  free(buf);
  return ret;
}
