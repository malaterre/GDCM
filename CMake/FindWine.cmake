#
# This module finds if wine is installed
#
#  WINE_EXECUTABLE         = full path to the wine binary
#
#
#  Copyright (c) 2006-2011 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

find_program(WINE_EXECUTABLE
  NAMES wine
  )

mark_as_advanced(
  WINE_EXECUTABLE
  )
