#!/bin/sh

cd $HOME/Dashboards/GDCMScripts && git pull

echo "Starting dcmqrscp"

rm -rf /tmp/GDCM_STORE
mkdir /tmp/GDCM_STORE
HOSTNAME=`hostname`
sed -e "s/HOSTNAME/${HOSTNAME}/g" ./dcmqrscp.cfg.in > /tmp/dcmqrscp.cfg
dcmqrscp --allow-shutdown -v -d -c /tmp/dcmqrscp.cfg 5678 &

# nightly
for i in `ls zorglub-*.cmake`; do
  ctest -S $i -V -O $i.log
done

echo "Stopping dcmqrscp"

HOSTIP=`hostname -I`
termscu --aetitle GDCMDASH --call GDCM_STORE $HOSTIP 5678
