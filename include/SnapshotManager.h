#pragma once

#include <string>

class SnapshotManager {
public:
    explicit SnapshotManager(std::string  targetDir);
    void runBackup();

private:
    std::string _targetDir;
    std::string _snapshotDir;

    static std::string _generateSnapshotDir();
    inline static std::string SNAPSHOT_PATH = "../snapshots/snapshot_";
    static constexpr size_t BUFFER_SIZE = 32;
};
