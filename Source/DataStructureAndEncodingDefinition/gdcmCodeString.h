/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMCODESTRING_H
#define GDCMCODESTRING_H

#include "gdcmString.h"

namespace gdcm
{

/**
 * \brief CodeString
 *
 * \note TODO
 */
class GDCM_EXPORT CodeString : public String<'\\',16> /* PLEASE do not export me */
{
public:
  // typedef are not inherited:
  typedef String<'\\',16> Superclass;
  typedef Superclass::value_type             value_type;
  typedef Superclass::pointer                pointer;
  typedef Superclass::reference              reference;
  typedef Superclass::const_reference        const_reference;
  typedef Superclass::size_type              size_type;
  typedef Superclass::difference_type        difference_type;
  typedef Superclass::iterator               iterator;
  typedef Superclass::const_iterator         const_iterator;
  typedef Superclass::reverse_iterator       reverse_iterator;
  typedef Superclass::const_reverse_iterator const_reverse_iterator;

  // CodeString constructors.
  CodeString(): Superclass() {}
  CodeString(const value_type* s): Superclass(s) {}
  CodeString(const value_type* s, size_type n): Superclass(s, n) {}
  CodeString(const Superclass& s, size_type pos=0, size_type n=npos):
    Superclass(s, pos, n) {}

  bool IsValid() const;
};

} // end namespace gdcm

#endif //GDCMCODESTRING_H

