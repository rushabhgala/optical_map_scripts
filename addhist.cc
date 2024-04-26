#include <TFile.h>
#include <TH3F.h>

void addhist() {
    // Open the ROOT file containing the histograms
    TFile *file1 = new TFile("/data9/legend/LGND_1T_CDR_LNGS_Sims/OpticalSims/slab/center/LGND_1T_CDR_LGND1TLiquidArgon_201-1.root");  // Replace with the actual file name
    TFile *file2 = new TFile("/data9/legend/LGND_1T_CDR_LNGS_Sims/OpticalSims/slab/center/LGND_1T_CDR_LGND1TLiquidArgon_201-1.root");
    TFile *file3 = new TFile("/data9/legend/LGND_1T_CDR_LNGS_Sims/OpticalSims/slab/center/LGND_1T_CDR_LGND1TLiquidArgon_201-1.root");
    TFile *file4 = new TFile("/data9/legend/LGND_1T_CDR_LNGS_Sims/OpticalSims/slab/center/LGND_1T_CDR_LGND1TLiquidArgon_201-1.root");
    TFile *file5 = new TFile("/data9/legend/LGND_1T_CDR_LNGS_Sims/OpticalSims/slab/center/LGND_1T_CDR_LGND1TLiquidArgon_401-1.root");
    

    // Create pointers to 3D histograms
    TH3F *hist1 = (TH3F*)file1->Get("OpticalOutput/OpticalMap");  // Replace "hist1" with the actual histogram name
    TH3F *hist2 = (TH3F*)file2->Get("OpticalOutput/OpticalMap");  // Replace "hist2" with the actual histogram name
    TH3F *hist3 = (TH3F*)file3->Get("OpticalOutput/OpticalMap");  // Replace "hist3" with the actual histogram name
    TH3F *hist4 = (TH3F*)file4->Get("OpticalOutput/OpticalMap");  // Replace "hist4" with the actual histogram name
    TH3F *hist5 = (TH3F*)file5->Get("OpticalOutput/OpticalMap");  // Replace "hist5" with the actual histogram name

    // Combine the histograms by adding them
    hist1->Add(hist2);
    hist1->Add(hist3);
    hist1->Add(hist4);
    hist1->Add(hist5);

    // Save the combined histogram to a ROOT file
    TFile *outputFile = new TFile("L1T-reentrant-tube-700mm-8-3D.root", "RECREATE");
    hist1->Write();
    outputFile->Close();
}

