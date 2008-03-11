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

def TestScan(filename, recursive = False):
  d = gdcm.Directory()
  nfiles = d.Load( filename, recursive )
  print d
  print "done retrieving file list"
  
  s = gdcm.Scanner()
  t1 = gdcm.Tag(0x0020,0x000d)
  t2 = gdcm.Tag(0x0020,0x000e)
  s.AddTag( t1 )
  s.AddTag( t2 )
  b = s.Scan( d.GetFilenames() )
  if not b:
    print "Scanner failed";
    sys.exit(1)
  values  = s.GetValues()
  print "Values found for all tags are:"
  print values
  mappings = s.GetMappings()
  
  #filename = d.GetFilenames()[0]
  #mapping = s.GetMapping(filename)
  #print mapping
  #print dir(mapping)
  
  # Let's work only on t1 for example:
  # For each file get the value for tag t1:
  for f in d.GetFilenames():
    # Is the file a DICOM file ?
    b = s.IsKey(f)
    # print !
    # Three case:
    # 1. Tag found and value found
    # 2. Tag found but no value
    # 3. Tag not found and/or file not DICOM
    print "%s -> [%s] (%s)"%(f, s.GetValue(f,t1),b)
  
if __name__ == "__main__":
  try:
    filename = os.sys.argv[1]
    recursive = True
  except:
    t = gdcm.Testing()
    filename = t.GetDataRoot()
    recursive = False
  TestScan( filename, recursive)
  
  sys.exit(0)

