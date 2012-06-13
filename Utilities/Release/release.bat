@rem
@rem  Program: GDCM (Grassroots DICOM). A DICOM library
@rem
@rem  Copyright (c) 2006-2011 Mathieu Malaterre
@rem  All rights reserved.
@rem  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.
@rem
@rem     This software is distributed WITHOUT ANY WARRANTY; without even
@rem     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
@rem     PURPOSE.  See the above copyright notice for more information.
@rem

@rem generate GDCM release on Windows

@rem get tmpdir:
set TMPDIR=%TMP%\gdcm_release

set major=2
set minor=2
set patch=0
set version="%major%.%minor%.%patch%"

@rem use VCExpress 2005 for portability
call "%VS80COMNTOOLS%vsvars32.bat"

SET LIB=C:\Program Files\Microsoft SDKs\Windows\v7.0\Lib;%LIB%
SET INCLUDE=C:\Program Files\Microsoft SDKs\Windows\v7.0\Include;%INCLUDE%
@rem SET LIB=C:\Program Files\Microsoft SDKs\Windows\v7.0A\Lib;%LIB%
@rem SET INCLUDE=C:\Program Files\Microsoft SDKs\Windows\v7.0A\Include;%INCLUDE%
SET PATH=%PATH%;C:\Program Files\Git\bin
@rem SET PATH=%PATH%;C:\Program Files\Swig\swigwin-2.0.7

@rem prepare target dir
mkdir %TMPDIR%
mkdir %TMPDIR%\gdcm-build

copy config.win32 %TMPDIR%\gdcm-build\CMakeCache.txt

c:
cd %TMPDIR%
@rem git is itselft a batch:
call git clone --branch release git://gdcm.git.sourceforge.net/gitroot/gdcm/gdcm
cd gdcm
call git checkout "v%version%"
cd ..

cd %TMPDIR%\gdcm-build
cmake -G "NMake Makefiles" ..\gdcm > config.log 2>&1

@rem build gdcm
nmake > nmake.log 2>&1

@rem create NSIS installer
cpack -G NSIS > nsis.log 2>&1

@rem create binary zip
cpack -G ZIP > zip.log 2>&1

@rem create source zip
cpack -G ZIP --config CPackSourceConfig.cmake szip.log 2>&1
