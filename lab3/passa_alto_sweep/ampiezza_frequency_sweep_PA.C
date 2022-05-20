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

Double_t transferFunc(Double_t *x, Double_t *par)
{
  Double_t w = x[0] * TMath::TwoPi();
  Double_t wt = w * par[0];
  Double_t val = wt / sqrt(4 + pow(wt, 2.));
  return val; 
}

void plotFunc()
{
  TF1* func = new TF1("transferFunc", transferFunc, 500, 3E4,1);
  func->SetParameter(0, 2.12E-5);
  
  TCanvas c1 = new TCanvas("c1");
  func->Draw();
}


void analyse()
{
  TF1 *f = new TF1("f", transferFunc, 500, 3 * 1E4 ,1);
  f->SetParameter(0, 2.12E-5);

  TGraph *graph = new TGraph("frequenza_PA_sweep_1k-20k.txt", "%lg %lg %*lg");
  graph->SetTitle("H_A frequency sweep 1k - 30k: ampiezza; frequenza(Hz); H_A");
  for (int i = 0; i < 572; ++i) {
        if (graph->GetPointX(i) < 7200) {
            Double_t y = graph->GetPointY(i);
            graph->SetPointY(i, y/(2.49501 - 1.23303E-5 * graph->GetPointX(i)));
        } else {
            Double_t y = graph->GetPointY(i);
            graph->SetPointY(i, y/(2.45428 - 6.50081E-6 * graph->GetPointX(i)));
        }
    }
  /*graph->SetMarkerStyle(kOpenCircle);
  graph->SetMarkerSize(1);
  graph->SetMarkerColor(2);*/
  graph->SetLineColor(5);
  graph->SetLineWidth(4);
  graph->SetFillColor(0);

  graph->Fit("f", "R");
  TF1 *fitFunc = graph->GetFunction("f");

  //graph->Fit("f", "F", "R");
  //TF1 *fitFunc = graph->GetFunction("f");

  fitFunc->GetChisquare(); 
  fitFunc->GetNDF(); 
  fitFunc->GetParameter(0); 
  fitFunc->GetParError(0);
  std::cout << "ampiezze PA:" << '\n';
  for (int i = 122; i < 138; i++){
    std::cout << "f = " << graph->GetPointX(i) << " -> ampiezza/V_in = " << graph->GetPointY(i) << '\n';
  }
  //fitFunc->GetParameter(1); 
  //fitFunc->GetParError(1);
  //fitFunc->GetParameter(2); 
  //fitFunc->GetParError(2);
  //fitFunc->GetParameter(3); 
  //fitFunc->GetParError(3);
  //fitFunc->GetParameter(4); 
  //fitFunc->GetParError(4);
  //fitFunc->GetParameter(5); 
  //fitFunc->GetParError(5);

  TCanvas *c = new TCanvas("c");
  graph->Draw("AC");
  //fitFunc->Draw();
}