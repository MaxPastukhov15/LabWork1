// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
#ifndef BMP_UTILS_HPP
#define BMP_UTILS_HPP

#include <fstream>
#include <vector>
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

bool readBMP(std::ifstream& file, BMPFileHeader& fileHeader, BMPInfoHeader& infoHeader, std::vector<RGB>& pixels);

#endif

