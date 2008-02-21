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
#include "gdcmStringFilter.h"
#include "gdcmReader.h"
#include "gdcmSequenceOfItems.h"

#include "gdcmDataImages.h"

int TestStringFilt(const char *filename)
{
  gdcm::StringFilter sf;
  gdcm::Reader r;
  r.SetFileName( filename );
  if( !r.Read() )
    {
    return 1;
    }
  gdcm::DataSet const& ds = r.GetFile().GetDataSet();
  
  int ret = 0;
  gdcm::DataSet::ConstIterator it = ds.Begin();
  for( ; it != ds.End(); ++it)
    {
    const gdcm::DataElement &ref = *it;
    std::pair<std::string, std::string> s = sf.ToStringPair( ref );
    if( !s.second.empty() || ref.GetVL() == 0 )
      {
      std::cout << s.first << " -> " << s.second << std::endl;
      }
    else if( !ref.GetByteValue() ) // It means it's a SQ
      {
      std::cout << "SQ:" << ref.GetTag() << std::endl;
      }
    else if( ref.GetTag().IsPrivate() )
      {
      std::cout << "Private:" << ref.GetTag() << std::endl;
      }
    else
      {
      std::cerr << "Not supported: " << ref << std::endl;
      //ret += 1;
      }
    }

  return ret;
}

int TestStringFilter(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestStringFilt(filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    r += TestStringFilt( filename );
    ++i;
    }

  return r;
}

