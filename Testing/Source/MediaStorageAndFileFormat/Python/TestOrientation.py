############################################################################
#
#  Program: GDCM (Grassroots DICOM). A DICOM library
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

if __name__ == "__main__":
  sucess = True

  ori1 = (1,0,0,0,1,0)
  ori2 = (1,0,0,0,0,1)

  label1 = gdcm.Orientation.GetLabel( gdcm.Orientation.GetType( ori1 ) )
  if label1 != 'AXIAL':
    print "Found:",label1
    sucess = False
  label2 = gdcm.Orientation.GetLabel( gdcm.Orientation.GetType( ori2 ) )
  if label2 != 'CORONAL':
    print "Found:",label2
    sucess = False

  # Test succeed ?
  sys.exit(sucess == False)

