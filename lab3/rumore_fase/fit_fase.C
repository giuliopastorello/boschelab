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

void analyse()
{
  const int n_points = 3;
  double x[n_points] = {1000, 7200, 20000};
  double y[n_points] = {-0.9818, -0.5339, 0.3089};
  double ey[n_points] = {0.06983, 0.04884, 0.1025};

  TGraphErrors *graph = new TGraphErrors(n_points, x, y, 0, ey );

  //x[3] = {1000, 7200, 20000};
  //y[3] = {-0.9818, -0.5339, 0.3089};
  //ey[3] = {0.06983, 0.04884, 0.1025};

  graph->SetTitle("Fasi V_in; tempo(s); tensione(V)");
  /*graph->SetMarkerStyle(kOpenCircle);
  graph->SetMarkerSize(1);
  graph->SetMarkerColor(2);*/
  graph->SetLineColor(5);
  graph->SetLineWidth(4);
  graph->SetFillColor(0);

  TF1 *f = new TF1("f", "[0] + [1] * x", 1000, 20000);
  f->SetParameters(-1.1, 0.5);

  graph->Fit("f", "R");
  TF1 *fitFunc = graph->GetFunction("f");

  fitFunc->GetChisquare(); 
  fitFunc->GetNDF(); 
  fitFunc->GetParameter(0); 
  fitFunc->GetParError(0);
  fitFunc->GetParameter(1); 
  fitFunc->GetParError(1);

  TCanvas *c = new TCanvas("c");
  graph->Draw("AC");
}