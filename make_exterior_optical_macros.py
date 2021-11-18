import os
import sys

#TODO set the path and the filename
#path = '/home/rushabh_gala/LGND200_14String_PENSims/OpticalSims/try/'
path = '/home/rushabh_gala/LGND1000_14String_Sims/OpticalSims/'
#filename = 'LArSiPlates' # naming convention generator-SiPlate material - anything different
filename = 'LArSiPlatesExteriorCorrectedNewGeom'#'PENPENPlatesCorrectlyModified'

use_own_MaGe = True #TODO set this to true or false

#TODO select a generator
#generator = 'LGNDPENParts'
#generator = 'LGNDLiquidArgon'
generator = 'LGND1TLiquidArgon'

#detector = 'LGND_200_14String'
detector = 'LGND_1T_Baseline'
binwidth = 50 #TODO set the bin width
try:
	os.mkdir(path+filename)
	os.mkdir(path+filename+'/error')
	os.mkdir(path+filename+'/output')
	t = 4000
	for i in range(0,160): #lower limit inclusive, upper limit exclusive
		t = t - binwidth
		#file = open(path+filename+'/'+filename+"Interior_%d.mac"%(i),"w")
		file = open(path+filename+'/'+filename+"_%d.mac"%(i),"w")
		file.write("/MG/manager/mglog routine\n")
		file.write("/MG/manager/seedWithUUID\n")
		file.write("/MG/processes/realm DarkMatter\n")
		file.write("/MG/processes/lowenergy false\n")
		file.write("/MG/processes/opticalOnly true\n")
		file.write("/MG/geometry/detector "+detector+ " \n")
		if (detector == 'LGND_200_14String'):
			file.write("/MG/L200/RadonShroudRadius 700 mm\n")
			file.write("/MG/L200/SetSensitiveVolumeArgon false\n")
			file.write("/MG/L200/SetSensitiveVolumeGermanium false\n")
			file.write("/MG/L200/SetSensitiveVolumeSiPM true\n")
			file.write("/MG/L200/SetSensitiveVolumePEN false\n")
			file.write("/MG/L200/MakeSiPlatePEN true\n") #TODO select whether SiPlate or PENPlate
		elif (detector == 'LGND_1T_Baseline'):
			file.write("/MG/L1000/SetSensitiveVolumeArgon false\n")
			file.write("/MG/L1000/SetSensitiveVolumeGermanium false\n")
			file.write("/MG/L1000/SetSensitiveVolumeSiPM false\n")
			file.write("/MG/L1000/SetSensitiveVolumePEN false\n")
			file.write("/MG/L1000/MakeSiPlatePEN false\n")
			file.write("/MG/L1000/SetSensitiveVolumeCryostat true\n")
			file.write("/MG/L1000/SetSensitiveVolumeCanShroud true\n")
		else:
			sys.exit()
		file.write("/run/initialize\n")
		file.write("/MG/eventaction/rootschema MCOpticalRun\n")
		file.write("/MG/eventaction/reportingfrequency 10\n")
		file.write("/MG/eventaction/rootfilename "+filename+"_%d.root\n"%(i))
		file.write("/MG/io/MCOpticalRun/SetSensitiveIDLabelScheme askGeom\n")
		file.write("/MG/io/MCOpticalRun/setRunID 001\n")
		file.write("/MG/io/MCOpticalRun/useTimeWindow true\n")
		file.write("/MG/io/MCOpticalRun/setTimeWindow 86400 second\n")
		file.write("/MG/io/MCOpticalRun/setNSteps 10000000000000\n")
		file.write("/MG/io/MCOpticalRun/MaxXYLimitForHistogram 3500\n")
		file.write("/MG/io/MCOpticalRun/MaxZLimitForHistogram 4000\n")
		file.write("/MG/generator/select "+generator+"\n")
		file.write("/MG/generator/"+generator+"/SetRadiusMin 0. mm\n")
		file.write("/MG/generator/"+generator+"/SetRadiusMax 3500. mm\n")  #TODO change this when you change between l200 and l1000
		file.write("/MG/generator/"+generator+"/SetHeight %f mm\n" %(t))
		file.write("/MG/generator/"+generator+"/SetCenterVector 0.0 0.0 0.0 mm\n")
		file.write("/MG/generator/"+generator+"/SetNParticles 1\n")
		file.write("/MG/generator/"+generator+"/SetBinWidth %d mm\n"%(binwidth))
		file.write("/MG/generator/LGND1TLiquidArgon/SetExternalMap true\n")
		file.write("/run/beamOn 500")

#creating the bash file to submit jobs
#no need to change anything here
	file2 = open(path+filename+'/'+"makeBashFilesForQsub.sh","w")
	file2.write("#!/bin/bash -l\n")
	file2.write("FIRST=0\n")
	file2.write("LAST=1\n")
	file2.write("\n")
	file2.write("read -p 'Start Run Number: ' FIRST\n")
	file2.write("read -p 'Stop Run Number: ' LAST\n")
	file2.write("for a in `seq $FIRST $LAST`\n")
	file2.write("do\n")
	file2.write("	JOBNAME="+filename+"Interior_$a.sh\n")
	file2.write("	rm $JOBNAME\n")
	file2.write("	echo creating job qsub -V -d "+path+filename+"  $JOBNAME\n")
	file2.write("	echo \"#!/bin/bash -l\" >> $JOBNAME\n")
	file2.write("	echo \"source ~/.bashrc\" >> $JOBNAME\n")
	#file2.write("	echo \"MaGe "+path+filename+"/"+filename+"Interior_$a.mac > Output_$a.log\">>$JOBNAME\n")
	if(use_own_MaGe == False):
		file2.write("	echo \"MaGe "+path+filename+"/"+filename+"_$a.mac > Output_$a.log\">>$JOBNAME\n")
	else:
		file2.write("   echo \"/home/rushabh_gala/MaGe/bin/Linux-g++/./MaGe "+path+filename+"/"+filename+"_$a.mac > Output_$a.log\">>$JOBNAME\n")
	file2.write("	qsub -V -d "+path+filename+" $JOBNAME -e "+path+filename+"/error/ -o "+path+filename+"/output/ -A legend\n") 
	file2.write("\n")
	file2.write("done")

	print("macros and bash file created at : ")
	print(path+filename)
	print("")
except OSError as error:
	print(error)
	print('Directory already present, choose a different name')
	print("")
