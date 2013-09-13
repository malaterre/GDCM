# - Find PHP5
# This module finds if PHP5 is installed and determines where the include files
# and libraries are. It also determines what the name of the library is. This
# code sets the following variables:
#
#  PHP5_INCLUDE_PATH       = path to where php.h can be found
#  PHP5_EXECUTABLE         = full path to the php5 binary
#
#  Copyright (c) 2006-2011 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

SET(PHP5_POSSIBLE_INCLUDE_PATHS
  /usr/include/php5
  /usr/local/include/php5
  /usr/include/php
  /usr/local/include/php
  /usr/local/apache/php
  )

SET(PHP5_POSSIBLE_LIB_PATHS
  /usr/lib
  )

FIND_PATH(PHP5_FOUND_INCLUDE_PATH main/php.h
  ${PHP5_POSSIBLE_INCLUDE_PATHS})

IF(PHP5_FOUND_INCLUDE_PATH)
  SET(php5_paths "${PHP5_POSSIBLE_INCLUDE_PATHS}")
  FOREACH(php5_path Zend main TSRM)
    SET(php5_paths ${php5_paths} "${PHP5_FOUND_INCLUDE_PATH}/${php5_path}")
  ENDFOREACH(php5_path Zend main TSRM)
  SET(PHP5_INCLUDE_PATH "${php5_paths}" CACHE INTERNAL "PHP5 include paths")
ENDIF(PHP5_FOUND_INCLUDE_PATH)

FIND_PROGRAM(PHP5_EXECUTABLE NAMES php5 php )

MARK_AS_ADVANCED(
  PHP5_EXECUTABLE
  PHP5_FOUND_INCLUDE_PATH
  )

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PHP5 DEFAULT_MSG PHP5_EXECUTABLE PHP5_INCLUDE_PATH)
