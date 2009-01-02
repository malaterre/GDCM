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
/* 
 */
#include "gdcmSorter.h"
#include "gdcmDataSet.h"
#include "gdcmAttribute.h"


bool mysort(gdcm::DataSet const & ds1, gdcm::DataSet const & ds2 )
{
  gdcm::Attribute<0x0020,0x0013> at1;
  at1.SetFromDataElement( ds1.GetDataElement( at1.GetTag() ) );
  gdcm::Attribute<0x0020,0x0013> at2;
  at2.SetFromDataElement( ds2.GetDataElement( at2.GetTag() ) );
  return at1 < at2;
}

int main(int argc, char *argv[])
{
  const char *dirname = argv[1];
  gdcm::Directory dir;
  dir.Load( dirname );

  dir.Print( std::cout );
  
  gdcm::Sorter sorter;
  sorter.SetSortFunction( mysort );
  sorter.Sort( dir.GetFilenames() );

  std::cout << "Sorter:" << std::endl;
  sorter.Print( std::cout );

  return 0;
}
