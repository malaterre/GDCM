//
// (C) CharLS Team 2014, all rights reserved. See the accompanying "License.txt" for licensed use. 
//

#pragma once

#include "util.h"
#include "jpegsegment.h"
#include "jpegstreamwriter.h"
#include <vector>

class JpegImageDataSegment : public JpegSegment
{
public:
	JpegImageDataSegment(ByteStreamInfo rawStream, const JlsParameters& info, LONG icompStart, int ccompScan) :
		_ccompScan(ccompScan),
		_icompStart(icompStart),
		_rawStreamInfo(rawStream),
		_info(info)
	{
	}

	void Serialize(JpegStreamWriter& streamWriter);

private:
	int _ccompScan;
	LONG _icompStart;
	ByteStreamInfo _rawStreamInfo;
	JlsParameters _info;
};
