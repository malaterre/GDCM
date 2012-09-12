cmake_minimum_required(VERSION 2.4)

# Remove these policy lines when CMake 2.6 is the minimum version.
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif()

# Choose behavior based on whether we are building inside the GDCM tree.
if(GDCM_BINARY_DIR)
subdirs(Cxx)

if(GDCM_WRAP_PYTHON)
  subdirs(Python)
endif()

if(GDCM_WRAP_CSHARP)
  subdirs(Csharp)
endif()

if(GDCM_WRAP_JAVA)
  subdirs(Java)
endif()

else()

  # We are building outside the GDCM tree.  Build the examples directly.
  project(GDCMExamples)

  # Find and load the VTK configuration.
  find_package(GDCM REQUIRED)
  include(${GDCM_USE_FILE})

  subdirs(Cxx)

endif()
