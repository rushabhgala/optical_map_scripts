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
  ofstream outputfilePEN, outputfileSilicon, outputfileRatio;
  outputfilePEN.open("LAr_CDR_Baseine.txt");
  outputfileSilicon.open("LAr_CDR_Alt1.txt");
  outputfileRatio.open("Ratio_Alt1_to_Baseline.txt");
  //outputfile << "test2" << endl;

  TString dir = "/home/rushabh_gala/scripts/";
  TString inFileName1 = "L1T_CDR_Alt1_LAr_All3Maps_2022_03_28.root";
  TString inFileName2 = "L1T_LAr_CDR_2022_02_12.root";

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

  /*Double_t x = 5*i - 1500;
  Double_t y = 5*j - 1500;
  Double_t z = 5*k - 1000;*/  
  
  //int x = map->GetNbinsX();
  //int y = map->GetNbinsY();
  //int z = map->GetNbinsZ();

  //for(k=0; k < map_Si->GetNbinsZ(); k++)
  for(k=100; k <= 100; k++) //180-187 //158-179
  {
    Double_t z = 5*k - 1000;
    for(j= 0; j < map_Si->GetNbinsX(); j++)
    {
      Double_t y = 5*j - 1500;
      Double_t ZY_Si;// = 0.0;
      Double_t ZY_PEN;// = 0.0;   
      for(i= 0; i < map_Si->GetNbinsY(); i++)
      {   
        Double_t x = 5*i - 1500;
        
        //if(z < -60 && z > -70) {
        //ZY += i;
        //outputfile << x << "\t" << y << "\t" << z << endl;
          ZY_Si = map_Si->GetBinContent(map_Si->FindBin(x,y,z));
          ZY_PEN = map_PEN->GetBinContent(map_PEN->FindBin(x,y,z));
          outputfilePEN << ((ZY_PEN)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
          outputfileSilicon << ((ZY_Si)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
          outputfileRatio << ((ZY_PEN)+0.0000001)/((ZY_Si)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
          //outputfile << ZY << "\t" << z << endl;
       // }
      }
      //outputfilePEN << ((ZY_PEN/600)+0.0000001) << "\t" << y << "\t" << z << endl;
      //outputfileSilicon << ((ZY_Si/600)+0.0000001) << "\t" << y << "\t" << z << endl;
    }
  }


}

