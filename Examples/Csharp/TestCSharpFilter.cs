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
  Convertor convertor = new Convertor();
  int a = convertor.Convert<int>( some_int_blob );
  double b = convertor.Convert<double>( some_double_blob ); 
*/

/*
 * Usage: 
 * $ export LD_LIBRARY_PATH=$HOME/Projects/gdcm/debug-gcc/bin
 * $ mono bin/TestCSharpFilter.exe gdcmData/012345.002.050.dcm
 */
using System;
using gdcm;

public class TestCSharpFilter
{
  public static int Main(string[] args)
    {
    string filename = args[0];
    Reader reader = new Reader();
    reader.SetFileName( filename );
    bool ret = reader.Read();
    if( !ret )
      {
      return 1;
      }
    File f = reader.GetFile();
    DataSet ds = f.GetDataSet();
    CSharpDataSet cds = new CSharpDataSet(ds);

    cds.Start(); // Make iterator go at begining
    while(!cds.IsAtEnd())
      {
      System.Console.WriteLine( "out:" + cds.GetCurrent().toString() );
      cds.Next();
      }

    return 0;
    }
}

