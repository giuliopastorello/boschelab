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
#define _USE_MATH_DEFINES //imports math constants such as M_PI
#include <cmath>

double SQR (double tau) 
{
    TGraph *graph = new TGraph("frequenza_V_out_1k-30k_3_bis.txt", "%lg %*lg %lg");
    double SQR;
    for (int i = 0; i < 561; i++) {
        double x = graph->GetPointX(i);
        double omega = TMath::TwoPi() * x * 1E-6;
        double wt = tau * omega;
        double val = 180/TMath::Pi() * TMath::ATan(4 * wt/(pow(wt, 2.) - 1));
        double diff = pow(graph->GetPointY(i) - val, 2.);
        SQR += diff;
    }
    return SQR;
}

/*void test1 ()
{
    TGraph *graph = new TGraph("frequenza_V_out_1k-30k_3_bis.txt", "%lg %*lg %lg");
    double x[561];
    double vals[561];
    double tau = 22.105;
    for (int i = 0; i < 561; i++) {
        double x = graph->GetPointX(i);
        double omega = TMath::TwoPi() * x * 10E-6;
        double wt = tau * omega;
        double vals[i] = 180/TMath::Pi() * atan(4 * wt/(pow(wt, 2.) - 1));
    }
    TGraph *test = new TGraph(561, x, vals);

    TCanvas *c = new TCanvas("c");
    test->Draw();
}*/

Double_t test_atan (double* x, double* par) 
{
    Double_t W = x[0] * (TMath::TwoPi());
    Double_t wt = W * par[0];
    Double_t val = 180/TMath::Pi() * TMath::ATan(4 * wt/(pow(wt, 2.) - 1));
    return val;
}


void test2 () 
{
    TF1 *test = new TF1("test", test_atan, 5E02, 3E04, 1);
    test->SetParameter(0, 2.2105E-5);

    TCanvas *c = new TCanvas("c");
    test->Draw();
} 

void plotSQR () 
{
    const int n = 2E6;
    double x[n];
    double y[n];
    for (int i = 0; i < 2E6; ++i) {
        double tau = 21 + i * 1E-6;
        x[i] = tau;
        double sqr = SQR(tau);
        std::cout << tau << '\t' << sqr << '\n';
        y[i] = sqr;
    }
    TGraph *graph = new TGraph(n, x, y);

    TCanvas *c = new TCanvas("c");
    graph->Draw();
    
    //double xmin = x[0];
    //for (int i = 1; i < 2E6; ++i) {
    //    if (y[i] < y[i-1]) {
    //        xmin = x[i];
    //    } 
    //}

    //std::cout << xmin << '\n';
}

void bootstrap()
{
    TGraph *graph = new TGraph("frequenza_V_out_1k-30k_3_bis.txt", "%lg %*lg %lg");
    for (int i= 0; i < 10; i++) {
        double x[i];
        double y[i];
        for (int j = 0; j < 561; j++) {

        }
    }
}
