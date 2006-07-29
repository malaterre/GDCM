/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
gdcmraw - ACR/NEMA DICOM PS3 ... DICOM PS3 - DICOM image to raw file
Synopsis:
gdcmraw [ -t | --tag Tag# (default: 07fe,0010) ] -i inputfile
Description:
gdcmraw
reads the named dicom or acr-nema input file and copies the raw image
pixel data to a raw binary file without a header of any kind.
The byte order, packing or encapsulation of the raw result is dependent
only
on the encoding of the input file and cannot be changed.
*/

int main(int argc, char *argv[])
{
  return 0;
}
