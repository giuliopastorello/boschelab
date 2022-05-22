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

Double_t computeYerr()
{
    double yerr;
    TGraph *graph = new TGraph("frequenza_V_out_sweep_6k-9k.txt", "%lg %lg %*lg");
    for (int i = 0; i < 256; ++i) {
        if (graph->GetPointX(i) < 7200) {
            yerr = (1.7E-3/(2.49501 - 1.23303E-5 * graph->GetPointX(i)));
        } else {
            yerr = (1.7E-3/(2.45428 - 6.50081E-6 * graph->GetPointX(i)));
        }
    return yerr;
    //per controllare che gli errori abbiano senso (già fatto)
    //std::cout << yerr << '\n';
    }
}

void computeChisquare()
{
  TGraphErrors *graph = new TGraphErrors("frequenza_V_out_sweep_6k-9k.txt", "%lg %lg %*lg");
  graph->SetTitle("V_out frequency sweep 6k - 9k: ampiezza; frequenza(Hz); tensione(V)");
  for (int i = 0; i < 256; ++i) {
        if (graph->GetPointX(i) <= 7200) {
            Double_t x = graph->GetPointX(i);
            Double_t y = graph->GetPointY(i);
            graph->SetPointY(i, y/(2.49501 - 1.23303E-5 * x));
            graph->SetPointError(i, 0, computeYerr());
        } else {
            Double_t x = graph->GetPointX(i);
            Double_t y = graph->GetPointY(i);
            graph->SetPointY(i, y/(2.45428 - 6.50081E-6 * x));
            graph->SetPointError(i, 0, computeYerr());
        }
    }

  graph->Fit("pol2", "C", "SAME", 6800, 7600); //gli ultimi due numeri sono il range (grazie al cazz0)
  TF1 *fitFunc = graph->GetFunction("pol2");

  graph->SetMarkerSize(1);
  graph->SetMarkerColor(2);
  graph->SetLineColor(5);
  graph->SetLineWidth(4);
  graph->SetFillColor(0);
  graph->GetXaxis()->SetRangeUser(6750, 7650);
  graph->GetYaxis()->SetRangeUser(0.025, 0.045);
 
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
  //std::cout << "Ampiezza misurata: " << fitFunc->GetParameter(1) << " +/- " << fitFunc->GetParError(1) << '\n';
  std::cout << "Intercetta misurata: " << fitFunc->GetParameter(1) << " +/- " << fitFunc->GetParError(1) << '\n';

  TCanvas *c = new TCanvas("c");
  graph->Draw("AC");
}