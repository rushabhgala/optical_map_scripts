#!/bin/bash -l
FIRST=0
LAST=1

read -p 'Start Run Number: ' FIRST
read -p 'Stop Run Number: ' LAST
for a in `seq $FIRST $LAST`
do
	JOBNAME=LAr_L1000_testInterior_$a.sh
	rm $JOBNAME
	echo creating job qsub -V -d /home/rushabh_gala/scripts/optical_map_scripts/macrosLAr_L1000_test  $JOBNAME
	echo "#!/bin/bash -l" >> $JOBNAME
	echo "source ~/.bashrc" >> $JOBNAME
   echo "/home/rushabh_gala/MaGe/bin/Linux-g++/./MaGe /home/rushabh_gala/scripts/optical_map_scripts/macrosLAr_L1000_test/LAr_L1000_test_$a.mac > Output_$a.log">>$JOBNAME
	qsub -V -d /home/rushabh_gala/scripts/optical_map_scripts/macrosLAr_L1000_test $JOBNAME -e /home/rushabh_gala/scripts/optical_map_scripts/macrosLAr_L1000_test/error/ -o /home/rushabh_gala/scripts/optical_map_scripts/macrosLAr_L1000_test/output/ -A legend

done