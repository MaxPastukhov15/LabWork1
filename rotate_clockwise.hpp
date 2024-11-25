// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
#ifndef ROTATE_CLOCKWISE_HPP
#define ROTATE_CLOCKWISE_HPP

#include <vector>
#include "bmp_utils.hpp"


std::vector<RGB> rotate90Clockwise(const std::vector<RGB>& data, int width, int height) {
    std::vector<RGB> rotated(height * width);

for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            rotated[(width - x - 1) * height + y] = data[y * width + x];
        }
    }

    return rotated;
}
#endif // ROTATE_CLOCKWISE_HPP
