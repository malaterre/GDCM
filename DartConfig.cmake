# Dashboard is opened for submissions for a 24 hour period starting at
# the specified NIGHLY_START_TIME. Time is specified in 24 hour format.
SET (NIGHTLY_START_TIME "21:00:00 EDT")

# Dart server to submit results (used by client)
SET (DROP_METHOD "http")
SET (DROP_SITE "public.kitware.com")
SET (DROP_LOCATION "/cgi-bin/HTTPUploadDartFile.cgi")
SET (TRIGGER_SITE 
    "http://${DROP_SITE}/cgi-bin/Submit-Public-TestingResults.cgi")

# Project Home Page
SET (PROJECT_URL "http://www.creatis.insa-lyon.fr/Public/Gdcm")

# Dart server configuration 
SET (ROLLUP_URL "http://${DROP_SITE}/cgi-bin/Public-rollup-dashboard.sh")
SET (CVS_WEB_URL "http://${DROP_SITE}/cgi-bin/cvsweb.cgi/Public/")
SET (CVS_WEB_CVSROOT "Public")

OPTION(BUILD_DOXYGEN "Build source documentation using doxygen" "Off")
SET (DOXYGEN_CONFIG "${PROJECT_BINARY_DIR}/doxygen.config" )
SET (USE_DOXYGEN "On")
SET (DOXYGEN_URL "http://${DROP_SITE}/Public/Doxygen/html/" )

SET (USE_GNATS "On")
SET (GNATS_WEB_URL "http://${DROP_SITE}/Bug/index.php")

# Continuous email delivery variables
SET (CONTINUOUS_FROM "luis.ibanez@kitware.com")
SET (SMTP_MAILHOST "public.kitware.com")
SET (CONTINUOUS_MONITOR_LIST "mathieu.malaterre@kitware.com gdcm-cvs@lists.sf.net")
SET (CONTINUOUS_BASE_URL "http://www.kitware.com/Testing")

#MARK_AS_ADVANCED(BUILD_DOXYGEN)

SET (DELIVER_BROKEN_BUILD_EMAIL_WITH_TEST_FAILURES ON)
SET (DELIVER_BROKEN_BUILD_EMAIL "Continuous Nightly")
SET (EMAIL_FROM "gdcm-developers@lists.sf.net")
#SET (DARTBOARD_BASE_URL "${PROJECT_URL}/Testing")
                                                                                
SET (DELIVER_BROKEN_BUILD_EMAIL_WITH_CONFIGURE_FAILURES 1)
SET (DELIVER_BROKEN_BUILD_EMAIL_WITH_BUILD_ERRORS 1)
SET (DELIVER_BROKEN_BUILD_EMAIL_WITH_BUILD_WARNINGS 1)
SET (DELIVER_BROKEN_BUILD_EMAIL_WITH_TEST_NOT_RUNS 1)
SET (DELIVER_BROKEN_BUILD_EMAIL_WITH_TEST_FAILURES 1)
