/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __gdcmImageReader_h
#define __gdcmImageReader_h

#include "gdcmReader.h"
#include "gdcmImageValue.h"

namespace gdcm
{
/**
 * \brief ImageReader
 * \note its role is to convert the DICOM DataSet into a gdcm::Image
 * representation
 */
class ByteValue;
class GDCM_EXPORT ImageReader : public Reader
{
public:
  ImageReader();
  ~ImageReader();

  const Image& GetImage() const;
  //void SetImage(Image const &img);

  bool Read();

protected:
  const ByteValue* GetPointerFromElement(Tag const &tag) const;
  bool ReadImage();
  bool ReadACRNEMAImage();
  
  // ugliest thing ever:
  signed short ReadSSFromTag( Tag const &t, std::stringstream &ss,
    std::string &conversion );
  unsigned short ReadUSFromTag( Tag const &t, std::stringstream &ss,
    std::string &conversion );
  int ReadISFromTag( Tag const &t, std::stringstream &ss,
    std::string &conversion );

private:
  ImageValue PixelData;
};

} // end namespace gdcm

#endif //__gdcmImageReader_h

