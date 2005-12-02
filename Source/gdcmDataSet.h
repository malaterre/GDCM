
#ifndef __gdcmDataSet_h
#define __gdcmDataSet_h



#include "gdcmDataElement.h"
#include <map>

namespace gdcm
{
// This is needed in order to declare a friend of template class
template<class DEType>
class DataSet;
template<class DEType>
std::ostream& operator<<(std::ostream &_os, const DataSet<DEType> &_val);

// Data Set
template<class DEType> // DataElementType
/**
 * \brief Class to represent a Data Set (which contains Data Elements)
 * A Data Set represents an instance of a real world Information Object
 * \note bla
 */
class GDCM_EXPORT DataSet
{
public:
  DataSet() {}

  typedef typename std::map<Tag, DEType> ElementsMap;
  friend std::ostream& operator<< < >(std::ostream &_os, const DataSet<DEType> &_val);

  void AddDataElement(const DEType& de)
    {
    // FIXME warn if about to enter duplicate ?
#ifndef NDEBUG
    typename ElementsMap::const_iterator it = DataElements.find(de.GetTag());
    assert (it == DataElements.end());
#endif
    DataElements.insert(typename
      ElementsMap::value_type(de.GetTag(), de));
    }
  const DEType& GetDataElement(const Tag &t) const
    {
    typename ElementsMap::const_iterator it = DataElements.find(t);
    if (it == DataElements.end())
      {
      assert( 0 && "Impossible" );
      return GetDataElement(Tag(0,0));
      }
    return it->second;
    }

  bool IsEmpty() { return DataElements.empty(); }

private:
  ElementsMap DataElements;
};
//-----------------------------------------------------------------------------
template<class DEType>
inline std::ostream& operator<<(std::ostream &_os, const DataSet<DEType> &_val)
{
  typename DataSet<DEType>::ElementsMap::const_iterator it = _val.DataElements.begin();
  for(;
    it != _val.DataElements.end();
    ++it)
    {
    //const Tag &t = it->first;
    const DEType &de = it->second;
    _os << de << std::endl;
    }
  return _os;
}

} // end namespace gdcm

#endif //__gdcmDataSet_h
