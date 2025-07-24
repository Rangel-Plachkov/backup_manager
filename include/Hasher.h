#pragma once
#include <string>

class Hasher {
public:
    static std::string computeSHA256(const std::string& filePath);
private:
    inline static std::string DEFAULT_HASH = "N/A";
};
