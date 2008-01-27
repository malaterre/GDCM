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

r = gdcm.ImageReader()
r.SetFileName( filename )
sucess = r.Read()

print r.GetImage().Print()

# Test succeed ?
sys.exit(sucess != 1)

