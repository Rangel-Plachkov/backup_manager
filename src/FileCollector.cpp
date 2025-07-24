#include "FileCollector.h"
#include <filesystem>
#include <iostream>

std::vector<std::string> FileCollector::collectFilesRecursive(const std::string& rootDir) {

    std::vector<std::string> collectedFiles;
    try {
        for (std::filesystem::recursive_directory_iterator it(rootDir), end; it != end; ++it) {
            if (std::filesystem::is_regular_file(*it)) {
                collectedFiles.push_back(it->path().string());
            }
        }
    } catch ( ... ) {
        std::cerr << "Error while scanning '" << rootDir << '\n';
    }

    return collectedFiles;
}
