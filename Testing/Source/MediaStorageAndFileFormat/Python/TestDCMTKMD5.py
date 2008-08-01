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
import os,sys,re

def TestDCMTKMD5( filename, verbose = False ):
  #print filename
  dcmdump_exec = "dcmdump -dc -E +P 2,10 -s " + filename + " 2> /dev/null"
  #print dcmdump_exec
  #ret = os.system( dcmdump_exec )
  f = os.popen(dcmdump_exec)
  ret = f.read()
  #assert ret == 0
  #print ret
  jpegre = re.compile('^.*JPEGLossless.*$')
  rlere = re.compile('^.*RLELossless.*$')
  lexre = re.compile('^.*LittleEndianExplicit.*$')
  if not ret:
    print "empty, problem with:", filename
    return 1
  if type(ret) != type(''):
    print "problem of type with:", filename
    return 1
  #print ret
  #print ret.__class__
  if( jpegre.match( ret ) ):
    print "jpeg: ",filename
  return 0

if __name__ == "__main__":
  sucess = 0
  try:
    filename = os.sys.argv[1]
    sucess += TestDCMTKMD5( filename, True )
  except:
    # loop over all files:
    t = gdcm.Testing()
    nfiles = t.GetNumberOfFileNames()
    for i in range(0,nfiles):
      filename = t.GetFileName(i)
      sucess += TestDCMTKMD5( filename )
  
  
  # Test succeed ?
  sys.exit(sucess)


