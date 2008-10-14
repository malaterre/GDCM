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

using System;
using gdcm;

public class HelloWorld
{
  public static void Main(string[] args)
    {
    System.Console.WriteLine("Hello World !");
    //System.Console.WriteLine( args[0] );
    gdcm.Reader reader;
    string filename = args[0];
    reader.SetFileName( filename );
    reader.Read();

    }
}

