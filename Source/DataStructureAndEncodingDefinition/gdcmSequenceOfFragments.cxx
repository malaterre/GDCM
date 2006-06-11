#include "gdcmSequenceOfFragments.h"
//#include "gdcmFragment.h"

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
    do
      {
      frag.Read(is);
      //std::cout << "Frag: " << frag << std::endl;
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
  FragmentVector::const_iterator it = Fragments.begin();
  for(;it != Fragments.end(); ++it)
    {
    it->Write(os);
    }
  return os;
}

} // end namespace gdcm
