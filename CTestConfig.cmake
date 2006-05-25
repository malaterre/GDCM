# Set the project name
SET(CTEST_PROJECT_NAME "GDCM")

# Dashboard is opened for submissions for a 24 hour period starting at
# the specified NIGHLY_START_TIME. Time is specified in 24 hour format.
SET(CTEST_NIGHTLY_START_TIME "21:00:00 EDT")

SET(CTEST_DROP_METHOD "http")
SET(CTEST_DROP_SITE "public.kitware.com")
SET(CTEST_DROP_LOCATION "/cgi-bin/HTTPUploadDartFile.cgi")
SET(CTEST_TRIGGER_SITE
  "http://${CTEST_DROP_SITE}/cgi-bin/Submit-${CTEST_PROJECT_NAME}-TestingResults.cgi")
