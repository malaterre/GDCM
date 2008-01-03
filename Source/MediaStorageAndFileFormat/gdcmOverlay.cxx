/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmOverlay.h"
#include <vector>

namespace gdcm
{

class OverlayInternal
{
public:
  OverlayInternal():Data() { }
  /*
  (6000,0010) US 484                                      #   2, 1 OverlayRows
  (6000,0011) US 484                                      #   2, 1 OverlayColumns
  (6000,0015) IS [1]                                      #   2, 1 NumberOfFramesInOverlay
  (6000,0022) LO [Siemens MedCom Object Graphics]         #  30, 1 OverlayDescription
  (6000,0040) CS [G]                                      #   2, 1 OverlayType
  (6000,0050) SS 1\1                                      #   4, 2 OverlayOrigin
  (6000,0051) US 1                                        #   2, 1 ImageFrameOrigin
  (6000,0100) US 1                                        #   2, 1 OverlayBitsAllocated
  (6000,0102) US 0                                        #   2, 1 OverlayBitPosition
  (6000,3000) OW 0000\0000\0000\0000\0000\0000\0000\0000\0000\0000\0000\0000\0000... # 29282, 1 OverlayData
  */

  unsigned short Rows;           // (6000,0010) US 484                                      #   2, 1 OverlayRows
  unsigned short Columns;        // (6000,0011) US 484                                      #   2, 1 OverlayColumns
  unsigned int   NumberOfFrames; // (6000,0015) IS [1]                                      #   2, 1 NumberOfFramesInOverlay
  std::string    Description;    // (6000,0022) LO [Siemens MedCom Object Graphics]         #  30, 1 OverlayDescription
  std::string    Type;           // (6000,0040) CS [G]                                      #   2, 1 OverlayType
  signed short   Origin[2];         // (6000,0050) SS 1\1                                      #   4, 2 OverlayOrigin
  unsigned short FrameOrigin;    // (6000,0051) US 1                                        #   2, 1 ImageFrameOrigin
  unsigned short BitsAllocated;  // (6000,0100) US 1                                        #   2, 1 OverlayBitsAllocated
  unsigned short BitPosition;    // (6000,0102) US 0                                        #   2, 1 OverlayBitPosition
  std::vector<bool> Data;
};

Overlay::Overlay()
{
  Internal = new OverlayInternal;
}

Overlay::~Overlay()
{
  delete Internal;
}

  void Overlay::SetRows(unsigned short rows) { Internal->Rows = rows; }
  void Overlay::SetColumns(unsigned short columns) { Internal->Columns = columns; }
  void Overlay::SetNumberOfFrames(unsigned int numberofframes) { Internal->NumberOfFrames = numberofframes; }
  void Overlay::SetDescription(const char* description) { Internal->Description = description; }
  void Overlay::SetType(const char* type) { Internal->Type = type; }
  void Overlay::SetOrigin(signed short *origin) { /*Internal->Origin = origin;*/ abort(); }
  void Overlay::SetFrameOrigin(unsigned short frameorigin) { Internal->FrameOrigin = frameorigin; }
  void Overlay::SetBitsAllocated(unsigned short bitsallocated) { Internal->BitsAllocated = bitsallocated; }
  void Overlay::SetBitPosition(unsigned short bitposition) { Internal->BitPosition = bitposition; }

void Overlay::SetOverlay(const unsigned char *array, unsigned int length)
{
  unsigned char * p = (unsigned char*)&Internal->Data[0];
  std::copy(array, array+length, p);
}

void Overlay::Decode(std::istream &is, std::ostream &os)
{
  unsigned char packedbytes;
  unsigned char unpackedbytes[8];
  while( is.read((char*)&packedbytes,1) )
    {
    unsigned char mask = 1;
    for (unsigned int i = 0; i < 8; ++i)
      {
      if ( (packedbytes & mask) == 0)
        {
        unpackedbytes[i] = 0;
        }
      else
        {
        unpackedbytes[i] = 1;
        }
      mask <<= 1;
      }
    os.write((char*)unpackedbytes, 8);
    }
}

} // end namespace gdcm
