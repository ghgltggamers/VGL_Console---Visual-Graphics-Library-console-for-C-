#include <iostream>
#include "VGL_Extensions.h"

using namespace VGL_Extensions;

int main() {
    std::string input_filename = "text.cxx";
    std::string compressed_filename = "example.vglcomp";
    std::string decompressed_filename = "example_decompressed.txt";

    try {
        // Compress file
        FileExtensions::compressFile(input_filename, compressed_filename);
        std::cout << "File compressed successfully.\n";

        // Decompress file
        FileExtensions::decompressFile(compressed_filename, decompressed_filename);
        std::cout << "File decompressed successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}