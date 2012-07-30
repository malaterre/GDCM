#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <cstdlib>
//#include <Windows.h>

namespace gdcm
{
class Helper
{
  public:
  //static void PrintHex(unsigned char* data, int len)
  //{
  //  for (int i = 0; i < len; i++) printf("%02x", data[i]);
  //  printf("\n");
  //}

  static void ReverseBytes(unsigned char* data, int len)
  {
    unsigned char temp;
    for (int i = 0; i < len/2; i++)
    {
      temp = data[len-i-1];
      data[len-i-1] = data[i];
      data[i] = temp;
    }
    printf("\n");
  }

  /*static void HexToBin(unsigned char* data, unsigned long len, unsigned char* out, unsigned long outLen)
  {
    if (len % 2) return;
    //out = new unsigned char[len/2];

    char a[5] = "0xAA";
    for (int i = 0; i < len ; i+=2)
    {
      a[2] = data[i];
      a[3] = data[i+1];
      out[i/2] = strtoul(a, NULL, 0);
    }
  }*/

  static void DumpToFile(const char * filename, unsigned char* data, unsigned long len)
  {
    FILE * f = fopen(filename, "wb");
    fwrite(data, 1, len, f);
    fclose(f);
  }

  static bool LoadFileWin(const char * filename, char * & buffer, unsigned long & bufLen)
  {
    FILE * f = fopen(filename, "rb");
    if (f == NULL)
      {
      printf("Couldn't open the file: %s\n", filename);
      return false;
      }
    
    fseek(f, 0L, SEEK_END);
    long sz = ftell(f);
    //fseek(f, 0L, SEEK_SET);
    rewind(f);
    
    buffer = new char[sz];
    /*if (bufLen < sz)
      {
      printf("Buffer too small to load the file: %d < %d\n", bufLen, sz);
      return false;
      }
      */
    bufLen = sz;


    while (sz)
    {
      sz -= fread(buffer + bufLen - sz, sizeof(char), sz, f);
    }

    return true;
  }

};
}

#endif
