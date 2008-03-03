############################################################################
#
#  Program: GDCM (Grass Root DICOM). A DICOM library
#  Module:  $URL$
#
#  Copyright (c) 2006-2008 Mathieu Malaterre
#  All rights reserved.
#  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.
#
#     This software is distributed WITHOUT ANY WARRANTY; without even
#     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#     PURPOSE.  See the above copyright notice for more information.
#
############################################################################

import gdcm
import os,sys

def TestAnonymizer(filename, verbose = False):
  r = gdcm.Reader()
  r.SetFileName( filename )
  sucess = r.Read()
  if( not sucess ): return 1
  #print r.GetFile().GetDataSet()

  ano = gdcm.Anonymizer()
  ano.SetFile( r.GetFile() )
  # 1. Replace with another value
  ano.Replace( gdcm.Tag(0x0010,0x0010), "Test^Anonymize" )
  # 2. Remove a tag (even a SQ)
  ano.Remove( gdcm.Tag(0x0008,0x2112) )
  # 3. Make a tag empty
  ano.Empty( gdcm.Tag(0x0008,0x0070) )
  # Call the main function:
  sucess = ano.RemovePrivateTags() # do it !
  if( not sucess ): return 1

  if verbose:
    print ano.GetFile().GetDataSet()

  return sucess

if __name__ == "__main__":
  sucess = 0
  try:
    filename = os.sys.argv[1]
    sucess += TestAnonymizer( filename, True )
  except:
    # loop over all files:
    t = gdcm.Testing()
    nfiles = t.GetNumberOfFileNames()
    for i in range(0,nfiles):
      filename = t.GetFileName(i)
      sucess += TestAnonymizer( filename )
  
  
  # Test succeed ?
  sys.exit(sucess == 0)

