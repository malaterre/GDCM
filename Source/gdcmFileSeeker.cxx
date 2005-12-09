#include "gdcmFileSeeker.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmIStream.h"
#include <errno.h>

namespace gdcm
{

// Take advantage of the group length
template<class DEType>
bool SkipGroup(FileSeeker &is)
{
  DEType de;
  gdcm::DataElement &de_tag = de;

  std::streampos offset = is.Tellg();
  std::streampos last_offset = offset; // last valid offset to do seek back
  is >> de_tag;
  while( !is.eof() )
    {
    uint16_t current_group = de_tag.GetTag().GetGroup();
    is.AddOffset(current_group, offset);
    //std::cerr << "Group: " << std::hex << current_group << " " << offset << std::endl;
    uint16_t current_element = de_tag.GetTag().GetElement();
    if( current_element == 0x0 )
      {
      // Great let's use the length
      is >> de;
      uint32_t length;
      if( de.GetValue().GetLength() == 4)
        memcpy(&length, de.GetValue().GetPointer(), 4);
      else
        {
        uint16_t l;
        memcpy(&l, de.GetValue().GetPointer(), 2);
        length = l;
        }
      // Indeed group length is zero sometime 
      // e.g. MARCONI_MxTWin-12-MONO2-JpegLossless-ZeroLengthSQ.dcm
      assert( length );
      //std::cout << "Debug Length: " << std::dec << length << std::endl;
      is.Seekg( length, std::ios::cur );
      last_offset = offset;
      offset = is.Tellg();
      is >> de_tag;
      if( is.eof() ) break;
      if( de_tag.GetTag().GetGroup() <= current_group 
        || de_tag.GetTag().GetElement() != 0x0 )
        {
        // Something went wrong (lenght is probably wrong)
        // First thing seek back to last know valid position
        is.Seekg(last_offset, std::ios::beg);
        std::cerr << "Group length seems to be wrong" << std::endl;
        return false;
        }
      }
    else
      {
      // I gave up on writting a partial skip and seek method due to the image:
      // MARCONI_MxTWin-12-MONO2-JpegLossless-ZeroLengthSQ.dcm
      is.Seekg(last_offset, std::ios::beg);
      std::cerr << "No group length found, fallback to seeking file instead" << std::endl;
      return false;
      }
    }
  return true;
}

// fallback method is SkipGroup did not work (slower)
template<class DEType>
bool SeekGroup(FileSeeker &is)
{
  DEType de;
  gdcm::DataElement &de_tag = de;

  uint16_t last_group = 0x0;
  while( !is.eof() && is >> de_tag )
    {
    std::streampos offset = is.Tellg();
    offset -= de_tag.GetLength();
    is >> de;
    //std::cout << "DE : " << de << std::endl;
    uint16_t current_group = de_tag.GetTag().GetGroup();
    if( current_group != last_group )
      {
      is.AddOffset(current_group, offset);
      std::cerr << "Group: " << std::hex << current_group << " " << offset << std::endl;
      last_group = current_group;
      }
    }
  return true;
}

template<class DEType>
void BrowseDataElements(FileSeeker &is)
{
  if( !SkipGroup<DEType>(is))
    {
    if( !SeekGroup<DEType>(is))
      {
      abort(); // ooooops
      }
    }
}

void FileSeeker::Initialize()
{
  DICOMIStream::Initialize();
  Offsets.clear(); // Cleanup

  if( NegociatedTS == Explicit )
    {
    BrowseDataElements<gdcm::ExplicitDataElement>(*this);
    }
  else
    {
    BrowseDataElements<gdcm::ImplicitDataElement>(*this);
    }
  // FIXME a file that reach eof is not valid...
  Close();
  Open();
//  assert( Tellg() != (std::streamoff)-1);
}

template<class DEType>
bool SeekElements(DICOMIStream &is, const Tag& tag)
{
  DEType de;
  DataElement &de_tag = de;
  bool success = false;
  while(!is.eof() && is >> de_tag)
    {
    if( de_tag.GetTag().GetGroup() != tag.GetGroup() )
      break;
    if( de_tag.GetTag().GetElement() > tag.GetElement() )
      break;
    assert( de_tag.GetTag().GetGroup() == tag.GetGroup() );
    assert( de_tag.GetTag().GetElement() <= tag.GetElement() ); // redundant ??
    if( de_tag.GetTag() != tag )
      is >> de; // FIXME is.Skip(de);
    else
      {
      success = true;
      break;
      }
    }
  return success;
}

template<class DEType>
void ReadElements(DICOMIStream &is, DEType& de)
{
  const Tag tag = de.GetTag(); // Save the tag to search
  DataElement &de_tag = de;
  while(!is.eof() && is >> de_tag)
    {
    //std::cerr << "Reading: " << de_tag << std::endl;
    if( de_tag.GetTag().GetGroup() != tag.GetGroup() )
      break;
    if( de_tag.GetTag().GetElement() > tag.GetElement() )
      break;
    assert( de_tag.GetTag().GetGroup() == tag.GetGroup() );
    assert( de_tag.GetTag().GetElement() <= tag.GetElement() ); // redundant ??
    if( de_tag.GetTag() != tag )
      {
      is >> de; // FIXME de.Skip(is);
      }
    else
      {
      is >> de;
      break;
      }
    }
}

bool FileSeeker::FindTag(const Tag& tag)
{
  uint16_t group = tag.GetGroup();
  SeekTo(group);
  if( NegociatedTS == Explicit )
    {
    return SeekElements<gdcm::ExplicitDataElement>(*this, tag);
    }
  else
    {
    return SeekElements<gdcm::ImplicitDataElement>(*this, tag);
    }
}

const char *FileSeeker::GetTagAsRaw(const Tag& tag)
{
  static char buffer[512];
  uint16_t group = tag.GetGroup();
  SeekTo(group);
  if( NegociatedTS == Explicit )
    {
    ExplicitDataElement de;
    de.SetTag(tag);
    ReadElements<ExplicitDataElement>(*this, de);
    assert( de.GetValue().GetLength() < 512 );
    memcpy(buffer, de.GetValue().GetPointer(), de.GetValue().GetLength() );
    }
  else
    {
    ImplicitDataElement de;
    de.SetTag(tag);
    ReadElements<ImplicitDataElement>(*this, de);
    assert( de.GetValue().GetLength() < 512 );
    memcpy(buffer, de.GetValue().GetPointer(), de.GetValue().GetLength() );
    }
  return buffer;
}

void FileSeeker::SeekTo(uint16_t group)
{
  GroupOffsets::const_iterator it = Offsets.find(group);
  if( it != Offsets.end() )
    Seekg(Offsets[group], std::ios::beg);
  else
    {
    // This is quite expensive...
    Seekg(0, std::ios::beg);
    if(!ReadDICM())
      IStream::Seekg(0, std::ios::beg);
    }
}

}
