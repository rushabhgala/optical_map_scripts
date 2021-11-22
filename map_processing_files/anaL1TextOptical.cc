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

  TDatime time;
  //time 12:36:26 133626
  ///date 24/12/1997 19971224
  TString fileName = TString("MaGe.")+to_string(time.GetTime())+TString("-")+to_string(time.GetDate())+TString(".root");
  TFile *outFileMaGe = new TFile(fileName,"recreate");
//  TFile *outFileOpticalMap = new TFile(TString("OpticalMap.")+to_string(time.GetTime())+TString("-")+to_string(time.GetDate())+TString(".root"),"recreate");
  
 // TNtuple *ntpleStepSiPM = new TNtuple("Optical_PEN","Optical_PEN","event:edep:ke:x:y:z:r:primX:primY:primZ:primR:primTheta");

  std::map<std::vector<Int_t>,Double_t> prob_map;
  //Double_t gridSpacing = 2;//*mm
  Double_t QE = 0.14;//LEGEND 0.164; //0.14 for 128, 0.24 for 175
  Double_t gridSpacing = 15;//*mm
  Double_t maxX = 2000.,minX = -2000.,maxY=2000.,minY = -2000,maxZ= 2000,minZ = -2000,minR = 0, maxR = 2000.;
  Double_t binVal;
  //Double_t maxX = 700.,minX = -700.,maxY=700.,minY = -700,maxZ= 845,minZ = -850,minR = 300, maxR = 700.;
  Int_t nbinsX = (maxX-minX)/gridSpacing,nbinsY = (maxY-minY)/gridSpacing,nbinsZ = (maxZ-minZ)/gridSpacing, nbinsR = (maxR-minR)/gridSpacing;
  TH3D* hMap = new TH3D("ProbMapExterior","ProbMapExterior",nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  //TH3D* hMapRaw = new TH3D("ProbMapExterior_Raw","ProbMapExterior_Raw",nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  //TH3D* hMapScaled = new TH3D("ProbMapExterior_Scaled","ProbMapExterior_Scaled",nbinsX,minX,maxX,nbinsY,minY,maxY,nbinsZ,minZ,maxZ);
  
  Double_t totalEvents = 0,totalPrimaries;
  Int_t n3D = 0;
  cout<<"Histogram has "<<nbinsX<<" "<<nbinsY<<" "<<nbinsZ<<" "<<nbinsX*nbinsY*nbinsZ <<" bins"<<endl;

  //weight 3Dhistogram
  cout<<hMap->GetNbinsX()<<" "<<hMap->GetNbinsY()<<" "<<hMap->GetNbinsZ()<<" "<<endl;
  for(int k = 0; k < hMap->GetNbinsZ();k++){
    for(int j = 0; j < hMap->GetNbinsY();j++){
      for(int i = 0; i < hMap->GetNbinsX();i++){
        //Double_t binVal = 0.005; //constant bin value
        //if(binVal !=0) {cout << binVal << "at " << i+1<<","<< j+1<<","<< k+1 << endl;}
        Double_t x = gridSpacing*(i)-maxX;
        Double_t y = gridSpacing*(j)-maxY;
        Double_t z = gridSpacing*(k)+minZ;
        //if((((x-500)^(2)+ y^(2) > 350^(2)) && ((x)^(2)+ (y-500)^(2) > 350^(2)) && ((x+500)^(2)+ y^(2) > 350^(2)) && ((x)^(2)+ (y+500)^(2) > 350^(2))))
        if(((pow((x-1000),2)+pow(y,2)<pow(450,2) || (pow((x+1000),2)+pow(y,2)<pow(450,2)) || (pow(x,2)+pow((y-1000),2)<pow(450,2)) || (pow(x,2)+pow((y+1000),2)<pow(450,2))) && (z<1000 && z>-1000) ))
        //if(pow(z,2) + pow(y,2) > 100)
        binVal = 0;
        else if(((x*x) + (y*y)) > (2000*2000))
        binVal = 0;
        else
        binVal = 0.005;
        if(binVal ==0 ){cout << "bin value is " << binVal << " at " << i+1<<","<< j+1<<","<< k+1 <<"" << " at " <<x << "," <<y<<"," << z <<"" <<endl;}
        if(binVal == 0){
            //binVal = hMapRaw->Interpolate(x,y,z);
            //cout<<"("<<x<<","<<y<<","<<z<<") ... bin center value"<<endl;
            n3D++;
        }
        //hMap->SetBinContent(i+1,j+1,k+1,binVal/(totalPrimaries/(nbinsX*nbinsY*nbinsZ)));//totalEvents);
        hMap->SetBinContent(i+1,j+1,k+1,binVal/(500));//totalPrimaries/(nbinsX*nbinsY*nbinsZ)));//totalEvents);
        //if(binVal !=0) cout << hMap->GetBinContent(i+1,j+1,k+1) << endl;
	     // hMapScaled->SetBinContent(i+1,j+1,k+1,QE*binVal/(500));
      }
    }
  }
  cout<<"finished XYZ Histogram"<<endl;
  outFileMaGe->Write();
  outFileMaGe->Close();
  cout<<"Total events = "<<totalEvents<<", total primaries "<<totalPrimaries<<endl;
  cout<<"Events per bin..."<<totalPrimaries/(nbinsX*nbinsY)<<" XY, "<<totalPrimaries/(nbinsY*nbinsZ)
    <<" YZ, "<<totalPrimaries/(nbinsR*nbinsZ)<<" RZ, "<<totalPrimaries/(nbinsX*nbinsY*nbinsZ)<<" XYZ"<<endl;
  cout<<"Histogram has "<<nbinsX*nbinsY<<" XY bins, "<<nbinsY*nbinsZ<<" YZ bins, "<<nbinsZ*nbinsR<<" RZ bins, "<<nbinsX*nbinsY*nbinsZ <<", xyz bins"<<endl;
  cout<<"Zero bins found..."<<n3D <<", xyz bins"<<endl;
  cout<<"root -l "<<fileName<<endl;
  return 0;
}
