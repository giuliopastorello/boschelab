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
#include <math.h>

Double_t fase(Double_t *x, Double_t *par)
{
  Double_t w = x[0] * TMath::TwoPi();
  Double_t wt = w * par[0];
  double_t val = 180/TMath::Pi() * atan(4*wt/(pow(wt, 2.) - 1));
  return val;
}

void testFunction()
{
  TF1 *test = new TF1("test", fase, 1E3, 3*1E4, 1);
  test->SetParameter(0, 2.25 * 1E-5);
  TCanvas *c1 = new TCanvas("c1");
  test->Draw();
}

void analyse()
{
  TF1 *f = new TF1("f", fase, 1E3, 3*1E4, 1);
  f->SetParameter(0, 2.25 * 1E-5);

  TGraph *graph1 = new TGraph("frequenza_V_out_1k-30k_3_bis.txt", "%lg %*lg %lg");
  graph1->SetTitle("V_out frequency sweep 1k - 20k: fase; frequenza(Hz); tensione(V)");
  /*graph1->SetMarkerStyle(kOpenCircle);
  graph1->SetMarkerSize(1);
  graph1->SetMarkerColor(2);*/
  graph1->SetLineColor(6);
  graph1->SetLineWidth(4);
  graph1->SetFillColor(0);

  graph1->Fit("f", "R");
  TF1 *fitFunc = graph1->GetFunction("f");

  fitFunc->GetChisquare(); 
  fitFunc->GetNDF(); 
  fitFunc->GetParameter(0); 
  fitFunc->GetParError(0);

  std::cout << "ChiQuadro ridotto: " << fitFunc->GetChisquare() / fitFunc->GetNDF() << '\n';
  std::cout << "Tau misurato: " << fitFunc->GetParameter(0) << " +/- " << fitFunc->GetParError(0) << '\n';

  TCanvas *c = new TCanvas("c");
  graph1->Draw("AC");
}