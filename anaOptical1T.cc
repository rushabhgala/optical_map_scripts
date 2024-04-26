#include "MGTMCEventSteps.hh"
#include "MGTMCStepData.hh"
#include "MGTMCRun.hh"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TString.h"
#include "TCanvas.h"
#include "TH3F.h"
#include "TH2F.h"
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

  TDatime time;
  //time 12:36:26 133626
  ///date 24/12/1997 19971224
  TString fileName = TString("L1T_CDR_wPENEnclosure_penmap_")+to_string(time.GetTime())+TString("-")+to_string(time.GetDate())+TString(".root");
  TFile *outFileMaGe = new TFile(fileName,"recreate");
//  TFile *outFileOpticalMap = new TFile(TString("OpticalMap.")+to_string(time.GetTime())+TString("-")+to_string(time.GetDate())+TString(".root"),"recreate");
  
  TNtuple *ntpleStepSiPM = new TNtuple("L1000_OpticalMap","L1000_OpticalMap","event:edep:ke:x:y:z:r:primX:primY:primZ:primR:primTheta");

  std::map<std::vector<Int_t>,Double_t> prob_map;
  //Double_t gridSpacing = 2;//*mm
  Double_t QE = 0.14;//LEGEND 0.164; //0.14 for 128, 0.24 for 175
  Double_t gridSpacing = 5;//*mm
  Double_t maxX = 1000.,minX = -1000.,maxY= 1000.,minY = -1000,maxZ= 2000,minZ = -2000,minR = 0, maxR = 1000.;
  //Double_t maxX = 700.,minX = -700.,maxY=700.,minY = -700,maxZ= 845,minZ = -850,minR = 300, maxR = 700.;
  Int_t nbinsX = (maxX-minX)/gridSpacing,nbinsY = (maxY-minY)/gridSpacing,nbinsZ = (maxZ-minZ)/gridSpacing, nbinsR = (maxR-minR)/gridSpacing;
  TH3F* hMap = new TH3F("ProbMapInterior","ProbMapInterior",nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  TH3F* hMapRaw = new TH3F("ProbMapInterior_Raw","ProbMapInterior_Raw",nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  TH3F* hMapScaled = new TH3F("ProbMapInterior_Scaled","ProbMapInterior_Scaled",nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsZ,minZ,maxZ);

  TH2F* h2DMapRZ = new TH2F("LAr_OpticalMap_RZ","LAr_OpticalMap_RZ",nbinsR,minR,maxR,nbinsZ,minZ,maxZ);
  TH2F* h2DMapRZRaw = new TH2F("LAr_OpticalMap_RZRaw","LAr_OpticalMap_RZRaw",nbinsR,minR,maxR,nbinsZ,minZ,maxZ);
  TH2F* h2DMapRZScaled = new TH2F("LAr_OpticalMap_RZScaled","LAr_OpticalMap_RZScaled",nbinsR,minR,maxR,nbinsZ,minZ,maxZ);

  TH2F* h2DMapXY = new TH2F("LAr_OpticalMap_XY","LAr_OpticalMap_XY",nbinsX,minX,maxX,nbinsY,minY,maxY);
  TH2F* h2DMapXYRaw = new TH2F("LAr_OpticalMap_XYRaw","LAr_OpticalMap_XYRaw",nbinsX,minX,maxX,nbinsY,minY,maxY);
  TH2F* h2DMapXYScaled = new TH2F("LAr_OpticalMap_XYScaled","LAr_OpticalMap_XYScaled",nbinsX,minX,maxX,nbinsY,minY,maxY);

  TH2F* h2DMapYZ = new TH2F("LAr_OpticalMap_YZ","LAr_OpticalMap_YZ",nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  TH2F* h2DMapYZRaw = new TH2F("LAr_OpticalMap_YZRaw","LAr_OpticalMap_YZRaw",nbinsY,minY,maxY,nbinsZ,minZ,maxZ);  
  TH2F* h2DMapYZScaled = new TH2F("LAr_OpticalMap_YZScaled","LAr_OpticalMap_YZScaled",nbinsY,minY,maxY,nbinsZ,minZ,maxZ);  
  
  Double_t totalEvents = 0,totalPrimaries;
  Int_t n3D = 0, nXY = 0, nYZ = 0, nRZ = 0;
  cout<<"Histogram has "<<nbinsX<<" "<<nbinsY<<" "<<nbinsZ<<" "<<nbinsX*nbinsY*nbinsZ <<" bins"<<endl;

  cout<<"starting run"<<endl; 
  TFile * infile;
  //TODO--This array contains the Z slice number of the location of SiPlates. Uncomment it while merging PEN maps
  //int Z = 0;
  for(int k =100; k <=600; k++){ //TODO change the limits of k when merging PEN maps //for fibers make it 39 to 382
    //TODO--Uncomment the next line as well when merging PEN maps
    //TODO--change input dir
    TString dir = "";
    dir = "/data9/legend/LGND_1T_CDR_wGeEnclosure/OpticalSims/pen-reentrant-tube/";
	//TODO -- change fileName
    //
    TString fileName = "LGND_1T_CDR_LGNDPENParts_" + to_string(k); //TODO replace k with Z for PEN map

    cout<<"File location at: "<<dir+fileName+TString(".root")<<endl;;
    if(!fileExist(string(dir+fileName+TString(".root")))){
      cout<<"processed "<<k<<" files"<<endl;
      continue;
      //break;
    }
    infile = new TFile(dir+fileName+TString(".root"));
    if(infile->IsZombie()){
      cout<<"File "<<k<<" is Zombie"<<endl;
      continue;
    }
    else
      infile = TFile::Open(dir+fileName+TString(".root"));
    if(infile->Get("NumberOfEvents") == NULL) {
      cout<<"NumberOfEvents is NULL... maybe file has not closed yet"<<endl;
      continue;
    }
    string neventsString = infile->Get("NumberOfEvents")->GetTitle();
    totalEvents += std::stoi(neventsString,nullptr,10);

    string nprimariesString = infile->Get("NumberOfPrimaries")->GetTitle();
    if(fileName.Contains("Exterior")) totalPrimaries += 78400;//std::stoi(nprimariesString,nullptr,10);
    else totalPrimaries += std::stoi(nprimariesString,nullptr,10);
    cout<<"adding to total Primaries "<<std::stoi(nprimariesString,nullptr,10)<<"... Total Primaries is "<<totalPrimaries<<endl;
    infile->Close();
    delete infile;
    outFileMaGe->cd();
    
    TChain *fTree = new TChain("fTree");
    fTree->Add(dir+fileName+TString(".root"));
    if(fTree == NULL) break; 
    Long64_t nentries = (Long64_t)fTree->GetEntries();
	if(nentries == NULL) continue;
    
    cout<<". Processing "<<nentries<<" entries"<<endl;
    MGTMCEventSteps *eventSteps = 0;
    MGTMCEventSteps *eventPrimaries = 0;
    
    if(fTree->GetBranchStatus("eventSteps")){
      fTree->SetBranchAddress("eventSteps",&eventSteps);
    }
    else{
      cout<<"eventSteps is NULL"<<endl;
      continue;
    }

    if(fTree->GetBranchStatus("eventPrimaries")){
      fTree->SetBranchAddress("eventPrimaries",&eventPrimaries);
    }
    else{
      cout<<"eventSteps is NULL"<<endl;
      continue;
    }  
    
    const MGTMCStepData *step,*primaries;
    
    for(Int_t i = 0; i < nentries ; i++){
      if((i+1)%10000 == 0 || i == nentries - 1 ) cout<<"\tprocessed "<<i+1<<" events"<<endl;
      //if(i==0) break;
      fTree->GetEntry(i);
      TString physName;
      Int_t sensID;
      primaries = eventPrimaries->GetStep(0);
      if(primaries == NULL){
        cout<<"null primary"<<endl;
        continue;
      }
      /*
      Double_t x = primaries->GetX(),y = primaries->GetY(),z = primaries->GetZ();//,time = primaries->GetT();
      Double_t px = primaries->GetPx(),py = primaries->GetPy(),pz = primaries->GetPz();
      Double_t r = sqrt(x*x+y*y);
      Double_t theta = std::acos(x/r);
      bool hitSiPM = false,hitFiber = false;
      Int_t hitSiPMCounter = 0,hitFiberCounter = 0;
      if( y < 0) theta += 3.14159265359;
      */
      Int_t pastTrackID = -1;
      for (Int_t j = 0; j < eventSteps->GetNSteps();j++){
        step = eventSteps->GetStep(j);
        Int_t trackID = step->GetTrackID();
        physName = step->GetPhysVolName();
        sensID = step->GetSensitiveVolumeID();
        Double_t x = step->GetLocalX(),y = step->GetLocalY(),z = step->GetLocalZ();//,time = step->GetT();
        Double_t r = sqrt(x*x+y*y);
        Double_t theta = std::acos(x/r);
        //cout<<"x "<<x<<", y "<<y<<" z "<<z<<" volName "<< physName<<", Edep "<<step->GetEdep()<<" process "<<step->GetTrackWeight()
        //  <<" trackID "<<trackID<<" pastTrackID "<<pastTrackID<<" parentID "<<step->GetParentTrackID()<<endl;
        if( y < 0) theta += 3.14159265359;
        //Track weight == 1 is for scintillation, track weight == 2 is for OpWLS
        //if(physName.Contains("SiPM") && step->GetEdep() > 0 && step->GetTrackWeight() == 2 && pastTrackID != trackID){
        //For SiPM Array, Photons are created directly (i.e. not Scint or WLS)
        //if(physName.Contains("SiPM") && step->GetEdep() > 0 && pastTrackID != trackID){
        if(sensID > 30000 && step->GetEdep() > 0 && pastTrackID != trackID){
          //cout << sensID << endl;
          ntpleStepSiPM->Fill(i,step->GetEdep(),step->GetKineticE(),step->GetX(),step->GetY(),step->GetZ(),sqrt(step->GetX()*step->GetX() +step->GetY()*step->GetY()),x,y,z,r,theta);
          //cout<<"\tx "<<x<<", y "<<y<<" z "<<z<<" r "<<r<<" volName "<< physName<<endl;
          //if(x>=abs(y)){       //right array
        hMapRaw->Fill(x,y,z);
        h2DMapRZRaw->Fill(r,z);
        h2DMapXYRaw->Fill(x,y);
        h2DMapYZRaw->Fill(y,z);
          //}
          //else{//if(y>=abs(x)){ // top array
        /*hMapRaw->Fill(-y,x,z);
        h2DMapRZRaw->Fill(r,z);
        h2DMapXYRaw->Fill(-y,x);
        h2DMapYZRaw->Fill(x,z);
         // }                   //left arrray
        hMapRaw->Fill(-x,-y,z);
        h2DMapRZRaw->Fill(r,z);
        h2DMapXYRaw->Fill(-x,-y);
        h2DMapYZRaw->Fill(-y,z);
        ////                     //bottom array
        hMapRaw->Fill(y,-x,z);
        h2DMapRZRaw->Fill(r,z);
        h2DMapXYRaw->Fill(y,-x);
        h2DMapYZRaw->Fill(-x,z);*/   
        }
        //only fill when a new track is being looped over
        if(pastTrackID != trackID) pastTrackID = trackID;
      }
    }
    delete step;
    delete primaries;
    delete fTree;
  }
  //weight 3Dhistogram
  cout<<hMap->GetNbinsX()<<" "<<hMap->GetNbinsY()<<" "<<hMap->GetNbinsZ()<<" rBins "<<h2DMapRZRaw->GetNbinsX()<<endl;
  for(int i = 0; i < hMap->GetNbinsX();i++){
    for(int j = 0; j < hMap->GetNbinsY();j++){
      for(int k = 0; k < hMap->GetNbinsZ();k++){
        Double_t binVal = hMapRaw->GetBinContent(i+1,j+1,k+1);
        //if(binVal !=0) {cout << binVal << "at " << i+1<<","<< j+1<<","<< k+1 << endl;}
        Double_t x = gridSpacing*(i)-maxX;
        Double_t y = gridSpacing*(j)-maxY;
        Double_t z = gridSpacing*(k)+minZ;
        if(binVal == 0){
            //binVal = hMapRaw->Interpolate(x,y,z);
            //cout<<"("<<x<<","<<y<<","<<z<<") ... bin center value"<<endl;
            n3D++;
        }
        //hMap->SetBinContent(i+1,j+1,k+1,binVal/(totalPrimaries/(nbinsX*nbinsY*nbinsZ)));//totalEvents);
        hMap->SetBinContent(i+1,j+1,k+1,binVal/(500));//totalPrimaries/(nbinsX*nbinsY*nbinsZ)));//totalEvents);
        //if(binVal !=0) cout << hMap->GetBinContent(i+1,j+1,k+1) << endl;
		hMapScaled->SetBinContent(i+1,j+1,k+1,QE*binVal/(500));
      }
    }
  }
  cout<<"finished XYZ Histogram"<<endl;
  for(int i = 0; i < h2DMapXY->GetNbinsX();i++){
    for(int j = 0; j < h2DMapXY->GetNbinsY();j++){
      Double_t binVal = h2DMapXYRaw->GetBinContent(i+1,j+1);
      //cout << h2DMapXYRaw->GetBinContent(i+1,j+1) << " at "<< i <<" , " << j << endl;
      Double_t x = gridSpacing*(i)-maxX;
      Double_t y = gridSpacing*(j)-maxY;
      Double_t j1 = (y+maxY)/gridSpacing;
      Double_t i1 = (x+maxX)/gridSpacing;
      //cout << i << "," << j << " get rotated to " << -1*j << "," << i << endl;
      if(binVal == 0){
         //binVal = h2DMapXYRaw->Interpolate(x,y);
         nXY++;
      }
      h2DMapXY->SetBinContent(i+1,j+1,(binVal)/(totalPrimaries/(nbinsX*nbinsY)));//totalEvents);
      //if(binVal !=0)//{
      //if(x >= abs(y)){
        //h2DMapXY->SetBinContent(j+1,i+1,(binVal)/(totalPrimaries/(nbinsX*nbinsY)));
      //h2DMapXY->SetBinContent(400-j1,i1,binVal/(totalPrimaries/(nbinsX*nbinsY)));
       // h2DMapXY->SetBinContent(j,i-201,binVal/(totalPrimaries/(nbinsX*nbinsY)));
      //}
      //else {h2DMapXY->SetBinContent(j,i,binVal/(totalPrimaries/(nbinsX*nbinsY)));}
      h2DMapXYScaled->SetBinContent(i+1,j+1,QE*binVal/(totalPrimaries/(nbinsX*nbinsY)));//totalEvents);
      //h2DMapXY->SetBinContent(i+1,j+1,binVal/(500*340.));
      //h2DMapXYScaled->SetBinContent(i+1,j+1,QE*binVal/(500*340));
    }
  }
  cout<<"finished XY Histogram"<<endl;
  for(int i = 0; i < h2DMapYZ->GetNbinsX();i++){
    for(int j = 0; j < h2DMapYZ->GetNbinsY();j++){
      Double_t binVal = h2DMapYZRaw->GetBinContent(i+1,j+1);
      Double_t y = gridSpacing*(i+1)-maxY;
      Double_t z = gridSpacing*(j+1)+minZ;
      if(binVal == 0){
        //binVal = h2DMapYZRaw->Interpolate(y,z);
        nYZ++;
      }
      h2DMapYZ->SetBinContent(i+1,j+1,binVal/(totalPrimaries/(nbinsX*nbinsY)));//totalEvents);
      h2DMapYZScaled->SetBinContent(i+1,j+1,QE*binVal/(totalPrimaries/(nbinsX*nbinsY)));//totalEvents);
      //h2DMapYZ->SetBinContent(i+1,j+1,binVal/(500.*160));
      //h2DMapYZScaled->SetBinContent(i+1,j+1,QE*binVal/(500*160.));
    }
  }
  cout<<"finished YZ Histogram"<<endl;
  TH1D * hWeight = new TH1D("rWeight","rWeight",h2DMapRZ->GetNbinsX(),minR,maxR);
  for(int i = 0; i < h2DMapRZ->GetNbinsX();i++){
    for(int j = 0; j < h2DMapRZ->GetNbinsY();j++){
      Double_t binVal = h2DMapRZRaw->GetBinContent(i+1,j+1);
      Double_t r = gridSpacing*(i+1)+minR;
      Double_t z = gridSpacing*(j+1)+minZ;
      Double_t weight = ((r+gridSpacing)*(r+gridSpacing)-r*r)/(maxR*maxR-minR*minR);
      //binVal /= weight;
      if(binVal == 0){
        //binVal = h2DMapRZRaw->Interpolate(r,z);
        nRZ++; 
      }
      hWeight->SetBinContent(i+1,weight);
      //h2DMapRZ->SetBinContent(i+1,j+1,binVal/(totalPrimaries/(nbinsZ*nbinsR)));//totalEvents);
      h2DMapRZ->SetBinContent(i+1,j+1,binVal/(500));
      h2DMapRZScaled->SetBinContent(i+1,j+1,QE*binVal/(totalPrimaries/(nbinsZ*nbinsR)));//totalEvents);
      //h2DMapRZ->SetBinContent(i+1,j+1,binVal/(500*160*160));//totalEvents);
      //h2DMapRZScaled->SetBinContent(i+1,j+1,QE*binVal/(500*160*160));//totalEvents);
    }
  }
  cout<<"finished RZ Histogram"<<endl;

  outFileMaGe->Write();
  outFileMaGe->Close();
  cout<<"Total events = "<<totalEvents<<", total primaries "<<totalPrimaries<<endl;
  cout<<"Events per bin..."<<totalPrimaries/(nbinsX*nbinsY)<<" XY, "<<totalPrimaries/(nbinsY*nbinsZ)
    <<" YZ, "<<totalPrimaries/(nbinsR*nbinsZ)<<" RZ, "<<totalPrimaries/(nbinsX*nbinsY*nbinsZ)<<" XYZ"<<endl;
  cout<<"Histogram has "<<nbinsX*nbinsY<<" XY bins, "<<nbinsY*nbinsZ<<" YZ bins, "<<nbinsZ*nbinsR<<" RZ bins, "<<nbinsX*nbinsY*nbinsZ <<", xyz bins"<<endl;
  cout<<"Zero bins found..."<<nXY<<" XY, "<<nYZ<<" YZ, "<<nRZ<<" RZ bins, "<<n3D <<", xyz bins"<<endl;
  cout<<"root -l "<<fileName<<endl;
  return 0;
}
