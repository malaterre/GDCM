# Script to patch dcmtk in order to compare gdcm version against it
sed -i -e 's/IJG_INT32/INT32/g' *.c
sed -i -e's/jinclude16.h/jinclude.h/g' *.c
sed -i -e's/jpeglib16.h/jpeglib.h/g' *.c
sed -i -e's/jlossy16.h/jlossy.h/g' *.c
sed -i -e's/mymain/mainPtr/g' *.c
