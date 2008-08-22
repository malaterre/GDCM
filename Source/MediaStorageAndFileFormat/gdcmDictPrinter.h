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
#ifndef __gdcmDictPrinter_h
#define __gdcmDictPrinter_h

#include "gdcmPrinter.h"

namespace gdcm
{

/**
 * \brief DictPrinter class
 */
// It's a sink there is no output
class GDCM_EXPORT DictPrinter : public Printer
{
public:
  DictPrinter();
  ~DictPrinter();

  void Print(std::ostream& os);

protected:
  void PrintDataElement2(std::ostream& os, const DataSet &ds, const DataElement &ide);
  void PrintDataSet2(std::ostream& os, const DataSet &ds);
};

} // end namespace gdcm

#endif //__gdcmDictPrinter_h
