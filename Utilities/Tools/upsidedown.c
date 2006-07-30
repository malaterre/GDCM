#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[])
{
  int i = 1;
  const char *filename = argv[1];
  const char *outfilename = argv[2];
  FILE *in = fopen(filename, "rb" );
  FILE *out = fopen(outfilename, "wb" );
  const unsigned int x = 512;
  const unsigned int y = 512;
  const unsigned int bit = 2;
  char buffer[x*y*bit];
  size_t len = fread(buffer,1,bit*x*y,in);
  assert( len == x*y*bit );

  const char *p = buffer;
  for(i = y; i > 0; --i)
  {
  fwrite(p+bit*x*(i-1),1,bit*x,out);
  }
  fclose(in);
  fclose(out);
  return 0;
}
