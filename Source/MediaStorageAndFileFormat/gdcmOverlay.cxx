/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmOverlay.h"
#include "gdcmTag.h"
#include "gdcmDataElement.h"
#include "gdcmDataSet.h"
#include "gdcmAttribute.h"

#include <vector>

namespace gdcm
{

class OverlayInternal
{
public:
  OverlayInternal():
  InPixelData(false),
  Group(0), // invalid default
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

  bool InPixelData;
// Identifier need to be in the [6000,60FF] range (no odd number):
  unsigned short Group;
// Descriptor:
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
    os << "Group           0x" <<  std::hex << Group << std::dec << std::endl;
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

Overlay::Overlay(Overlay const &ov):Object(ov)
{
  Internal = new OverlayInternal;
  // TODO: copy OverlayInternal into other...
  *Internal = *ov.Internal;
}

unsigned int Overlay::GetNumberOfOverlays(DataSet const & ds)
{
  Tag overlay(0x6000,0x0000); // First possible overlay
  bool finished = false;
  unsigned int numoverlays = 0;
  while( !finished )
    {
    const DataElement &de = ds.FindNextDataElement( overlay );
    if( de.GetTag().GetGroup() > 0x60FF ) // last possible curve
      {
      finished = true;
      }
    else if( de.GetTag().IsPrivate() )
      {
      // Move on to the next public one:
      overlay.SetGroup( de.GetTag().GetGroup() + 1 );
      }
    else
      {
      // Yeah this is an overlay element
      ++numoverlays;
      // Move on to the next possible one:
      overlay.SetGroup( overlay.GetGroup() + 2 );
      }
    }

  return numoverlays;
}

void Overlay::Update(const DataElement & de)
{
/*
  8.1.2 Overlay data encoding of related data elements
    Encoded Overlay Planes always have a bit depth of 1, and are encoded separately from the Pixel Data in Overlay Data (60xx,3000). The following two Data Elements shall define the Overlay Plane structure:
    ¿ Overlay Bits Allocated (60xx,0100)
    ¿ Overlay Bit Position (60xx,0102)
    Notes: 1. There is no Data Element analogous to Bits Stored (0028,0101) since Overlay Planes always have a bit depth of 1.
    2. Restrictions on the allowed values for these Data Elements are defined in PS 3.3. Formerly overlay data stored in unused bits of Pixel Data (7FE0,0010) was described, and these attributes had meaningful values but this usage has been retired. See PS 3.5 2004. For overlays encoded in Overlay Data Element (60xx,3000), Overlay Bits Allocated (60xx,0100) is always 1 and Overlay Bit Position (60xx,0102) is always 0.
*/

  assert( de.GetTag().IsPublic() );
  const ByteValue* bv = de.GetByteValue();
  if( !bv ) return; // Discard any empty element (will default to another value)
  assert( bv->GetPointer() && bv->GetLength() );
  std::string s( bv->GetPointer(), bv->GetLength() );
  // What if a \0 can be found before the end of string...
  //assert( strlen( s.c_str() ) == s.size() );

  // First thing check consistency:
  if( !GetGroup() )
    {
    SetGroup( de.GetTag().GetGroup() );
    }
  else // check consistency
    {
    assert( GetGroup() == de.GetTag().GetGroup() ); // programmer error
    }

  //std::cerr << "Tag: " << de.GetTag() << std::endl;
  if( de.GetTag().GetElement() == 0x0000 ) // OverlayGroupLength
    {
    // ??
    }
  else if( de.GetTag().GetElement() == 0x0010 ) // OverlayRows
    {
    Attribute<0x6000,0x0010> at;
    at.SetFromDataElement( de );
    SetRows( at.GetValue() );
    }
  else if( de.GetTag().GetElement() == 0x0011 ) // OverlayColumns
    {
    Attribute<0x6000,0x0011> at;
    at.SetFromDataElement( de );
    SetColumns( at.GetValue() );
    }
  else if( de.GetTag().GetElement() == 0x0015 ) // NumberOfFramesInOverlay
    {
    Attribute<0x6000,0x0015> at;
    at.SetFromDataElement( de );
    SetNumberOfFrames( at.GetValue() );
    }
  else if( de.GetTag().GetElement() == 0x0022 ) // OverlayDescription
    {
    SetDescription( s.c_str() );
    }
  else if( de.GetTag().GetElement() == 0x0040 ) // OverlayType
    {
    SetType( s.c_str() );
    }
  else if( de.GetTag().GetElement() == 0x0045 ) // OverlaySubtype
    {
    gdcmWarningMacro( "FIXME" );
    }
  else if( de.GetTag().GetElement() == 0x0050 ) // OverlayOrigin
    {
    Attribute<0x6000,0x0050> at;
    at.SetFromDataElement( de );
    SetOrigin( at.GetValues() );
    }
  else if( de.GetTag().GetElement() == 0x0051 ) // ImageFrameOrigin
    {
    Attribute<0x6000,0x0051> at;
    at.SetFromDataElement( de );
    SetFrameOrigin( at.GetValue() );
    }
  else if( de.GetTag().GetElement() == 0x0060 ) // OverlayCompressionCode (RET)
    {
    assert( s == "NONE" ); // FIXME ??
    }
  else if( de.GetTag().GetElement() == 0x0100 ) // OverlayBitsAllocated
    {
    Attribute<0x6000,0x0100> at;
    at.SetFromDataElement( de );
    if( at.GetValue() != 1 )
      {
      gdcmWarningMacro( "Unsuported OverlayBitsAllocated: " << at.GetValue() );
      }
    SetBitsAllocated( at.GetValue() );
    }
  else if( de.GetTag().GetElement() == 0x0102 ) // OverlayBitPosition
    {
    Attribute<0x6000,0x0102> at;
    at.SetFromDataElement( de );
    if( at.GetValue() != 0 ) // For old ACR when using unused bits...
      {
      gdcmWarningMacro( "Unsuported OverlayBitPosition: " << at.GetValue() );
      }
    SetBitPosition( at.GetValue() );
    }
  else if( de.GetTag().GetElement() == 0x0110 ) // OverlayFormat (RET)
    {
    assert( s == "RECT" );
    }
  else if( de.GetTag().GetElement() == 0x0200 ) // OverlayLocation (RET)
    {
    gdcmWarningMacro( "FIXME" );
    }
  else if( de.GetTag().GetElement() == 0x1301 ) // ROIArea
    {
    gdcmWarningMacro( "FIXME" );
    }
  else if( de.GetTag().GetElement() == 0x1302 ) // ROIMean
    {
    gdcmWarningMacro( "FIXME" );
    }
  else if( de.GetTag().GetElement() == 0x1303 ) // ROIStandardDeviation
    {
    gdcmWarningMacro( "FIXME" );
    }
  else if( de.GetTag().GetElement() == 0x1500 ) // OverlayLabel
    {
    gdcmWarningMacro( "FIXME" );
    }
  else if( de.GetTag().GetElement() == 0x3000 ) // OverlayData
    {
    SetOverlay(bv->GetPointer(), bv->GetLength());
    }
  else
    {
    gdcmErrorMacro( "Tag is not supported: " << de.GetTag() << std::endl );
    abort();
    }
}

void Overlay::SetGroup(unsigned short group) { Internal->Group = group; }
unsigned short Overlay::GetGroup() const { return Internal->Group; }

void Overlay::SetRows(unsigned short rows) { Internal->Rows = rows; }
unsigned short Overlay::GetRows() const { return Internal->Rows; }
void Overlay::SetColumns(unsigned short columns) { Internal->Columns = columns; }
unsigned short Overlay::GetColumns() const { return Internal->Columns; }
void Overlay::SetNumberOfFrames(unsigned int numberofframes) { Internal->NumberOfFrames = numberofframes; }
void Overlay::SetDescription(const char* description) { Internal->Description = description; }
void Overlay::SetType(const char* type) { Internal->Type = type; }
void Overlay::SetOrigin(const signed short *origin)
{
  Internal->Origin[0] = origin[0];
  Internal->Origin[1] = origin[1];
}
void Overlay::SetFrameOrigin(unsigned short frameorigin) { Internal->FrameOrigin = frameorigin; }
void Overlay::SetBitsAllocated(unsigned short bitsallocated) { Internal->BitsAllocated = bitsallocated; }
unsigned short Overlay::GetBitsAllocated() const { return Internal->BitsAllocated; }
void Overlay::SetBitPosition(unsigned short bitposition) { Internal->BitPosition = bitposition; }
unsigned short Overlay::GetBitPosition() const { return Internal->BitPosition; }

bool Overlay::IsEmpty() const
{
  return Internal->Data.empty();
}
bool Overlay::IsInPixelData() const { return Internal->InPixelData; }
void Overlay::IsInPixelData(bool b) { Internal->InPixelData = b; }

void Overlay::SetOverlay(const char *array, unsigned int length)
{
  if( !array || length == 0 ) return;
  //char * p = (char*)&Internal->Data[0];
  Internal->Data.resize( length ); // ??
  std::copy(array, array+length, Internal->Data.begin());
  assert( 8 * length == (unsigned int)Internal->Rows * Internal->Columns );
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
