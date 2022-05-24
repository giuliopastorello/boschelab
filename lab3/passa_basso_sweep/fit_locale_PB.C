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
  Double_t p0 = 16.6974;
  Double_t p1 = -0.0112809; 
  Double_t p2 = 3.12027e-06; 
  Double_t p3 = -4.30112e-10;
  Double_t p4 =  2.94652e-14;
  Double_t p5 = -8.01919e-19;
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