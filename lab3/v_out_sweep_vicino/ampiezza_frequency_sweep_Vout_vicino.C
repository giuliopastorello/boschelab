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
#include <fstream>
#include <iostream>

void analyse()
{
  TGraph *graph1 = new TGraph("frequenza_V_out_sweep_6k-9k.txt", "%lg %lg %*lg");
  graph1->SetTitle("V_out frequency sweep 6k - 9k: ampiezza; frequenza(Hz); tensione(V)");
  /*graph1->SetMarkerStyle(kOpenCircle);
  graph1->SetMarkerSize(1);
  graph1->SetMarkerColor(2);*/
  graph1->SetLineColor(5);
  graph1->SetLineWidth(4);
  graph1->SetFillColor(0);

  graph1->Fit("pol2", "C", "SAME", 6650, 7750); //gli ultimi due numeri sono il range (grazie al cazz0)
  TF1 *fitFunc = graph1->GetFunction("pol2");

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
  //fitFunc->Draw();
}