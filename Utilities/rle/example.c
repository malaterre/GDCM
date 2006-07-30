#include <stdio.h>
#include <stdlib.h> // abort

#include "rlelib.h"

void std_print_header(rle_compressed_frame * frame)
{
  rle_header *header = frame->header;
  unsigned long ns = header->num_segments;
  printf("%lu\n", ns);
}


int write_RLE_file(const char *filename)
{
  abort();
  return 0;
}


int fill_input_buffer(rle_decompressed_frame * frame)
{
  return 1;
}

int read_RLE_file(const char *filename)
{
  abort();
  return 1;
}

int main()
{
  return 0;
}
