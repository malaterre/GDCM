/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * Simple example showing that Jav UTF-16 string are properly passed to
 * GDCM layer as locale 8bits
 *
 * Compilation:
 * $ CLASSPATH=gdcm.jar javac ../../gdcm/Examples/Java/ReadFiles.java -d .
 *
 * Usage:
 * $ LD_LIBRARY_PATH=. CLASSPATH=gdcm.jar:. java ReadFiles gdcmData
 */
import gdcm.*;
import java.io.File;

public class ReadFiles
{
  public static void process(File file)
    {
    String path = file.getPath();
    assert PosixEmulation.FileExists(path) : "Problem converting to 8bits";

    System.out.println("Reading: " + path );
    Reader r = new Reader();
    r.SetFileName( path );
    boolean b = r.ReadUpToTag( new Tag(0x88,0x200) );
    System.out.println("DS:\n" + r.GetFile().GetDataSet().toString() );
    }

  // Process only files under dir
  public static void visitAllFiles(File dir)
    {
    if (dir.isDirectory())
      {
      String[] children = dir.list();
      for (int i=0; i<children.length; i++)
        {
        visitAllFiles(new File(dir, children[i]));
        }
      }
    else
      {
      process(dir);
      }
    }

  public static void main(String[] args) throws Exception
    {
    String directory = args[0];

    File dir = new File(directory);
    visitAllFiles(dir);
    }
}
