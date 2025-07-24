#include "FileTask.h"
#include "Compressor.h"
#include "MetadataWriter.h"
#include "Hasher.h"

#include <thread>
#include <filesystem>

FileTask::FileTask(const std::string& filePath, const std::string& snapshotDir)
    : _filePath(filePath) {
    const std::string fileName = std::filesystem::path(filePath).filename().string();
    _compressedPath = snapshotDir + "/" + fileName + COMPRESSED_FILE_EXTENSION;
    _metadataFilePath = snapshotDir + METADATA_FILE_NAME;
    _fileHash = DEFAULT_HASH;
}

void FileTask::run() {
    std::thread t1(&FileTask::_compressFile, this);
    std::thread t2(&FileTask::_computeHash, this);

    t1.join();
    t2.join();

    _writeMetadata();
}

void FileTask::_compressFile() const {
    std::filesystem::create_directories(std::filesystem::path(_compressedPath).parent_path());
    Compressor::compressToFile(_filePath, _compressedPath);
}

void FileTask::_computeHash() {
    _fileHash = Hasher::computeSHA256(_filePath);
}

void FileTask::_writeMetadata() const {
    MetadataWriter::writeEntry(_metadataFilePath, _filePath, _compressedPath, _fileHash);
}

