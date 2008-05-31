# Try to rebuild wrapping a little more often:
INCLUDE_REGULAR_EXPRESSION("^(gdcm).*$")
# TODO:
# SWIG is really a pain in the neck to use, a better alternative is Py++ which is using
# gccxml for the C++ parser and allow a full ANSI C++ support
# Note gcc has some issue with RTTI stuff:
# http://groups.google.com/group/comp.lang.c++.moderated/browse_thread/thread/ac889a7d9eac902f
# http://gcc.gnu.org/ml/gcc-help/2007-10/msg00239.html
# http://wiki.python.org/moin/boost.python/CrossExtensionModuleDependencies
# http://www.boost-consulting.com/writing/bpl.html
# http://gcc.gnu.org/ml/gcc/2002-05/msg00866.html
# http://mail.python.org/pipermail/c++-sig/2002-May/001021.html
# http://mail.python.org/pipermail/python-dev/2002-May/023923.html

FIND_PACKAGE(SWIG REQUIRED)
MARK_AS_ADVANCED(SWIG_DIR SWIG_EXECUTABLE)
INCLUDE(${SWIG_USE_FILE})

# Note:
# python -c "from struct import pack; print  pack('5b', (41*len('99')), pow(8,2)+20, 4900**0.5, range(78)[-1], 10)"

INCLUDE_DIRECTORIES(
  "${GDCM_BINARY_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/Common"
  "${GDCM_SOURCE_DIR}/Source/DataStructureAndEncodingDefinition"
  "${GDCM_SOURCE_DIR}/Source/InformationObjectDefinition"
  "${GDCM_SOURCE_DIR}/Source/MediaStorageAndFileFormat"
  "${GDCM_SOURCE_DIR}/Source/DataDictionary"
  ${CMAKE_CURRENT_SOURCE_DIR}
)
# Provide some C99 compatilities for all win system...hopefully there won't be no collision
IF(WIN32 AND NOT CYGWIN)
  INCLUDE_DIRECTORIES(
    "${GDCM_SOURCE_DIR}/Utilities/C99"
  )
ENDIF(WIN32 AND NOT CYGWIN)

FIND_PACKAGE(PythonLibs REQUIRED)
MARK_AS_ADVANCED(PYTHON_LIBRARY PYTHON_INCLUDE_PATH)
# Lamest excuse ever:
# http://mail.python.org/pipermail/python-list/2002-April/141189.html
# So here come craziest hack ever, since I cannot control the output of swig,
# I need to fake a Python.h file only for MSVC compilers...insane !
IF(MSVC)
  CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/Python.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/Python.h @ONLY
  )
  INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )
  # does not work quite as expected...
  #  IF(CMAKE_CONFIGURATION_TYPES)
  #SET_SOURCE_FILES_PROPERTIES(
  #        "${swig_generated_file_fullname}"
  #        PROPERTIES 
  #        COMPILE_FLAGS "/U _DEBUG")
  #  ENDIF(CMAKE_CONFIGURATION_TYPES)
  
  ELSE(MSVC)
  # just plain including pyconfig.h is working...until one crazy python dev decide otherwise...
    INCLUDE_DIRECTORIES(
      ${PYTHON_INCLUDE_PATH}
    )
ENDIF(MSVC)
SET_SOURCE_FILES_PROPERTIES(gdcm.i PROPERTIES CPLUSPLUS ON)


# Some old swig 1.3 did not support this option:
#SET(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}")

#SET(GDCM_PYTHON_IMPLEMENTATION_NAME gdcmpython)
SET(GDCM_PYTHON_IMPLEMENTATION_NAME gdcm)
SET(CMAKE_SWIG_FLAGS "-interface _${GDCM_PYTHON_IMPLEMENTATION_NAME}")
SEPARATE_ARGUMENTS(CMAKE_SWIG_FLAGS)

# While trying to get rid of the compilation warning in swig generated c++ code, I thought I could
# simply do the following:
#SET(CMAKE_CXX_FLAGS "")
# well no, you cannot, it get rid of some important flags, and make the _gdcm.so incompatible with
# the other gdcm lib. bad !!!
SWIG_ADD_MODULE(${GDCM_PYTHON_IMPLEMENTATION_NAME} python gdcm.i gdcmPythonFilter.cxx)
SWIG_LINK_LIBRARIES(${GDCM_PYTHON_IMPLEMENTATION_NAME} gdcmMSFF gdcmIOD ${PYTHON_LIBRARIES})
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/gdcm.pth.in
  ${CMAKE_CURRENT_BINARY_DIR}/gdcm.pth
)

# Python extension modules on Windows must have the extension ".pyd"
# instead of ".dll" as of Python 2.5.  Older python versions do support
# this suffix.
IF(WIN32 AND NOT CYGWIN)
  SET_TARGET_PROPERTIES(${SWIG_MODULE_${GDCM_PYTHON_IMPLEMENTATION_NAME}_REAL_NAME} PROPERTIES SUFFIX ".pyd")
ENDIF(WIN32 AND NOT CYGWIN)
#SET_TARGET_PROPERTIES(${SWIG_MODULE_${GDCM_PYTHON_IMPLEMENTATION_NAME}_REAL_NAME} PROPERTIES ${GDCM_LIBRARY_PROPERTIES})

# swig generates a _gdcm.so and a gdcm.py, we need to copy gdcm.py to the proper place:
# gdcm.py is the interface name != implementation name, so we need to keep 'gdcm', so that 'import gdcm'
# from a python script always work
ADD_CUSTOM_COMMAND(
  TARGET    ${SWIG_MODULE_${GDCM_PYTHON_IMPLEMENTATION_NAME}_REAL_NAME}
  POST_BUILD
  COMMAND   ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/gdcm.py ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}
  DEPENDS "${swig_generated_file_fullname}" "${CMAKE_CURRENT_BINARY_DIR}/gdcm.py"
  COMMENT   "Copy gdcm.py into ${LIBRARY_OUTPUT_PATH}"
)

#Module are always place in the library destination
#but for poor win32 user I decided to place them
# right next to the other dlls
IF(NOT GDCM_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS ${SWIG_MODULE_${GDCM_PYTHON_IMPLEMENTATION_NAME}_REAL_NAME}
    #RUNTIME DESTINATION ${GDCM_INSTALL_BIN_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package}/${subdir} COMPONENT Runtime
    ARCHIVE DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package}/${subdir} COMPONENT Development
    #DESTINATION ${python_site_package}/${subdir}
  )
# the python file is not a dev file, but part of the gdcm module...
  INSTALL(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/gdcm.py 
    DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package}/${subdir} COMPONENT Runtime
    #DESTINATION ${python_site_package}/${subdir}
  )
  INSTALL(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/gdcm.pth
    DESTINATION ${GDCM_INSTALL_LIB_DIR}/${python_site_package} COMPONENT Runtime
    #DESTINATION ${python_site_package}
  )
ENDIF(NOT GDCM_INSTALL_NO_LIBRARIES)

# Test that will try to load any class in the target language: python
# it make sure swig was not broken accidentally
IF(BUILD_TESTING)
  ADD_PYTHON_TEST(TestWrapPython TestWrap.py ${GDCM_SOURCE_DIR}/Source)
ENDIF(BUILD_TESTING)

# TODO
# python -c "from distutils import sysconfig; print sysconfig.get_python_lib()"
# /usr/lib/python2.4/site-packages


