#include <TCanvas.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraphErrors.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<double> fileToVector(std::string const& inputFileName) {
    std::ifstream inputFile;
    inputFile.open(inputFileName);
    if (!inputFile.is_open()) {
        throw std::runtime_error(static_cast<std::string>("Cannot open ") += inputFileName);
    }

    std::vector<double> dataVector;

    double x = 0;

    while (!inputFile.eof()) {
        inputFile >> x;
        dataVector.push_back(x);
    }

    inputFile.close();

    return dataVector;
}

double func(double* x, double* par) {
    double xx = x[0];
    double val = par[0] + std::atan(xx / par[1]) / (xx * xx / (par[1] * par[1]) - 1) * par[2];
    return val;
}

TGraph* drawGraphSErr(std::string const& inputFileName1, std::string const& inputFileName2, std::string const& graphName = "Graph") {
    auto xVector = fileToVector(inputFileName1);

    double xArray[xVector.size()];
    for (int i = 0; i < xVector.size(); ++i) {
        xArray[i] = xVector[i];
    }

    auto yVector = fileToVector(inputFileName2);

    double yArray[yVector.size()];
    for (int i = 0; i < yVector.size(); ++i) {
        yArray[i] = yVector[i];
    }

    double xArrayErr[xVector.size()];
    for (int i = 0; i < xVector.size(); ++i) {
        xArrayErr[i] = 0.;
    }

    double yArrayErr[yVector.size()];
    for (int i = 0; i < yVector.size(); ++i) {
        yArrayErr[i] = 180. / 500e3 * (500 + 50 * i);
    }

    TGraphErrors* graph = new TGraphErrors(xVector.size(), xArray, yArray, xArrayErr, yArrayErr);
    graph->SetName(graphName.c_str());
    TF1* f1 = new TF1("f1", func, 0, 6500, 3);
    f1->SetParameter(1, 7200.);
    graph->Fit(f1, "R");
    TCanvas* canvas = new TCanvas("Canvas grafico");
    graph->Draw();

    return graph;
}