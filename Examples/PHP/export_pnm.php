<?php
/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

/*
 * This simple example will read in an image file
 * and try to write out as a PNM file
 */
require_once( 'gdcm.php' );

$reader = new PixmapReader();
$reader->SetFilename( "test.dcm" );
$reader->Read();

$file = $reader->GetFile();
$pixmap = $reader->GetPixmap();

$pnm = new PNMCodec();
$pnm.SetDimensions( $imageori->GetDimensions() );
$pnm.SetPixelFormat( $imageori->GetPixelFormat() );
$pnm.SetPhotometricInterpretation( $imageori->GetPhotometricInterpretation() );
$in = $pixmap->GetDataElement();
$outfilename = 'test.pnm';
$pnm.Write( outfilename, in );

?>
