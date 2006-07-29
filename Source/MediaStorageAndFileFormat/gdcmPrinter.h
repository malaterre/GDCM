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
#ifndef __gdcmPrinter_h
#define __gdcmPrinter_h

// TODO Class to implement printing
// Since DICOM does printing ?
// Also I would like to encapsulate the IsCharacterPrintable thing 
// (to avoid printing \0 and other weird characters)
// \todo I still need to implement skiping of group (shadow)
// need to implement longer field to read

#include "gdcmDataSet.h"

namespace gdcm
{

// It's a sink there is no output
class GDCM_EXPORT Printer
{
public:
  Printer();
  ~Printer();

  // Set the input dataset to the printer
  void SetDataSet(DataSet const &ds) {
    DS = const_cast<DataSet*>(&ds);
  }
  DataSet const &GetDataSet() const {
    return *DS;
  }
  typedef enum {
    VERBOSE_STYLE = 0, // GDCM Legacy VERBOSE one
    CONDENSED_STYLE,         //
    // Ok I am missing voc here ...better naming would be nice
    XML // sure why not
  } PrintStyles;

  void SetStyle(PrintStyles ps) {
    PrintStyle = ps;
  }
  PrintStyles GetPrintStyle() const {
    return PrintStyle;
    }

  void Print(std::ostream& os);

private:
  PrintStyles PrintStyle;
  DataSet *DS;
};

} // end namespace gdcm

#endif //__gdcmPrinter_h
