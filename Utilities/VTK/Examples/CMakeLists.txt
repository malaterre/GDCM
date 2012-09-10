#subdirs(Cxx Python)
subdirs(Cxx)

if(GDCM_WRAP_CSHARP)
  subdirs(Csharp)
endif(GDCM_WRAP_CSHARP)

if(GDCM_WRAP_JAVA)
  subdirs(Java)
endif(GDCM_WRAP_JAVA)
