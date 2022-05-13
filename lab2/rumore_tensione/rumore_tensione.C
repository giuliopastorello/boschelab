#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TMath.h"
#include <fstream>
#include <iostream>

void setStyle()
{
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(112210);
  gStyle->SetOptFit(1111);
}

void computeRMS()
{
  constexpr int N = 3979;
  // ***** CALCOLO DEVIAZIONE STANDARD DEL RUMORE *****
  TH1D *stdHisto = new TH1D("stdHisto", "Rumore", 2000, 0, 0.03);
  std::ifstream in;
  in.open("rumore_tensione1.txt");
  Double_t Vin;
  while (1)
  {
    in >> Vin;
    if (!in.good())
    {
      break;
    }
    Double_t displacement = TMath::Abs(Vin) - 2.5;
    stdHisto->Fill(displacement);
  }
  in.close();

  stdHisto->Fit("gaus");

  Double_t stdDev = stdHisto->GetStdDev();
  std::cout << '\n'
            << " ***** DEVIAZIONE STANDARD RUMORE *****" << '\n'
            << "Deviazione Standard: " << stdDev << '\n'
            << "Underflows: " << stdHisto->GetBinContent(0) << '\n'
            << "Overflows: " << stdHisto->GetBinContent(N+1) << '\n'
            << "**********" << '\n';

  TCanvas *cRMS = new TCanvas("cRMS");
  stdHisto->Draw();
}