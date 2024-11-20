#include "bmp_utils.hpp"
#include <iostream>
#include <fstream>

bool readBMP(std::ifstream& file, BMPFileHeader& fileHeader, BMPInfoHeader& infoHeader, std::vector<RGB>& pixels) {
    // Read the BMP file header
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    if (fileHeader.bfType != 0x4D42) {  // 'BM'
        std::cerr << "Not a BMP file!" << std::endl;
        return false;
    }

    // Print bfSize for debugging
    std::cout << "bfSize (File Size in Header): " << fileHeader.bfSize << " bytes\n";

    // Read the BMP info header
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    if (infoHeader.biBitCount != 24) {
        std::cerr << "Only 24-bit BMP files are supported!" << std::endl;
        return false;
    }

    // Verify bfOffBits
    if (fileHeader.bfOffBits < sizeof(fileHeader) + infoHeader.biSize) {
        std::cerr << "Invalid bfOffBits value!" << std::endl;
        return false;
    }

    // Seek to pixel data
    file.seekg(fileHeader.bfOffBits, std::ios::beg);
    if (file.fail()) {
        std::cerr << "Failed to seek to pixel data!" << std::endl;
        return false;
    }

    // Calculate padding
    int width = infoHeader.biWidth;
    int height = abs(infoHeader.biHeight);
    int rowPadding = (4 - (width * 3) % 4) % 4;

    // Resize pixel vector
    pixels.resize(width * height);

    // Read pixel data
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            RGB pixel;
            file.read(reinterpret_cast<char*>(&pixel), sizeof(RGB));
            if (file.eof()) {
                std::cerr << "Unexpected end of file while reading pixels!" << std::endl;
                return false;
            }
            pixels[y * width + x] = pixel;
        }
        file.ignore(rowPadding);  // Skip padding
    }

    return true;  // Successful read
}

