# - MONO module for CMake
# Defines the following macros:
#   MONO_ADD_MODULE(name language [ files ])
#     - Define swig module with given name and specified language
#   MONO_LINK_LIBRARIES(name [ libraries ])
#     - Link libraries to swig module
# All other macros are for internal use only.
# To get the actual name of the swig module,
# use: ${MONO_MODULE_name_REAL_NAME}.
# Set Source files properties such as CPLUSPLUS and MONO_FLAGS to specify
# special behavior of MONO. Also global CMAKE_MONO_FLAGS can be used to add
# special flags to all swig calls.
# Another special variable is CMAKE_MONO_OUTDIR, it allows one to specify 
# where to write all the swig generated module (swig -outdir option)
# The name-specific variable MONO_MODULE_<name>_EXTRA_DEPS may be used
# to specify extra dependencies for the generated modules.

#
# Create Swig module
#
MACRO(MONO_ADD_MODULE name language)
  MONO_MODULE_INITIALIZE(${name} ${language})
  SET(swig_dot_i_sources)
  SET(swig_other_sources)
  FOREACH(it ${ARGN})
    IF(${it} MATCHES ".*\\.i$")
      SET(swig_dot_i_sources ${swig_dot_i_sources} "${it}")
    ELSE(${it} MATCHES ".*\\.i$")
      SET(swig_other_sources ${swig_other_sources} "${it}")
    ENDIF(${it} MATCHES ".*\\.i$")
  ENDFOREACH(it)

  SET(swig_generated_sources)
  FOREACH(it ${swig_dot_i_sources})
    MONO_ADD_SOURCE_TO_MODULE(${name} swig_generated_source ${it})
    SET(swig_generated_sources ${swig_generated_sources} "${swig_generated_source}")
  ENDFOREACH(it)
  GET_DIRECTORY_PROPERTY(swig_extra_clean_files ADDITIONAL_MAKE_CLEAN_FILES)
  SET_DIRECTORY_PROPERTIES(PROPERTIES
    ADDITIONAL_MAKE_CLEAN_FILES "${swig_extra_clean_files};${swig_generated_sources}")
  ADD_LIBRARY(${MONO_MODULE_${name}_REAL_NAME}
    MODULE
    ${swig_generated_sources}
    ${swig_other_sources})
  SET_TARGET_PROPERTIES(${MONO_MODULE_${name}_REAL_NAME}
    PROPERTIES PREFIX "")
ENDMACRO(MONO_ADD_MODULE)

#
# Like TARGET_LINK_LIBRARIES but for swig modules
#
MACRO(MONO_LINK_LIBRARIES name)
  IF(MONO_MODULE_${name}_REAL_NAME)
    TARGET_LINK_LIBRARIES(${MONO_MODULE_${name}_REAL_NAME} ${ARGN})
  ELSE(MONO_MODULE_${name}_REAL_NAME)
    MESSAGE(SEND_ERROR "Cannot find Swig library \"${name}\".")
  ENDIF(MONO_MODULE_${name}_REAL_NAME)
ENDMACRO(MONO_LINK_LIBRARIES name)

