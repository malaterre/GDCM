subdirs(Cxx)

if(GDCM_WRAP_PYTHON)
  subdirs(Python)
endif(GDCM_WRAP_PYTHON)

if(GDCM_WRAP_JAVA)
  subdirs(Java)
endif(GDCM_WRAP_JAVA)
