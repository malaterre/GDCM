// 
// (C) Jan de Vaan 2007-2009, all rights reserved. See the accompanying "License.txt" for licensed use. 
// 


#ifndef CHARLS_DECODERSTRATEGY
#define CHARLS_DECODERSTRATEGY

#include "streams.h"
#include "colortransform.h"

class DecoderStrategy
{
public:
	DecoderStrategy(const JlsParamaters& info) :
	  _readCache(0),
		  _validBits(0),
		  _pbyteCompressed(0),
		  _info(info)
	  {
		  if (_info.ilv != ILV_LINE)
		  {
				_info.components  = 1;
		  }
	  }

	 enum { IsDecoding = 1};

	  virtual ~DecoderStrategy()
	  {}

	  virtual void SetPresets(const JlsCustomParameters& presets) = 0;
	  virtual size_t DecodeScan(void* pvoidOut, const Size& size, const void* pvoidIn, size_t cbyte, bool bCheck) = 0;

	  void Init(BYTE* pbyteCompressed, size_t cbyte)
	  {
		  _validBits = 0;
		  _readCache = 0;
		  _pbyteCompressed = pbyteCompressed;
		  _pbyteCompressedEnd = pbyteCompressed + cbyte;
		  _pbyteNextFF = FindNextFF();
		  MakeValid();
	  }

	  inlinehint void Skip(LONG length)
	  {
		  _validBits -= length;
		  _readCache = _readCache << length; 
	  }

	
	  void OnLineBegin(int iline, LONG cpixel, void* ptypeBuffer, LONG pixelStride) 
	  {}



	  void OnLineEnd(int iline, LONG cpixel, const Triplet* ptypeBuffer, LONG pixelStride)
	  {
		  Triplet* ptypeUnc = ((Triplet*)_ptypeUncompressed) + iline * cpixel;				
	
	  		switch(_info.colorTransform)
			{
				case COLORXFORM_NONE : return TransformLine(ptypeUnc, ptypeBuffer, cpixel, TransformNone());
				case COLORXFORM_HP1 :  return TransformLine(ptypeUnc, ptypeBuffer, cpixel, TransformHp1ToRgb());
				case COLORXFORM_HP2 :  return TransformLine(ptypeUnc, ptypeBuffer, cpixel, TransformHp2ToRgb());
				case COLORXFORM_HP3 :  return TransformLine(ptypeUnc, ptypeBuffer, cpixel, TransformHp3ToRgb());
			}
	  }

	  template <class T>
	  void OnLineEnd(int iline, LONG cpixel, const T* ptypeBuffer, LONG pixelStride)
	  {

		  
		  for (int icomponent = 0; icomponent < _info.components; ++icomponent)
			{
				T* ptypeUnc = ((T*)_ptypeUncompressed) + (iline *_info.components + icomponent)* cpixel;				
#ifdef _DEBUG			
				for (LONG i = 0; i < cpixel; ++i)
				{
					//CheckedAssign(ptypeLine[i], ptypeCur[i]);
					ptypeUnc[i] = ptypeBuffer[i + icomponent*pixelStride];
				}
#else
				memcpy(ptypeUnc, ptypeBuffer+ icomponent*pixelStride, cpixel * sizeof(T) );
#endif
			}
	  }
	 
	  void OnLineEnd(int iline, LONG cpixel, const BYTE* ptypeBuffer, LONG pixelStride)
	  {
		BYTE* ptypeUnc = ((BYTE*)(_ptypeUncompressed));
		if (_info.components == 1)
		{
			memcpy(ptypeUnc + cpixel * iline,  ptypeBuffer, cpixel * sizeof(BYTE));
			return;
		}

		ptypeUnc += iline * _info.components * cpixel;
		
		switch(_info.colorTransform)
		{
			case COLORXFORM_NONE : return TransformLineToTriplet(ptypeBuffer, pixelStride, ptypeUnc, cpixel, TransformNone());			
			case COLORXFORM_HP1 : return TransformLineToTriplet(ptypeBuffer, pixelStride, ptypeUnc, cpixel, TransformHp1ToRgb());
			case COLORXFORM_HP2 : return TransformLineToTriplet(ptypeBuffer, pixelStride, ptypeUnc, cpixel, TransformHp2ToRgb());
			case COLORXFORM_HP3 : return TransformLineToTriplet(ptypeBuffer, pixelStride, ptypeUnc, cpixel, TransformHp3ToRgb());			
		}

	  }

	  typedef size_t bufType;

	  enum { 
		  bufferbits = sizeof( bufType ) * 8,
	  };
		
	  void MakeValid()
	  {
		  ASSERT(_validBits <=bufferbits - 8);

		  if (_pbyteCompressed < _pbyteNextFF)
		  {
			  do
			  {
				  _readCache		 |= bufType(_pbyteCompressed[0]) << (bufferbits - 8  - _validBits);
				  _validBits		 += 8; 				  
				  _pbyteCompressed   += 1;				
			  }
			  while (_validBits < bufferbits - 8);
			  
			  ASSERT(_validBits >= bufferbits - 8);
			  return;
		  }

		  do
		  {
			  if (_pbyteCompressed >= _pbyteCompressedEnd)
			  {
				  if (_validBits <= 0)
					  throw JlsException(InvalidCompressedData);

				  return;
			  }

			  bufType valnew	  = *_pbyteCompressed;
			  _readCache		 |= bufType(_pbyteCompressed[0]) << (bufferbits - 8  - _validBits);
			  _pbyteCompressed   += 1;				
			  _validBits		 += 8; 

			  if (valnew == 0xFF)		
			  {
				  _validBits--;		
			  }
		  }
		  while (_validBits < bufferbits - 8);

		  _pbyteNextFF = FindNextFF();

	  }


	  BYTE* FindNextFF()
	  {
		  BYTE* pbyteNextFF =_pbyteCompressed;

		  while (pbyteNextFF < _pbyteCompressedEnd && *pbyteNextFF != 0xFF)
	      {
			   pbyteNextFF++;
		  }
		  
		  return pbyteNextFF - (sizeof(bufType)-1);
	  }

	  BYTE* GetCurBytePos() const
	  {
		  LONG  cbitValid = _validBits;
		  BYTE* pbyteCompressed = _pbyteCompressed;

		  for (;;)
		  {
			  LONG cbitLast = pbyteCompressed[-1] == 0xFF ? 7 : 8;

			  if (cbitValid < cbitLast )
				  return pbyteCompressed;

			  cbitValid -= cbitLast; 
			  pbyteCompressed--;
		  }	
	  }


	  inlinehint LONG ReadValue(LONG length)
	  {
		  if (_validBits < length)
		  {
			  MakeValid();
		  }

		  ASSERT(length != 0 && length <= _validBits);
		  ASSERT(length < 32);
		  LONG result = LONG(_readCache >> (bufferbits - length));
		  Skip(length);		
		  return result;
	  }


	  inlinehint LONG PeekByte()
	  { 
		  if (_validBits < 8)
		  {
			  MakeValid();
		  }

		  return _readCache >> (bufferbits - 8); 
	  }



	  inlinehint bool ReadBit()
	  {
		  if (_validBits == 0)
		  {
			  MakeValid();
		  }

		  bool bSet = (_readCache & (bufType(1) << (bufferbits - 1))) != 0;
		  Skip(1);
		  return bSet;
	  }



	  inlinehint LONG Peek0Bits()
	  {
		  if (_validBits < 16)
		  {
			  MakeValid();
		  }
		  bufType valTest = _readCache;

		  for (LONG cbit = 0; cbit < 16; cbit++)
		  {
			  if ((valTest & (bufType(1) << (bufferbits - 1))) != 0)
				  return cbit;

			  valTest <<= 1;
		  }
		  return -1;
	  }



	  inlinehint LONG ReadHighbits()
	  {
		  LONG cbit = Peek0Bits();
		  if (cbit >= 0)
		  {
			  Skip(cbit + 1);
			  return cbit;
		  }
		  Skip(15);

		  for (LONG highbits = 15; ; highbits++)
		  { 
			  if (ReadBit())
				  return highbits;
		  }                 	
	  }


	  LONG ReadLongValue(LONG length)
	  {
		  if (length <= 24)
			  return ReadValue(length);

		  return (ReadValue(length - 24) << 24) + ReadValue(24);
	  }

protected:
	JlsParamaters _info;
	void* _ptypeUncompressed;

private:
	// decoding
	bufType _readCache;
	LONG _validBits;
	BYTE* _pbyteCompressed;
	BYTE* _pbyteNextFF;
	BYTE* _pbyteCompressedEnd;
};


#endif
