#pragma once
#include <string>

class Compressor {
public:
    static bool compressToFile(const std::string& inputPath, const std::string& outputPath);
private:
    static constexpr size_t BUFFER_SIZE = 4096;
};
