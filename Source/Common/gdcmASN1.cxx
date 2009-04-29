/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmASN1.h"
#include "gdcmSystem.h"

#include <fstream>

/*
 */
namespace gdcm
{

class ASN1Internals
{
public:
};

ASN1::ASN1()
{
  Internals = new ASN1Internals;
}

ASN1::~ASN1()
{
  delete Internals;
}

bool ASN1::ParseDumpFile(const char *filename)
{
  std::ifstream is(filename);
  size_t length = System::FileSize(filename);
  char * str = new char[length];
  is.read( str, length );
  bool b = ParseDump( str, length );
  delete[] str;
  return b;
}

bool ASN1::ParseDump(const char *array, size_t length)
{
  int indent = 1;
  int dump = 0; // -1
	BIO *in=NULL,*out=NULL,*b64=NULL, *derout = NULL;
  
	out=BIO_new(BIO_s_file());
  assert( out );
	BIO_set_fp(out,stdout,BIO_NOCLOSE|BIO_FP_TEXT);
  if (!ASN1_parse_dump(out,(unsigned char*)array,length,indent,dump) )
    {
    return false;
    }

  return true;
}

} // end namespace gdcm
