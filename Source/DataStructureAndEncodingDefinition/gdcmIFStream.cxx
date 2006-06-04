#include "gdcmIFStream.h"
#include "gdcmByteSwap.txx"
#include <assert.h>

namespace gdcm
{

IStream& IFStream::Read(char* s, std::streamsize n )
{
  // Following operation is nice for debuging but is way to extensive and
  // appear really high in the top ten expensive operation
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

//IStream& IFStream::Read(uint16_t &vl)
//{
//  union { uint16_t vl; char vl_str[2]; } uvl;
//  InternalStream.read(uvl.vl_str,2);
//  //ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem((uint16_t*)(&vl_str),
//  //  SwapCode, 1);
//  vl = uvl.vl;
//  assert( vl != static_cast<uint16_t>(-1) );
//  return *this;
//}

} // end namespace gdcm

