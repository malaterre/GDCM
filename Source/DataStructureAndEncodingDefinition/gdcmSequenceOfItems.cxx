#include "gdcmSequenceOfItems.h"

namespace gdcm
{
IStream &SequenceOfItems::Read(IStream &is)
{
//  ItemVector::iterator it = Items.begin();
//  for(;it != Items.end(); ++it)
//    {
//    it->Read(is);
//    }
  if( SequenceLengthField.IsUndefined() )
    {
    Item item;
    const Tag seqDelItem(0xfffe,0xe0dd);
    do
      {
      item.Read(is);
      std::cout << "Item: " << item << std::endl;
      Items.push_back( item );
      }
    while( item.GetTag() != seqDelItem );
    }
  else
    {
    abort();
    }
  return is;
}

OStream const & SequenceOfItems::Write(OStream &os) const
{
  ItemVector::const_iterator it = Items.begin();
  for(;it != Items.end(); ++it)
    {
    it->Write(os);
    }
  return os;
}

} // end namespace gdcm
