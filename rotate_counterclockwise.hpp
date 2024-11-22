#ifndef ROTATE_COUNTERCLOCKWISE_HPP
#define ROTATE_COUNTERCLOCKWISE_HPP

#include <vector>
#include "bmp_utils.hpp"


std::vector<RGB> rotate90CounterClockwise(const std::vector<RGB>& data, int width, int height) {
    std::vector<RGB> rotated(height * width);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            rotated[x * height + (height - y - 1)] = data[y * width + x];
        }
    }

    return rotated;
}

#endif // ROTATE_COUNTERCLOCKWISE_HPP
