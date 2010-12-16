

#include "config.h"
#include <iostream>
#include <vector>


#include "util.h"
#include "../interface.h"


int findstring(std::vector<BYTE>& container, BYTE* bytesToFind, unsigned int bytesLength)
{
	for (unsigned int i=0; i < container.size() - bytesLength; ++i)
	{
		for (unsigned int j=0; j < bytesLength; ++j)
		{
			if (bytesToFind[j] != container[i + j])
				goto next;
		}
		return i;

		next:;
	}
	return -1;
}

#define COUNT(x) (sizeof(x)/sizeof(x[0]))


void TestDicomSampleImage(const char* name)
{
	std::vector<BYTE> data;
	bool success = ReadFile(name, &data, 9);

	ASSERT(success);
	
        BYTE pixeldataStart[] =  { 0x00, 0x00, 0x01, 0x00, 0xFF, 0xD8, 0xFF, 0xF7 };

	int offset = findstring(data, pixeldataStart, COUNT(pixeldataStart));

	data.erase(data.begin(), data.begin() + offset - 4);

	// remove the dicom fragment headers (in the concerned images they occur every 64k)
	for (unsigned int i =  0; i < data.size(); i+= 64 * 1024)
	{
		data.erase(data.begin() + i, data.begin() + i + 8);		
	}

	JlsParameters info;

	JLS_ERROR error = JpegLsReadHeader(&data[0], data.size(), &info);


//    0xFE, 0xFF, 0x00, 0xE0, 0x00, 0x00, 0x01, 0x00
	std::vector<BYTE> dataUnc;
	dataUnc.resize(info.bytesperline * info.height);

	error = JpegLsDecode(&dataUnc[0], dataUnc.size(), &data[0], data.size(), NULL);
	ASSERT(error == OK);
	std::cout << ".";
}

void TestDicomWG4Images()
{
	TestDicomSampleImage("test/compsamples_jpegls/IMAGES/JLSL/XA1_JLSL");	
	TestDicomSampleImage("test/compsamples_jpegls/IMAGES/JLSL/CT2_JLSL");	
	TestDicomSampleImage("test/compsamples_jpegls/IMAGES/JLSL/MG1_JLSL");
	TestDicomSampleImage("test/compsamples_jpegls/IMAGES/JLSL/MR1_JLSL");
	TestDicomSampleImage("test/compsamples_jpegls/IMAGES/JLSL/MR2_JLSL");
	TestDicomSampleImage("test/compsamples_jpegls/IMAGES/JLSL/MR3_JLSL");
	TestDicomSampleImage("test/compsamples_jpegls/IMAGES/JLSL/MR4_JLSL");
	TestDicomSampleImage("test/compsamples_jpegls/IMAGES/JLSL/NM1_JLSL");
	TestDicomSampleImage("test/compsamples_jpegls/IMAGES/JLSL/RG1_JLSL");
	TestDicomSampleImage("test/compsamples_jpegls/IMAGES/JLSL/RG2_JLSL");
	TestDicomSampleImage("test/compsamples_jpegls/IMAGES/JLSL/RG3_JLSL");
	TestDicomSampleImage("test/compsamples_jpegls/IMAGES/JLSL/SC1_JLSL");
}
