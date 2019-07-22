/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
 */
import gdcm.*;
import java.util.Properties;
import java.util.Enumeration;
import java.io.IOException;
import java.nio.file.Files;

public class TestReaderUnicode
{
  public static void copyFile( java.io.File from, java.io.File to ) throws IOException {
    Files.copy( from.toPath(), to.toPath() );
  }
  public static void process(String template, String tmpdir, String targetname) throws IOException, Exception {
    if(!PosixEmulation.FileIsDirectory( tmpdir ) )
    {
      PosixEmulation.MakeDirectory( tmpdir );
    }
    
    String filename = tmpdir + "/" + targetname;
    PosixEmulation.RemoveFile( filename );
    try {
      copyFile(new java.io.File(template), new java.io.File(filename ));
    } catch (IOException ex) {
      System.err.println("Error copying: " + template + " to " + filename );
      return;
    }
    Reader reader = new Reader();
    System.out.println("Reading: " + filename );
    reader.SetFileName( filename );
    if ( !reader.Read() )
      {
      throw new Exception("Could not read: " + filename );
      }
    String ref = Testing.GetMediaStorageFromFile(template);
    if( ref == null )
      {
      throw new Exception("Missing ref for: " + template);
      }
    MediaStorage ms = new MediaStorage();
    ms.SetFromFile( reader.GetFile() );
    if( ms.IsUndefined() && !"".equals( ref ) )
      {
      // gdcm-CR-DCMTK-16-NonSamplePerPix.dcm is empty
      throw new Exception("ref is undefined for: " + filename + " should be " + ref );
      }
    MediaStorage.MSType ref_mstype = MediaStorage.GetMSType( ref );
    if( !"".equals( ref ) && ms.GetType() != ref_mstype )
      {
      throw new Exception("incompatible type: " + ref + " vs " + ms.GetString() + " for " + filename );
      }
    }

  public static void main(String[] args) throws Exception
    {
    String dataroot = Testing.GetDataRoot();
    String filename = dataroot + "/012345.002.050.dcm";
    String subdir = "TestReaderUnicode";
    String tmpdir = Testing.GetTempDirectory( subdir );
    process(filename, tmpdir, "ascii.dcm" );
    process(filename, tmpdir, "ê.dcm" );
    process(filename, tmpdir, "А.dcm" );
    }
}
