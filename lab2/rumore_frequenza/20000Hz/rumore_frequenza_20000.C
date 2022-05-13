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
  constexpr int N = 1000;
  // ***** CALCOLO DEVIAZIONE STANDARD DEL RUMORE *****
  TH1D *stdHisto = new TH1D("stdHisto", "Rumore", N, 1000.0290, 1000.0408);
  std::ifstream in;
  in.open("rumore_frequenza_1000.txt");
  Double_t frequenza1k;
  while (1)
  {
    in >> frequenza1k;
    if (!in.good())
    {
      break;
    }
    stdHisto->Fill(frequenza1k);
  }
  in.close();

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