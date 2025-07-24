#pragma once
#include <string>

class MetadataWriter {
public:
    static bool writeEntry(const std::string& metadataFilePath,
                            const std::string& filePath,
                            const std::string& compressedPath,
                            const std::string& hash);
private:
    static std::string _formatMetadata(const std::string& filePath,
                                        const std::string& compressedPath,
                                        const std::string& hash);
};
