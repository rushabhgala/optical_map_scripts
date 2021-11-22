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
  TString fileName = "L1000_PEN_LightCompare_new.root";

  TFile *outFileMaGe = new TFile(fileName,"recreate");
  
  //TString dir = "/mnt/mjdDisk1/Majorana/users/nmcfadden/RooT/";
  //TString dir = "/home/nmcfadden/RooT/MaGe_RooT/";
  //TString dir = "/data4/legend/sim/l1000sims/XenonDoping/L200XeD/";
  TString dir = "/home/rushabh_gala/scripts/";
  
  //TString inFileNameTH3D = "OpticalMapLEGEND200.4e9_2mm.TwoFiber.5Rows_RawProb.root";
  //TString inFileNameTH3D = "OpticalMapLEGEND200.2.032e+09.19String.twoFiber.NO_HV.5mm.Radon500.root";
  //TString inFileNameTH3D = "OpticalMapLEGEND200.2e9.14String.Radon500.root";
  //TString inFileNameTH3D = "LGND200_14_OpticalMap.root";
  //TString inFileNameTH3D = "OpticalMapPENPlate.root";
  //TString inFileNameTH3Dint = "OML1TReflector14rotation.root";
  TString inFileNameTH3Dint = "L1000_PENNew_LightCompare.115036-20210712.root";
  //TString inFileNameTH3D = "OpticalMapLEGEND200.4e8.14String.25mm.root";
  //TString inFileNameTH2D = "OpticalMapLEGEND200.4e9_50mm.1e7.Exterior.root";
  //TString inFileNameTH2D = "LGND200_14_OpticalMapExterior.root";
  //////////TString inFileNameTH3Dext = "OpticalMapL1000Ext.root";
  //TString inFileNameTH2D = "OpticalMapLEGEND200.Exterior.14String.5mm.2e8.Radon500.root";
  //TString inFileNameTH2D = "OpticalMapLEGEND200.Exterior.19String.5mm.2e8.Radon500.root";

  TH3F* mapint = nullptr;
  //////////TH3F* mapext = nullptr;
  TFile* fileTH3Dint = TFile::Open(dir+inFileNameTH3Dint);
  //fileTH3D->GetObject("EnergyMapUnscaled",h3D);
  fileTH3Dint->GetObject("ProbMapInterior",mapint);
  cout << "test2" << endl;
  mapint->SetNameTitle("ProbMapInterior","ProbMapInterior");
  cout << "test3" << endl;
  //////////TFile* fileTH3Dext = TFile::Open(dir+inFileNameTH3Dext);
  //////////fileTH3Dext->GetObject("ProbMapInterior",mapext);
  //////////mapext->SetNameTitle("ProbMapExterior","ProbMapExterior");
  outFileMaGe->cd();
  mapint->Write();
  //////////mapext->Write();
  //outFileMaGe->Write();
  outFileMaGe->Close();
  cout<<"root -l "<<fileName<<endl;
}

