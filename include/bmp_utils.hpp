/**
 * @file bmp_utils.hpp
 * @author Maksim Pastukhov (st131119@student.spbu.ru)
 * @brief BMP structures and class definitions.
 */

#ifndef BMP_UTILS_HPP
#define BMP_UTILS_HPP

#include <vector>
#include <string>
#include <cstdint>

#pragma pack(push, 1)
/**
 * @struct BMPFileHeader
 * @brief BMP file header structure.
 */
struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};
/**
 * @struct BMPInfoHeader
 * @brief BMP info header structure.
 */
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
/**
 * @struct RGB
 * @brief RGB pixel structure.
 */
struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
/**
 * @class BMPImage
 * @brief Class for handling BMP image data and operations.
 */
class BMPImage {
private:
    BMPFileHeader fileHeader;  
    BMPInfoHeader infoHeader;  
    std::vector<RGB> pixels;  
    int width;  
    int height; 

    void updateHeaders();

public:
/**
 * @brief Reads a BMP image from a file.
 * 
 * @param filename The name of the BMP file to read.
 * @return true if the file was read successfully, false otherwise.
 */
    bool read(const std::string& filename);

/**
 * @brief Saves the BMP image to a file.
 * 
 * @param filename The name of the output BMP file.
 */
    void save(const std::string& filename);

/**
 * @brief Gets the RGB pixel at the specified coordinates.
 * 
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @return RGB The pixel value.
 * @throws std::out_of_range if coordinates are out of bounds.
 */
    RGB getPixel(int x, int y) const;
   /**
 * @brief Sets the RGB pixel at the specified coordinates.
 * 
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The new RGB pixel value.
 * @throws std::out_of_range if coordinates are out of bounds.
 */
    void setPixel(int x, int y, const RGB& color);

/**
 * @brief Sets all pixels in the image.
 * 
 * @param newPixels The new pixel data.
 * @throws std::invalid_argument if the new pixel data size doesn't match the current size.
 */
    void setPixels(const std::vector<RGB>& newPixels);
  /**
 * @brief Sets the dimensions of the image and resizes the pixel buffer.
 * 
 * @param w The new width.
 * @param h The new height.
 * @throws std::invalid_argument if width or height are not positive.
 */
    void setDimensions(int w, int h);
/**
*  @brief Methods for access to header
*/
    const BMPFileHeader& getFileHeader() const { return fileHeader; }
    const BMPInfoHeader& getInfoHeader() const { return infoHeader; }
};

#endif // BMP_UTILS_HPP

