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
  ofstream outputfilePEN0, outputfilePEN1, outputfilePEN2, outputfilePEN3, outputfilePEN4, outputfilePEN5, outputfilePEN6, outputfilePEN7, outputfileSilicon, outputfileRatio;
  outputfilePEN0.open("PEN_48_0_new.txt");
  outputfilePEN1.open("PEN_48_5_new.txt");
  outputfilePEN2.open("PEN_48_10_new.txt");
  outputfilePEN3.open("PEN_48_15_new.txt");
  outputfilePEN4.open("PEN_48_20_new.txt");
  outputfilePEN5.open("PEN_48_25_new.txt");
  outputfilePEN6.open("PEN_48_30_new.txt");
  outputfilePEN7.open("PEN_48_35_new.txt");
  outputfileSilicon.open("Silicon_CanOnly_0.txt");
  outputfileRatio.open("Ratio_Ge.txt");
  //outputfile << "test2" << endl;

  TString dir = "/home/rushabh_gala/scripts/";
  TString inFileName1 = "L1000_Silicon_LightCompare.root";
  TString inFileName2 = "LAr_PEN_48.root";

  TH3F* map_Si = nullptr;
  TH3F* map_PEN = nullptr; 

  //Silicon map
  TFile* fileTH3D_Si = TFile::Open(dir+inFileName1);
  fileTH3D_Si->GetObject("ProbMapInterior",map_Si);
  map_Si->SetNameTitle("ProbMapInterior","ProbMapInterior");

  //PEN map
  TFile* fileTH3D_PEN = TFile::Open(dir+inFileName2);
  fileTH3D_PEN->GetObject("ProbMapInterior",map_PEN);
  map_PEN->SetNameTitle("ProbMapInterior","ProbMapInterior");
 
  int i,j,k;
 
  Double_t ZY_Si;// = 0.0;
  Double_t ZY_PEN;// = 0.0;   

  //for(k=0; k < map_Si->GetNbinsZ(); k++)
  for(k=180; k <= 187; k++) //180-187 //158-179
  {
    for(j= 0; j < map_Si->GetNbinsX(); j++)
    {
      Double_t ZY_Si = 0.0;
      Double_t ZY_PEN = 0.0;
      for(i= 0; i < map_Si->GetNbinsY(); i++)
      {   
          Double_t x = 5*i - 1500;
          Double_t y = 5*j - 1500;
          Double_t z = 5*k - 1000;
          if(((((pow((x-1000),2))+(pow(y,2))) < pow(300,2)) && (((pow((x-1000),2))+(pow(y,2))) > pow(200,2))))
          {
            ZY_Si = map_Si->GetBinContent(map_Si->FindBin(x,y,z));
            ZY_PEN = map_PEN->GetBinContent(map_PEN->FindBin(x,y,z));      
            outputfileSilicon << ((ZY_Si)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
			if(k ==180)
				outputfilePEN0 << ((ZY_PEN)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
			else if(k ==181)
				outputfilePEN1 << ((ZY_PEN)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
			else if(k ==182)
				outputfilePEN2 << ((ZY_PEN)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
			else if(k ==183)
				outputfilePEN3 << ((ZY_PEN)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
			else if(k ==184)
				outputfilePEN4 << ((ZY_PEN)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
			else if(k ==185)
				outputfilePEN5 << ((ZY_PEN)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
			else if(k ==186)
				outputfilePEN6 << ((ZY_PEN)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
			else if(k ==187)
				outputfilePEN7 << ((ZY_PEN)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
			//if(ZY_PEN > 0.00001) {cout << ZY_PEN << endl;}
          }
      }
    }
  }


}

