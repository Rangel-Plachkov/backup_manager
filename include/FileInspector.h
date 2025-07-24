#pragma once
#include <string>
#include <vector>

class FileInspector {
public:
    FileInspector(const std::vector<std::string>& files, std::string  snapshotDir);
    void run();

private:
    std::vector<std::string> _filePaths;
    std::string _snapshotDir;
};
