subdirs(Cxx)

if(VTK_WRAP_PYTHON)
  subdirs(Python)
endif(VTK_WRAP_PYTHON)

if(GDCM_WRAP_JAVA)
  if(VTK_WRAP_JAVA)
    subdirs(Java)
  endif(VTK_WRAP_JAVA)
endif(GDCM_WRAP_JAVA)
