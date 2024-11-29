// Maksim Pastukhov B82 mail: st131119@student.spbu.ru

#include "bmp_utils.hpp"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

bool BMPImage::read(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    if (fileHeader.bfType != 0x4D42) {
        std::cerr << "Not a BMP file!" << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    width = infoHeader.biWidth;
    height = abs(infoHeader.biHeight);

    if (fileHeader.bfOffBits < sizeof(fileHeader) + infoHeader.biSize) {
        std::cerr << "Invalid bfOffBits value!" << std::endl;
        return false;
    }

    file.seekg(fileHeader.bfOffBits, std::ios::beg);
    int rowPadding = (4 - (width * 3) % 4) % 4;

    pixels.resize(width * height);
    for (int y = 0; y < height; ++y) {
        file.read(reinterpret_cast<char*>(&pixels[y * width]), width * sizeof(RGB));
        file.ignore(rowPadding);
    }

    return true;
}

void BMPImage::save(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error creating output file!" << std::endl;
        return;
    }

    int rowPadding = (4 - (width * 3) % 4) % 4;
    infoHeader.biSizeImage = (width * 3 + rowPadding) * abs(height);
    fileHeader.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + infoHeader.biSizeImage;

    outFile.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    outFile.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    for (int y = 0; y < abs(height); ++y) {
        outFile.write(reinterpret_cast<char*>(&pixels[y * width]), width * sizeof(RGB));
        outFile.write("\0\0\0", rowPadding);
    }

    outFile.close();
}

