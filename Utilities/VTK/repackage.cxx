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

#include <iostream>
#include <fstream>

bool ProcessOneFile(const char *filename )
{
  std::cout << filename << std::endl;
  std::filebuf fbuf;
  fbuf.open( filename ,std::ios::in | std::ios::out);
  std::istream in(&fbuf);
  std::ostream out(&fbuf);

  if( !in || !out ) 
    {
    std::cerr << "canot find file" << std::endl;
    return false;
    }
  std::string line;
  while(std::getline(in, line))
    {
    if( line == "package vtk;" )
      {
      std::cout << "Found !" << std::endl;
      const char vtkgdcm[] = "\npackage vtkgdcm;\n";
      long pos = (long)(in.tellg()) - line.size() - 6;
      if( pos < 0 ) return false;
      out.seekp( pos, std::ios::beg );
      out << vtkgdcm;
      out.flush();
      }
    }
  //fbuf.close();

  return true;
}

int main(int argc, char *argv[])
{
  if( argc < 2 )
    {
    return 1;
    }
  for( int i = 1; i < argc; ++i )
    {
    const char *filename = argv[i];
    if( !ProcessOneFile( filename ) )
      {
      return 1;
      }
    }

  return 0;
}
