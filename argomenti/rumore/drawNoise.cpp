#include <TCanvas.h>
#include <TH1D.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

void drawNoise(std::string const& inputFileName, std::string const& outputFileName = "file_rumore.root", int binsNumber = 1e2) {
    std::ifstream inputFile;
    inputFile.open(inputFileName);
    if (!inputFile.is_open()) {
        throw std::runtime_error(static_cast<std::string>("Cannot open ") += inputFileName);
        return;
    }

    double x = 0;
    std::vector<double> dataVector;

    while (!inputFile.eof()) {
        inputFile >> x;
        dataVector.push_back(x);
    }

    auto maxElementIterator = std::max_element(dataVector.begin(), dataVector.end());
    auto minElementIterator = std::min_element(dataVector.begin(), dataVector.end());

    TH1D* histo = new TH1D("NoiseHisto", "Rumore", binsNumber, *minElementIterator, *maxElementIterator);

    for (int i = i; i < dataVector.size(); ++i) {
        histo->Fill(dataVector[i]);
    }

    TCanvas* canvas = new TCanvas("Canvas rumore");
    histo->Draw();
}