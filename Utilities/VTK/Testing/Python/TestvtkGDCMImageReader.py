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

# Simply check that we can read mr.001 from VTKData

import vtkgdcm
import vtk

from vtk.util.misc import vtkGetDataRoot
VTK_DATA_ROOT = vtkGetDataRoot()

r = vtkgdcm.vtkGDCMImageReader()
r.SetFileName( VTK_DATA_ROOT + "/Data/mr.001" )
r.Update()

#print r.GetOutput()

# Pixel Spacing
# 0.78125, 0.78125, 0

# Image Position (Patient)
# -13.3034, -80.8219, 119.178

