/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmExplicitImplicitDataElement_txx
#define __gdcmExplicitImplicitDataElement_txx

#include "gdcmSequenceOfItems.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmVL.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"

#include "gdcmValueIO.h"
#include "gdcmSwapper.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
template <typename TSwap>
std::istream &ExplicitImplicitDataElement::Read(std::istream &is)
{
  DataElement &de = *this;
  try
    {
    de.Read<ExplicitDataElement,TSwap>( is );
    }
  catch(ParseException &ex)
    {
    is.seekg( -6, std::ios::cur );
    de.Read<ImplicitDataElement,TSwap>( is );
    }
  return is;
}


} // end namespace gdcm

#endif // __gdcmExplicitImplicitDataElement_txx
