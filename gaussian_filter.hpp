#ifndef GAUSSIAN_FILTER_HPP
#define GAUSSIAN_FILTER_HPP



#include <vector>
#include "bmp_utils.hpp"
#include <cmath>
#include <algorithm>

std::vector<RGB> applyGaussianFilter(const std::vector<RGB>& data, int width, int height) {
    std::vector<RGB> filteredData(data.size());

    // 5x5 Gaussian kernel
    float kernel[5][5] = {
        {1 / 273.0f, 4 / 273.0f, 7 / 273.0f, 4 / 273.0f, 1 / 273.0f},
        {4 / 273.0f, 16 / 273.0f, 26 / 273.0f, 16 / 273.0f, 4 / 273.0f},
        {7 / 273.0f, 26 / 273.0f, 41 / 273.0f, 26 / 273.0f, 7 / 273.0f},
        {4 / 273.0f, 16 / 273.0f, 26 / 273.0f, 16 / 273.0f, 4 / 273.0f},
        {1 / 273.0f, 4 / 273.0f, 7 / 273.0f, 4 / 273.0f, 1 / 273.0f}
    };

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float red = 0.0f;
            float green = 0.0f;
            float blue = 0.0f;

            // Apply the Gaussian kernel
            for (int ky = -2; ky <= 2; ++ky) {
                for (int kx = -2; kx <= 2; ++kx) {
                    int nx = std::clamp(x + kx, 0, width - 1);
                    int ny = std::clamp(y + ky, 0, height - 1);

                    float weight = kernel[ky + 2][kx + 2];
                    const RGB& neighbor = data[ny * width + nx];

                    red += neighbor.r * weight;
                    green += neighbor.g * weight;
                    blue += neighbor.b * weight;
                }
            }

            // Clamp and store the filtered values
            RGB& outputPixel = filteredData[y * width + x];
            outputPixel.r = static_cast<uint8_t>(std::clamp(red, 0.0f, 255.0f));
            outputPixel.g = static_cast<uint8_t>(std::clamp(green, 0.0f, 255.0f));
            outputPixel.b = static_cast<uint8_t>(std::clamp(blue, 0.0f, 255.0f));
        }
    }

    return filteredData;
}

#endif // GAUSSIAN_FILTER_HPP




