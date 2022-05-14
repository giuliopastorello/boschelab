#include <TCanvas.h>
#include <TFile.h>
#include <TGraph.h>

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

    int i = 0;

    while (!inputFile.eof()) {
        inputFile >> x;
        dataVector.push_back(x);
        std::cout << ++i << '\n';
    }

    inputFile.close();

    return dataVector;
}

TGraph* drawGraphS(std::string const& inputFileName1, std::string const& inputFileName2, std::string const& graphName = "Graph") {
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

    TGraph* graph = new TGraph(xVector.size(), xArray, yArray);
    graph->SetName(graphName.c_str());
    TCanvas* canvas = new TCanvas("Canvas grafico");
    graph->Draw();

    return graph;
}