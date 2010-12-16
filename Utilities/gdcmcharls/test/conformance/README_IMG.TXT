JPEG-LS TEST IMAGES
===================

The images included in this package constitute the data set used for 
implementing the JPEG-LS conformance test as described in Section 8
and Annex E of the JPEG-LS standard document (ITU-T Rec. T.87|ISO/IEC 14495-1).

Test images:
------------
(See explanation of PPM and PGM formats below)

TEST8.PPM    - 8-bit color test image (photo+graphics+text+random data).
TEST8R.PGM   - "red" component of TEST8
TEST8G.PGM   - "green" component of TEST8
TEST8B.PGM   - "blue" component of TEST8
TEST8GR4.PGM - "green" component of TEST8, subsampled 4X in the vertical 
               direction
TEST8BS2.PGM - "blue" component of TEST8, subsampled 2X in both directions
TEST16.PGM   - 16-bit test gray-scale image (actually 12-bit)

Compressed images:
------------------
	T8CxEy.JLS  x=0,1,2  y=0,3
	   Image TEST8 compressed in color mode x with near-lossless error y
	   (y=0 means lossless).

	T16Ey.JLS            y=0,3
	   Image TEST16 compressed with near-lossless error y.

	T8SSE0.JLS
	T8SSE3.JLS
           Image TEST8 compressed in line-interleaved mode, with near-lossless
	   error 0 and 3 (resp.), and with color components subsampled 
	   as follows:
	   R: not subsampled (256 cols x 256 rows)
	   G: subsampled 4x in the vertical direction (256 cols x 64 rows)
	   B: subsampled 2x in both directions (128 cols x 128 rows)

	T8NDE0.JLS
	T8NDE3.JLS
           Image TEST8 compressed in line-interleaved mode, with near-lossless
	   error 0 and 3 (resp.), and with NON-DEFAULT parameters T1=T2=T3=9,
	   RESET=31.

The compressed images are provided to help testers/developers debug their 
JPEG-LS implementations. The test images contain a mixture of data that will
exercise many paths in the compression/decompression algorithms. There is
no guarantee, however, that every path of the algorithm is tested.
THE TEST IMAGES SHOULD NOT BE USED TO BENCHMARK COMPRESSION CAPABILITY.
THEY ARE DESIGNED TO BE "HARD" ON THE JPEG-LS COMPRESSOR.  JPEG-LS
MAY DO WORSE THAN YOUR FAVORITE COMPRESSOR ON THE TEST IMAGES.

All compressed images have standard JPEG-LS headers (which follow the
standard JPEG marker syntax).  All compressed images were produced using 
default parameters, except for T8NDE0.JLS and T8NDE3.JLS as noted above.



PPM and PGM INPUT IMAGE FORMATS
-------------------------------

Uncompressed test images images are in either PGM (grayscale) or 
PPM (3-color) format.  This is of course NOT part of the JPEG-LS 
standard.

These formats have an ASCII header consisting of 3 lines of the 
following form

* PGM (single component):

    P5
    cols rows
    maxval

* PPM (3 components)

    P6
    cols rows
    maxval

    
For PGM, the header is followed by cols*rows samples in binary 
format, where cols and rows are the number of columns and rows, 
respectively.  A test image "cmpnd2g.pgm" is included in the 
archive. Samples have 8 bits if maxval < 256, or 16 bits if 
256 <= maxval < 65536. 

For PPM, the header is followed by cols*rows TRIPLETS of symbols in
binary format. Each symbol in a triplet represents a color component
value (viewers usually interpret PPM triplets as RGB).
