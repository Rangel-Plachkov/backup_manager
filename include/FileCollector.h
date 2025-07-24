#pragma once
#include <vector>
#include <string>

class FileCollector {
public:
    static std::vector<std::string> collectFilesRecursive(const std::string& rootDir);
};
