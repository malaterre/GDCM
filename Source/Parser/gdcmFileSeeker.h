#ifndef __gdcmFileSeeker_h
#define __gdcmFileSeeker_h

#include "gdcmDICOMIStream.h"
#include <map>
#include <fstream>

namespace gdcm
{
/**
 * \brief FileSeeker is a class meant to quickly access a sub set of information
 * There is a few chance that this class can be used on network, since it built
 * an array of offset to quickly search through the group (eventually sequence)
 *
 * \note bla
 */
class GDCM_EXPORT FileSeeker : public DICOMIStream
{
public:
  typedef std::map<uint16_t, std::streampos> GroupOffsets;
  void Initialize();

  // Check if Tag exist
  bool FindTag(const Tag& tag);

  // 
  //void GetTag(const Tag& tag);
  const char *GetTagAsRaw(const Tag& tag);

  void AddOffset(uint16_t group, std::streampos pos) { 
#ifndef NDEBUG
    // Check that for new group the offset is always different and bigger
    GroupOffsets::const_iterator it = Offsets.begin();
    for(;
      it != Offsets.end();
      ++it)
      {
      if( it->first != group ) assert( it->second < pos );
      }
#endif
    Offsets.insert( GroupOffsets::value_type(group, pos) ); }

  unsigned int GetNumberOfOffset() { return Offsets.size(); }
  std::streampos GetOffset(uint16_t group_number)
    {
    return Offsets[group_number];
    }
  std::streampos GetOffsetByNumber(unsigned int num)
    {
    GroupOffsets::const_iterator it = Offsets.begin();
    for(unsigned int i=0; i<num; ++i) it++;
    return it->second;
    }

protected:
  void SeekTo(uint16_t group_number);

private:
  // map from group number -> offset
  GroupOffsets Offsets;
};

} // end namespace gdcm
#endif //__gdcmFileSeeker_h
