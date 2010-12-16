// 
// (C) Jan de Vaan 2007-2010, all rights reserved. See the accompanying "License.txt" for licensed use. 
// 


#include "config.h"
#include <iostream>
#include <vector>

#include "../interface.h"
#include "../util.h"
#include "../streams.h"

#include "util.h"
#include "time.h"


bool IsMachineLittleEndian()
{
	int a = 0xFF000001;
	char* chars = reinterpret_cast<char*>(&a);
	return chars[0] == 0x01;
}


void FixEndian(std::vector<BYTE>* rgbyte, bool littleEndianData)
{ 
	if (littleEndianData == IsMachineLittleEndian())
		return;

	for (size_t i = 0; i < rgbyte->size()-1; i += 2)
	{
		std::swap((*rgbyte)[i], (*rgbyte)[i + 1]);
	}
}



bool ReadFile(SZC strName, std::vector<BYTE>* pvec, int ioffs, int bytes)
{
	FILE* pfile = fopen(strName, "rb");
	if( !pfile ) 
	{
		fprintf( stderr, "Could not open %s\n", strName );
		return false;
	}

	fseek(pfile, 0, SEEK_END);	
	int cbyteFile = ftell(pfile);
	if (ioffs < 0)
	{
		assert(bytes != 0);
		ioffs = cbyteFile - bytes;
	}
	if (bytes == 0)
	{
		bytes = cbyteFile  -ioffs;
	}

	fseek(pfile, ioffs, SEEK_SET);	
	pvec->resize(bytes);
	size_t bytesRead = fread(&(*pvec)[0],1, pvec->size(), pfile);
	fclose(pfile);
	return bytesRead == pvec->size();
}


void WriteFile(SZC strName, std::vector<BYTE>& vec)
{
	FILE* pfile = fopen(strName, "wb");
	if( !pfile ) 
	{
		fprintf( stderr, "Could not open %s\n", strName );
		return;
	}

	fwrite(&vec[0],1, vec.size(), pfile);
	fclose(pfile);
}


void TestRoundTrip(const char* strName, std::vector<BYTE>& rgbyteRaw, Size size, int cbit, int ccomp)
{	
	std::vector<BYTE> rgbyteCompressed(size.cx *size.cy * ccomp * cbit / 4);

	std::vector<BYTE> rgbyteOut(size.cx * size.cy * ((cbit + 7) / 8) * ccomp);

	double dblstart = getTime();

	JlsParameters info = JlsParameters();
	info.components = ccomp;
	info.bitspersample = cbit;
	info.height = size.cy;
	info.width = size.cx;

	if (ccomp == 4)
	{
		info.ilv = ILV_LINE;
	}
	else if (ccomp == 3)
	{
		info.ilv = ILV_LINE;
		info.colorTransform = COLORXFORM_HP1;
	}

	size_t compressedLength;
	JLS_ERROR err = JpegLsEncode(&rgbyteCompressed[0], rgbyteCompressed.size(), &compressedLength, &rgbyteRaw[0], rgbyteOut.size(), &info);
	assert(err == OK);

	double dwtimeEncodeComplete = getTime();

	err = JpegLsDecode(&rgbyteOut[0], rgbyteOut.size(), &rgbyteCompressed[0], int(compressedLength), NULL);
	assert(err == OK);

	double bitspersample = compressedLength  * 8  * 1.0 /  (ccomp *size.cy * size.cx);
	double dwtimeDecodeComplete = getTime();
	std::cout << "RoundTrip test for: " << strName << "\n\r";
	double decodeTime = dwtimeDecodeComplete - dwtimeEncodeComplete;
	double symbolRate = (ccomp *size.cy * size.cx)/(1000.0 * decodeTime);
	printf("Size:%4ldx%4ld Encode:%7.2f Decode:%7.2f Bps:%5.2f Decode rate:%5.1f M/s \n\r", size.cx, size.cy, dwtimeEncodeComplete - dblstart, dwtimeDecodeComplete - dwtimeEncodeComplete, bitspersample, symbolRate);
	BYTE* pbyteOut = &rgbyteOut[0];
	for (size_t i = 0; i < rgbyteOut.size(); ++i)
	{
		if (rgbyteRaw[i] != pbyteOut[i])
		{
			assert(false);
			break;
		}
	}	
}


void TestFile(SZC strName, int ioffs, Size size2, int cbit, int ccomp, bool littleEndianFile)
{
	int byteCount = size2.cx * size2.cy * ccomp * ((cbit + 7)/8);
	std::vector<BYTE> rgbyteUncompressed;

	if (!ReadFile(strName, &rgbyteUncompressed, ioffs, byteCount))
		return;

	if (cbit > 8)
	{
		FixEndian(&rgbyteUncompressed, littleEndianFile);		
	}

	TestRoundTrip(strName, rgbyteUncompressed, size2, cbit, ccomp);
}

