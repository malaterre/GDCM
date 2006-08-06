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

#ifndef __gdcmLookupTable_h
#define __gdcmLookupTable_h

#include "gdcmTypes.h"
#include "gdcmObject.h"


namespace gdcm
{
  
class LookupTableInternal;
class ByteValue;
class IStream;
class OStream;
class LookupTable : public Object
{
public:
  typedef enum {
    RED = 0,  // Keep RED == 0 
    GREEN,
    BLUE,
    GRAY,
    UNKNOWN
  } LookupTableType;

  LookupTable();
  ~LookupTable();

  void Allocate( int bitsample = 8 );
  void InitializeLUT(LookupTableType type, unsigned short length,
    unsigned short subscript, unsigned short bitsize);
  void SetLUT(LookupTableType type, unsigned char *array,
    unsigned int length);
  void InitializeRedLUT(unsigned short length, unsigned short subscript,
    unsigned short bitsize);
  void SetRedLUT(unsigned char *red, unsigned int length);
  void InitializeBlueLUT(unsigned short length, unsigned short subscript,
    unsigned short bitsize);
  void SetGreenLUT(unsigned char *green, unsigned int length);
  void InitializeGreenLUT(unsigned short length, unsigned short subscript,
    unsigned short bitsize);
  void SetBlueLUT(unsigned char *blue, unsigned int length);

  void Decode(IStream &is, OStream &os);

  LookupTable(LookupTable const &lut):Object(lut)
    {
    abort();
    }

private:
  LookupTableInternal *Internal;
};

} // end namespace gdcm

#endif //__gdcmLookupTable_h
