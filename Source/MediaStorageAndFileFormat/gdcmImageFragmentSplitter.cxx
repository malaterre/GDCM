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
#include "gdcmImageFragmentSplitter.h"
#include "gdcmSequenceOfFragments.h"

namespace gdcm
{

bool ImageFragmentSplitter::Split()
{
  Output = Input;
  const Image &image = *Input;

  const unsigned int *dims = image.GetDimensions();
  if( dims[2] != 1 )
    {
    gdcmDebugMacro( "Cannot split a 3D image" );
    return false;
    }
  const DataElement& pixeldata = image.GetDataElement();

  const SequenceOfFragments *sqf = pixeldata.GetSequenceOfFragments();
  if( !sqf )
    {
    gdcmDebugMacro( "Cannot split a non-encapsulated syntax" );
    return false;
    }

  //assert( sqf->GetNumberOfFragments() == 1 );

  // WARNING do not keep the same Basic Offset Table...
  const Fragment& frag = sqf->GetFragment(0);
  const ByteValue *bv = frag.GetByteValue();
  const char *p = bv->GetPointer();
  unsigned long len = bv->GetLength();
  if( FragmentSizeMax > len && !Force )
    {
    // I think it is ok
    return true;
    }
  // prevent zero division
  if( FragmentSizeMax == 0 )
    {
    gdcmDebugMacro( "Need to set a real value for fragment size" );
    return false; // seriously...
    }
  unsigned long nfrags = len / FragmentSizeMax;
  unsigned long lastfrag = len % FragmentSizeMax;

  SmartPointer<SequenceOfFragments> sq = new SequenceOfFragments;
  // Let's do all complete frag:
  for(unsigned long i = 0; i < nfrags; ++i)
    {
    Fragment splitfrag;
    splitfrag.SetByteValue( p + i * FragmentSizeMax, FragmentSizeMax);
    sq->AddFragment( splitfrag );
    }
  // Last (incomplete one):
  if( lastfrag )
    {
    Fragment splitfrag;
    splitfrag.SetByteValue( p + nfrags * FragmentSizeMax, lastfrag );
    assert( nfrags * FragmentSizeMax + lastfrag == len );
    sq->AddFragment( splitfrag );
    }
  Output->GetDataElement().SetValue( *sq );

  bool success = true;
  return success;
}

void ImageFragmentSplitter::SetFragmentSizeMax(unsigned int fragsize)
{
  FragmentSizeMax = fragsize;
  if( fragsize % 2 )
    {
    // what is FragmentSizeMax == 0 ...
    FragmentSizeMax--;
    }
}

} // end namespace gdcm

