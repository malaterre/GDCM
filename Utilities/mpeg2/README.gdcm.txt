This directory contains a subset of the MPEG Software Simulation Group 
- Motion Picture Experts Group file interchange format (version 1) -.
We only include enough of distribution to build libmpeg2.  We do not
 include the subdir par, doc and verify. We do not include either the standard 
executables that come with libmpeg2 (verify, mpeg2dec, mpeg2enc). Furthermore, the standard 
libmpeg2 build process is replaced with a CMake build process.

We'd like to thank the MPEG Software Simulation Group for distributing a public MPEG IO library.

Modifications
-------------

- modification were made so that compilation with gcc -Wall flags passes without warnings
- remove all explicit tabs and replace by proper amount of spaces
- rename toplevel Makefile to LICENSE in order to keep copyright and to avoid conflict when doing insource built
