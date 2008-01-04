/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
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
  OverlayInternal():
  Rows(0),
  Columns(0),
  NumberOfFrames(0),
  Description(),
  Type(),
  //Origin[2],
  FrameOrigin(0),
  BitsAllocated(0),
  BitPosition(0),
  Data() { Origin[0] = Origin[1] = 0; }
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
  signed short   Origin[2];      // (6000,0050) SS 1\1                                      #   4, 2 OverlayOrigin
  unsigned short FrameOrigin;    // (6000,0051) US 1                                        #   2, 1 ImageFrameOrigin
  unsigned short BitsAllocated;  // (6000,0100) US 1                                        #   2, 1 OverlayBitsAllocated
  unsigned short BitPosition;    // (6000,0102) US 0                                        #   2, 1 OverlayBitPosition
  //std::vector<bool> Data;
  std::vector<char> Data;
  void Print(std::ostream &os) const {
    os << "Rows            " <<  Rows << std::endl;
    os << "Columns         " <<  Columns << std::endl;
    os << "NumberOfFrames  " <<  NumberOfFrames << std::endl;
    os << "Description     " <<  Description << std::endl;
    os << "Type            " <<  Type << std::endl;
    os << "Origin[2]       " <<  Origin[0] << "," << Origin[1] << std::endl;
    os << "FrameOrigin     " <<  FrameOrigin << std::endl;
    os << "BitsAllocated   " <<  BitsAllocated << std::endl;
    os << "BitPosition     " <<  BitPosition << std::endl;
    //std::vector<bool> Data;
  }
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
  unsigned short Overlay::GetRows() const { return Internal->Rows; }
void Overlay::SetColumns(unsigned short columns) { Internal->Columns = columns; }
  unsigned short Overlay::GetColumns() const { return Internal->Columns; }
void Overlay::SetNumberOfFrames(unsigned int numberofframes) { Internal->NumberOfFrames = numberofframes; }
void Overlay::SetDescription(const char* description) { Internal->Description = description; }
void Overlay::SetType(const char* type) { Internal->Type = type; }
void Overlay::SetOrigin(const signed short *origin) {
  Internal->Origin[0] = origin[0];
  Internal->Origin[1] = origin[1];
}
void Overlay::SetFrameOrigin(unsigned short frameorigin) { Internal->FrameOrigin = frameorigin; }
void Overlay::SetBitsAllocated(unsigned short bitsallocated) { Internal->BitsAllocated = bitsallocated; }
void Overlay::SetBitPosition(unsigned short bitposition) { Internal->BitPosition = bitposition; }

bool Overlay::IsEmpty() const
{
  return Internal->Data.empty();
}

void Overlay::SetOverlay(const char *array, unsigned int length)
{
  //char * p = (char*)&Internal->Data[0];
  Internal->Data.resize( length ); // ??
  std::copy(array, array+length, Internal->Data.begin());
  assert( length * 8 == Internal->Rows * Internal->Columns );
  assert( Internal->Data.size() == length );
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
    os.write(reinterpret_cast<char*>(unpackedbytes), 8);
    }
}

void Overlay::Decompress(std::ostream &os)
{
  unsigned char unpackedbytes[8];
  for( std::vector<char>::const_iterator it = Internal->Data.begin(); it != Internal->Data.end(); ++it )
    {
    unsigned char packedbytes = *it;
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
    os.write(reinterpret_cast<char*>(unpackedbytes), 8);
    }
}

void Overlay::Print(std::ostream &os) const
{
  Internal->Print( os );
}

} // end namespace gdcm
