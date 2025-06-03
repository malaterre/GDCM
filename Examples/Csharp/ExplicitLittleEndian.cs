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
 * Simple C# example to show how one would 'Standardize' a DICOM File-Set
 *
 * Usage:
 * $ export LD_LIBRARY_PATH=$HOME/Projects/gdcm/debug-gcc/bin
 * $ mono bin/StandardizeFiles.exe input_path output_path
 */
using System;
using gdcm;

public class ExplicitLittleEndian
{
  public static bool ToExplicitLittleEndian(string aSrc, string aDst)
  {
    using (ImageReader reader = new ImageReader())
    {
      bool b = System.IO.File.Exists(aSrc);
      reader.SetFileName(aSrc);
      if (!reader.Read())
      {
        throw new System.Exception(string.Format("Cannot read '{0}'", aSrc));
      }
      using (FileExplicitFilter fef = new FileExplicitFilter())
      {
        fef.SetChangePrivateTags(false);
        fef.SetFile(reader.GetFile());
        if (!fef.Change())
        {
          throw new System.Exception(string.Format("Cannot make explicit '{0}'", aSrc));
        }
        using (var syntax = new TransferSyntax(TransferSyntax.TSType.ExplicitVRLittleEndian))
        {
          using (ImageChangeTransferSyntax tsc = new ImageChangeTransferSyntax())
          {
            tsc.SetTransferSyntax(syntax);
            tsc.SetInput(reader.GetImage());
            tsc.SetForce(true);
            if (!tsc.Change())
            {
              throw new System.Exception(string.Format("Cannot change '{0}'", aSrc));
            }
            using (var writer = new ImageWriter())
            {
              writer.SetFile(fef.GetFile());
              writer.SetImage(tsc.GetOutput());
              writer.SetFileName(aDst);
              if (!writer.Write())
              {
                throw new System.Exception(string.Format("Cannot write to '{0}'", aDst));
              }
            }
          }
        }
      }
    }
    return true;
  }

  public static int Main(string[] args)
  {
  gdcm.FileMetaInformation.SetSourceApplicationEntityTitle( "My Standardize App" );

  // http://www.oid-info.com/get/1.3.6.1.4.17434
  string THERALYS_ORG_ROOT = "1.3.6.1.4.17434";
  gdcm.UIDGenerator.SetRoot( THERALYS_ORG_ROOT );
  System.Console.WriteLine( "Root dir is now: " + gdcm.UIDGenerator.GetRoot() );

  string dir1 = args[0];
  string dir2 = args[1];

  // Check input is valid:
  if( !gdcm.PosixEmulation.FileIsDirectory(dir1) )
    {
    System.Console.WriteLine( "Input directory: " + dir1 + " does not exist. Sorry" );
    return 1;
    }
  if( !gdcm.PosixEmulation.FileIsDirectory(dir2) )
    {
    System.Console.WriteLine( "Output directory: " + dir2 + " does not exist. Sorry" );
    return 1;
    }

  Directory d = new Directory();
  uint nfiles = d.Load( dir1, true );
  if(nfiles == 0) return 1;

  // Process all filenames:
  FilenamesType filenames = d.GetFilenames();
  for( uint i = 0; i < nfiles; ++i )
    {
    string filename = filenames[ (int)i ];
    string outfilename = filename.Replace( dir1, dir2 );
    System.Console.WriteLine( "Filename: " + filename );
    System.Console.WriteLine( "Out Filename: " + outfilename );
    if( !ToExplicitLittleEndian( filename, outfilename ) )
    {
    System.Console.WriteLine( "Could not process filename: " + filename );
    //return 1;
    }
    }


  return 0;
  }
}
