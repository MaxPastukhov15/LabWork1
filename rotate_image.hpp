// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
#ifndef ROTATE_IMAGE_HPP
#define ROTATE_IMAGE_HPP

#include "bmp_utils.hpp"

enum class RotationDirection { Clockwise, CounterClockwise };

void rotateImage(BMPImage& image, RotationDirection direction) {
    int width = image.getWidth();
    int height = image.getHeight();
    std::vector<RGB> rotatedPixels(width * height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (direction == RotationDirection::Clockwise) {
                rotatedPixels[(width - x - 1) * height + y] = image.getPixel(x, y);
            } else {
                rotatedPixels[x * height + (height - y - 1)] = image.getPixel(x, y);
            }
        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            image.setPixel(x, y, rotatedPixels[y * width + x]);
        }
    }

    image.setDimensions(height, width);
}

#endif // ROTATE_IMAGE_HPP

