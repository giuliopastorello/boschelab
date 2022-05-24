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
 
  double p[6] = {42.6779, -0.0290747, 7.95567e-06, -1.08546e-09, 7.39158e-14, -2.00986e-18};
  double dhpa[3] = {0.0019426262, 0.0019362054, 0.0019296780};  
  for (int i = 0; i < 180; ++i){
      Double_t x = h->GetBinCenter(i);
      Double_t hpa = p[0] + p[1] * x + p[2] * pow (x, 2.) + p[3] * pow (x, 3.) + p[4] * pow (x, 4.) + p[5] * pow (x, 5.); 
      h->SetBinContent(i, hpa);
      if (x <= 7025){
        h->SetBinError(i, dhpa[0]);
      } else if (7125 < x && x <= 7075) {
        h->SetBinError(i, dhpa[1]); 
        } else {
        h->SetBinError(i, dhpa[2]);   
        } 
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
      std::cout << "p" << i << " = " <<
      fitFunc->GetParameter(i) << " +/- " << fitFunc->GetParError(i) << '\n';
  }
  std::cout << "ChiQuadro ridotto: " << fitFunc->GetChisquare() / fitFunc->GetNDF() << '\n';  
 
  TCanvas *c = new TCanvas("c");
  h->Draw();
}