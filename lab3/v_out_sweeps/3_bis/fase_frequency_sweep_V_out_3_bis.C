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
  Double_t w = x[0] * TMath::TwoPi() / 1E3;
  Double_t t = par[0] * 1E3;
  Double_t wt = w * t;
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

Double_t systErr()
{
  TGraph *graph = new TGraph("frequenza_V_out_1k-30k_3_bis.txt", "%lg %*lg %lg");
  graph->SetTitle("V_out frequency sweep 1k - 20k: fase; frequenza(Hz); tensione(V)");

  for (int i = 0; i < 561; ++i) {
    Double_t x = graph->GetPointX(i);   
    Double_t y = 6.79668E-05 * x - 1.03441;
    return y;
  }
}

void analyse()
{
  TF1 *f = new TF1("f", fase, 1E3, 2*1E4, 1);
  f->SetParameter(0, 2.25 * 1E-5);

  TGraphErrors *graph = new TGraphErrors("frequenza_V_out_1k-30k_3_bis.txt", "%lg %*lg %lg");
  graph->SetTitle("V_out frequency sweep 1k - 20k: fase; frequenza(Hz); tensione(V)");
  for (int i = 0; i < 561; ++i) {
    Double_t y = graph->GetPointY(i);
    graph->SetPointY(i, y - systErr());
  }
  /*graph->SetMarkerStyle(kOpenCircle);
  graph->SetMarkerSize(1);
  graph->SetMarkerColor(2);*/
  graph->SetLineColor(5);
  graph->SetLineWidth(4);
  graph->SetFillColor(0);
  graph->GetYaxis()->SetRangeUser(-90., 90.);

  //int n = 1E9;
  //ROOT::Math::MinimizerOptions::DefaultMaxFunctionCalls(n);
  graph->Fit("f", "R");
  TF1 *fitFunc = graph->GetFunction("f");

  fitFunc->GetChisquare(); 
  fitFunc->GetNDF(); 
  fitFunc->GetParameter(0); 
  fitFunc->GetParError(0);

  std::cout << "ChiQuadro ridotto: " << fitFunc->GetChisquare() / fitFunc->GetNDF() << '\n';
  std::cout << "Tau misurato: " << fitFunc->GetParameter(0) << " +/- " << fitFunc->GetParError(0) << '\n';

  TCanvas *c = new TCanvas("c");
  graph->Draw("AC");
}