/**
 * @file bmp_utils.hpp
 * @author Maksim Pastukhov (st131119@student.spbu.ru)
 * @brief BMP structures and class definitions
 * 
 * Contains:
 * - BMPFileHeader and BMPInfoHeader structures
 * - RGB pixel structure
 * - BMPImage class with image manipulation methods
 * 
 * Features:
 * - 24-bit uncompressed BMP support
 * - pragma pack for proper BMP format alignment
 * - Safe pixel access methods
 */

#ifndef BMP_UTILS_HPP
#define BMP_UTILS_HPP

#include <vector>
#include <string>
#include <cstdint>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class BMPImage {
private:
    BMPFileHeader fileHeader;  // headerfile
    BMPInfoHeader infoHeader;  // infoheader
    std::vector<RGB> pixels;  // pixels of picture
    int width;  // width pictures
    int height; // height pictures

    void updateHeaders();

public:
    // reading picture from file
    bool read(const std::string& filename);

    // saving image in file
    void save(const std::string& filename);

    // methods access to width and height
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // methods for working with pixels
    RGB getPixel(int x, int y) const;
    void setPixel(int x, int y, const RGB& color);
    void setPixels(const std::vector<RGB>& newPixels);
    void setDimensions(int w, int h);

    // methods for access to header
    const BMPFileHeader& getFileHeader() const { return fileHeader; }
    const BMPInfoHeader& getInfoHeader() const { return infoHeader; }
};

#endif // BMP_UTILS_HPP

