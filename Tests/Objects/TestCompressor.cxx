#include "gdcmCompressor.h"
#include "gdcmDecompressor.h"

int main(int , char *[])
{
  const char stream[] = "ABCDEFG";
  gdcm::Compressor c;
  c.SetType( DEFLATE ); // JPEG, RLE, MPEG2...
  c.SetStream( stream );
  c.Compress();

  gdcm::Decompressor d;
  d.SetType( DEFLATE );
  d.SetStream( c.GetOutput() );
  d.Decompress();

  memcmp( d.GetOutput() == stream );
}
