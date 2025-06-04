/**
 * @file bmp_utils.cpp
 * @author Maksim Pastukhov : st131119@student.spbu.ru
 * @brief BMPImage class methods implementation
 * 
 * Implements methods for:
 * - Reading BMP files (supports 24-bit uncompressed format)
 * - Saving BMP files
 * - Managing pixels and image headers
 * 
 * Implementation details:
 * - Automatic row padding handling
 * - File format validation
 * - Header updates when image dimensions change
 */

#include "bmp_utils.hpp"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

void BMPImage::updateHeaders() {
    infoHeader.biWidth = width;
    infoHeader.biHeight = height;
    infoHeader.biSizeImage = width * height * sizeof(RGB);
    fileHeader.bfSize = fileHeader.bfOffBits + infoHeader.biSizeImage;
}

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
        outFile.write("\0", rowPadding);
    }

    outFile.close();
}

RGB BMPImage::getPixel(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return pixels[y * width + x];
    }
    throw std::out_of_range("Pixel coordinates out of range");
}

void BMPImage::setPixel(int x, int y, const RGB& color) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        pixels[y * width + x] = color;
    } else {
        throw std::out_of_range("Pixel coordinates out of range");
    }
}

void BMPImage::setPixels(const std::vector<RGB>& newPixels) {
    if (newPixels.size() == pixels.size()) {
        pixels = newPixels;
    } else {
        throw std::invalid_argument("New pixel data size does not match current size");
    }
}

void BMPImage::setDimensions(int w, int h) {
    if (w > 0 && h > 0) {
        width = w;
        height = h;
        pixels.resize(width * height);
        updateHeaders();
    } else {
        throw std::invalid_argument("Width and height must be positive");
    }
}

