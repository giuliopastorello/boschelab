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
  TGraph *graph1 = new TGraph("tensione_tempo_7700.txt", "%lg %lg %*lg %*lg %*lg");
  graph1->SetTitle("7700Hz Tensione-Tempo; tempo(s); tensione(V)");
  /*graph1->SetMarkerStyle(kOpenCircle);
  graph1->SetMarkerSize(1);
  graph1->SetMarkerColor(2);*/
  graph1->SetLineColor(2);
  graph1->SetLineWidth(4);
  graph1->SetFillColor(0);
  graph1->GetXaxis()->SetRangeUser(0, 0.005);
  
  TGraph *graph2 = new TGraph("tensione_tempo_7700.txt", "%lg %*lg %lg %*lg %*lg");
  graph2->SetTitle("; x(UDM); y(UDM)");
  /*graph2->SetMarkerStyle(kOpenCircle);
  graph2->SetMarkerSize(1);
  graph1->SetMarkerColor(3);*/
  graph2->SetLineColor(3);
  graph2->SetLineWidth(4);
  graph2->SetFillColor(0);

  TGraph *graph3 = new TGraph("tensione_tempo_7700.txt", "%lg %*lg %*lg %lg %*lg");
  graph3->SetTitle("; x(UDM); y(UDM)");
  /*graph3->SetMarkerStyle(kOpenCircle);
  graph3->SetMarkerSize(1);
  graph1->SetMarkerColor(4);*/
  graph3->SetLineColor(4);
  graph3->SetLineWidth(4);
  graph3->SetFillColor(0);

  TGraph *graph4 = new TGraph("tensione_tempo_7700.txt", "%lg %*lg %*lg %*lg %lg");
  graph4->SetTitle("; x(UDM); y(UDM)");
  /*graph4->SetMarkerStyle(kOpenCircle);
  graph4->SetMarkerSize(1);
  graph1->SetMarkerColor(5);*/
  graph4->SetLineColor(5);
  graph4->SetLineWidth(4);
  graph4->SetFillColor(0);

  TCanvas *c = new TCanvas("c");
  graph1->Draw("AC");
  graph2->Draw("CP");
  graph3->Draw("CP");
  graph4->Draw("CP");

  TLegend *legend = new TLegend(0.1,0.7,0.48,0.9);
  legend->SetHeader("Legenda","C"); // option "C" allows to center the header
  legend->AddEntry(graph1, "V_in");
  legend->AddEntry(graph2, "Passa Alto");
  legend->AddEntry(graph3, "Passa Basso");
  legend->AddEntry(graph4, "V_o");
  legend->Draw();
}