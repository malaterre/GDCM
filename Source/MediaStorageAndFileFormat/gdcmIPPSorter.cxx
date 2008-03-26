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
#include "gdcmIPPSorter.h"
#include "gdcmScanner.h"
#include "gdcmElement.h"

#include <map>

namespace gdcm
{

IPPSorter::IPPSorter()
{
  ComputeZSpacing = false;
  ZSpacing = 0;
}


IPPSorter::~IPPSorter()
{
}


bool IPPSorter::Sort(std::vector<std::string> const & filenames)
{
  Scanner scanner;
  //scanner.SetFilenames( Filenames );
  //const Tag t1(0x0020,0x000d); // Study Instance UID
  //const Tag t2(0x0020,0x000e); // Series Instance UID
  //const Tag t3(0x0010,0x0010); // Patient's Name
  //const Tag t5(0x0028,0x0010); // Rows
  //const Tag t6(0x0028,0x0011); // Columns
  const Tag ipp(0x0020,0x0032); // Image Position (Patient)
  const Tag iop(0x0020,0x0037); // Image Orientation (Patient)
  // Temporal Position Identifier (0020,0100) 3 Temporal order of a dynamic or functional set of Images.
  const Tag tpi(0x0020,0x0100);
  scanner.AddTag( ipp );
  scanner.AddTag( iop );
  bool b = scanner.Scan( filenames );
  if( !b )
    {
    //std::cerr << "Scanner failed" << std::endl;
    return false;
    }
  const char *reference = filenames[0].c_str();
  Scanner::TagToValue const &t2v = scanner.GetMapping(reference);
  Scanner::TagToValue::const_iterator it = t2v.find( iop );
  // Take the first file in the list of filenames, if not IOP is found, simply gives up:
  if( it == t2v.end() )
    {
    //std::cerr << "No iop in: " << reference << std::endl;
    return false;
    }
  if( it->first != iop )
    {
    // first file does not contains Image Orientation (Patient), let's give up
    return false;
    }
  const char *dircos = it->second;
  std::stringstream ss;
  ss.str( dircos );
  Element<VR::DS,VM::VM6> cosines;
  cosines.Read( ss );

  // http://www.itk.org/pipermail/insight-users/2003-September/004762.html
  // Compute normal:
  // The steps I take when reconstructing a volume are these: First,
  // calculate the slice normal from IOP:
  double normal[3];
  normal[0] = cosines[1]*cosines[5] - cosines[2]*cosines[4];
  normal[1] = cosines[2]*cosines[3] - cosines[0]*cosines[5];
  normal[2] = cosines[0]*cosines[4] - cosines[1]*cosines[3];

  //std::cout << "normal:" << normal[0] << ",";
  //std::cout << normal[1] << ",";
  //std::cout << normal[2] << ",";
  //std::cout << std::endl;

  // You only have to do this once for all slices in the volume. Next, for
  // each slice, calculate the distance along the slice normal using the IPP
  // tag ("dist" is initialized to zero before reading the first slice) :
  //typedef std::multimap<double, const char*> SortedFilenames;
  typedef std::map<double, const char*> SortedFilenames;
  SortedFilenames sorted;
{
  std::vector<std::string>::const_iterator it = filenames.begin();
  for(; it != filenames.end(); ++it)
    {
    const char *filename = it->c_str();
    const char *value =  scanner.GetValue(filename, ipp);
    if( value )
      {
      //std::cout << filename << " has " << ipp << " = " << value << std::endl;
      Element<VR::DS,VM::VM3> ipp;
      std::stringstream ss;
      ss.str( value );
      ipp.Read( ss );
      double dist = 0;
      for (int i = 0; i < 3; ++i) dist += normal[i]*ipp[i];
      // FIXME: This test is weak, since implicitely we are doing a != on floating point value
      if( sorted.find(dist) != sorted.end() )
        {
        std::cerr << "dist: " << dist << " already found" << std::endl;
        return false;
        }
      sorted.insert(
            SortedFilenames::value_type(dist,filename) );
      }
    else
      {
      abort();
      }
    }
}
{
  SortedFilenames::const_iterator it = sorted.begin();
  Filenames.clear();
  for( ; it != sorted.end(); ++it)
    {
    //std::cout << it->first << " " << it->second << std::endl;
    Filenames.push_back( it->second );
    }
}

  return true;
}


} // end namespace gdcm
