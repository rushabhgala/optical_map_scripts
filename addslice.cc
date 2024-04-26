#include <TFile.h>
#include <TH2F.h>
#include <TCanvas.h>

void addslice() {
    // Create a canvas to display the histograms
    TCanvas *canvas = new TCanvas("canvas", "Combined 2D Histograms", 1000, 800);
    canvas->SetRightMargin(0.15);
    canvas->SetLeftMargin(0.15);

    // Open the ROOT file containing the histograms
    TFile *file1 = new TFile("/home/rushabh_gala/scripts/L1T-reentrant-tube-700mm-1.root");  // Replace "your_file.root" with the actual file name
    TFile *file2 = new TFile("/home/rushabh_gala/scripts/L1T-reentrant-tube-700mm-2.root");
	TFile *file3 = new TFile("/home/rushabh_gala/scripts/L1T-reentrant-tube-700mm-3.root");
	TFile *file4 = new TFile("/home/rushabh_gala/scripts/L1T-reentrant-tube-700mm-4.root");
    TFile *file5 = new TFile("/home/rushabh_gala/scripts/L1T-reentrant-tube-700mm-5.root");
    TFile *file6 = new TFile("/home/rushabh_gala/scripts/L1T-reentrant-tube-700mm-6.root");
    TFile *file7 = new TFile("/home/rushabh_gala/scripts/L1T-reentrant-tube-700mm-7.root");

    // Create pointers to 2D histograms
    TH2F *hist1 = (TH2F*)file1->Get("2DOpticalMapXY");  // Replace "hist1" with the actual histogram name
    TH2F *hist2 = (TH2F*)file2->Get("2DOpticalMapXY");  // Replace "hist2" with the actual histogram name
    TH2F *hist3 = (TH2F*)file3->Get("2DOpticalMapXY");  // Replace "hist3" with the actual histogram name
    TH2F *hist4 = (TH2F*)file4->Get("2DOpticalMapXY");  // Replace "hist4" with the actual histogram name
    TH2F *hist5 = (TH2F*)file5->Get("2DOpticalMapXY");  // Replace "hist5" with the actual histogram name
    TH2F *hist6 = (TH2F*)file6->Get("2DOpticalMapXY");  // Replace "hist6" with the actual histogram name
    TH2F *hist7 = (TH2F*)file7->Get("2DOpticalMapXY");  // Replace "hist7" with the actual histogram name

    // Combine the histograms by adding them
    hist1->Add(hist2);
    hist1->Add(hist3);
    hist1->Add(hist4);
    hist1->Add(hist5);
	hist1->Add(hist6);
	hist1->Add(hist7);

    hist1->SetOption("colz");  // Colored 2D plot
    hist1->SetStats(0);        // Turn off statistics box
	hist1->Scale(1.0 / 7.0);

    // Set log scale for the z-axis
    canvas->SetLogz();

    // Set z-axis range
    hist1->GetZaxis()->SetRangeUser(0.001, 0.1);

    // Set axis titles
    hist1->GetXaxis()->SetTitle("X (mm)");
    hist1->GetXaxis()->CenterTitle();
    hist1->GetYaxis()->SetTitle("Y (mm)");
    hist1->GetYaxis()->CenterTitle();
    hist1->GetZaxis()->SetTitle("Detection Probability");
    hist1->GetZaxis()->CenterTitle();
    hist1->GetZaxis()->RotateTitle();
    hist1->SetTitle("");

    // Draw the combined histogram
    hist1->Draw("colz");

    // Save the canvas as an image (optional)
    canvas->SaveAs("L1T-reentrant-tube-700mm-7.pdf");  // Replace "combined_histogram.png" with your desired output file name
	// Save the combined histogram to a ROOT file
    TFile *outputFile = new TFile("L1T-reentrant-tube-700mm-9.root", "RECREATE");
    hist1->Write();
    outputFile->Close();
}

