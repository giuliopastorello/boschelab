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

double ampiezza (double* x, double* par)
{
double W = x[0] * (TMath::TwoPi());
double wt2 = pow(W * par[0], 2.);
double val = abs((1 - wt2)/( sqrt(pow((1 - wt2), 2.) + 16 * wt2)));
return val;
}

Double_t computeYerr()
{
    const int n = 561;
    double yerr;
    TGraph *graph = new TGraph("frequenza_V_out_1k-30k_3_bis.txt", "%lg %lg %*lg");
    for (int i = 0; i < n; ++i) {
        double k = 1;//fattore di copertura
        double x = graph->GetPointX(i);
        double y = graph->GetPointY(i);
        if (graph->GetPointX(i) < 7200) {
            yerr = k * (1.7E-3/(2.49501 - 1.23303E-5 * x) + 1.7E-3/y) * y/(2.49501 - 1.23303E-5 * x);
        } else {
            yerr = k * (1.7E-3/(2.45428 - 6.50081E-6 * x) + 1.7E-3/y) * y/(2.45428 - 6.50081E-6 * x);
        }
    return yerr;
    //per controllare che gli errori abbiano senso (già fatto)
    //std::cout << yerr << '\n';
    }
}

void computeChisquare()
{
  TF1 *f = new TF1("f", ampiezza, 1E3, 3 * 1E4, 1);
  f->SetParameters(2.20 * 1E-5, 0);
  TGraphErrors *graph = new TGraphErrors("frequenza_V_out_1k-30k_3_bis.txt", "%lg %lg %*lg");
  graph->SetTitle("H frequency sweep 1k - 30k: mod(H); frequenza(Hz); mod(H)");
  for (int i = 0; i < 561; ++i) {
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
  
    graph->Fit("f", "R", "EX");
    TF1 *fitFunc = graph->GetFunction("f");
  
    fitFunc->GetChisquare(); 
    fitFunc->GetNDF(); 
    fitFunc->GetParameter(0); 
    fitFunc->GetParError(0);
    //fitFunc->GetParameter(1); 
    //fitFunc->GetParError(1);
    graph->GetYaxis()->SetRangeUser(0, 0.95);
    
  
    std::cout << "ChiQuadro ridotto: " << fitFunc->GetChisquare() / fitFunc->GetNDF() << '\n';
    std::cout << "Tau misurato: " << fitFunc->GetParameter(0) << " +/- " << fitFunc->GetParError(0) << '\n';
    //std::cout << "Ampiezza misurata: " << fitFunc->GetParameter(1) << " +/- " << fitFunc->GetParError(1) << '\n';
    //std::cout << "Intercetta misurata: " << fitFunc->GetParameter(1) << " +/- " << fitFunc->GetParError(1) << '\n';
  
  
    TCanvas *c = new TCanvas("c");
    graph->Draw("AC");
}