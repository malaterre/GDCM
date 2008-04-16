""" This module loads all the classes from the GDCM-VTK library into
its namespace.  This is a required module."""

import os

if os.name == 'posix':
  # extremely important !
  # http://gcc.gnu.org/faq.html#dso
  import sys
  orig_dlopen_flags = sys.getdlopenflags()
  try:
    import dl
  except ImportError:
    # are we on AMD64 ?
    try:
      import DLFCN as dl
    except ImportError:
      print "Could not import dl"
      dl = None
  if dl:
    #print "dl was imported"
    #sys.setdlopenflags(dl.RTLD_LAZY|dl.RTLD_GLOBAL)    
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
