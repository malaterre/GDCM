This directory contains a subset of the JPEG-LS Public Domain Code.
ISO/IEC  JPEG-LS "The emerging lossless/near-lossless compression standard for
continuous-tone still images"

UBC's JPEG-LS Codec Implementation
http://kt.ijs.si/aleks/jpeg-ls/mirror.htm

The software is available via anonymous ftp at
ftp://dspftp.ece.ubc.ca/pub/jpeg-ls. Version 1.1 supports only the lossless part
of the standard, while version 2 supports the lossless and near lossless mode of
JPEG-LS. Version 2 also supports color and gray level images. Please note that
version 2 is based on HP's LOCO-I/JPEG-LS implementation V.0.90. 

We only include enough of distribution to build libjpegls. We do not include
either the standard  executables that come with JPEG-LS (JLSEncoder.exe), or the
sample dataset. Furthermore, the standard  libjpegls build process is replaced
with a CMake build process.

We'd like to thank the UBC for releasing an open source JPEG-LS implementation

Modifications
-------------

- modification were made so that compilation with gcc -Wall flags passes without warnings
- remove all explicit tabs and replace by proper amount of spaces
- remove all hardcoded makefile (hpux, vc)
