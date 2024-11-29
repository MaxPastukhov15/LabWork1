// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
#ifndef ROTATE_COUNTERCLOCKWISE_HPP
#define ROTATE_COUNTERCLOCKWISE_HPP

#include "bmp_utils.hpp"

void rotateCounterClockwise(BMPImage& image) {
    int width = image.getWidth();
    int height = image.getHeight();
    const auto& pixels = image.getPixels();

    std::vector<RGB> rotatedPixels(height * width);  

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            rotatedPixels[x * height + (height - y - 1)] = pixels[y * width + x];
        }
    }

    image.setPixels(rotatedPixels);
    image.setDimensions(height, width); 
}

#endif // ROTATE_COUNTERCLOCKWISE_HPP


