#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <io.h>
#include <Windows.h>

namespace gdcm
{
class Helper
{
  public:
  static void PrintHex(BYTE* data, DWORD len)
  {
    for (int i = 0; i < len; i++) printf("%02x", data[i]);
    printf("\n");
  }

  static void ReverseBytes(BYTE* data, DWORD len)
  {
    BYTE temp;
    for (int i = 0; i < len/2; i++)
    {
      temp = data[len-i-1];
      data[len-i-1] = data[i];
      data[i] = temp;
    }
    printf("\n");
  }

  static void HexToBin(BYTE* data, DWORD len, BYTE* out, DWORD outLen)
  {
    if (len % 2) return;
    //out = new BYTE[len/2];

    char a[5] = "0xAA";
    for (int i = 0; i < len ; i+=2)
    {
      a[2] = data[i];
      a[3] = data[i+1];
      out[i/2] = strtoul(a, NULL, 0);
    }
  }

  static void DumpToFile(const char * filename, BYTE* data, DWORD len)
  {
    FILE * f = fopen(filename, "wb");
    fwrite(data, 1, len, f);
    fclose(f);
  }

  /*static bool LoadFileWin(const char * filename, BYTE * & buffer, DWORD & bufLen)
  {
    //HANDLE hFile = CreateFileA( filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    HANDLE hFile = CreateFileA( filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    if ( hFile == INVALID_HANDLE_VALUE )
      {
      fprintf( stderr, "Failed to open file. error: %dn", GetLastError() );
      return false;
      }

    DWORD bytesToRead = GetFileSize(hFile, NULL);
    bufLen = bytesToRead;
    buffer = new BYTE[bytesToRead]; //add allocation check

    // what if it doesn't read all in one call ? ( + sort things out with bufLen)
    if ( !ReadFile( hFile, buffer, bufLen, &bufLen, NULL ) )
      {
      fprintf( stderr, "Failed to read file. error: %dn", GetLastError() );
      return false;
      }

      return true;
  }*/

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
