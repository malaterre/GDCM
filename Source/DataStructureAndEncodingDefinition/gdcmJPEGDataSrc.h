/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmIStream.h"
#include "gdcmOStream.h"

#include <setjmp.h>

extern "C" {
#include "jinclude.h"
#include "jpeglib.h"
#include "jerror.h"
}

namespace gdcm
{


struct my_error_mgr {
   struct jpeg_error_mgr pub; /* "public" fields */
   jmp_buf setjmp_buffer;     /* for return to caller */
};
typedef struct my_error_mgr* my_error_ptr;

class JPEGDataSrc
{
public:
  JPEGDataSrc():cinfo(),jerr(),StateSuspension(0),SampBuffer(0) {}
  bool Decode(IStream &is, OStream &os);
private:
  jpeg_decompress_struct cinfo;
  my_error_mgr jerr;
  int StateSuspension;
  void *SampBuffer;

};

} // end namespace gdcm
