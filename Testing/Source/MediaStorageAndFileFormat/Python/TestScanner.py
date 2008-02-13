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

try:
  filename = os.sys.argv[1]
except:
  # failure
  print "Need a filename"
  sys.exit(1)

d = gdcm.Directory()
nfiles = d.Load( filename )
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

mapping = s.GetMapping(t1)
print mapping
print dir(mapping)

for f in d.GetFilenames():
  #print t2
  print "%s -> %s"%(f, s.GetValue(t2, f))

#ex = gdcm.FilenameToValueExtractor(mapping)
#ex.GetValue( "/tmp/Perfusion/Perfusion_205_0087" )
#print ex.GetValue( "/tmp/Perfusion/Perfusion_205_1809" )

sys.exit(0)

