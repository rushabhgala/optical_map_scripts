#include "MGTMCEventSteps.hh"
#include "MGTMCStepData.hh"
#include "MGTMCRun.hh"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TString.h"
#include "TCanvas.h"
#include "TH3D.h"
#include "TH2D.h"
#include "TProof.h"
#include "TROOT.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TObject.h"
#include "TString.h"
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <TDatime.h>
#include <TNtuple.h>
#include <unordered_map>
#include <map>

using namespace std;

inline bool fileExist (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}


int main(){
  cout << "test1i" << endl;

  //output file
  ofstream outputfile1, outputfile2, outputfileRatio;
  outputfile1.open("LAr_CDR_Alt1_340.txt");
  outputfile2.open("LAr_CDR_Baseline_340.txt");
  outputfileRatio.open("Ratio_Alt1_to_Baseline_340.txt");
  //outputfile << "test2" << endl;

  TString dir = "/home/rushabh_gala/scripts/";
  TString inFileName1 = "L1T_CDR_Alt1_LAr_All3Maps_2022_03_28.root";
  TString inFileName2 = "L1T_LAr_CDR_2022_02_12.root";

  TH3F* map_1 = nullptr;
  TH3F* map_2 = nullptr; 

  //first file
  TFile* fileTH3D_1 = TFile::Open(dir+inFileName1);
  fileTH3D_1->GetObject("ProbMapInterior",map_1);
  map_1->SetNameTitle("ProbMapInterior","ProbMapInterior");

  //second file
  TFile* fileTH3D_2 = TFile::Open(dir+inFileName2);
  fileTH3D_2->GetObject("ProbMapInterior",map_2);
  map_2->SetNameTitle("ProbMapInterior","ProbMapInterior");

	int i,j,k,x,y,z;
	k = 340;
	z = 5*k-1000;
	//x = 5*i - 1500;
	//y = 5*j - 1500;
	Double_t sum1 =0.0;
	Double_t sum2 =0.0;
    cout << map_1->GetNbinsX() << endl;
   	for (i = 0; i < map_1->GetNbinsX(); ++i) {
        for (j = 0; j < map_1->GetNbinsY(); ++j) {
			x = 5*i - 1500;
			y = 5*j - 1500;
        	sum1 = sum1 + map_1->GetBinContent(map_1->FindBin(x,y,z));
        	sum2 = sum2 + map_2->GetBinContent(map_2->FindBin(x,y,z));
	 	}
	 	outputfile1 << sum1/map_1->GetNbinsY() << "\t" << x << "\t" << y << "\t" << z << endl;
	 	outputfile2 << sum2/map_2->GetNbinsY() << "\t" << x << "\t" << y << "\t" << z << endl;
		outputfileRatio << ((sum1/map_1->GetNbinsY())+0.00000001)/((sum2/map_2->GetNbinsY())+0.00000001) << "\t" << x << "\t" << y << "\t" << z << endl;
	 	sum1 = 0.0;
	 	sum2 = 0.0;
	}








return 0;
}

