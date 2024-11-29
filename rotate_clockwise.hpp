// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
#ifndef ROTATE_CLOCKWISE_HPP
#define ROTATE_CLOCKWISE_HPP

#include "bmp_utils.hpp"

void rotateClockwise(BMPImage& image) {
    
    int width = image.getWidth();
    int height = image.getHeight();
    const auto& pixels = image.getPixels();

    std::vector<RGB> rotatedPixels(height * width);  

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            rotatedPixels[(width - x - 1) * height + y] = pixels[y * width + x];
        }
    }

    image.setPixels(rotatedPixels);
    image.setDimensions(height, width);  

    // updating the header
    BMPInfoHeader& infoHeader = image.getInfoHeader();
    infoHeader.biWidth = height;
    infoHeader.biHeight = width;  
}


#endif // ROTATE_CLOCKWISE_HPP
