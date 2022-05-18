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

double ampiezza (double* x, double* par)
{
double W = x[0] * (TMath::TwoPi());
double wt2 = pow(W * par[0], 2.);
double val = par[1] * abs((1 - wt2)/( sqrt(pow((1 - wt2), 2.) + 16*wt2))) + par[2];
return val;
}

void testFunction ()
{
  TF1 *test = new TF1("test", ampiezza, 1E3/*/(TMath::TwoPi())*/, 3*1E4/*/(TMath::TwoPi())*/, 1);
  test->SetParameter(0, 2.25 * 1E-5);
  TCanvas *c1 = new TCanvas("c1");
  test->Draw();
}


void analyse()
{
  TF1 *f = new TF1("f", ampiezza, 1E3, 3*1E4, 3);
  f->SetParameters(2.25 * 1E-5, 2.5, 0.06);

  TGraph *graph1 = new TGraph("frequenza_V_out_1k-30k_3.txt", "%lg %lg %*lg");
  graph1->SetTitle("V_out frequency sweep 1k - 30k: ampiezza; frequenza(Hz); tensione(V)");
  /*graph1->SetMarkerStyle(kOpenCircle);
  graph1->SetMarkerSize(1);
  graph1->SetMarkerColor(2);*/
  graph1->SetLineColor(5);
  graph1->SetLineWidth(4);
  graph1->SetFillColor(0);

  //TF1 *f = new TF1("ampiezza", "(1 - pow(x*[0], 2.))/(sqrt(pow((1 - pow(x*[0], 2.)), 2.) + 16 * pow(x*[0], 2.)))", 10e04, 3*10e04);
  

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

  std::cout << "ChiQuadro ridotto: " << fitFunc->GetChisquare() / fitFunc->GetNDF() << '\n';
  std::cout << "Tau misurato: " << fitFunc->GetParameter(0) << " +/- " << fitFunc->GetParError(0) << '\n';
  std::cout << "Ampiezza misurata: " << fitFunc->GetParameter(1) << " +/- " << fitFunc->GetParError(1) << '\n';
  std::cout << "Intercetta misurata: " << fitFunc->GetParameter(2) << " +/- " << fitFunc->GetParError(2) << '\n';


  TCanvas *c = new TCanvas("c");
  graph1->Draw("AC");
}