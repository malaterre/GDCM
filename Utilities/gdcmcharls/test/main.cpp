// 
// (C) Jan de Vaan 2007-2010, all rights reserved. See the accompanying "License.txt" for licensed use. 
// 


#include "config.h"
#include <iostream>
#include <vector>

#include "../interface.h"
#include "../util.h"
#include "../defaulttraits.h"
#include "../losslesstraits.h"
#include "../colortransform.h"
#include "../streams.h"
#include "../processline.h"

#include "util.h"

typedef const char* SZC;


bool ScanFile(SZC strNameEncoded, std::vector<BYTE>* rgbyteFile, JlsParameters* info)
{
	if (!ReadFile(strNameEncoded, rgbyteFile))
	{
		assert(false);
		return false;
	}

	JLS_ERROR err = JpegLsReadHeader(&((*rgbyteFile)[0]), rgbyteFile->size(), info);
	assert(err == OK);
	return err == OK;
}




void TestTraits16bit()
{
	DefaultTraitsT<USHORT,USHORT> traits1 = DefaultTraitsT<USHORT,USHORT>(4095,0);
	LosslessTraitsT<USHORT,12> traits2 = LosslessTraitsT<USHORT,12>();

	assert(traits1.LIMIT == traits2.LIMIT);
	assert(traits1.MAXVAL == traits2.MAXVAL);
	assert(traits1.RESET == traits2.RESET);
	assert(traits1.bpp == traits2.bpp);
	assert(traits1.qbpp == traits2.qbpp);

	for (int i = -4096; i < 4096; ++i)
	{
		assert(traits1.ModRange(i) == traits2.ModRange(i));
		assert(traits1.ComputeErrVal(i) == traits2.ComputeErrVal(i));
	}

	for (int i = -8095; i < 8095; ++i)
	{
		assert(traits1.CorrectPrediction(i) == traits2.CorrectPrediction(i));
		assert(traits1.IsNear(i,2) == traits2.IsNear(i,2));	
	}	
}

void TestTraits8bit()
{
	DefaultTraitsT<BYTE,BYTE> traits1 = DefaultTraitsT<BYTE,BYTE>(255,0);
	LosslessTraitsT<BYTE,8> traits2 = LosslessTraitsT<BYTE,8>();

	assert(traits1.LIMIT == traits2.LIMIT);
	assert(traits1.MAXVAL == traits2.MAXVAL);
	assert(traits1.RESET == traits2.RESET);
	assert(traits1.bpp == traits2.bpp);
	assert(traits1.qbpp == traits2.qbpp);	

	for (int i = -255; i < 255; ++i)
	{
		assert(traits1.ModRange(i) == traits2.ModRange(i));
		assert(traits1.ComputeErrVal(i) == traits2.ComputeErrVal(i));
	}

	for (int i = -255; i < 512; ++i)
	{
		assert(traits1.CorrectPrediction(i) == traits2.CorrectPrediction(i));
		assert(traits1.IsNear(i,2) == traits2.IsNear(i,2));	
	}
}


void TestNoiseImage()
{
	srand(21344); 
	Size size2 = Size(1024, 1024);
	std::vector<BYTE> rgbyteNoise(size2.cx * size2.cy);

	for (int line = 0; line<size2.cy; ++line)
	{
		for (int icol= 0; icol<size2.cx; ++icol)
		{
			BYTE val = BYTE(rand());
			rgbyteNoise[line*size2.cx + icol] = BYTE(val & 0x7F);// < line ? val : 0;
		}	
	}

	TestRoundTrip("noise", rgbyteNoise, size2, 7, 1);
}



void TestBgra()
{
	char rgbyteTest[] = "RGBARGBARGBARGBA1234";
	char rgbyteComp[] = "BGRABGRABGRABGRA1234";
	TransformRgbToBgr(rgbyteTest, 4, 4);
	assert(strcmp(rgbyteTest, rgbyteComp) == 0);
}


void TestBgr()
{
	JlsParameters info;
	std::vector<BYTE> rgbyteEncoded;	
	ScanFile("test/conformance/T8C2E3.JLS", &rgbyteEncoded, &info);
	std::vector<BYTE> rgbyteDecoded(info.width * info.height * info.components);	

	info.outputBgr = true;
	
	JLS_ERROR err = JpegLsDecode(&rgbyteDecoded[0], rgbyteDecoded.size(), &rgbyteEncoded[0], rgbyteEncoded.size(), &info);
	assert(err == OK);

	assert(rgbyteDecoded[0] == 0x69);
	assert(rgbyteDecoded[1] == 0x77);
	assert(rgbyteDecoded[2] == 0xa1);	
	assert(rgbyteDecoded[info.width * 6 + 3] == 0x2d);
	assert(rgbyteDecoded[info.width * 6 + 4] == 0x43);
	assert(rgbyteDecoded[info.width * 6 + 5] == 0x4d);	

}


void TestTooSmallOutputBuffer()
{
	std::vector<BYTE> rgbyteCompressed;	
	if (!ReadFile("test/lena8b.jls", &rgbyteCompressed, 0))
		return;

	std::vector<BYTE> rgbyteOut(512 * 511);	
	JLS_ERROR error = JpegLsDecode(&rgbyteOut[0], rgbyteOut.size(), &rgbyteCompressed[0], int(rgbyteCompressed.size()), NULL);

	assert(error == UncompressedBufferTooSmall);	
}


void TestDecodeRect()
{
	std::vector<BYTE> rgbyteCompressed;	
	JlsParameters info;
	if (!ScanFile("test/lena8b.jls", &rgbyteCompressed, &info))
		return;

	std::vector<BYTE> rgbyteOutFull(info.width*info.height*info.components);		
	JLS_ERROR error = JpegLsDecode(&rgbyteOutFull[0], rgbyteOutFull.size(), &rgbyteCompressed[0], int(rgbyteCompressed.size()), NULL);	
	assert(error == OK);	

	JlsRect rect = { 128, 128, 256, 1 };
	std::vector<BYTE> rgbyteOut(rect.Width * rect.Height);	
	rgbyteOut.push_back(0x1f);
	error = JpegLsDecodeRect(&rgbyteOut[0], rgbyteOut.size(), &rgbyteCompressed[0], int(rgbyteCompressed.size()), rect, NULL);	
	assert(error == OK);	

	assert(memcmp(&rgbyteOutFull[rect.X + rect.Y*512], &rgbyteOut[0], rect.Width * rect.Height) == 0);
	assert(rgbyteOut[rect.Width * rect.Height] == 0x1f);
}


void TestColorTransforms_HpImages();
void TestConformance();
void TestSampleAnnexH3();
void PerformanceTests();
void DamagedBitstreamTests();
void TestDicomWG4Images();

void UnitTest()
{
	TestDecodeRect();

	printf("Test Traits\r\n");
	TestTraits16bit();		
	TestTraits8bit();		

	printf("Windows bitmap BGR/BGRA output\r\n");
	TestBgr();
	TestBgra();

	printf("Test Small buffer\r\n");
	TestTooSmallOutputBuffer();

	printf("Test Conformance\r\n");
	TestConformance();

	printf("Test Color transform equivalence on HP images\r\n");
	TestColorTransforms_HpImages();

	printf("Test Annex H3\r\n");
	TestSampleAnnexH3();

	TestNoiseImage();
}


int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		printf("CharLS test runner.\r\nOptions: -unittest, -bitstreamdamage, -performance, -dontwait\r\n");		
		return 0;
	}

	bool wait = true; 
	for (int i = 1; i < argc; ++i)
	{
		std::string str = argv[i];
		if (str.compare("-unittest") == 0)
		{
			UnitTest();		
			continue;
		}

		if (str.compare("-bitstreamdamage") == 0)
		{
			DamagedBitstreamTests();		
			continue;
		}

		if (str.compare("-performance") == 0)
		{
			PerformanceTests();		
			continue;
		}

		if (str.compare("-dicom") == 0)
		{
			TestDicomWG4Images();		
			continue;
		}

		if (str.compare("-dontwait") == 0)
		{
			wait = false;		
			continue;
		}

		printf("Option not understood: %s\r\n", argv[i]);
		break;

	}

	if (wait)
	{
		char c;
		std::cin >> c;
		return 0;
	}
}

