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
#ifndef __gdcmTagPath_h
#define __gdcmTagPath_h

#include "gdcmTag.h"

#include <vector>

namespace gdcm
{
  
/**
 * \brief class to handle a path of tag.
 *
 * Any Resemblance to Existing XPath is Purely Coincidental
 */
class GDCM_EXPORT TagPath
{
public:
  TagPath();
  ~TagPath();
  void Print(std::ostream &) const;

  /// "/0018,0018/"...
  /// No space allowed, comma is use to separate tag group
  /// from tag element and slash is used to separate tag
  /// throw an error if invalid
  void ConstructFromString(const char *path);

  /// Return if path is valid or not
  static bool IsValid(const char *path);

  /// Construct from a list of tags
  void ConstructFromTagList(Tag const *l, unsigned int n);

  void Push(Tag const & t);
  void Push(unsigned int itemnum);

private:
  std::vector<Tag> Path;
};

} // end namespace gdcm

#endif //__gdcmTagPath_h
