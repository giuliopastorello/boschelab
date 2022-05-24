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

Double_t computeYerr()
{
  TGraph *graph = new TGraph("frequenza_PB_sweep_1k-30k.txt", "%lg %lg %*lg");  
  int n = 557;
  Double_t yerr;
  for (int i = 0; i < n; ++i){
    if (graph->GetPointX(i) < 7200){
      Double_t hpb = graph->GetPointY(i)/(2.49501 - 1.23303E-5 * graph->GetPointX(i));
      yerr = (1.7E-3/(2.49501 - 1.23303E-5 * graph->GetPointX(i)) + 1.7E-3/graph->GetPointY(i)) * hpb;
    } else {
      Double_t hpb = graph->GetPointY(i)/(2.45428 - 6.50081E-6 * graph->GetPointX(i));
      yerr = (1.7E-3/(2.45428 - 6.50081E-6 * graph->GetPointX(i))+ 1.7E-3/graph->GetPointY(i)) * hpb;
    }
  }
  return yerr;  
}
void analyse()
{
  TGraphErrors *graph = new TGraphErrors("frequenza_PB_sweep_1k-30k.txt", "%lg %lg %*lg");
  graph->SetTitle("H_B frequency sweep 1k - 30k: ampiezza; frequenza(Hz); H_B");
  for (int i = 0; i < 557; ++i) {
        if (graph->GetPointX(i) < 7200) {
            Double_t y = graph->GetPointY(i);
            graph->SetPointY(i, y/(2.49501 - 1.23303E-5 * graph->GetPointX(i)));
            graph->SetPointError(i, 0, computeYerr());
        } else {
            Double_t y = graph->GetPointY(i);
            graph->SetPointY(i, y/(2.45428 - 6.50081E-6 * graph->GetPointX(i)));
            graph->SetPointError(i, 0, computeYerr());  
        }
    }
  
  
  graph->SetLineColor(5);
  graph->SetLineWidth(4);
  graph->SetFillColor(0);
  graph->GetXaxis()->SetRangeUser(6750, 7750);

  graph->Fit("pol5", "C", "SAME", 6800, 7700);
  TF1 *fitFunc = graph->GetFunction("pol5");

  fitFunc->GetChisquare(); 
  fitFunc->GetNDF();
  for (int i = 0; i < 5; ++i){
    fitFunc->GetParameter(i); 
    fitFunc->GetParError(i);
  } 
  
  TCanvas *c = new TCanvas("c");
  graph->Draw("AC");
}   