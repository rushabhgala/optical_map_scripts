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
  TString fileName = "OpticalMapL200.SiPMArray.14String.5mm.root";

  TFile *outFileMaGe = new TFile(fileName,"recreate");
  
  //TString dir = "/mnt/mjdDisk1/Majorana/users/nmcfadden/RooT/";
  //TString dir = "/home/nmcfadden/RooT/MaGe_RooT/";
  //TString dir = "/data4/legend/sim/l1000sims/XenonDoping/L200XeD/";
  TString dir = "/home/rushabh_gala/scripts/";
  
  //TString inFileNameTH3D = "OpticalMapLEGEND200.4e9_2mm.TwoFiber.5Rows_RawProb.root";
  //TString inFileNameTH3D = "OpticalMapLEGEND200.2.032e+09.19String.twoFiber.NO_HV.5mm.Radon500.root";
  //TString inFileNameTH3D = "OpticalMapLEGEND200.2e9.14String.Radon500.root";
  //TString inFileNameTH3D = "LGND200_14_OpticalMap.root";
  TString inFileNameTH3D = "OpticalMapL1000.root";
  //TString inFileNameTH3D = "OpticalMapLEGEND200.4e8.14String.25mm.root";
  //TString inFileNameTH2D = "OpticalMapLEGEND200.4e9_50mm.1e7.Exterior.root";
  //TString inFileNameTH2D = "LGND200_14_OpticalMapExterior.root";
  TString inFileNameTH2D = "OpticalMapL1000Ext.root";
  //TString inFileNameTH2D = "OpticalMapLEGEND200.Exterior.14String.5mm.2e8.Radon500.root";
  //TString inFileNameTH2D = "OpticalMapLEGEND200.Exterior.19String.5mm.2e8.Radon500.root";

  TH3D * h3D;
  TH3D* h2D;
  TFile* fileTH3D = TFile::Open(dir+inFileNameTH3D);
  //fileTH3D->GetObject("EnergyMapUnscaled",h3D);
  fileTH3D->GetObject("ProbMapExterior",h3D);
  h3D->SetNameTitle("ProbMapInterior","ProbMapInterior");
  TFile* fileTH2D = TFile::Open(dir+inFileNameTH2D);
  fileTH2D->GetObject("ProbMapExterior",h2D);
  h2D->SetNameTitle("ProbMapExterior","ProbMapExterior");
  outFileMaGe->cd();
  h3D->Write();
  h2D->Write();
  outFileMaGe->Write();
  outFileMaGe->Close();
  cout<<"root -l "<<fileName<<endl;
}

