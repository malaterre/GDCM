
#ifndef __gdcmString_h
#define __gdcmString_h

#include "gdcmType.h"
#include <string>
#include <iostream>

namespace gdcm
{

/** \class String
 * \brief Short-name version of the STL basic_string class template.
 *
 * The standard library "std::string" type is actually a typedef for
 * "std::basic_string<..long argument list..>".  This string class is
 * simply a subclass of this type with the same interface so that the
 * name is shorter in debugging symbols and error messages.
 */
class GDCM_EXPORT String : public std::string
{
public:

  /** String member types.  */
  typedef std::string::value_type             value_type;
  typedef std::string::pointer                pointer;
  typedef std::string::reference              reference;
  typedef std::string::const_reference        const_reference;
  typedef std::string::size_type              size_type;
  typedef std::string::difference_type        difference_type;
  typedef std::string::iterator               iterator;
  typedef std::string::const_iterator         const_iterator;
  typedef std::string::reverse_iterator       reverse_iterator;
  typedef std::string::const_reverse_iterator const_reverse_iterator;
  //friend std::ostream& operator<<(std::ostream &_os, const String &_val);

  /** String constructors.  */
  String(): std::string() {}
  String(const value_type* s): std::string(s) {}
  String(const value_type* s, size_type n): std::string(s, n) {}
  String(const std::string& s, size_type pos=0, size_type n=npos):
    std::string(s, pos, n) {}
};

inline std::istream& operator>>(std::istream &_is, String& _s)
{
  assert( _is.good() );
  char buffer[2048]; //FIXME, buffer overflow ?
  if( _is )
    {
    _is.get(buffer, 2048, '\\'); //getline extract the separator character
    std::string &_ss = _s;
    _ss = buffer;
    }
  //assert( _is.good() );
  return _is;
}

} // end namespace gdcm

#endif
