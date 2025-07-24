#include "Hasher.h"
#include "picosha2.h" //https://github.com/okdshin/PicoSHA2

#include <fstream>
#include <vector>

std::string Hasher::computeSHA256(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return DEFAULT_HASH;

    std::vector<unsigned char> hash(picosha2::k_digest_size);
    picosha2::hash256(file, hash.begin(), hash.end());

    return picosha2::bytes_to_hex_string(hash.begin(), hash.end());
}
