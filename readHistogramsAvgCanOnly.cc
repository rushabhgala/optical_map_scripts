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
  outputfile1.open("LAr_CDR_Alt1.txt");
  outputfile2.open("LAr_CDR_Baseline.txt");
  outputfileRatio.open("Ratio_Alt1_to_Baseline.txt");
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
 
  int i,j,k;
 
  Double_t ZY_1;// = 0.0;
  Double_t ZY_2;// = 0.0;   

  //for(k=0; k < map_Si->GetNbinsZ(); k++)
  for(k=20; k <= 20; k++) //180-187 //158-179
  {
    for(j= 0; j < map_1->GetNbinsX(); j++)
    {
      Double_t ZY_1 = 0.0;
      Double_t ZY_2 = 0.0;
      Double_t ZY_1_avg = 0.0;
      Double_t ZY_2_avg = 0.0;
	  int z = 5*k - 1000;
      int x = 5*i - 1500;
      int y = 5*j - 1500;
      for(i= 0; i < map_1->GetNbinsY(); i++)
      {   
          //Double_t x = 5*i - 1500;
          //Double_t y = 5*j - 1500;
          //Double_t z = 5*k - 1000;
          //if(((((pow((x-1000),2))+(pow(y,2))) < pow(300,2)) && (((pow((x-1000),2))+(pow(y,2))) > pow(200,2))))
          //if((((pow((x-1000),2))+(pow(y,2))) < pow(450,2))) //scan only the detector array 1
          //{
            ZY_1 = map_1->GetBinContent(map_1->FindBin(x,y,z));
            ZY_2 = map_2->GetBinContent(map_2->FindBin(x,y,z));
			cout << x <<","<< y <<","<< z <<"," << endl;      
            //outputfile1 << ((ZY_1)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
            //outputfile2 << ((ZY_2)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
			//if(ZY_PEN > 0.00001) {cout << ZY_PEN << endl;}
			//outputfileRatio << ((ZY_1)+0.0000001)/((ZY_2)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl; 
          //}
      }
      ZY_1_avg = ZY_1/map_1->GetNbinsY();
      ZY_2_avg = ZY_2/map_2->GetNbinsY();
	  outputfile1 << ZY_1_avg << "\t" << x << "\t" << y << "\t" << z << endl;
      outputfile2 << ZY_2_avg << "\t" << x << "\t" << y << "\t" << z << endl;
      outputfileRatio << (ZY_1_avg+0.00000001)/(ZY_2_avg+0.00000001) << "\t" << x << "\t" << y << "\t" << z << endl;
    }
  }


}

