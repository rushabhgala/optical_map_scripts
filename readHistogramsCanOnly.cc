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
  outputfilePEN.open("PEN_Space_all.txt");
  outputfileSilicon.open("Silicon_Space_all.txt");
  outputfileRatio.open("Ratio_Ge.txt");
  //outputfile << "test2" << endl;

  TString dir = "/home/rushabh_gala/scripts/";
  TString inFileName1 = "L1000_Silicon_LightCompare.root";
  TString inFileName2 = "L1000_PEN_LightCompare.root";

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
          if(((((pow((x-1000),2))+(pow(y,2))) < pow(450,2)) && (((pow((x-1000),2))+(pow(y,2))) > pow(300,2))) || ((((pow((x-1000),2))+(pow(y,2))) < pow(200,2))))
          {
            ZY_Si = map_Si->GetBinContent(map_Si->FindBin(x,y,z));
            ZY_PEN = map_PEN->GetBinContent(map_PEN->FindBin(x,y,z));
          //}
          //ZY_Si = map_Si->GetBinContent(map_Si->FindBin(x,y,z));
          //ZY_PEN = map_PEN->GetBinContent(map_PEN->FindBin(x,y,z));
          
          
            outputfileSilicon << ((ZY_Si)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
            outputfilePEN << ((ZY_PEN)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
          //outputfile << ZY << "\t" << z << endl;
          }
      }
      //outputfilePEN << ((ZY_PEN/600)+0.0000001) << "\t" << y << "\t" << z << endl;
      //outputfileSilicon << ((ZY_Si/600)+0.0000001) << "\t" << y << "\t" << z << endl;
      //outputfileRatio << ((ZY_PEN)+0.0000001)/((ZY_Si)+0.0000001) << "\t" << x << "\t" << y << "\t" << z << endl;
    }
  }


}

