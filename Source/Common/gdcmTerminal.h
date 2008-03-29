/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmTerminal_h
#define __gdcmTerminal_h

#include "gdcmTypes.h"


namespace gdcm
{
/*
 * \brief Class for Terminal
 */
//-----------------------------------------------------------------------------
#if 0
class GDCM_EXPORT Terminal
{
public :
  Terminal() {}
  ~Terminal() {}

  typedef enum {
    Black = 0,
    Red = 1
  } ColorType;

  void ColorPrint(FILE * file, ColorType color, const char *str) const;
  void ColorPrint(std::ostream & file, ColorType color, const char *str) const;

protected:
  bool Setup(FILE *file);
  bool Setup(std::ostream &os);
};
#endif

namespace terminal
{
  typedef enum
  {
    VT100 = 0,
    CONSOLE
  } Type;
  typedef enum
  {
    black = 0,
    red,
    green,
    yellow, // brown ??
    blue,
    magenta,
    cyan,
    white
  } Color;
  typedef enum
  {
  reset = 0,
  bright, // Bold
  dim,
  underline,
  blink,
  reverse,
  hidden,
  } Attribute;
  GDCM_EXPORT std::string setattribute( Attribute att );
  GDCM_EXPORT std::string setfgcolor( Color c );
  GDCM_EXPORT std::string setbgcolor( Color c );
}

} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmTerminal_h
