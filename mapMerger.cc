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
  TString fileName = "L1000_CDR_LAr_internal_and_external.root";

  TFile *outFileMaGe = new TFile(fileName,"recreate");
  

  TString dir = "/home/rushabh_gala/scripts/";
  TString inFileNameTH3D = "L1T_CDR_internal_lar_merged_bottom_included.root";
  TString inFileNameTH2D = "L1T_CDR_external_lar_cryostat_164104-20240216.root";

  TH3F * h3D;
  TH3F* h2D;
  TFile* fileTH3D = TFile::Open(dir+inFileNameTH3D);
  //fileTH3D->GetObject("EnergyMapUnscaled",h3D);
  fileTH3D->GetObject("ProbMapInterior",h3D);
  h3D->SetNameTitle("ProbMapInterior","ProbMapInterior");
  TFile* fileTH2D = TFile::Open(dir+inFileNameTH2D);
  fileTH2D->GetObject("LAr_OpticalMap_RZ",h2D);
  h2D->SetNameTitle("LAr_OpticalMap_RZ","LAr_OpticalMap_RZ");
  outFileMaGe->cd();
  h3D->Write();
  h2D->Write();
  outFileMaGe->Write();
  outFileMaGe->Close();
  cout<<"root -l "<<fileName<<endl;
}
