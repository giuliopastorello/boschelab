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

void analyse()
{
    //considero le due rette PA: a + Xb, e PB = c + Xd, con X asse x, che sarebbero le frequenze 
    Double_t a = 0.180112;
    Double_t Da = 0.105822;
    Double_t b = 2.60085e-05;
    Double_t Db = 1.50098e-05;
    Double_t c = 0.533344;
    Double_t Dc = 0.106122;
    Double_t d = -2.40985e-05;
    Double_t Dd = 1.50529e-05;
    //variabili per calcoli
    Double_t v = b - d;
    Double_t u = c - a;
    Double_t Dv = TMath::Sqrt(TMath::Power(Db, 2.) + TMath::Power(Dd, 2.));
    Double_t Du = TMath::Sqrt(TMath::Power(Da, 2.) + TMath::Power(Dc, 2.));
    Double_t DuR = Du / u;
    Double_t DvR = Dv / v;
    //risultati
    Double_t f = u / v;
    Double_t Df = TMath::Sqrt(TMath::Power(DuR, 2.) + TMath::Power(DvR, 2.)) * f;
    //stampa su terminale
    std::cout << "f_n = " << f << "  +/-  " << Df << '\n';
    std::cout << "dv/v = " << DvR << '\n';
    std::cout << "du/u = " << DuR << '\n';
}