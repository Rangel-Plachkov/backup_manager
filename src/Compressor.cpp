#include "Compressor.h"
#include <zlib.h>
#include <fstream>
#include <vector>
#include <iostream>

bool Compressor::compressToFile(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream inFile(inputPath, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open input file: " << inputPath << '\n';
        return false;
    }

    gzFile outFile = gzopen(outputPath.c_str(), "wb");
    if (!outFile) {
        std::cerr << "Failed to open output file: " << outputPath << '\n';
        inFile.close();
        return false;
    }

    std::vector<char> buffer(BUFFER_SIZE);
    while (inFile.read(buffer.data(), buffer.size()) || inFile.gcount() > 0) {
        gzwrite(outFile, buffer.data(), static_cast<size_t>(inFile.gcount()));
    }

    inFile.close();
    gzclose(outFile);
    return true;
}
