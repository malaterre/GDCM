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
#ifndef __gdcmImageReader_h
#define __gdcmImageReader_h

#include "gdcmReader.h"
#include "gdcmImage.h"

namespace gdcm
{

class ByteValue;
class MediaStorage;
/**
 * \brief ImageReader
 * \note its role is to convert the DICOM DataSet into a gdcm::Image
 * representation
 * By default it is also loading the lookup table and overlay when found as they impact the rendering or the image
 * \todo
 * old gdcm 1.X used to have in its dictionary:
 *
 * - 0028 0015 US 1 UsedNbX ACR Special (RET)
 * - 0028 0016 US 1 UsedNbY ACR Special (RET)
 * - 0028 0017 US 1 UsedNbZ ACR Special (RET)
 * - 0028 0018 US 1 UsedNbT ACR Special (RET)
 *
 * since I cannot find them *anywhere* I'll have to hard code them directly in a specific libido image reader
 * 
 */
class GDCM_EXPORT ImageReader : public Reader
{
public:
  ImageReader();
  ~ImageReader();

  /// Read the DICOM image. There are two reason for failure:
  /// 1. The input filename is not DICOM
  /// 2. The input DICOM file does not contains an Image
  bool Read();

  // Following methods are valid only after a call to 'Read'

  /// Return the read image
  const Image& GetImage() const;
  Image& GetImage();
  //void SetImage(Image const &img);

protected:
  const ByteValue* GetPointerFromElement(Tag const &tag) const;
  bool ReadImage(MediaStorage const &ms);
  bool ReadACRNEMAImage();
  
  // ugliest thing ever:
  signed short ReadSSFromTag( Tag const &t, std::stringstream &ss,
    std::string &conversion );
  unsigned short ReadUSFromTag( Tag const &t, std::stringstream &ss,
    std::string &conversion );
  int ReadISFromTag( Tag const &t, std::stringstream &ss,
    std::string &conversion );

private:
  SmartPointer<Image> PixelData;
};

} // end namespace gdcm

#endif //__gdcmImageReader_h

