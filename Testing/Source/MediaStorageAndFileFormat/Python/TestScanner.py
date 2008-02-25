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
  #print s
  values  = s.GetValues()
  print values
  mappings = s.GetMappings()
  print mappings
  print dir(mappings)
  
  filename = d.GetFilenames()[0]
  mapping = s.GetMapping(filename)
  print mapping
  print dir(mapping)
  
  for f in d.GetFilenames():
    #print t2
    print "%s -> [%s]"%(f, s.GetValue(f,t2))
  
  #ex = gdcm.FilenameToValueExtractor(mapping)
  #ex.GetValue( "/tmp/Perfusion/Perfusion_205_0087" )
  #print ex.GetValue( "/tmp/Perfusion/Perfusion_205_1809" )

try:
  filename = os.sys.argv[1]
  TestScan( filename, True )
except:
  t = gdcm.Testing()
  filename = t.GetDataRoot()
  TestScan( filename, False )

sys.exit(0)

