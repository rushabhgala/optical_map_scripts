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
  TString fileName = "L1T_LAr_CDR_wPENenclosure_PEN.root";

  TFile *outFileMaGe = new TFile(fileName,"recreate");
  
  //TString dir = "/mnt/mjdDisk1/Majorana/users/nmcfadden/RooT/";
  //TString dir = "/home/nmcfadden/RooT/MaGe_RooT/";
  //TString dir = "/data4/legend/sim/l1000sims/XenonDoping/L200XeD/";
  TString dir = "/home/rushabh_gala/scripts/";
  
  TString inFileNameTH3Dint = "L1T_CDR_wPENEnclosure_penmap_222446-20240416.root";//"L1T_CDR_Alt1_BotSiPMs_LAr_2022_05_09.root";
  //TString inFileNameTH3Dintextended = "OpticalMapL1000PhysicalDetectorInterior1mTo3m.root";
  //TString inFileNameTH3Dext = "OpticalMapL1000PhysicalDetectorExtended3Hists.root";

  TH3F* mapint = nullptr;
  //TH3F* mapintextended = nullptr;
  //TH3F* mapext = nullptr;
  
  TFile* fileTH3Dint = TFile::Open(dir+inFileNameTH3Dint);
  fileTH3Dint->GetObject("ProbMapInterior",mapint);
  mapint->SetNameTitle("ProbMapInterior","ProbMapInterior");

  //TFile* fileTH3Dintextended = TFile::Open(dir+inFileNameTH3Dintextended);  
  //fileTH3Dintextended->GetObject("ProbMapInterior",mapintextended);  
  //mapintextended->SetNameTitle("ProbMapInteriorExtended","ProbMapInteriorExtended");


  //TFile* fileTH3Dext = TFile::Open(dir+inFileNameTH3Dext);
  //fileTH3Dext->GetObject("ProbMapInterior",mapext);
  //mapext->SetNameTitle("ProbMapExterior","ProbMapExterior");
  outFileMaGe->cd();
  mapint->Write();
  //mapintextended->Write();
  //mapext->Write();
  /////////////////outFileMaGe->Write();
  outFileMaGe->Close();
  cout<<"root -l "<<fileName<<endl;
}

