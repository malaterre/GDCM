# Script to patch dcmtk in order to compare gdcm version against it
sed -i -e 's/IJG_INT32/INT32/g' *.c *.h
sed -i -e's/jinclude[8|12|16].h/jinclude.h/g' *.c
sed -i -e's/jpeglib[8|12|16].h/jpeglib.h/g' *.c
sed -i -e's/jlossy[8|12|16].h/jlossy.h/g' *.c
sed -i -e's/jmemsys[8|12|16].h/jmemsys.h/g' *.c
sed -i -e's/jdct[8|12|16].h/jdct.h/g' *.c
sed -i -e's/jversion[8|12|16].h/jversion.h/g' *.c
sed -i -e's/jerror[8|12|16].h/jerror.h/g' *.c
sed -i -e's/jdhuff[8|12|16].h/jdhuff.h/g' *.c
sed -i -e's/jlossls[8|12|16].h/jlossls.h/g' *.c
sed -i -e's/jchuff[8|12|16].h/jchuff.h/g' *.c
sed -i -e's/mymain/mainPtr/g' *.c
