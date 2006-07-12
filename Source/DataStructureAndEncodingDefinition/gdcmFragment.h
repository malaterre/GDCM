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

#ifndef __gdcmFragment_h
#define __gdcmFragment_h

#include "gdcmDataElement.h"
#include "gdcmByteValue.h"

namespace gdcm
{
/**
 * \brief Class to represent an Fragment
 */

class GDCM_EXPORT Fragment : public DataElement
{
public:
  Fragment(const Tag &t = Tag(0), uint32_t const &vl = 0) : DataElement(t, vl) {}
  friend std::ostream &operator<<(std::ostream &os, const Fragment &val);

  void Clear() {
    FragmentValue.Clear();
    }

  Fragment(const Fragment &val):DataElement(val)
    {
    FragmentValue = val.FragmentValue;
    }
  Fragment &operator=(Fragment const &val)
    {
    FragmentValue = val.FragmentValue;
    return *this;
    }

  IStream &Read(IStream &is)
    {
    // Superclass
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !TagField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    if( TagField != itemStart && TagField != seqDelItem )
      {
      // gdcm-JPEG-LossLess3a.dcm
      std::streampos pos = is.Tellg();
      is.Seekg( 0, std::ios::end );
      std::streampos end = is.Tellg();
      gdcmWarningMacro( "Broken file: " << (long)(end-pos) 
        << " bytes were skipped at the end of file. Use at own risk." );
      // Pretend to end properly...
      TagField = Tag(0xfffe,0xe0dd);
      ValueLengthField = 0;
      return is;
      }
    if( !ValueLengthField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    // Self
    FragmentValue.SetLength(ValueLengthField);
    if( !FragmentValue.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    return is;
    }

  OStream &Write(OStream &os) const {
    abort();
    return os;
    }

  Value const &GetValue() const {
    return FragmentValue;
  }

private:
  ByteValue FragmentValue;
};
//-----------------------------------------------------------------------------
inline std::ostream &operator<<(std::ostream &os, const Fragment &val)
{
  os << "Tag: " << val.TagField;
  os << "\tVL: " << val.ValueLengthField;
  os << "\t" << val.FragmentValue;

  return os;
}


} // end namespace gdcm

#endif //__gdcmFragment_h
