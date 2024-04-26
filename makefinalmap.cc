#include <iostream>
#include <TFile.h>
#include <TH3F.h>
#include <TH2F.h>

int makefinalmap() {
    // Open the input files
    TFile *file1 = new TFile("L1T_CDR_internal_lar_wPENenclosure_bottom_included.root", "READ");
    //OpticalMapL1000.root for external map with all three fibers and use L1000_CDR_lar_wPENenclosure_wo_fiber1.root for maps without fibers 1
    TFile *file2 = new TFile("L1000_CDR_lar_wPENenclosure_wo_fiber1.root", "READ");  

    // Open the output file
    TFile *outputFile = new TFile("L1000_CDR_lar_wPENenclosure_only2ext_fibers.root", "RECREATE");

    // Check if the files are opened successfully
    if (!file1 || file1->IsZombie()) {
        std::cerr << "Error: Unable to open inputFile1.root" << std::endl;
        return 1;
    }

    if (!file2 || file2->IsZombie()) {
        std::cerr << "Error: Unable to open inputFile2.root" << std::endl;
        return 1;
    }

    if (!outputFile || outputFile->IsZombie()) {
        std::cerr << "Error: Unable to create outputFile.root" << std::endl;
        return 1;
    }

    // Copy and rename the 3D histogram from file1
    TH3F *hist3D = (TH3F*)file1->Get("ProbMapInterior");
    if (hist3D) {
        TH3F *hist3Dclone = (TH3F*)hist3D->Clone("ProbMapInterior");
        outputFile->cd();
        hist3Dclone->Write();
    } else {
        std::cerr << "Error: 3D histogram not found in file1" << std::endl;
        return 1;
    }

    // Copy and rename the 2D histogram from file2
    TH2F *hist2D = (TH2F*)file2->Get("ProbMapExterior");
    if (hist2D) {
        TH2F *hist2Dclone = (TH2F*)hist2D->Clone("ProbMapExterior");
        outputFile->cd();
        hist2Dclone->Write();
    } else {
        std::cerr << "Error: 2D histogram not found in file2" << std::endl;
        return 1;
    }

    // Close all files
    file1->Close();
    file2->Close();
    outputFile->Close();

    std::cout << "Histograms copied and renamed successfully." << std::endl;

    return 0;
}

