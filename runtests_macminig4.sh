#!/bin/sh

cd $HOME/Dashboards/GDCMScripts && git pull

#ctest -S zorglub-gcc-snap-64-makefiles.cmake -V -O zorglub-gcc-snap-64-makefiles.log
ctest -S macminig4-gcc-makefiles.cmake            -V -O macminig4-gcc-makefiles.log
ctest -S macminig4-gcc-64-makefiles-kwstyle.cmake -V -O macminig4-gcc-64-makefiles-kwstyle.log

# Nightly doxygen:
cd $HOME/Dashboards/MyTests/gdcm-nightly-kwstyle && touch Utilities/doxygen/Doxyfile
cd $HOME/Dashboards/MyTests/gdcm-nightly-kwstyle && make
cd $HOME/Dashboards/MyTests/gdcm-nightly-kwstyle && make rebuild_cache && make vtkgdcmDoxygenDoc
rsync --quiet -av Utilities/doxygen/gdcm-2.3.0-doc.tar.gz malat,gdcm@web.sourceforge.net:htdocs
rsync --quiet -av -r Utilities/doxygen/html malat,gdcm@web.sourceforge.net:htdocs

# Nightly PDF Doxygen
cd $HOME/Dashboards/MyTests/gdcm-nightly-kwstyle/Utilities/doxygen/latex
rsync --quiet -av gdcm-2.3.0.pdf malat,gdcm@web.sourceforge.net:htdocs

# mirror on github:
cd $HOME/Dashboards/MyTests/gdcm.git
git remote update
git push --mirror git@github.com:malaterre/GDCM.git


cd $HOME/Dashboards/MyTests/tifffile
./getorig.sh
