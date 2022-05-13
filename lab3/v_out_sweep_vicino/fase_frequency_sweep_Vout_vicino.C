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
  TGraph *graph1 = new TGraph("frequenza_V_out_sweep_6k-9k.txt", "%lg %*lg %lg");
  graph1->SetTitle("V_out frequency sweep 1k - 20k: ampiezza; frequenza(Hz); fase(gradi)");
  /*graph1->SetMarkerStyle(kOpenCircle);
  graph1->SetMarkerSize(1);
  graph1->SetMarkerColor(2);*/
  graph1->SetLineColor(2);
  graph1->SetLineWidth(4);
  graph1->SetFillColor(0);

  TCanvas *c = new TCanvas("c");
  graph1->Draw("AC");
}