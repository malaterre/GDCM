This directory contains a subset of the CharLS project

See:
http://charls.codeplex.com
https://github.com/team-charls/charls

This version corresponds to the code from the "1.x-master" branch on github,
specifically commit 5650402cb204161cf03b926267ed5b24f2626e60:

https://github.com/team-charls/charls/tree/1.x-master
https://github.com/team-charls/charls/commit/5650402cb204161cf03b926267ed5b24f2626e60

The 1.x-master branch is used becase it suppports C++03.  The master branch requires C++11 (which GDCM does not require).

Project Description
An optimized implementation of the JPEG-LS standard for lossless and near-lossless image compression. JPEG-LS is a low-complexity standard that matches JPEG 2000 compression ratios. In terms of speed, CharLS outperforms open source and commercial JPEG LS implementations.

About JPEG-LS
JPEG-LS (ISO-14495-1/ITU-T.87) is a standard derived from the Hewlett Packard LOCO algorithm. JPEG LS has low complexity (meaning fast compression) and high compression ratios, similar to JPEG 2000. JPEG-LS is more similar to the old Lossless JPEG than to JPEG 2000, but interestingly the two different techniques result in vastly different performance characteristics.
Wikipedia on lossless JPEG and JPEG-LS: http://en.wikipedia.org/wiki/Lossless_JPEG

Legal
The code in this project is available through a BSD style license, allowing use of the code in commercial closed source applications if you wish. All the code in this project is written from scratch, and not based on other JPEG-LS implementations.


We only include enough of distribution to build the charls library.


Modifications
-------------

- use only contents of src folder
- exclude the following files:
 - CharLS_VS2015.vcxproj
 - CharLS_VS2015.vcxproj.filters
 - charls.def
 - charls.rc
- there are zero code modifications, we match upstream exactly
