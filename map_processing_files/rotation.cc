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
  TString fileName = "try.root";
  TFile *outFileMaGe = new TFile(fileName,"recreate");
  TString dir = "/home/rushabh_gala/scripts/";
  TString inputFile = "OpticalMapL1000Reflector.root";

  TH3F* mapold = nullptr;
  TH3F* mapoldext = nullptr;
  TH3F* mapnewext = nullptr;
  TH3F* mapnew = new TH3F("ProbMapInterior","ProbMapInterior",600,-1500,1500,600,-1500,1500,400,-1000,1000);
  TFile* fileTH3Dint = TFile::Open(dir+inputFile);
  fileTH3Dint->GetObject("ProbMapInterior",mapold);

  for(int k=0; k < mapold->GetNbinsZ(); k++)
  {
    for(int j= 0; j < mapold->GetNbinsY(); j++)
    {
      for(int i= 0; i < mapold->GetNbinsX(); i++)
      {
        Double_t x = 5*i - 1500;
        Double_t y = 5*j - 1500;
        Double_t z = 5*k - 1000;
		   //if((((pow((x-1000),2))+(pow(y,2))) < pow(450,2)) && (((pow((x-1000),2))+(pow(y,2))) > pow(300,2))) //|| (pow((x+1000),2)+pow(y,2)<pow(450,2)) || (x,2)+pow((y-1000),2)<pow(450,2)) || (pow(x,2)+pow((y+1000),2)<pow(450,2)))) //condiition to check for interior of the containemnt can
		   if(((((pow((x-1000),2))+(pow(y,2))) < pow(450,2)) && (((pow((x-1000),2))+(pow(y,2))) > pow(300,2))) || ((((pow((x-1000),2))+(pow(y,2))) < pow(200,2))))
		   {

			   Double_t binVal = 1* (mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(0*360/14.0)) - ((y-0)*std::sin(0*360/14.0)) + 1000,((y-0)*std::cos(0*360/14.0)) + ((x-1000)*std::sin(0*360/14.0))+ 0, z)) +
                               mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(1*360/14.0)) - ((y-0)*std::sin(1*360/14.0)) + 1000,((y-0)*std::cos(1*360/14.0)) + ((x-1000)*std::sin(1*360/14.0))+ 0, z)) +
                               mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(2*360/14.0)) - ((y-0)*std::sin(2*360/14.0)) + 1000,((y-0)*std::cos(2*360/14.0)) + ((x-1000)*std::sin(2*360/14.0))+ 0, z)) +
                               mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(3*360/14.0)) - ((y-0)*std::sin(3*360/14.0)) + 1000,((y-0)*std::cos(3*360/14.0)) + ((x-1000)*std::sin(3*360/14.0))+ 0, z)) +
                               mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(4*360/14.0)) - ((y-0)*std::sin(4*360/14.0)) + 1000,((y-0)*std::cos(4*360/14.0)) + ((x-1000)*std::sin(4*360/14.0))+ 0, z)) +
                               mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(5*360/14.0)) - ((y-0)*std::sin(5*360/14.0)) + 1000,((y-0)*std::cos(5*360/14.0)) + ((x-1000)*std::sin(5*360/14.0))+ 0, z)) +
                               mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(6*360/14.0)) - ((y-0)*std::sin(6*360/14.0)) + 1000,((y-0)*std::cos(6*360/14.0)) + ((x-1000)*std::sin(6*360/14.0))+ 0, z)) +
                               mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(7*360/14.0)) - ((y-0)*std::sin(7*360/14.0)) + 1000,((y-0)*std::cos(7*360/14.0)) + ((x-1000)*std::sin(7*360/14.0))+ 0, z)) +
                               mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(8*360/14.0)) - ((y-0)*std::sin(8*360/14.0)) + 1000,((y-0)*std::cos(8*360/14.0)) + ((x-1000)*std::sin(8*360/14.0))+ 0, z)) +
                               mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(9*360/14.0)) - ((y-0)*std::sin(9*360/14.0)) + 1000,((y-0)*std::cos(9*360/14.0)) + ((x-1000)*std::sin(9*360/14.0))+ 0, z)) +
                               mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(10*360/14.0)) - ((y-0)*std::sin(10*360/14.0)) + 1000,((y-0)*std::cos(10*360/14.0)) + ((x-1000)*std::sin(10*360/14.0))+ 0, z)) +
                               mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(11*360/14.0)) - ((y-0)*std::sin(11*360/14.0)) + 1000,((y-0)*std::cos(11*360/14.0)) + ((x-1000)*std::sin(11*360/14.0))+ 0, z)) +
                               mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(12*360/14.0)) - ((y-0)*std::sin(12*360/14.0)) + 1000,((y-0)*std::cos(12*360/14.0)) + ((x-1000)*std::sin(12*360/14.0))+ 0, z)) +
                               mapold->GetBinContent(mapold->FindBin(((x-1000)*std::cos(13*360/14.0)) - ((y-0)*std::sin(13*360/14.0)) + 1000,((y-0)*std::cos(13*360/14.0)) + ((x-1000)*std::sin(13*360/14.0))+ 0, z)))/14.0;

        //Double_t binVal = 0.5*(mapold->GetBinContent(mapold->FindBin(x,y,z)) + mapold->GetBinContent(mapold->FindBin(-x,-y,z)));
          mapnew->SetBinContent(i+1,j+1,k+1,binVal);
        }
      // else if((((pow((x+1000),2))+(pow(y,2))) < pow(450,2)) && (((pow((x+1000),2))+(pow(y,2))) > pow(300,2))) //|| (pow((x+1000),2)+pow(y,2)<pow(450,2)) || (x,2)+pow((y-1000),2)<pow(450,2)) || (pow(x,2)+pow((y+1000),2)<pow(450,2)))) //condiition to check for interior of the containemnt can
      else if(((((pow((x+1000),2))+(pow(y,2))) < pow(450,2)) && (((pow((x+1000),2))+(pow(y,2))) > pow(300,2))) || ((((pow((x+1000),2))+(pow(y,2))) < pow(200,2))))
 		   {

 			   Double_t binVal = 1* (mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(0*360/14.0)) - ((y-0)*std::sin(0*360/14.0)) - 1000,((y-0)*std::cos(0*360/14.0)) + ((x+1000)*std::sin(0*360/14.0))+ 0, z)) +
                                mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(1*360/14.0)) - ((y-0)*std::sin(1*360/14.0)) - 1000,((y-0)*std::cos(1*360/14.0)) + ((x+1000)*std::sin(1*360/14.0))+ 0, z)) +
                                mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(2*360/14.0)) - ((y-0)*std::sin(2*360/14.0)) - 1000,((y-0)*std::cos(2*360/14.0)) + ((x+1000)*std::sin(2*360/14.0))+ 0, z)) +
                                mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(3*360/14.0)) - ((y-0)*std::sin(3*360/14.0)) - 1000,((y-0)*std::cos(3*360/14.0)) + ((x+1000)*std::sin(3*360/14.0))+ 0, z)) +
                                mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(4*360/14.0)) - ((y-0)*std::sin(4*360/14.0)) - 1000,((y-0)*std::cos(4*360/14.0)) + ((x+1000)*std::sin(4*360/14.0))+ 0, z)) +
                                mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(5*360/14.0)) - ((y-0)*std::sin(5*360/14.0)) - 1000,((y-0)*std::cos(5*360/14.0)) + ((x+1000)*std::sin(5*360/14.0))+ 0, z)) +
                                mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(6*360/14.0)) - ((y-0)*std::sin(6*360/14.0)) - 1000,((y-0)*std::cos(6*360/14.0)) + ((x+1000)*std::sin(6*360/14.0))+ 0, z)) +
                                mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(7*360/14.0)) - ((y-0)*std::sin(7*360/14.0)) - 1000,((y-0)*std::cos(7*360/14.0)) + ((x+1000)*std::sin(7*360/14.0))+ 0, z)) +
                                mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(8*360/14.0)) - ((y-0)*std::sin(8*360/14.0)) - 1000,((y-0)*std::cos(8*360/14.0)) + ((x+1000)*std::sin(8*360/14.0))+ 0, z)) +
                                mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(9*360/14.0)) - ((y-0)*std::sin(9*360/14.0)) - 1000,((y-0)*std::cos(9*360/14.0)) + ((x+1000)*std::sin(9*360/14.0))+ 0, z)) +
                                mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(10*360/14.0)) - ((y-0)*std::sin(10*360/14.0)) - 1000,((y-0)*std::cos(10*360/14.0)) + ((x+1000)*std::sin(10*360/14.0))+ 0, z)) +
                                mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(11*360/14.0)) - ((y-0)*std::sin(11*360/14.0)) - 1000,((y-0)*std::cos(11*360/14.0)) + ((x+1000)*std::sin(11*360/14.0))+ 0, z)) +
                                mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(12*360/14.0)) - ((y-0)*std::sin(12*360/14.0)) - 1000,((y-0)*std::cos(12*360/14.0)) + ((x+1000)*std::sin(12*360/14.0))+ 0, z)) +
                                mapold->GetBinContent(mapold->FindBin(((x+1000)*std::cos(13*360/14.0)) - ((y-0)*std::sin(13*360/14.0)) - 1000,((y-0)*std::cos(13*360/14.0)) + ((x+1000)*std::sin(13*360/14.0))+ 0, z)))/14.0;

         //Double_t binVal = 0.5*(mapold->GetBinContent(mapold->FindBin(x,y,z)) + mapold->GetBinContent(mapold->FindBin(-x,-y,z)));
           mapnew->SetBinContent(i+1,j+1,k+1,binVal);
       }
       //else if((((pow(x,2))+(pow((y-1000),2))) < pow(450,2)) && (((pow(x,2))+(pow((y-1000),2))) > pow(300,2))) //|| (pow(x,2)+pow(y,2)<pow(450,2)) || (x,2)+pow((y-1000),2)<pow(450,2)) || (pow(x,2)+pow((y+1000),2)<pow(450,2)))) //condiition to check for interior of the containemnt can
       else if(((((pow((y-1000),2))+(pow(x,2))) < pow(450,2)) && (((pow((y-1000),2))+(pow(x,2))) > pow(300,2))) || ((((pow((y-1000),2))+(pow(x,2))) < pow(200,2))))
       {

           Double_t binVal = 1* (mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(0*360/14.0)) - ((y-1000)*std::sin(0*360/14.0)) - 0 ,((y-1000)*std::cos(0*360/14.0)) + ((x-0)*std::sin(0*360/14.0))+ 1000 , z)) +
                                 mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(1*360/14.0)) - ((y-1000)*std::sin(1*360/14.0)) - 0 ,((y-1000)*std::cos(1*360/14.0)) + ((x-0)*std::sin(1*360/14.0))+ 1000 , z)) +
                                 mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(2*360/14.0)) - ((y-1000)*std::sin(2*360/14.0)) - 0 ,((y-1000)*std::cos(2*360/14.0)) + ((x-0)*std::sin(2*360/14.0))+ 1000 , z)) +
                                 mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(3*360/14.0)) - ((y-1000)*std::sin(3*360/14.0)) - 0 ,((y-1000)*std::cos(3*360/14.0)) + ((x-0)*std::sin(3*360/14.0))+ 1000 , z)) +
                                 mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(4*360/14.0)) - ((y-1000)*std::sin(4*360/14.0)) - 0 ,((y-1000)*std::cos(4*360/14.0)) + ((x-0)*std::sin(4*360/14.0))+ 1000 , z)) +
                                 mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(5*360/14.0)) - ((y-1000)*std::sin(5*360/14.0)) - 0 ,((y-1000)*std::cos(5*360/14.0)) + ((x-0)*std::sin(5*360/14.0))+ 1000 , z)) +
                                 mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(6*360/14.0)) - ((y-1000)*std::sin(6*360/14.0)) - 0 ,((y-1000)*std::cos(6*360/14.0)) + ((x-0)*std::sin(6*360/14.0))+ 1000 , z)) +
                                 mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(7*360/14.0)) - ((y-1000)*std::sin(7*360/14.0)) - 0 ,((y-1000)*std::cos(7*360/14.0)) + ((x-0)*std::sin(7*360/14.0))+ 1000 , z)) +
                                 mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(8*360/14.0)) - ((y-1000)*std::sin(8*360/14.0)) - 0 ,((y-1000)*std::cos(8*360/14.0)) + ((x-0)*std::sin(8*360/14.0))+ 1000 , z)) +
                                 mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(9*360/14.0)) - ((y-1000)*std::sin(9*360/14.0)) - 0 ,((y-1000)*std::cos(9*360/14.0)) + ((x-0)*std::sin(9*360/14.0))+ 1000 , z)) +
                                 mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(10*360/14.0)) - ((y-1000)*std::sin(10*360/14.0)) - 0 ,((y-1000)*std::cos(10*360/14.0)) + ((x-0)*std::sin(10*360/14.0))+ 1000 , z)) +
                                 mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(11*360/14.0)) - ((y-1000)*std::sin(11*360/14.0)) - 0 ,((y-1000)*std::cos(11*360/14.0)) + ((x-0)*std::sin(11*360/14.0))+ 1000 , z)) +
                                 mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(12*360/14.0)) - ((y-1000)*std::sin(12*360/14.0)) - 0 ,((y-1000)*std::cos(12*360/14.0)) + ((x-0)*std::sin(12*360/14.0))+ 1000 , z)) +
                                 mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(13*360/14.0)) - ((y-1000)*std::sin(13*360/14.0)) - 0 ,((y-1000)*std::cos(13*360/14.0)) + ((x-0)*std::sin(13*360/14.0))+ 1000 , z)))/14.0;

          //Double_t binVal = 0.5*(mapold->GetBinContent(mapold->FindBin(x,y,z)) + mapold->GetBinContent(mapold->FindBin(-x,-y,z)));
            mapnew->SetBinContent(i+1,j+1,k+1,binVal);
        }
        //else if((((pow(x,2))+(pow((y+1000),2))) < pow(450,2)) && (((pow(x,2))+(pow((y+1000),2))) > pow(300,2))) //|| (pow(x,2)+pow(y,2)<pow(450,2)) || (x,2)+pow((y-1000),2)<pow(450,2)) || (pow(x,2)+pow((y+1000),2)<pow(450,2)))) //condiition to check for interior of the containemnt can
        else if(((((pow((y+1000),2))+(pow(x,2))) < pow(450,2)) && (((pow((y+1000),2))+(pow(x,2))) > pow(300,2))) || ((((pow((y+1000),2))+(pow(x,2))) < pow(200,2))))
        {

            Double_t binVal = 1* (mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(0*360/14.0)) - ((y+1000)*std::sin(0*360/14.0)) - 0 ,((y+1000)*std::cos(0*360/14.0)) + ((x-0)*std::sin(0*360/14.0))- 1000, z)) +
                                  mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(1*360/14.0)) - ((y+1000)*std::sin(1*360/14.0)) - 0 ,((y+1000)*std::cos(1*360/14.0)) + ((x-0)*std::sin(1*360/14.0))- 1000, z)) +
                                  mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(2*360/14.0)) - ((y+1000)*std::sin(2*360/14.0)) - 0 ,((y+1000)*std::cos(2*360/14.0)) + ((x-0)*std::sin(2*360/14.0))- 1000, z)) +
                                  mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(3*360/14.0)) - ((y+1000)*std::sin(3*360/14.0)) - 0 ,((y+1000)*std::cos(3*360/14.0)) + ((x-0)*std::sin(3*360/14.0))- 1000, z)) +
                                  mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(4*360/14.0)) - ((y+1000)*std::sin(4*360/14.0)) - 0 ,((y+1000)*std::cos(4*360/14.0)) + ((x-0)*std::sin(4*360/14.0))- 1000, z)) +
                                  mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(5*360/14.0)) - ((y+1000)*std::sin(5*360/14.0)) - 0 ,((y+1000)*std::cos(5*360/14.0)) + ((x-0)*std::sin(5*360/14.0))- 1000, z)) +
                                  mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(6*360/14.0)) - ((y+1000)*std::sin(6*360/14.0)) - 0 ,((y+1000)*std::cos(6*360/14.0)) + ((x-0)*std::sin(6*360/14.0))- 1000, z)) +
                                  mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(7*360/14.0)) - ((y+1000)*std::sin(7*360/14.0)) - 0 ,((y+1000)*std::cos(7*360/14.0)) + ((x-0)*std::sin(7*360/14.0))- 1000, z)) +
                                  mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(8*360/14.0)) - ((y+1000)*std::sin(8*360/14.0)) - 0 ,((y+1000)*std::cos(8*360/14.0)) + ((x-0)*std::sin(8*360/14.0))- 1000, z)) +
                                  mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(9*360/14.0)) - ((y+1000)*std::sin(9*360/14.0)) - 0 ,((y+1000)*std::cos(9*360/14.0)) + ((x-0)*std::sin(9*360/14.0))- 1000, z)) +
                                  mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(10*360/14.0)) - ((y+1000)*std::sin(10*360/14.0)) - 0 ,((y+1000)*std::cos(10*360/14.0)) + ((x-0)*std::sin(10*360/14.0))- 1000, z)) +
                                  mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(11*360/14.0)) - ((y+1000)*std::sin(11*360/14.0)) - 0 ,((y+1000)*std::cos(11*360/14.0)) + ((x-0)*std::sin(11*360/14.0))- 1000, z)) +
                                  mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(12*360/14.0)) - ((y+1000)*std::sin(12*360/14.0)) - 0 ,((y+1000)*std::cos(12*360/14.0)) + ((x-0)*std::sin(12*360/14.0))- 1000, z)) +
                                  mapold->GetBinContent(mapold->FindBin(((x-0)*std::cos(13*360/14.0)) - ((y+1000)*std::sin(13*360/14.0)) - 0 ,((y+1000)*std::cos(13*360/14.0)) + ((x-0)*std::sin(13*360/14.0))- 1000, z)))/14.0;

           //Double_t binVal = 0.5*(mapold->GetBinContent(mapold->FindBin(x,y,z)) + mapold->GetBinContent(mapold->FindBin(-x,-y,z)));
             mapnew->SetBinContent(i+1,j+1,k+1,binVal);
           }
        else{
             Double_t binVal = (mapold->GetBinContent(mapold->FindBin(x,y,z)));
             mapnew->SetBinContent(i+1,j+1,k+1,binVal);
        }
      }
    }
  }
  //fileTH3Dint->GetObject("ProbMapExterior",mapold);
  //mapnewext->SetNameTitle("ProbMapExterior","ProbMapExterior");
  outFileMaGe->cd();
  mapnew->Write();
  //mapnewext->Write();
  outFileMaGe->Close();
  cout<<"root -l "<<fileName<<endl;
}
