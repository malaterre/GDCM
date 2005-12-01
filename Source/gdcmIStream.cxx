#include "gdcmIStream.h"
#include "gdcmByteSwap.txx"
#include <assert.h>

#include <assert.h>

namespace gdcm
{

IStream& IStream::Read(char* s, std::streamsize n )
{
  if(s) { assert( memset(s,0,n) ); }
  assert( !(!InternalStream) );
  assert( !InternalStream.eof() );
  //std::cout << InternalStream.tellg() << std::endl;
  if( !InternalStream.read(s,n) )
    {
    if( !(InternalStream.eof()))
      {
      std::cerr << "Problem reading: " << n << " bytes" << std::endl;
      assert(0);
      }
    }
  return *this; 
}

//IStream& IStream::Read(short* s, std::streamsize n )
//{
//  Read((char*)s, 2*n);
//  ByteSwap<short>::SwapRangeFromSwapCodeIntoSystem(s, SwapCode, n);
//  return *this;
//}
 
} // end namespace gdcm

