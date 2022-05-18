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

void testFunction()
{
    TF1 *test = new TF1("test", "[0] * sin([1] * x)", 14.323905, 14.324701);
    test->SetParameters(2.41029, 42725.7);

    TCanvas *c = new TCanvas("c1");
    test->Draw();
}

void analyse()
{
  TGraph *graph1 = new TGraph("V_in_6800.txt", "%lg %lg");
  graph1->SetTitle("6800Hz Tensione-Tempo; tempo(s); tensione(V)");
  /*graph1->SetMarkerStyle(kOpenCircle);
  graph1->SetMarkerSize(1);
  graph1->SetMarkerColor(2);*/
  graph1->SetLineColor(5);
  graph1->SetLineWidth(4);
  graph1->SetFillColor(0);
  graph1->GetXaxis()->SetRangeUser(0, 0.005);

  TF1 *f = new TF1("f", "[0] * TMath::Sin([1] * x + [2])", 14.323905, 14.324701);
  f->SetParameters(2.5, 6800 * TMath::TwoPi(), 0);

  graph1->Fit("f", "R");
  TF1 *fitFunc = graph1->GetFunction("f");

  fitFunc->GetChisquare(); 
  fitFunc->GetNDF(); 
  fitFunc->GetParameter(0); 
  fitFunc->GetParError(0);
  fitFunc->GetParameter(1); 
  fitFunc->GetParError(1);
  fitFunc->GetParameter(2); 
  fitFunc->GetParError(2);

  TCanvas *c = new TCanvas("c");
  graph1->Draw("AC");
}