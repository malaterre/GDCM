# Always
subdirs(Cxx)

if(GDCM_WRAP_PYTHON)
  subdirs(Python)
endif(GDCM_WRAP_PYTHON)
