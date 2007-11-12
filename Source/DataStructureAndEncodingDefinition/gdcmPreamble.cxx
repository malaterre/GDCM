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
#include "gdcmPreamble.h"

namespace gdcm
{

Preamble::~Preamble()
{
  delete[] Internal;
}

std::istream &Preamble::Read(std::istream &is)
{
  // \precondition: we are at beg of Preamble
  bool r = false;
  //assert ( IsEmpty() /*&& is.tellg() == 0*/ );
  Internal = new char[128+4];
  is.read(Internal, 128+4);
  if( Internal[128+0] == 'D'
   && Internal[128+1] == 'I'
   && Internal[128+2] == 'C'
   && Internal[128+3] == 'M')
    {
    r = true;
    }
  if(!r)
    {
    gdcmDebugMacro( "Not a DICOM V3 file (No Preamble)" );
    delete[] Internal;
    Internal = 0;
    // Seek back
    is.seekg(0, std::ios::beg);
    }

  // \postcondition we are after the Preamble (or at beg of file if none)
  return is;
}

// \precondition we are at the beginning of file
std::ostream const &Preamble::Write(std::ostream &os) const
{
//  assert ( os.tellg()+0 == 0 );
  if( IsEmpty() )
    {
//    char dicm[128];
//    memset( dicm, 0, 128 );
//    os.write( dicm, 128);
//    os.write( "DICM" , 4);
    }
  else if( IsValid() )
  {
    os.write( Internal, 128+4);
  }
  else
  {
	  abort();
  }

  // \postcondition a valid Preamble has been written to stream
  return os;
}

} // end namespace gdcm 

