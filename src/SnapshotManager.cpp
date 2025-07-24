#include "SnapshotManager.h"
#include "FileCollector.h"
#include "FileInspector.h"

#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <utility>

SnapshotManager::SnapshotManager(std::string  targetDir)
    : _targetDir(std::move(targetDir)) {}

std::string SnapshotManager::_generateSnapshotDir() {
    const std::time_t timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char buffer[BUFFER_SIZE];
    std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", std::localtime(&timeNow));

    return std::string(SNAPSHOT_PATH) + buffer;
}

void SnapshotManager::runBackup() {
    const std::vector<std::string> files = FileCollector::collectFilesRecursive(_targetDir);

    if (files.empty()) {
        std::cout << "No files found in: " << _targetDir << std::endl;
        return;
    }

    _snapshotDir = _generateSnapshotDir();
    std::filesystem::create_directories(_snapshotDir);

    FileInspector inspector(files, _snapshotDir);
    inspector.run();

    std::cout << "Backup completed into snapshot: " << _snapshotDir << '\n';
}
