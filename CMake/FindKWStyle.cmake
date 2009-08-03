# 
# this module looks for KWStyle
# http://public.kitware.com/KWStyle
#
#
#  Copyright (c) 2009 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

find_program(KWSTYLE_EXECUTABLE
  NAMES KWStyle
  PATHS
  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Kitware Inc.\\KWStyle 1.0.0]/bin"
  )


mark_as_advanced(
  KWSTYLE_EXECUTABLE
  )

