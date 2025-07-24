#include "MetadataWriter.h"

#include <fstream>
#include <iostream>
#include <mutex>
#include <sys/file.h>
#include <unistd.h>
#include <filesystem>

bool MetadataWriter::writeEntry(const std::string& metadataFilePath,
                                const std::string& filePath,
                                const std::string& compressedPath,
                                const std::string& hash) {
    static std::mutex localMutex;
    std::lock_guard<std::mutex> lock(localMutex);

    std::filesystem::create_directories(std::filesystem::path(metadataFilePath).parent_path());

    const int fd = open(metadataFilePath.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        std::cerr << "Failed to open metadata file: " << metadataFilePath << "\n";
        return false;
    }

    if (flock(fd, LOCK_EX) < 0) {
        std::cerr << "Failed to acquire file lock.\n";
        close(fd);
        return false;
    }

    std::ofstream out(metadataFilePath, std::ios::app);
    if (!out) {
        std::cerr << "Failed to open output stream.\n";
        flock(fd, LOCK_UN);
        close(fd);
        return false;
    }

    out << _formatMetadata(filePath, compressedPath, hash);
    out.close();

    flock(fd, LOCK_UN);
    close(fd);
    return true;
}

std::string MetadataWriter::_formatMetadata(const std::string& filePath,
                                           const std::string& compressedPath,
                                           const std::string& hash) {
    std::string result;
    result += "File: " + std::filesystem::path(filePath).filename().string() + '\n';
    result += "Compressed: " + std::filesystem::path(compressedPath).filename().string() + '\n';

    try {
        const size_t size = std::filesystem::file_size(filePath);
        result += "Size: " + std::to_string(size) + " bytes\n";
    } catch (...) {
        result += "Size: UNKNOWN\n";
    }

    result += "Hash: " + hash + "\n";
    result += "-----------------------------\n";

    return result;
}
