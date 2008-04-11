""" This module loads all the classes from the GDCM-VTK library into
its namespace.  This is a required module."""

import os

if os.name == 'posix':
  # extremely important !
  import sys,dl
  orig_dlopen_flags = sys.getdlopenflags()
  sys.setdlopenflags(dl.RTLD_NOW|dl.RTLD_GLOBAL)    
  from libvtkgdcmPython import *
  # revert:
  sys.setdlopenflags(orig_dlopen_flags)
  del sys, dl
else:
  from vtkgdcmPython import *

# to provide a compatibilty layer with VTK 4.2 and VTK 4.4 where vtkStringArray was not present
# and VTK 5.x where there is one...
try:
  # if vtkStringArray can be found in vtk let's use it !
  from vtk import vtkStringArray
except:
  print "Using compatibility layer (VTK 4) for vtkStringArray"

# bye bye
del os
