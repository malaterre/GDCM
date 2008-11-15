
FIND_PACKAGE(DCMTK)
FIND_PACKAGE(DICOM3TOOLS)

SUBDIRS(
  Source
  )

#-----------------------------------------------------------------------------
# Here is one cool test: you can pretty much test all configuration using
# ctest...well except one, the case where a user set BUILD_TESTING=OFF
# since this would deactivate the dashboard and would not submit...doh!
# So instead let's create a test that would build gdcm with this option
IF(UNIX AND GDCM_TEST_BOOSTRAP)
  ADD_TEST(BuildGDCM ${CMAKE_CTEST_COMMAND}
    #${VTK_EXAMPLE_TEST_CONFIG_TYPE}
    --build-and-test ${GDCM_SOURCE_DIR} ${GDCM_BINARY_DIR}/GDCMLocal
    --build-two-config
    --build-generator ${CMAKE_GENERATOR}
    --build-makeprogram ${CMAKE_MAKE_PROGRAM}
    --build-project GDCMLOCAL
    #--build-run-dir ${VTK_EXAMPLE_TEST_RUN_DIR}
    --build-options -DGDCM_BUILD_TESTING:BOOL=OFF -DGDCM_BUILD_SHARED_LIBS:BOOL=ON -DGDCM_WRAP_PYTHON:BOOL=ON -DGDCM_SUPPORT_BROKEN_IMPLEMENTATION:BOOL=OFF
    #--test-command "${VTK_BINARY_DIR}/Examples/Build/vtkLocal/bin/vtkLocalTest"
    )
  ADD_TEST(InstallGDCM ${CMAKE_CTEST_COMMAND}
    #  ${GDCM_INSTALL_TEST_CONFIG_TYPE}
    --build-and-test ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}
    --build-generator ${CMAKE_GENERATOR}
    --build-project GDCM
    --build-makeprogram ${CMAKE_MAKE_PROGRAM}
    --build-noclean
    --build-target install
  )
ENDIF(UNIX AND GDCM_TEST_BOOSTRAP)



