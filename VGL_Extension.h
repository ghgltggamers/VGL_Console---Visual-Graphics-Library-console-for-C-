#ifndef VGL_EXTENSIONS_H
#define VGL_EXTENSIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <stdexcept>

namespace VGL_Extensions {

    // Custom compression and decompression functions
    namespace Compression {

        // Simple compression algorithm (for demonstration purposes)
        std::vector<char> compress(const std::vector<char>& data) {
            std::vector<char> compressed;

            char current_char = data[0];
            int count = 1;
            for (size_t i = 1; i < data.size(); ++i) {
                if (data[i] == current_char) {
                    ++count;
                } else {
                    compressed.push_back(current_char);
                    compressed.push_back(static_cast<char>(count));
                    current_char = data[i];
                    count = 1;
                }
            }
            compressed.push_back(current_char);
            compressed.push_back(static_cast<char>(count));

            return compressed;
        }

        // Simple decompression algorithm (for demonstration purposes)
        std::vector<char> decompress(const std::vector<char>& compressed_data) {
            std::vector<char> decompressed;

            for (size_t i = 0; i < compressed_data.size(); i += 2) {
                char character = compressed_data[i];
                char count = compressed_data[i + 1];

                for (int j = 0; j < count; ++j) {
                    decompressed.push_back(character);
                }
            }

            return decompressed;
        }

    } // namespace Compression

    // File extension handling
    class FileExtensions {
    public:
        // Check if the file has .vglcomp extension
        static bool isVGLCompressed(const std::string& filename) {
            return filename.size() > 8 && filename.substr(filename.size() - 8) == ".vglcomp";
        }

        // Compress file and save as .vglcomp
        static void compressFile(const std::string& input_filename, const std::string& output_filename) {
            std::ifstream input_file(input_filename, std::ios::binary);
            if (!input_file.is_open()) {
                throw std::runtime_error("Failed to open input file.");
            }

            // Read file content into a vector<char>
            std::vector<char> file_content((std::istreambuf_iterator<char>(input_file)),
                                           std::istreambuf_iterator<char>());

            input_file.close();

            // Compress the file content
            std::vector<char> compressed_content = Compression::compress(file_content);

            // Write compressed content to .vglcomp file
            std::ofstream output_file(output_filename, std::ios::binary);
            if (!output_file.is_open()) {
                throw std::runtime_error("Failed to create output file.");
            }

            output_file.write(reinterpret_cast<const char*>(&compressed_content[0]), compressed_content.size());
            output_file.close();
        }

        // Decompress .vglcomp file
        static void decompressFile(const std::string& input_filename, const std::string& output_filename) {
            std::ifstream input_file(input_filename, std::ios::binary);
            if (!input_file.is_open()) {
                throw std::runtime_error("Failed to open input file.");
            }

            // Read file content into a vector<char>
            std::vector<char> file_content((std::istreambuf_iterator<char>(input_file)),
                                           std::istreambuf_iterator<char>());

            input_file.close();

            // Decompress the file content
            std::vector<char> decompressed_content = Compression::decompress(file_content);

            // Write decompressed content to output file
            std::ofstream output_file(output_filename, std::ios::binary);
            if (!output_file.is_open()) {
                throw std::runtime_error("Failed to create output file.");
            }

            output_file.write(reinterpret_cast<const char*>(&decompressed_content[0]), decompressed_content.size());
            output_file.close();
        }
    };

} // namespace VGL_Extensions

#endif // VGL_EXTENSIONS_H