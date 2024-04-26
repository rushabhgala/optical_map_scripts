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
  TString fileName = "L60_LAr_OpticalMap_InternalAndExternal.root";

  TFile *outFileMaGe = new TFile(fileName,"recreate");
  
  //TString dir = "/mnt/mjdDisk1/Majorana/users/nmcfadden/RooT/";
  //TString dir = "/home/nmcfadden/RooT/MaGe_RooT/";
  //TString dir = "/data8/legend/L200_Sims/L200_OpticalSims_2022/L200_60kg_Fibers/";
  TString dir = "/home/rushabh_gala/scripts/";
  
  //TString inFileNameTH3D = "OpticalMapLEGEND200.4e9_2mm.TwoFiber.5Rows_RawProb.root";
  //TString inFileNameTH3D = "OpticalMapLEGEND200.2.032e+09.19String.twoFiber.NO_HV.5mm.Radon500.root";
  //TString inFileNameTH3D = "OpticalMapLEGEND200.2e9.14String.Radon500.root";
  //TString inFileNameTH3D = "LGND200_14_OpticalMap.root";
  //TString inFileNameTH3D = "OpticalMapPENPlate.root";
  //TString inFileNameTH3Dint = "OML1TReflector14rotation.root";
  TString inFileNameTH3Dint = "MaGe.124714-20220912.root";
  //TString inFileNameTH3D = "OpticalMapLEGEND200.4e8.14String.25mm.root";
  //TString inFileNameTH2D = "OpticalMapLEGEND200.4e9_50mm.1e7.Exterior.root";
  //TString inFileNameTH2D = "LGND200_14_OpticalMapExterior.root";
  TString inFileNameTH3Dext = "MaGe.85705-20220909.root";
  //TString inFileNameTH2D = "OpticalMapLEGEND200.Exterior.14String.5mm.2e8.Radon500.root";
  //TString inFileNameTH2D = "OpticalMapLEGEND200.Exterior.19String.5mm.2e8.Radon500.root";

  TH3D* mapint = nullptr;  //change between TH3D/TH3F for l200/l1000
  TH3D* mapext = nullptr;
  TFile* fileTH3Dint = TFile::Open(dir+inFileNameTH3Dint);
  //fileTH3D->GetObject("EnergyMapUnscaled",h3D);
  fileTH3Dint->GetObject("ProbMapInterior",mapint);
  cout << "test2" << endl;
  mapint->SetNameTitle("ProbMapInterior","ProbMapInterior");
  cout << "test3" << endl;
  TFile* fileTH3Dext = TFile::Open(dir+inFileNameTH3Dext);
  fileTH3Dext->GetObject("ProbMapInterior",mapext);
  mapext->SetNameTitle("ProbMapExterior","ProbMapExterior");
  outFileMaGe->cd();
  mapint->Write();
  mapext->Write();
  //outFileMaGe->Write();
  outFileMaGe->Close();
  cout<<"root -l "<<fileName<<endl;
}

