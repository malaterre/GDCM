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

import os
import gdcm

if __name__ == "__main__":
  dirname = os.sys.argv[1]

  gdcmclasses = dir(gdcm)
  for file in os.listdir(dirname):
    #print file[-2:]
    if file[-2:] != '.h': continue
    #print file[4:-2]
    gdcmclass = file[4:-2]
    if gdcmclass in gdcmclasses:
      print "ok:", gdcmclass
    else:
      print "not wrapped:",gdcmclass
