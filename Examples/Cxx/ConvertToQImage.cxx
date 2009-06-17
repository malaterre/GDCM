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
/* 
 * This example shows how to setup the pipeline from a gdcm::ImageReader into a
 * Qt QImage data structure.
 * It only handles 2D image.
 * 
 * Ref:
 * http://doc.trolltech.com/4.5/qimage.html
 *
 * Usage:
 *  ConvertToQImage gdcmData/012345.002.050.dcm

 * Thanks:
 *   Sylvain ADAM (sylvain51 hotmail com) for contributing this example
 */

#include "gdcmImageReader.h"
#include <QImage>

int main(int, char *[])
{

  gdcm::ImageReader ir;
  ir.SetFileName("wedges.ima");

  if(!ir.Read())
    {
    //Read failed
    }

  std::cout<<"Getting image from ImageReader..."<<std::endl;

  gdcm::Image &gimage = ir.GetImage();

  const unsigned int* dimension = gimage.GetDimensions();

  int dimX = int(dimension[0]);
  int dimY = int(dimension[1]);

  //This buffer has been declared elsewhere
  char *buffer = new char[gimage.GetBufferLength()];

  gimage.GetBuffer(buffer);

  //Let's now convert each 16-bits pixel to a 8-bits pixel, leveled to the maximum intensity value of the image
  //Because the image is a 16-bits grayscale, we thus have 65536 available values to store the gray value.
  // BUT, usually, the value doesn't oversize around 2000~2200. So if we directly convert the 16-bits to 8-bits (from max. 65536 to max255)
  // and try to display it, we will have very dark images. Then, we will level all the intensities to the maximum intensity value.
  //We are gonna use a RGB888 format for Qt display. In a grayscale image, R=G=B = the gray value.
  //The buffer length, in char, will thus be: 256*256*3 (if the image is 256x256) = 196608 chars.

  unsigned short *buffer16 = new unsigned short [dimX*dimY];
  unsigned short maxValue = 0;

  for(unsigned int i = 0; i < gimage.GetBufferLength(); i+=2)
    {
    //@todo: think about #typedef to avoid these long conversions lines.
    //Bitwise left shift and bitwise OR
    unsigned short pixel16bitValue = ((((unsigned short ) ((unsigned char) buffer [i+1]))<<8)|(unsigned char) buffer [i]);

    buffer16[i/2] = pixel16bitValue;
    if(pixel16bitValue > maxValue)
      {
      maxValue = pixel16bitValue;
      }
    }

  unsigned char *buffer888 = new unsigned char[dimX*dimY*3];

  for(int i = 0; i < dimX*dimY; i++)
    {
    unsigned char pixel8bitValue = (unsigned char) (buffer16[i]*255/maxValue);
    buffer888[i*3] = pixel8bitValue;
    buffer888[i*3+1] = pixel8bitValue;
    buffer888[i*3+2] = pixel8bitValue;
    }

  QImage *imageQt = new QImage(buffer888, dimX, dimY, QImage::Format_RGB888);

  //The DICOM image is a 16-bits image
  //For a 256x256 image, it's 256x256 = 65536 pixels.
  //So, normally in a char* (1 char = 1 byte = 1 bit), it does have a length of 65536
  //BUT as it's a 16-bits image (2*8-bits), we thus have 131072 chars
  // ============================================================================
  return 0;
}
