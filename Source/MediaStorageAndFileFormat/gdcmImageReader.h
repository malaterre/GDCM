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
#ifndef __gdcmImageReader_h
#define __gdcmImageReader_h

#include "gdcmReader.h"
#include "gdcmImageValue.h"
#include "gdcmOverlay.h"

namespace gdcm
{
/**
 * \brief ImageReader
 * \note its role is to convert the DICOM DataSet into a gdcm::Image
 * representation
 * By default it is also loading the lookup table and overlay when found as they impact the rendering or the image
 */
class ByteValue;
class GDCM_EXPORT ImageReader : public Reader
{
public:
  ImageReader();
  ~ImageReader();

  const Image& GetImage() const;
  //void SetImage(Image const &img);
  const Overlay& GetOverlay(unsigned int i = 0) const { 
    assert( i < Overlays.size() );
    return Overlays[i]; 
  }

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
  std::vector<Overlay>  Overlays;
};

} // end namespace gdcm

#endif //__gdcmImageReader_h

