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
    const int n = 572;
    double yerr;
    TGraph *graph = new TGraph("frequenza_PA_sweep_1k-20k.txt", "%lg %lg %*lg");
    for (int i = 0; i < n; ++i) {
        if (graph->GetPointX(i) < 7200) {
            yerr = (3 * 1.7E-3/(2.49501 - 1.23303E-5 * graph->GetPointX(i)));
        } else {
            yerr = (3 * 1.7E-3/(2.45428 - 6.50081E-6 * graph->GetPointX(i)));
        }
    return yerr;
    //per controllare che gli errori abbiano senso (già fatto)
    //std::cout << yerr << '\n';
    }
}

void analyse()
{
  TF1 *f = new TF1("f", "[0] + [1] * x", 7000, 7100);
  //f->SetParameter(0, 2.20 * 1E-5);

  TGraphErrors *graph = new TGraphErrors("frequenza_PA_sweep_1k-20k.txt", "%lg %lg %*lg");
  graph->SetTitle("Fit Locale H_pa; frequenza (Hz); H_pa");
  for (int i = 0; i < 572; ++i) {
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
    graph->GetXaxis()->SetRangeUser(6980, 7120);
    graph->GetYaxis()->SetRangeUser(0.35, 0.37);

  
    graph->Fit("f", "R");
    TF1 *fitFunc = graph->GetFunction("f");
  
    fitFunc->GetChisquare(); 
    fitFunc->GetNDF(); 
    fitFunc->GetParameter(0); 
    fitFunc->GetParError(0);
    fitFunc->GetParameter(1); 
    fitFunc->GetParError(1);

    std::cout << "ChiQuadro ridotto: " << fitFunc->GetChisquare() / fitFunc->GetNDF() << '\n';

    TCanvas *c = new TCanvas("c");
    graph->Draw("AC");
}