# VTK-Python testing
IF(GDCM_WRAP_PYTHON)
  IF(VTK_PYTHONPATH_DIRS)
     IF(WIN32)
       #MESSAGE(${VTK_PYTHONPATH_DIRS})
       #STRING(REGEX REPLACE ";" ";" UNIX_VTK_PYTHONPATH_DIRS "${VTK_PYTHONPATH_DIRS}")
       SET(UNIX_VTK_PYTHONPATH_DIRS "${VTK_PYTHONPATH_DIRS}")
     ELSE(WIN32)
       STRING(REGEX REPLACE ";" ":" UNIX_VTK_PYTHONPATH_DIRS "${VTK_PYTHONPATH_DIRS}")
     ENDIF(WIN32)
  ELSE(VTK_PYTHONPATH_DIRS)
  # if VTK_PYTHONPATH_DIRS is not given (very old VTK) then simply hope the user set his pythonpath properly:
  #  SET(UNIX_VTK_PYTHONPATH_DIRS "$ENV{PYTHONPATH}")
  # previous solution was not safe, let's hope the following are set properly:
   IF(WIN32)
     SET(PATH_SEPARATOR ";")
   ELSE(WIN32)
     SET(PATH_SEPARATOR ":")
   ENDIF(WIN32)
     IF(VTK_SOURCE_DIR)
      SET(UNIX_VTK_PYTHONPATH_DIRS "${VTK_SOURCE_DIR}/Wrapping/Python${PATH_SEPARATOR}${VTK_LIBRARY_DIRS}")
    ELSE(VTK_SOURCE_DIR)
      # FIXME: hardcoded
      SET(UNIX_VTK_PYTHONPATH_DIRS "/usr/local/src/vtk/build/Wrapping/Python${PATH_SEPARATOR}${VTK_LIBRARY_DIRS}")
    ENDIF(VTK_SOURCE_DIR)
  ENDIF(VTK_PYTHONPATH_DIRS)
  SET(VTK_PYTHON_TESTS
    TestvtkGDCMImageReader
    TestvtkGDCMImageWriter
    TestMultiframeGrayscaleWordSecondaryCaptureImageStorage
  )
  IF(GDCM_HAVE_PTHREAD_H)
    SET(VTK_PYTHON_TESTS ${VTK_PYTHON_TESTS}
      #TestvtkGDCMThreadedImageReader
      TestvtkGDCMThreadedImageReader2
    )
  ENDIF(GDCM_HAVE_PTHREAD_H)

  FOREACH(test ${VTK_PYTHON_TESTS})
          #MESSAGE(${UNIX_VTK_PYTHONPATH_DIRS})
    SET_SOURCE_FILES_PROPERTIES(${test}.py PROPERTIES PYTHONPATH "${UNIX_VTK_PYTHONPATH_DIRS}")
    ADD_PYTHON_TEST(${test}Python ${test}.py ${GDCM_DATA_ROOT}/test.acr)
  ENDFOREACH(test)

ENDIF(GDCM_WRAP_PYTHON)

