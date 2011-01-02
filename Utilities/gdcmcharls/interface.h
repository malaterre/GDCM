// 
// (C) Jan de Vaan 2007-2010, all rights reserved. See the accompanying "License.txt" for licensed use. 
// 


#ifndef JLS_INTERFACE
#define JLS_INTERFACE

#include "publictypes.h"

#if defined(WIN32) && defined(GDCM_BUILD_SHARED_LIBS)
#ifndef CHARLS_IMEXPORT
#define CHARLS_IMEXPORT(returntype) __declspec(dllimport) returntype __stdcall
#endif
#else
#ifndef CHARLS_IMEXPORT 
#define CHARLS_IMEXPORT(returntype) returntype
#endif
#endif /* _WIN32 */


#ifdef __cplusplus
extern "C" 
{
#endif
  CHARLS_IMEXPORT(enum JLS_ERROR) JpegLsEncode(void* compressedData, size_t compressedLength, size_t* pcbyteWritten, 
	    const void* uncompressedData, size_t uncompressedLength, struct JlsParameters* pparams);

  CHARLS_IMEXPORT(enum JLS_ERROR) JpegLsDecode(void* uncompressedData, size_t uncompressedLength, 
		const void* compressedData, size_t compressedLength, 
		struct JlsParameters* info);


  CHARLS_IMEXPORT(enum JLS_ERROR) JpegLsDecodeRect(void* uncompressedData, size_t uncompressedLength, 
		const void* compressedData, size_t compressedLength, 
		struct JlsRect rect, struct JlsParameters* info);

  CHARLS_IMEXPORT(enum JLS_ERROR) JpegLsReadHeader(const void* compressedData, size_t compressedLength, 
		struct JlsParameters* pparams);

  CHARLS_IMEXPORT(enum JLS_ERROR) JpegLsVerifyEncode(const void* uncompressedData, size_t uncompressedLength, 
		const void* compressedData, size_t compressedLength);

#ifdef __cplusplus
}
#endif

#endif
