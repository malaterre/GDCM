#!/bin/sh

cd $HOME/Dashboards/GDCMScripts && git pull

#export PATH=$HOME/Software/cmake-2.8.2-Linux-i386/bin:$PATH:$HOME/local/bin
#export JAVA_HOME=/opt/jdk

echo "Starting dcmqrscp"

rm -rf /tmp/GDCM_STORE
mkdir /tmp/GDCM_STORE
HOSTNAME=`hostname`
sed -e "s/HOSTNAME/${HOSTNAME}/g" ./dcmqrscp.cfg.in > /tmp/dcmqrscp.cfg
dcmqrscp --allow-shutdown -v -d -c /tmp/dcmqrscp.cfg 5678 &

#ctest -S zorglub-gcc4-64-makefiles.cmake -V -O zorglub-gcc4-64-makefiles.log
ctest -S zorglub-gcc43-64-makefiles.cmake -V -O zorglub-gcc43-64-makefiles.log
ctest -S zorglub-gcc-64-makefiles-dcmqrscp.cmake -V -O zorglub-gcc-64-makefiles-dcmqrscp.log
ctest -S zorglub-gcc-64-makefiles.cmake -V -O zorglub-gcc-64-makefiles.log
ctest -S zorglub-gcc-64-makefiles-release.cmake -V -O zorglub-gcc-64-makefiles-release.log
ctest -S zorglub-gcc-64-makefiles-valgrind.cmake -V -O zorglub-gcc-64-makefiles-valgrind.log
#ctest -S zorglub-gcc-snap-64-makefiles.cmake -V -O zorglub-gcc-snap-64-makefiles.log
#ctest -S zorglub-gcc-64-makefiles-kwstyle.cmake -V -O zorglub-gcc-64-makefiles-kwstyle.log

echo "Stopping dcmqrscp"

termscu --aetitle GDCMDASH --call GDCM_STORE $HOSTNAME 5678

