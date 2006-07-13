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
#include "gdcmSequenceOfFragments.h"
#include "gdcmImplicitDataElement.h"

namespace gdcm
{

IStream& SequenceOfFragments::Read(IStream &is)
{
  //FragmentVector::iterator it = Fragments.begin();
  //for(;it != Fragments.end(); ++it)
  //  {
  //  it->Read(is);
  //  std::cout << *it << std::endl;
  //  }
  if( SequenceLengthField.IsUndefined() )
    {
    Fragment frag;
    const Tag seqDelItem(0xfffe,0xe0dd);
    // First item is the basic offset table:
    Table.Read(is);
    gdcmDebugMacro( "Table: " << frag );
    // not used for now...
    do
      {
      frag.Read(is);
      gdcmDebugMacro( "Frag: " << frag );
      Fragments.push_back( frag );
      }
    while( frag.GetTag() != seqDelItem );
    assert( frag.GetVL() == 0 );
    }
  else
    {
    abort();
    }
  return is;
}

OStream const & SequenceOfFragments::Write(OStream &os) const
{
  if( !Table.Write(os) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  FragmentVector::const_iterator it = Fragments.begin();
  for(;it != Fragments.end(); ++it)
    {
    it->Write(os);
    }
  return os;
}

unsigned long SequenceOfFragments::ComputeLength() const
{
  unsigned long r = 0;
  FragmentVector::const_iterator it = Fragments.begin();
  for(;it != Fragments.end(); ++it)
    {
    r += it->GetVL();
    }
  return r;
}

bool SequenceOfFragments::GetBuffer(char *buffer, unsigned long length) const
{
  FragmentVector::const_iterator it = Fragments.begin();
  unsigned long total = 0;
  for(;it != Fragments.end(); ++it)
    {
    const Fragment &frag = *it;
    const ByteValue &bv = dynamic_cast<const ByteValue&>(frag.GetValue());
    const VL len = frag.GetVL();
    bv.GetBuffer(buffer, len);
    buffer += len;
    total += len;
    }
  (void)length;
  //std::cerr << " DEBUG: " << total << " " << length << std::endl;
  return true;
}

} // end namespace gdcm
