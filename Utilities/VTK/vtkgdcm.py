""" This module loads all the classes from the GDCM-VTK library into
its namespace.  This is a required module."""

import os

if os.name == 'posix':
    from libvtkgdcmPython import *
else:
    from vtkgdcmPython import *
