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

/*void testFunction()
{
    TF1 *test = new TF1("test", "[0] * sin([1] * x)", 0.379169, 0.379965);
    test->SetParameters(2.43029, 42725.7, -2);

    TCanvas *c = new TCanvas("c1");
    test->Draw();
}*/

void analyse()
{
  TGraphErrors *graph1 = new TGraphErrors("ampiezze_V_in.txt", "%lg %lg %lg");
  graph1->SetTitle("Ampiezze V_in; tempo(s); tensione(V)");
  /*graph1->SetMarkerStyle(kOpenCircle);
  graph1->SetMarkerSize(1);
  graph1->SetMarkerColor(2);*/
  graph1->SetLineColor(5);
  graph1->SetLineWidth(4);
  graph1->SetFillColor(0);

  //TF1 *f1 = new TF1("f1", "[0] + [1] * x", 0, 7200);
  //f1->SetParameters(2.5, -0.3);

  TF1 *f2 = new TF1("f2", "[0] + [1] * x", 7200, 20000);
  f2->SetParameters(-8000, 1, -0.5);

  //graph1->Fit("f1", "R");
  //TF1 *fitFunc1 = graph1->GetFunction("f1");
//
  //fitFunc1->GetChisquare(); 
  //fitFunc1->GetNDF(); 
  //fitFunc1->GetParameter(0); 
  //fitFunc1->GetParError(0);
  //fitFunc1->GetParameter(1); 
  //fitFunc1->GetParError(1);

  graph1->Fit("f2", "R");
  TF1 *fitFunc2 = graph1->GetFunction("f2");

  fitFunc2->GetChisquare(); 
  fitFunc2->GetNDF(); 
  fitFunc2->GetParameter(0); 
  fitFunc2->GetParError(0);
  fitFunc2->GetParameter(1); 
  fitFunc2->GetParError(1);
  //fitFunc2->GetParameter(2); 
  //fitFunc2->GetParError(2);

  

  TCanvas *c = new TCanvas("c");
  graph1->Draw("AC");
}