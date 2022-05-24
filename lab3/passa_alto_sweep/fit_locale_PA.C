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
  TF1 *f = new TF1("f", "[0] + [1] * x", 7000, 7100);

  TH1F *h = new TH1F("h", "H_pa", 180 , 6800, 7700);
  Double_t p0 = 59.168;
  Double_t p1 = -0.0404675;
  Double_t p2 = 1.11004E-05;
  Double_t p3 = -1.51896E-09;
  Double_t p4 = 1.03759E-13;
  Double_t p5 = -2.83069E-18;
  for (int i = 0; i < 180; ++i){
      Double_t x = h->GetBinCenter(i);
      h->SetBinError(i, 1.7E-3/(2.49501 - 1.23303E-5 * x));
      Double_t hpa = p0 + p1 * x + p2 * pow (x, 2.) + p3 * pow (x, 3.) + p4 * pow (x, 4.) + p5 * pow (x, 5.); 
      h->SetBinContent(i, hpa);
  }

  
  h->Fit("f", "R");
  TF1 *fitFunc = h->GetFunction("f");
  
  fitFunc->GetChisquare(); 
  fitFunc->GetNDF(); 
  fitFunc->GetParameter(0); 
  fitFunc->GetParError(0);
  fitFunc->GetParameter(1); 
  fitFunc->GetParError(1);  
 
  for (int i = 0; i < 2; ++i){
      std::cout << fitFunc->GetParameter(i) << " +/- " << fitFunc->GetParError(i) << '\n';
  }
  std::cout << "ChiQuadro ridotto: " << fitFunc->GetChisquare() / fitFunc->GetNDF() << '\n';  
 
  TCanvas *c = new TCanvas("c");
  h->Draw();
}