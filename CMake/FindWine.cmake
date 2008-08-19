#
# This module finds if wine is installed
#
#  WINE_EXECUTABLE         = full path to the wine binary
#

FIND_PROGRAM(WINE_EXECUTABLE
  NAMES wine
  )

MARK_AS_ADVANCED(
  WINE_EXECUTABLE
  )
