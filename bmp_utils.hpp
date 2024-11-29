// Maksim Pastukhov B82 mail: st131119@student.spbu.ru

#ifndef BMP_UTILS_HPP
#define BMP_UTILS_HPP

#include <vector>
#include <string>

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

public:
    // reading picture from file
    bool read(const std::string& filename);

    // saving image in  file
    void save(const std::string& filename);

    // methods access to width and height
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void setWidth(int newWidth) { width = newWidth; }
    void setHeight(int newHeight) { height = newHeight; }

    // methods for working  with pixels
    std::vector<RGB>& getPixels() { return pixels; }
    const std::vector<RGB>& getPixels() const { return pixels; }
    void setPixels(const std::vector<RGB>& newPixels) { pixels = newPixels; }
    void setDimensions(int w, int h) { 
        width = w; 
        height = h; 
        infoHeader.biWidth = w; 
        infoHeader.biHeight = h; 
    }

    // methods for access to header
    BMPFileHeader& getFileHeader() { return fileHeader; }
    const BMPFileHeader& getFileHeader() const { return fileHeader; }
    BMPInfoHeader& getInfoHeader() { return infoHeader; }
    const BMPInfoHeader& getInfoHeader() const { return infoHeader; }
};



#endif

