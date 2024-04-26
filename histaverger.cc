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

inline bool fileExist(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

int main() {
    TString fileName = "L200_PEN_combined.root";
    TFile *outFileMaGe = new TFile(fileName, "recreate");

    TString dir = "/home/rushabh_gala/scripts/";

    TString inFileNameTH3D = "L200_PEN.root";
    TString inFileNameTH2D = "L200_PEN2.root";
    TH3D* intMap = nullptr; // Initialize pointers
    TH3D* extMap = nullptr;

    TFile* fileTH3D = TFile::Open(dir + inFileNameTH3D);
    fileTH3D->GetObject("ProbMapInterior", intMap);
    if (!intMap) {
        cerr << "Failed to retrieve TH3D intMap!" << endl;
        return 1;
    }
    intMap->SetNameTitle("ProbMapInterior", "ProbMapInterior");

    TFile* fileTH2D = TFile::Open(dir + inFileNameTH2D);
    fileTH2D->GetObject("ProbMapInterior", extMap);
    if (!extMap) {
        cerr << "Failed to retrieve TH3D extMap!" << endl;
        return 1;
    }

    TH3F* mapnew = new TH3F("ProbMapInterior", "ProbMapInterior",
                            280, -700, 700,
                            280, -700, 700,
                            400, -900, 1100);

    double p1, p2, p_avg = 0.0;
    for (int i = 0; i < intMap->GetNbinsX(); i++) {
        int x = 5 * i - 700;
        for (int j = 0; j < intMap->GetNbinsY(); j++) {
            int y = 5 * j - 700;
            for (int k = 0; k < intMap->GetNbinsZ(); k++) {
                int z = 5 * k - 900;
                p1 = intMap->GetBinContent(intMap->FindBin(x, y, z));
                p2 = extMap->GetBinContent(extMap->FindBin(x, y, z));
                p_avg = (p1 + p2) / 2.0;
				if(p_avg >0) cout << "p1: " << p1 << " p2: " << p2 << " and pavg: " << p_avg << endl;
                mapnew->SetBinContent(i + 1, j + 1, k + 1, p_avg);
            }
        }
    }

    outFileMaGe->cd();
    mapnew->Write();
    outFileMaGe->Close();
    cout << "root -l " << fileName << endl;

    return 0;
}

