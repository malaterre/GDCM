# python
if(GDCM_WRAP_PYTHON)
  subdirs(Python)
endif(GDCM_WRAP_PYTHON)
# java
if(GDCM_WRAP_JAVA)
  subdirs(Java)
endif(GDCM_WRAP_JAVA)
# php
if(GDCM_WRAP_PHP)
  subdirs(PHP)
endif(GDCM_WRAP_PHP)
# perl
if(GDCM_WRAP_PERL)
  subdirs(Perl)
endif(GDCM_WRAP_PERL)
# C#
if(GDCM_WRAP_CSHARP)
#  subdirs(Csharp)
endif(GDCM_WRAP_CSHARP)
