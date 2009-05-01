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
#ifndef __gdcmPixmapWriter_h
#define __gdcmPixmapWriter_h

#include "gdcmWriter.h"
#include "gdcmPixmap.h"

namespace gdcm
{

class Pixmap;
/**
 * \brief PixmapWriter
 */
class GDCM_EXPORT PixmapWriter : public Writer
{
public:
  PixmapWriter();
  ~PixmapWriter();

  const Pixmap& GetPixmap() const { return *PixelData; }
  Pixmap& GetPixmap() { return *PixelData; } // FIXME 
  void SetPixmap(Pixmap const &img);

  /// Set/Get Pixmap to be written
  /// It will overwrite anything Pixmap infos found in DataSet
  /// (see parent class to see how to pass dataset)
  virtual const Pixmap& GetImage() const { return *PixelData; }
  virtual Pixmap& GetImage() { return *PixelData; } // FIXME 
  virtual void SetImage(Pixmap const &img);

  /// Write
  bool Write(); // Execute()

protected:
  void DoIconImage(DataSet & ds, Pixmap const & image);
  bool PrepareWrite();

  SmartPointer<Pixmap> PixelData;
};

} // end namespace gdcm

#endif //__gdcmPixmapWriter_h
