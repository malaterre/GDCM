// 
// (C) Jan de Vaan 2007-2010, all rights reserved. See the accompanying "License.txt" for licensed use. 
// 

#ifndef CHARLS_DECODERSTATEGY
#define CHARLS_DECODERSTATEGY

#include "jpegmarker.h"
#include "processline.h"
#include "config.h"
#include "util.h"

// Implements encoding to stream of bits. In encoding mode JpegLsCodec inherits from EncoderStrategy

class DecoderStrategy
{
public:
	DecoderStrategy(const JlsParameters& info) :
		_info(info),
		_byteStream(GDCM_NULLPTR),
		_readCache(0),
		_validBits(0),
		_position(GDCM_NULLPTR),
		_nextFFPosition(GDCM_NULLPTR),
		_endPosition(GDCM_NULLPTR)
	{
	}

	virtual ~DecoderStrategy()
	{
	}

	virtual ProcessLine* CreateProcess(ByteStreamInfo rawStreamInfo) = 0;

	virtual void SetPresets(const JlsCustomParameters& presets) = 0;
	virtual void DecodeScan(std::auto_ptr<ProcessLine> outputData, const JlsRect& size, ByteStreamInfo* compressedData, bool bCheck) = 0;

	void Init(ByteStreamInfo* compressedStream)
	{
		_validBits = 0;
		_readCache = 0;

		if (compressedStream->rawStream != GDCM_NULLPTR)
		{
			_buffer.resize(40000);
			_position = (BYTE*)&_buffer[0];
			_endPosition = _position;
			_byteStream = compressedStream->rawStream;
			AddBytesFromStream();
		}
		else
		{
			_byteStream = GDCM_NULLPTR;
			_position = compressedStream->rawData;
			_endPosition = _position + compressedStream->count;
		}

		_nextFFPosition = FindNextFF();
		MakeValid();
	}

	void AddBytesFromStream()
	{
		if (_byteStream == GDCM_NULLPTR || _byteStream->sgetc() == std::char_traits<char>::eof())
			return;

		size_t count = _endPosition - _position; 

		if (count > 64)
			return;

		for (size_t i = 0; i < count; ++i)
		{
			_buffer[i] = _position[i];
		}
		size_t offset = &_buffer[0] - _position;

		_position += offset;
		_endPosition += offset;
		_nextFFPosition += offset;

		std::streamsize readbytes = _byteStream->sgetn((char*)_endPosition, _buffer.size() - count);
		_endPosition += readbytes;
	}

	inlinehint void Skip(LONG length)
	{
		_validBits -= length;
		_readCache = _readCache << length; 
	}


	void OnLineBegin(LONG /*cpixel*/, void* /*ptypeBuffer*/, LONG /*pixelStride*/) 
	{
	}


	void OnLineEnd(LONG pixelCount, const void* ptypeBuffer, LONG pixelStride)
	{
		_processLine->NewLineDecoded(ptypeBuffer, pixelCount, pixelStride);
	}

	void EndScan()
	{
		if ((*_position) != 0xFF)
		{
			ReadBit();

			if ((*_position) != 0xFF)
			throw JlsException(TooMuchCompressedData);
		}

		if (_readCache != 0)
			throw JlsException(TooMuchCompressedData);
	}


	inlinehint bool OptimizedRead()
	{
		// Easy & fast: if there is no 0xFF byte in sight, we can read without bitstuffing
		if (_position < _nextFFPosition - (sizeof(bufType)-1))
		{
			_readCache |= FromBigEndian<sizeof(bufType)>::Read(_position) >> _validBits;
			int bytesToRead = (bufferbits - _validBits) >> 3;
			_position += bytesToRead;
			_validBits += bytesToRead * 8;
			ASSERT(_validBits >= bufferbits - 8);
			return true;
		}
		return false;
	}

	typedef size_t bufType;

	enum { 
		bufferbits = sizeof( bufType ) * 8
	};

	void MakeValid()
	{
		ASSERT(_validBits <=bufferbits - 8);

		if (OptimizedRead())
			return;

		AddBytesFromStream();

		do
		{
			if (_position >= _endPosition)
			{
				if (_validBits <= 0)
					throw JlsException(InvalidCompressedData);

				return;
			}

			bufType valnew	  = _position[0];

			if (valnew == 0xFF)
			{
				// JPEG bitstream rule: no FF may be followed by 0x80 or higher
				if (_position == _endPosition - 1 || (_position[1] & 0x80) != 0)
				{
					if (_validBits <= 0)
					throw JlsException(InvalidCompressedData);

					return;
				}
			}

			_readCache	|= valnew << (bufferbits - 8 - _validBits);
			_position		+= 1;
			_validBits	+= 8;

			if (valnew == 0xFF)
			{
				_validBits--;
			}
		}
		while (_validBits < bufferbits - 8);

		_nextFFPosition = FindNextFF();
		return;
	}


	BYTE* FindNextFF()
	{
		BYTE* pbyteNextFF = _position;

		while (pbyteNextFF < _endPosition)
		{
			if (*pbyteNextFF == 0xFF) 
				break;

			pbyteNextFF++;
		}

		return pbyteNextFF;
	}


	BYTE* GetCurBytePos() const
	{
		LONG validBits = _validBits;
		BYTE* compressedBytes = _position;

		for (;;)
		{
			LONG cbitLast = compressedBytes[-1] == 0xFF ? 7 : 8;

			if (validBits < cbitLast )
				return compressedBytes;

			validBits -= cbitLast; 
			compressedBytes--;
		}
	}


	inlinehint LONG ReadValue(LONG length)
	{
		if (_validBits < length)
		{
			MakeValid();
			if (_validBits < length)
				throw JlsException(InvalidCompressedData);
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
		if (_validBits <= 0)
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

		for (LONG count = 0; count < 16; count++)
		{
			if ((valTest & (bufType(1) << (bufferbits - 1))) != 0)
				return count;

			valTest <<= 1;
		}
		return -1;
	}


	inlinehint LONG ReadHighbits()
	{
		LONG count = Peek0Bits();
		if (count >= 0)
		{
			Skip(count + 1);
			return count;
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
	JlsParameters _info;
	std::auto_ptr<ProcessLine> _processLine;

private:
	std::vector<BYTE> _buffer;
	std::basic_streambuf<char>* _byteStream;

	// decoding
	bufType _readCache;
	LONG _validBits;
	BYTE* _position;
	BYTE* _nextFFPosition;
	BYTE* _endPosition;
};


#endif
