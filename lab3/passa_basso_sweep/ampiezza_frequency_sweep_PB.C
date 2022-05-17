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

/*Double_t pol5(Double_t *x, Double_t *par)
{
  Double_t xx = x[0];
  Double_t val = par[0] + par[1] * xx + par[2] * TMath::Power(xx, 2.) +
                par[3] * TMath::Power(xx, 3.) + par[4] * TMath::Power(xx, 4.) + par[5] * TMath::Power(xx, 5.);
  return val; 
}*/

/*void plotFunc()
{
  TF1 *func = new TF1("func", "[0] + [1] * x + [2] * TMath::Power(x, 2.) + [3] * TMath::Power(x, 3.) + [4] * TMath::Power(x, 4.) + [5] * TMath::Power(x,5.)", 6500, 8000);
  func->SetParameters(-2.86073E16, 1.97458E13, -5.44523E09, 749913, -51.5774, 0.00141728);
  TCanvas c1 = new TCanvas("c");
  func->Draw();
}*/

void analyse()
{
  //TF1 *f = new TF1("f", "pol5");
  //f->SetParameters(1, 1, 1, 1, 1, 1);

  TGraph *graph1 = new TGraph("frequenza_PB_sweep_1k-30k.txt", "%lg %lg %*lg");
  graph1->SetTitle("Passa Basso frequency sweep 1k - 30k: ampiezza; frequenza(Hz); ampiezza(V)");
  /*graph1->SetMarkerStyle(kOpenCircle);
  graph1->SetMarkerSize(1);
  graph1->SetMarkerColor(2);*/
  graph1->SetLineColor(5);
  graph1->SetLineWidth(4);
  graph1->SetFillColor(0);

  graph1->Fit("pol5", "C", "SAME", 6500, 8000);
  TF1 *fitFunc = graph1->GetFunction("pol5");

  fitFunc->GetChisquare(); 
  fitFunc->GetNDF(); 
  fitFunc->GetParameter(0); 
  fitFunc->GetParError(0);
  fitFunc->GetParameter(1); 
  fitFunc->GetParError(1);
  fitFunc->GetParameter(2); 
  fitFunc->GetParError(2);
  fitFunc->GetParameter(3); 
  fitFunc->GetParError(3);
  fitFunc->GetParameter(4); 
  fitFunc->GetParError(4);
  fitFunc->GetParameter(5); 
  fitFunc->GetParError(5);

  TCanvas *c = new TCanvas("c");
  graph1->Draw("AC");
  //fitFunc->Draw();
}   