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
#include "gdcmLookupTable.h"
#include "gdcmByteValue.h"

namespace gdcm
{

class LookupTableInternal
{
public:
  ByteValue *Red;
  ByteValue *Green;
  ByteValue *Blue;
};

LookupTable::LookupTable()
{
  Internal = new LookupTableInternal;
}

LookupTable::~LookupTable()
{
  delete Internal;
}

void LookupTable::SetRedLUT(ByteValue const &bv)
{
  Internal->Red = const_cast<ByteValue*>(&bv);
}

void LookupTable::SetGreenLUT(ByteValue const &bv)
{
  Internal->Green = const_cast<ByteValue*>(&bv);
}

void LookupTable::SetBlueLUT(ByteValue const &bv)
{
  Internal->Blue = const_cast<ByteValue*>(&bv);
}

} // end namespace gdcm
