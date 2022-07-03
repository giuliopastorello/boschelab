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
  TGraph *graph = new TGraph("frequenza_PB_sweep_1k-30k.txt", "%lg %lg %*lg");
  TF1 *f = new TF1("f", "[0] + [1] * x", 6800, 7700);

  TH1F *h = new TH1F("h", "H_pa", 180 , 6800, 7700);
  
  Double_t p[6] = {28.1956, -0.019197, 5.29935E-06, -7.29903E-10, 5.00788E-14, -1.36863E-18};
  Double_t d0 = 1.7E-3/0.877422;//se hai dubbi su come l'ho fatto in PA, è uguale
  Double_t d1 = 1.7E-3/0.874358;//formula che ti ho mandato su wa
  Double_t dhpb[2] = {d0, d1};
  for (int i = 0; i < 180; ++i){
      Double_t x = h->GetBinCenter(i);
      Double_t hpb = p[0] + p[1] * x + p[2] * pow (x, 2.) + p[3] * pow (x, 3.) + p[4] * pow (x, 4.) + p[5] * pow (x, 5.); 
      h->SetBinContent(i, hpb);
      if (x < 7050){
        h->SetBinError(i, dhpb[0]);
      } else 
        h->SetBinError(i, dhpb[1]);   
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