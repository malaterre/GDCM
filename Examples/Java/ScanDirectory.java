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
 * Simple example showing how to bind a custom Observer to the Scanner in response
 * to ProgressEvent
 *
 * Compilation:
 * $ CLASSPATH=gdcm.jar javac ../../gdcm/Examples/Java/ScanDirectory.java -d .
 *
 * Usage:
 * $ LD_LIBRARY_PATH=. CLASSPATH=gdcm.jar:. java ScanDirectory gdcmData
 */
import gdcm.*;

public class ScanDirectory
{
  public static class MyWatcher extends SimpleSubjectWatcher
    {
    public MyWatcher(Subject s) { super(s,"Override String"); }
    protected void ShowProgress(Subject caller, Event evt)
      {
      ProgressEvent pe = ProgressEvent.Cast(evt);
      System.out.println( "This is my progress: " + pe.GetProgress() );
      }
    }

  public static void main(String[] args) throws Exception
    {
    String directory = args[0];

    Directory d = new Directory();
    long nfiles = d.Load( directory );
    if(nfiles == 0)
      {
      throw new Exception("No files found");
      }
    System.out.println( "Files:\n" + d.toString() );

    //Scanner s = new Scanner();
    SmartPtrScan sscan = Scanner.New();
    Scanner s = sscan.__ref__();
    //SimpleSubjectWatcher watcher = new SimpleSubjectWatcher(s, "MySimple");
    MyWatcher watcher = new MyWatcher(s);
    Tag t1 = new Tag(0x8,0x8);
    Tag t2 = new Tag(0x10,0x10);
    s.AddTag( t1 );
    s.AddTag( t2 );
    boolean b = s.Scan( d.GetFilenames() );
    if(!b)
      {
      throw new Exception("Could not scan");
      }

    System.out.println( "Scan:\n" + s.toString() );

    System.out.println( "success" );
    }
}
