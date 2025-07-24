#pragma once

#include <string>

class FileTask {
public:
    FileTask(const std::string& filePath, const std::string& snapshotDir);
    void run();

private:
    std::string _filePath;
    std::string _compressedPath;
    std::string _metadataFilePath;
    std::string _fileHash;

    void _compressFile() const;
    void _computeHash();
    void _writeMetadata() const;

    inline static std::string DEFAULT_HASH = "N/A";
    inline static std::string METADATA_FILE_NAME = "/backup_log.txt";
    inline static std::string COMPRESSED_FILE_EXTENSION = ".gz";
};
