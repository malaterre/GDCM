/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

using System;
using System.IO;
using gdcm;

public class TestReaderUnicode
{
  public static void copyFile( string sourceFileName, string destFileName ) {
    System.IO.File.Copy (sourceFileName, destFileName);
  }
  public static void process(String template, String tmpdir, String targetname) {
    if(!PosixEmulation.FileIsDirectory( tmpdir ) )
    {
      PosixEmulation.MakeDirectory( tmpdir );
    }
    
    String filename = tmpdir + "/" + targetname;
    PosixEmulation.RemoveFile( filename );
    try {
      copyFile(template, filename);
    } catch (IOException ex) {
      Console.WriteLine("Error copying: " + template + " to " + filename );
      throw ex;
    }
    Reader reader = new Reader();
    Console.WriteLine("Reading: " + filename );
    reader.SetFileName( filename );
    if ( !reader.Read() )
      {
      throw new Exception("Could not read: " + filename );
      }
    String reference = Testing.GetMediaStorageFromFile(template);
    if( reference == null || reference == "" )
      {
      throw new Exception("Missing ref for: " + template);
      }
    MediaStorage ms = new MediaStorage();
    ms.SetFromFile( reader.GetFile() );
    if( ms.IsUndefined() )
      {
      throw new Exception("ref is undefined for: " + filename + " should be " + reference );
      }
    MediaStorage.MSType ref_mstype = MediaStorage.GetMSType( reference );
    if( ms.GetMSType() != ref_mstype )
      {
      throw new Exception("incompatible type: " + reference + " vs " + ms.GetString() + " for " + filename );
      }
    }


  public static int Main(string[] args)
    {
    String dataroot = Testing.GetDataRoot();
    String filename = dataroot + "/012345.002.050.dcm";
    String subdir = "TestReaderUnicode";
    String tmpdir = Testing.GetTempDirectory( subdir );
    process(filename, tmpdir, "ascii.dcm" );
    process(filename, tmpdir, "ê.dcm" );
    process(filename, tmpdir, "А.dcm" );

    return 0;
    }
}
