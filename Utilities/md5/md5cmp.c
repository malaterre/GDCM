#include "md5.h"

int main(int argc, char *argv[])
{

  if( argc < 3 )
  {
    return 1;
  }
  md5_state_t state;
  md5_byte_t digest[16];

  const char *filename1 = argv[1];
  const char *filename2 = argv[2];
  FILE *file1 = fopen(filename1, "rb");
  FILE *file2 = fopen(filename2, "rb");

  // go to the end
  /*int*/ fseek(file1, 0, SEEK_END);
  long file1_size = ftell(file1);
  /*int*/ fseek(file1, 0, SEEK_SET);
  void *buffer = malloc(file1_size);
  /*size_t*/ fread(buffer, 1, file1_size, file1);

  md5_init(&state);
  md5_append(&state, (const md5_byte_t *)buffer, file1_size);
  md5_finish(&state, digest);
  //printf("MD5 (\"%s\") = ", test[i]);
  for (di = 0; di < 16; ++di)
  printf("%02x", digest[di]);
  printf("\n");

  return 0;
}

