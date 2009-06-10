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
 * Compilation:
 * $ CLASSPATH=/home/mmalaterre/Projects/gdcm/debug-gcc43/bin/gdcm.jar javac HelloSimple.java 
 *
 * Usage: 
 * $ CLASSPATH=/home/mmalaterre/Projects/gdcm/debug-gcc43/bin/gdcm.jar java HelloSimple.class gdcmData/test.acr
 */
import gdcm.*;

public class HelloSimple
{
  static { 
    // System.loadLibrary("gdcm");
    try {
      System.loadLibrary("gdcm");
    } catch (Throwable e) {
      System.out.println("cannot load gdcm");
    }
  }

  public static void main(String[] args)
    {
    System.out.println("Hello World");
    String filename = args[0];
    Reader reader = new Reader();
    reader.SetFileName( filename );
    boolean ret = reader.Read();
    if( !ret )
      {
      }

    }
}

